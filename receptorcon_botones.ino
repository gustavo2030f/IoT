

#include <IRremote.h> // importa libreria IRremote
#include <LiquidCrystal_I2C.h> 
#include <Wire.h> 
#include <Keypad.h>
#define Pecho 8
#define Ptrig 9

LiquidCrystal_I2C lcd(0x27,20,4); // si no te sale con esta direccion  puedes usar (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2) 


const byte filas = 1;
const byte columnas = 4;
byte pinsFilas[filas] = {6};
byte pinsColumnas[columnas] = {5, 4, 3, 2};
int tecla = 0;
int menu_nivel = 0;
int valor = 0;
char opcion_seleccionada = ' ';
long duracion, distancia;  
boolean automatico = true;
int estadotv = 0;

char teclas[filas][columnas] = 
{
  {'1','2','3','4'},
};
Keypad teclado = Keypad(makeKeymap(teclas), pinsFilas, pinsColumnas, filas, columnas);

int SENSOREMI = 12;
int SENSOR = 11;        // sensor KY-022 a pin digital pi034 
void setup() {
  Serial.begin(9600);             // inicializa comunicacion serie a 9600 bps
 // IrReceiver.begin(SENSOR, DISABLE_LED_FEEDBACK);     // inicializa recepcion de datos
 IrSender.begin(SENSOREMI, DISABLE_LED_FEEDBACK);

  pinMode(Pecho, INPUT);     // define el pin 6 como entrada (echo)
  pinMode(Ptrig, OUTPUT);    // define el pin 7 como salida  (triger)

  lcd.init();//inicializa la pantalla
  lcd.backlight();//Enciende la luz de fondo
  
  lcd.setCursor(5, 0); //posicion 5 en x en la primer linea
  lcd.print("Modalidad");//
/*
  lcd.setCursor(7, 0); //posicion 5 en x en la primer linea
  lcd.print("Login");//

  lcd.setCursor(4,1);//posiciona el cursor x,y
  lcd.print("User: user1");//Imprime el msj

  lcd.setCursor(4,2);//posiciona el cursor x,y
  lcd.print("Pass: ");//Imprime el msj

  lcd.blink();//Enciende y apaga el cursor*/

  
} 

void loop() { 
 // if (IrReceiver.decode()) {          // si existen datos ya decodificados
 //   Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);  // imprime valor en hexadecimal en monitor
 //  IrReceiver.resume();              // resume la adquisicion de datos
 // }
 
  digitalWrite(Ptrig, LOW);
  delayMicroseconds(2);
  digitalWrite(Ptrig, HIGH);   // genera el pulso de triger por 10ms
  delayMicroseconds(10);
  digitalWrite(Ptrig, LOW);
  tecla = teclado.getKey();
  duracion = pulseIn(Pecho, HIGH);
  distancia = (duracion/2) / 29;            // calcula la distancia en centimetros


  if (distancia >= 500 || distancia <= 0){  // si la distancia es mayor a 500cm o menor a 0cm 
    Serial.println("---");      // no mide nada

  }
  else {
    Serial.print(distancia);           // envia el valor de la distancia por el puerto serial
    Serial.println("cm");              // le coloca a la distancia los centimetros "cm"
   
   
  } 

  


  switch (automatico) {
  case true:
    lcd.setCursor(5, 1);
    lcd.print("AUTOMATICO");//
    if (distancia <= 39 ){
          Serial.println(estadotv);
            if(estadotv == 0){
               lcd.setCursor(4, 3); //posicion 5 en x en la primer linea
               lcd.print("TV ENCENDIDA");//Imprime el msj
               delay (100);

              IrSender.sendSamsung(0x0707, 0xE6, 10);//apagar tvSamsung
              Serial.println("Encender TV");
              estadotv = 1; 
      }
   
    }
    
    if ( distancia >= 40 )  {  // si la distancia es mayor a 500cm o menor a 0cm 
     Serial.println(estadotv);
      if(estadotv == 1){
        
        lcd.setCursor(4,3);//posiciona el cursor x,y
        lcd.print("TV APAGADA     ");//Imprime el msj
         delay (100);  
        IrSender.sendSamsung(0x0707, 0x02, 0);//apagar tvSamsung
        Serial.println("APAGAR TV");
        estadotv = 0; 
      }
    
      
    }

    if(tecla == '2'){
       Serial.println("Desactivar Automatico");
       automatico = 0;
        lcd.clear(); 
        lcd.setCursor(5, 0); //posicion 5 en x en la primer linea
        lcd.print("Modalidad");//
      }
    break;
    
  case false:
        lcd.setCursor(5, 1); 
        lcd.print("MANUAL     ");//
   if(tecla == '3'){
      IrSender.sendSamsung(0x0707, 0xE6, 0);//apagar tvSamsung
        Serial.println("Encender TV");
        lcd.setCursor(4, 3); //posicion 5 en x en la primer linea
        lcd.print("TV ENCENDIDA");//Imprime el msj
        tecla = 0;
         delay (100);  
      }
      if(tecla == '4'){
     IrSender.sendSamsung(0x0707, 0x02, 0);//apagar tvSamsung
        Serial.println("APAGAR TV");
        tecla = 0;
         lcd.setCursor(4,3);//posiciona el cursor x,y
        lcd.print("TV APAGADA     ");//Imprime el msj
        delay (100);  
      }

     if(tecla == '2'){
        lcd.clear(); 
        lcd.setCursor(5, 0); //posicion 5 en x en la primer linea
        lcd.print("Modalidad");//
       Serial.println("Activar Automatico");
       automatico = 1;
      }
    break;
}

   
   /*tecla = teclado.getKey(); 
      if(tecla == '1'){
      IrSender.sendSamsung(0x0707, 0x07, 0);//SUBIR VOLUMEN tvSamsung
        Serial.println("SUBI EL VOLUMEN");
        Serial.println(tecla);
        tecla = 0;
      }

      if(tecla == '2'){
       IrSender.sendSamsung(0x0707, 0x0B, 0);//BAJAR VOLUMEN tvSamsung
         Serial.println("BAJE EL VOLUMEN");
        tecla = 0;
      }

      if(tecla == '3'){
      IrSender.sendSamsung(0x0707, 0xE6, 0);//apagar tvSamsung
        Serial.println("Encender TV");
        tecla = 0;
      }
      if(tecla == '4'){
     IrSender.sendSamsung(0x0707, 0x02, 0);//apagar tvSamsung
        Serial.println("APAGAR TV");
        tecla = 0;
      
      }*/
  delay (100);                  // breve demora de 100 ms.

}

//5FAB24D encedido CLIMA
//21DEB24D aoagado CLIMA

//19E60707 apagado Tv
//FD020707 Encendido tv
// F8070707 subir volumen
// F40B0707 bajar volumen

// estructuras datos: vector, array, tuple, pair 
// pair<T1,T2> = template class
#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <tuple>
#include <utility> // pair
//#include <math.h> // sqrt
#include <cmath> // hypot

#define INLINE inline __attribute__((always_inline))

using namespace std;

INLINE float square(float num) { return num * num; }

INLINE float hipo(float n1, float n2) { return sqrt(square(n1) + square(n2)); }

using Catetos = pair<float,float>; // sinonimo-tipo array<float,2>; tuple<float, float>; 
//using Catetos = tuple<float,float>; // sinonimo-tipo array<float,2>; tuple<float, float>; 
//using Catetos = array<float,2>; // sinonimo-tipo array<float,2>; tuple<float, float>; 
using  Triang = vector<Catetos>;

Triang cat = { {2.0F, 2.5F}, {5.0F, 5.5F}, {5.0F, 6.0F} }; // vector<pair<float, float>>

int LED_BUILTIN = 2;
int suma = 0;

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
  delay(1000);
 //for (auto [c1, c2] : cat) { // type inferencing + structured binding + for-collection
    for (auto par : cat) { // structured binding
       auto c1 = get<0>(par);
       auto c2 = get<1>(par);
        cout
            << fixed << setw(5) << setprecision(2)
            << "cateto#1: "   << c1 
            << ", cateto#2: " << c2 << ", hipotenusa: "
            //<< hipo(c1, c2) << endl;
            //<< hypot(c1, c2) << endl;
            << hypot(c1, c2) << endl;
            suma = hypot(c1, c2) + suma;
    }

cout << suma << endl;
    
}

void loop() {
  // put your main code here, to run repeatedly:
     if (suma >= 1){
        suma--;
        cout << suma << endl;
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200);
        digitalWrite(LED_BUILTIN, LOW);
        delay(200);
     }
     
     

}



    

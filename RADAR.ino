#include <Servo.h>
#include "Adafruit_VL53L0X.h"
#include <Wire.h>
#include <VL53L0X.h>
Servo servo1;
VL53L0X sensor;
//Quitar distancia del centro de giro del servo a la distancia de detección límite
int i=0, j=0 ,obj=0, cont=0 ,despl=0, maximo=0, maxi[50], minimo=0, mini[50], comenzar=0;
char objeto[]={'A','B','C','D','E','F'};
float coorX[70], coorY[70], X, Y;
float lectura=0;

void setup()
{
    Serial.begin(9600);
    Serial.println("PruebaSetup");
    Wire.begin();
    sensor.setTimeout(1500);
    sensor.init();
    sensor.startContinuous();
    servo1.attach(9);
    servo1.write(0);
    delay(1500); 
}

void loop()
{
    Serial.println("Buscando...");
    lectura=sensor.readRangeContinuousMillimeters();
    
    if (sensor.timeoutOccurred()) 
    { 
      Serial.print(" TIMEOUT"); 
    }
    j=0;
    despl=0;
    obj=0;
    
    for(i=0;despl<90;i++)
    {
    //Serial.println(despl);
    //Serial.print("Default: ");
   // Serial.println(lectura);
    despl=despl+10;
    servo1.write(despl);
    if(lectura<590-38) //Quitar distancia
    {
    //Serial.print("Detecta: ");
    //Serial.println(lectura);
    coorX[j]=lectura*cos(despl*PI/180);
    coorY[j]=lectura*sin(despl*PI/180);
    j++;
    comenzar=1;
    }
    if(lectura>580-38&&comenzar==1)
    {
    maximo=i-1;
    maxi[obj]=maximo;
    minimo=j-1;
    mini[obj]=minimo;
    obj++;
    comenzar=0;
    }
    // if(lectura>590)
    // {
    // Serial.println("Fuera de zona");
    // }
    delay(1000);
    }
    for(i=0;i<=obj;i++)
    {
    cont=maxi[obj]-mini[obj];
    for(j=mini[obj];j<=maxi[obj];j++)
    {
    X=X +coorX[j];
    Y=Y +coorY[j];
    }
    Serial.print("Objeto: ");
    Serial.println(objeto[i]);
    Serial.print("Ubicacion: (");
    Serial.print(X);
    Serial.print(",");
    Serial.print(Y);
    Serial.println(")");
    Serial.println();
    }
}

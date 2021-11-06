#include <Arduino.h>

//#include <Adafruit_MPU6050.h>
//#include <Adafruit_Sensor.h>
#include <Wire.h>

#define USE_SERIAL Serial

int Gx=0;      // valeur brute du gyroscope selon l'axe de roulis ( X ) récupérée grâce à la centrale MPU
int Gy=0;      // valeur brute du gyroscope selon l'axe de tangage ( Y ) récupérée grâce à la centrale MPU

float Ax=0;      // valeur brute de l'acceleration selon l'axe X récupérée grâce à la centrale MPU
float Ay=0;      // valeur brute de l'acceleration selon l'axe Y récupérée grâce à la centrale MPU
float Az=0;         // valeur brute de l'acceleration selon l'axe Z récupérée grâce à la centrale MPU

float Ax_init = 15.92;
float Ay_init = 0.01;
float Az_init = 15.05;

float Acceleration_deviation = 0.5;

bool engine_state = false;

void initMPUConnection() {
  if (!Wire.begin()) {
    while (1) {
      USE_SERIAL.println("Failed to find MPU9250 chip");
      delay(10);
    }
  }

  /////// Réglage de la sensibilité du gyroscope du MPU ///////
  Wire.beginTransmission(0x68); // début de la communication avec le MPU  
  Wire.write(0x1B); // On accède au registre permettant de configurer la sensibilité du gyroscope                    
  Wire.write(0x10); // On lui donne une sensibilité de +-1000 degrés/sec                    
  Wire.endTransmission(true); // fin de la transmission
  
  /////// Réglage de la sensibilité de l'accéléromètre ///////
  Wire.beginTransmission(0x68); // début de la communication avec le MPU 
  Wire.write(0x1C); // On accède au registre permettant de configurer la sensibilité de l'accéléromètre                     
  Wire.write(0x10); // on lui donne une sensiblité de +- 8g                    
  Wire.endTransmission(true); // fin de la transmission
}

void beginMPUCommunication() {
  //////////////////////////////////////////////////////////////////////
  Wire.beginTransmission(0x68); // on entame la communication avec le MPU 
  Wire.write(0x3B);               
  Wire.endTransmission(false);    
  Wire.requestFrom(0x68,6,true);  
}

void readAccelerationX() {
  /////////////////   on divise par 4096 (datasheet) pour obtenir une accélération en m.s^-2 /////////////////////////
  Ax=(Wire.read()<<8|Wire.read())/4096.0 ; //
}

void readAccelerationY() {
  /////////////////   on divise par 4096 (datasheet) pour obtenir une accélération en m.s^-2 /////////////////////////
  Ay=(Wire.read()<<8|Wire.read())/4096.0 ; //
}

void readAccelerationZ() {
  /////////////////   on divise par 4096 (datasheet) pour obtenir une accélération en m.s^-2 /////////////////////////
  Az=(Wire.read()<<8|Wire.read())/4096.0 ; //
}

void displayMPUAcceleration() {
  Serial.println("Accélération :");
  Serial.print("Axe x : ");
  Serial.println(Ax);
  Serial.print("Axe y : ");
  Serial.println(Ay);
  Serial.print("Axe z : ");
  Serial.println(Az);
  Serial.println("");
  Serial.println("");
}

void presentMPUAcceleration() {
  beginMPUCommunication();
  readAccelerationX();
  readAccelerationY();
  readAccelerationZ();
  displayMPUAcceleration();
}

bool checkMoveOnAxe(float acceleration, float acceleration_init, float acceleration_deviation) {
  if(acceleration < acceleration_init-acceleration_deviation || acceleration > acceleration_init+acceleration_deviation)
    return true;
  else 
    return false;
}

void defineEngineState() {
  if(checkMoveOnAxe(Ax, Ax_init, Acceleration_deviation)) {
    engine_state = true;
  }
  else if(checkMoveOnAxe(Ay, Ay_init, Acceleration_deviation)) {
    engine_state = true;
  }
  else if(checkMoveOnAxe(Az, Az_init, Acceleration_deviation)) {
    engine_state = true;
  }
  else {
    engine_state = false;
  }
}

void displayEngineState() {
  Serial.println("Etat de la machine");
  if(engine_state == true)
    Serial.println("HIGH");
  else 
    Serial.println("LOW");
}

void presentEngineState() {
  presentMPUAcceleration();
  defineEngineState();
  displayEngineState();
}


void setup() {

  USE_SERIAL.begin(9600);

  delay(5000);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  initMPUConnection();

}

void loop() {

 
  presentEngineState();
  

  delay(1000);
  
}

#include <Wire.h>
#include <FaBoProximity_VCNL4010.h>

FaBoProximity faboProximity;
int sensorValue;
int mappedValue;
int motorControl = 10;



void setup() {
  pinMode(motorControl, OUTPUT);
  Serial.begin(9600);
  Serial.println("RESET");
  Serial.println();

  faboProximity.begin();
}

void loop() {
  // proximityデータの出力
  if(faboProximity.checkProxReady()){
  sensorValue = faboProximity.readProx();
  Serial.print("Prox:");
  Serial.println(faboProximity.readProx());
  }

  mappedValue = map(sensorValue,2000,50000,0,255);
  Serial.println(mappedValue);

  if(mappedValue>4){
     // ramp up the motor speed
    for(int x = 0; x <= 255; x++){
      analogWrite(motorControl, x);
      delay(50);
    }
    // ramp down the motor speed
    for(int x = 255; x >= 0; x--){
      analogWrite(motorControl, x);
      delay(50);
    }   
  }

  // ambientデータの出力
  if(faboProximity.checkAmbiReady()){
  //Serial.print("Ambi:");
  //Serial.println(faboProximity.readAmbi());
  }
delay(1);        // delay in between reads for stability
}

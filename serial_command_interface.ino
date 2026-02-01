#include <Arduino.h>

struct SystemState {
  unsigned long startTime;
  int mode;
  bool debug;
};

SystemState sys;       
char cmdBuffer[32];        
uint8_t cmdIndex = 0;   
bool cmdReady = false;    

void setup() {
  Serial.begin(9600);
  sys.startTime = millis();
  Serial.println("Mini-OS ready. Type 'help'.");
}

void loop() {
  readSerial();            

  if (cmdReady) {           
    Serial.print("Command received: ");
    Serial.println(cmdBuffer);
    cmdIndex = 0;
    cmdReady = false;
  }
}

void readSerial(){
  while(Serial.available()){
    char c = Serial.read();
    if(c == '\n' || c == '\r'){
      cmdBuffer[cmdIndex] = '\0';
      cmdReady = true;
      return;
    }
    if (cmdIndex < sizeof(cmdBuffer) - 1) { 
      cmdBuffer[cmdIndex++] = c;
    }
  }
}

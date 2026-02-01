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
}

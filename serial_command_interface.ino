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
    processCommand(cmdBuffer);
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

void processCommand(const char* cmd){
  if(strcmp(cmd, "help")==0){
    Serial.println("Commands: help, uptime, status, reset");
  }  else if (strcmp(cmd, "uptime") == 0) {
    unsigned long now = millis();
    Serial.print("Uptime (ms): ");
    Serial.println(now - sys.startTime);
  } 
  else if (strcmp(cmd, "status") == 0) {
    Serial.println("System OK");
  } 
  else if (strcmp(cmd, "reset") == 0) {
    Serial.println("Resetting...");
    asm volatile ("jmp 0");  // reset software
  } 
  else {
    Serial.println("Unknown command");
  }
}

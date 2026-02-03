#include <Arduino.h>

#define CMD_BUFFER_SIZE 32

struct SystemState {
  unsigned long startTime;
  int mode;
  bool debug;
};

SystemState sys;

char cmdBuffer[CMD_BUFFER_SIZE];
uint8_t cmdIndex = 0;
bool cmdReady = false;

void readSerial();
void processCommand(const char* cmd);
void cmdHelp();
void cmdUptime();
void cmdStatus();
void cmdReset();

void setup() {
  Serial.begin(9600);
  sys.startTime = millis();
  sys.mode = 0;
  sys.debug = false;

  Serial.println("Arduino Serial Shell ready.");
  Serial.println("Type 'help' for commands.");
  Serial.print("> ");
}

void loop() {
  readSerial();

  if (cmdReady) {
    processCommand(cmdBuffer);
    cmdIndex = 0;
    cmdReady = false;
    Serial.print("> ");
  }
}


void readSerial() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n' || c == '\r') {
      if (cmdIndex == 0) return;   
      cmdBuffer[cmdIndex] = '\0';
      cmdReady = true;
      return;
    }

    // adaugă caracter dacă e loc
    if (cmdIndex < CMD_BUFFER_SIZE - 1) {
      cmdBuffer[cmdIndex++] = c;
    }
  }
}

void processCommand(const char* cmd) {
  if (strcmp(cmd, "help") == 0) {
    cmdHelp();
  }
  else if (strcmp(cmd, "uptime") == 0) {
    cmdUptime();
  }
  else if (strcmp(cmd, "status") == 0) {
    cmdStatus();
  }
  else if (strcmp(cmd, "reset") == 0) {
    cmdReset();
  }
  else {
    Serial.println("Unknown command");
  }
}

void cmdHelp() {
  Serial.println("Available commands:");
  Serial.println("  help   - show this message");
  Serial.println("  uptime - system uptime (ms)");
  Serial.println("  status - system status");
  Serial.println("  reset  - software reset");
}

void cmdUptime() {
  unsigned long now = millis();
  Serial.print("Uptime (ms): ");
  Serial.println(now - sys.startTime);
}

void cmdStatus() {
  Serial.println("System OK");
}

void cmdReset() {
  Serial.println("Resetting...");
  delay(10);                 
  asm volatile ("jmp 0");
}

#include <SoftwareSerial.h>

SoftwareSerial nv10Serial(10, 11);  // RX, TX

byte SSP_CMD_RESET[] = {0x7F};
byte SSP_CMD_SYNC[] = {0x11, 0x05, 0x50, 0x01};
byte SSP_CMD_ENABLE[] = {0x0E, 0x05, 0x50, 0x01};

void setup() {
  Serial.begin(9600);
  nv10Serial.begin(9600);

  sendCommand(SSP_CMD_RESET, sizeof(SSP_CMD_RESET));
  delay(1000);
  sendCommand(SSP_CMD_SYNC, sizeof(SSP_CMD_SYNC));
  delay(1000);
  sendCommand(SSP_CMD_ENABLE, sizeof(SSP_CMD_ENABLE));
}

void loop() {
  // Zde můžete kontrolovat příchozí data z NV10
  if (nv10Serial.available()) {
    char inByte = nv10Serial.read();
    Serial.print(inByte, HEX);  // Vypište data v HEX formátu
  }
}

void sendCommand(byte cmd[], byte length) {
  for (byte i = 0; i < length; i++) {
    nv10Serial.write(cmd[i]);
  }
}

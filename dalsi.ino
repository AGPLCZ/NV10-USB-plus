#include <SoftwareSerial.h>

SoftwareSerial NoteAcceptor(10, 11); // RX, TX
//  NV10 PIN 1 (RS232) Tx <-> Arduino Serial3 Rx 10
//  NV10 PIN 5 (RS232) Rx <-> Arduino Serial3 Tx 11
// NV10 PIN 1  -> Tx 10 Arduino
// NV10 PIN 5 -> Rx 11 Arduino 


const byte enableAcceptor = 0x3E;
const byte enableSerialEscrow = 0x3A;
const byte verifyAcceptor = 0x3D;

byte channelValues[] = {5, 10, 20};
byte noteInEscrow = 0;
int credit = 0;

void setup() {
  Serial.begin(9600);
  NoteAcceptor.begin(9600);

  pinMode(10, INPUT);
  pinMode(11, OUTPUT);

  NoteAcceptor.write(enableAcceptor);
  NoteAcceptor.write(enableSerialEscrow);
  NoteAcceptor.write(verifyAcceptor);
  
}

void loop() {
  Serial.println(Serial.read());

  if (NoteAcceptor.available()) {
    Serial.println("Zahajuji komunikaci");
    byte byteIn = NoteAcceptor.read();
    Serial.print("**IN-");
    Serial.print(byteIn);
    Serial.println("**");

    if (byteIn >= 1 && byteIn <= 3){
      if (noteInEscrow){
        Serial.println("Escrow accepted");
        credit = credit + channelValues[byteIn - 1];
        Serial.print("Credit: €");
        Serial.println(credit);
        noteInEscrow = 0;
      } else {
        Serial.print("€");
        Serial.print(channelValues[byteIn - 1]);
        Serial.println(" in escrow");
        Serial.println("Accept 'Y' or 'N'");
        noteInEscrow = byteIn;
      }
    }
    if (byteIn == 70){
       Serial.println("Abort from escrow");
       noteInEscrow = 0;
    }
  }

  if (Serial.available()){
    byte byteIn = Serial.read();
    if (byteIn == 'Y'){
      NoteAcceptor.write(172);
      Serial.println("Accept");
    }
    if (byteIn == 'N'){
      NoteAcceptor.write(173);
      Serial.println("Decline");
    }
    if (byteIn == 'R'){
      credit = 0;
      Serial.println("Credit reset.");
    }
    if (byteIn == 'E'){
      NoteAcceptor.write(184);
      Serial.println("Acceptor enabled");
    }
    if (byteIn == 'D'){
      NoteAcceptor.write(185);
      Serial.println("Acceptor Disabled");
    }
    if (byteIn == 'M'){
      NoteAcceptor.write(170);
      Serial.println("Enable serial escrow mode");
    }
    if (byteIn == 'S'){
      NoteAcceptor.write(182);
      Serial.println("Status");
    }
  }
}

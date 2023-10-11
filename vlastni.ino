#include <SoftwareSerial.h>

SoftwareSerial NoteAcceptor(10, 11); // RX, TX
//  NV10 PIN 1 (RS232) Tx <-> Arduino Serial3 Rx 10
//  NV10 PIN 5 (RS232) Rx <-> Arduino Serial3 Tx 11
// NV10 PIN 1  -> Tx 10 Arduino
// NV10 PIN 5 -> Rx 11 Arduino 


const byte enableAcceptor = 184;
const byte enableSerialEscrow = 170;
const byte verifyAcceptor = 191;

byte channelValues[] = {5, 10, 20};
byte noteInEscrow = 0;
int credit = 0;

void setup() {
  Serial.begin(9600);
  NoteAcceptor.begin(300, SERIAL_8N2);


  pinMode(10, INPUT);
  pinMode(11, OUTPUT);

  NoteAcceptor.write(enableAcceptor);
  NoteAcceptor.write(enableSerialEscrow);
  NoteAcceptor.write(verifyAcceptor);

}

void loop() {
   
  if (NoteAcceptor.available()) {
  
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
    // Add here control commands based on your needs
        Serial.println("avalibe");
  }
}

#include <SoftwareSerial.h>

SoftwareSerial NoteAcceptor(10, 11);  // RX, TX

/* 
 *  control a NV10 Bank Note Validating System with a Arduino UNO R3
 *  NV10 PIN 1 (RS232) Tx <-> Arduino Digital Pin 10
 *  NV10 PIN 5 (RS232) Rx <-> Arduino Digital Pin 11
 *  Make sure both grounds (NV 10 PIN 16 <-> Arduino GND) are connected
 *  Documentation https://www.coinoperatorshop.com/media/products/NV10%20Manual%20Deutsch.pdf
 *  page 16 shows the messages which can be send and received
 */

byte noteInEscrow = 0;
int credit = 0;
byte channelValues[] = {5, 10, 20};

void setup() {
  Serial.begin(9600);
  NoteAcceptor.begin(300);  // SERIAL_8N2 je defaultní nastavení pro SoftwareSerial, nemusíte to specifikovat

  NoteAcceptor.write(184);
  NoteAcceptor.write(170);
  NoteAcceptor.write(191);
}

void loop() {
  if (NoteAcceptor.available()){
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
    // Ostatní část kódu zůstává stejná...
  }
}

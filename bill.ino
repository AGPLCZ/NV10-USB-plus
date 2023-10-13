#define NoteAcceptor Serial3

/* 
 *  control a NV10 Bank Note Validating System with a Arduino Mega 2560
 *  NV10 PIN 1 (RS232) Tx <-> Arduino Serial3 Rx 15
 *  NV10 PIN 5 (RS232) Rx <-> Arduino Serial3 Tx 14
 *  Make sure both grounds (NV 10 PIN 16 <-> Arduino GND) are connected
 *  Documentation https://www.coinoperatorshop.com/media/products/NV10%20Manual%20Deutsch.pdf
 *  page 16 shows the messages which can be send and received
 */

byte noteInEscrow = 0;

int credit = 0;
int prijmout = 3;
int max = 2700;
byte channelValues[] = { 100, 200, 500, 1000 };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  NoteAcceptor.begin(300, SERIAL_8N2);

  pinMode(15, INPUT_PULLUP);

  NoteAcceptor.write(184);
  NoteAcceptor.write(170);
  NoteAcceptor.write(191);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (NoteAcceptor.available()) {
    byte byteIn = NoteAcceptor.read();
    Serial.print("**IN-");
    Serial.print(byteIn);
    Serial.println("**");

    if (byteIn >= 1 && byteIn <= 5) {
      if (noteInEscrow) {
        Serial.println(byteIn);
        Serial.print("Přijato: ");
        Serial.print((channelValues[byteIn - 1]));
        Serial.println(" Kč");


        credit = credit + byteIn;

        Serial.print("Celkem přijato: ");
        Serial.print(credit);
        Serial.println(" Kč");
        noteInEscrow = 0;
      } else {
        Serial.println(byteIn);
        Serial.print((channelValues[byteIn - 1]));
        Serial.print(" Kč");
        Serial.println(" uvnitř");
        Serial.println("Přijmout? 'Y' or 'N'");
        prijmout = 1;
        noteInEscrow = byteIn;
      }
    }
    if (byteIn == 70) {
      Serial.println("Abort from escrow");
      noteInEscrow = 0;
    }
  }


  if (prijmout == 1) {
    if (credit < max) {

      NoteAcceptor.write(172);
      Serial.println("Vzito");
      Serial.print("Celkem přijato: ");
      Serial.println(credit);
      Serial.println(" Kč");
      prijmout = 3;
    }


    if (credit >= max) {

      NoteAcceptor.write(173);
      Serial.println("Vráceno");
      Serial.print("Celkem přijato: ");
      Serial.println(credit);
      Serial.println(" Kč");
      prijmout = 3;
    }
  }






  if (Serial.available()) {
    byte byteIn = Serial.read();
    if (byteIn == 'Y') {
      NoteAcceptor.write(172);
      Serial.println("Accept");
    }
    if (byteIn == 'N') {
      NoteAcceptor.write(173);
      Serial.println("Decline");
    }
    if (byteIn == 'R') {
      credit = 0;
      Serial.println("Credit reset.");
    }
    if (byteIn == 'E') {
      NoteAcceptor.write(184);
      Serial.println("Acceptor enabled");
    }
    if (byteIn == 'D') {
      NoteAcceptor.write(185);
      Serial.println("Acceptor Disabled");
    }
    if (byteIn == 'M') {
      NoteAcceptor.write(170);
      Serial.println("Enable serial escrow mode");
    }
    if (byteIn == 'S') {
      NoteAcceptor.write(182);
      Serial.println("Status");
    }
  }
}

#define NoteAcceptor Serial3

/* 
 *  control a NV10 Bank Note Validating System with a Arduino Mega 2560
 *  NV10 PIN 1 (RS232) Tx <-> Arduino Serial3 Rx 15
 *  NV10 PIN 5 (RS232) Rx <-> Arduino Serial3 Tx 14
 *  Make sure both grounds (NV 10 PIN 16 <-> Arduino GND) are connected
 *  Documentation https://www.coinoperatorshop.com/media/products/NV10%20Manual%20Deutsch.pdf
 *  page 16 shows the messages which can be send and received
 */

int credit = 0;

int max = 400;
int accepted = 0;


void take() {

  if (credit < max) {
    NoteAcceptor.write(172);  // Přijmout
  }
  if (credit >= max) {
    NoteAcceptor.write(173);  // Vrátit
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  NoteAcceptor.begin(300, SERIAL_8N2);

  pinMode(15, INPUT_PULLUP);

  NoteAcceptor.write(184);  //Acceptor enabled
  //NoteAcceptor.write(185); //Acceptor Disabled
  NoteAcceptor.write(170);  //Enable serial escrow mode
  NoteAcceptor.write(191);
  //NoteAcceptor.write(182); //Status
  //NoteAcceptor.write(173); //Decline
  delay(1000);
}

void loop() {

  if (NoteAcceptor.available()) {
    byte byteIn = NoteAcceptor.read();
    Serial.print("Výstup: ");
    Serial.println(byteIn);



    if (byteIn == 70) {
      Serial.println("Přerušena úschova");
    }


    if (byteIn == 1) {
      Serial.println("Přijato do akceptoru 100 Kč");
      take();
      if (accepted == 1) {
        credit = credit + 100;
        Serial.print("Celkem přijato: ");
        Serial.print(credit);
        Serial.println(" Kč");
      }
      if (accepted == 1) {
        accepted = 0;
      } else {
        accepted = 1;
      }
    }
    if (byteIn == 2) {
      Serial.println("Přijato do akceptoru 200 Kč");
      take();

      if (accepted == 1) {

        credit = credit + 200;
        Serial.print("Celkem přijato: ");
        Serial.print(credit);
        Serial.println(" Kč");
      }
      if (accepted == 1) {
        accepted = 0;
      } else {
        accepted = 1;
      }
    }
  }
}


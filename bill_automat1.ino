#define NoteAcceptor Serial3
#include <Keypad.h>
/* 
 * Acceptor NV10  - Arduino Mega 2560
 * NV10 PIN 1 (RS232) Tx <-> Arduino Serial3 Rx 15
 * NV10 PIN 5 (RS232) Rx <-> Arduino Serial3 Tx 14
 * NV10 Top tier of pins - TOP PIN 1 -> Rx 15 TOP PIN 3 -> Tx 14
 * NV10 PIN 15 (top) <-> Arduino Vin - 12 V   
 * NV10 PIN 16 (down) <-> Arduino GND)  
 * NoteAcceptor.write(184);  //Acceptor enabled
 * NoteAcceptor.write(185); //Acceptor Disabled
 * NoteAcceptor.write(170);  //Enable serial escrow mode
 * NoteAcceptor.write(191); // Enable escrow timeout
 * NoteAcceptor.write(182); //Status
 * NoteAcceptor.write(173); //Decline
 */

int credit = 0;  // // Váš kredit
int max = 700;
byte accepted = 0;
const int buttonPin10 = 10;  // číslo pinu, ke kterému je připojeno tlačítko

int buttonState10 = 0;      // proměnná pro aktuální stav tlačítka




// keypad
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


void bill(int banknoteValue) {
  take(banknoteValue);
  if (accepted == 1) {
    credit += banknoteValue;
    Serial.print("Celkem přijato: ");
    Serial.print(credit);
    Serial.println(" Kč");
    accepted = 0;
  } else {
    accepted = 1;
  }
}

void take(int banknoteValue) {
  if ((credit + banknoteValue) <= max) {
    NoteAcceptor.write(172);  // Přijmout
  } else {
    NoteAcceptor.write(173);  // Vrátit
  }
}

void press_ko() {
  buttonState10 = digitalRead(buttonPin10);  // čte stav tlačítka (HIGH = nepovoleno, LOW = stisknuto)

  if (buttonState10 == LOW) {
    Serial.println("Vrátit");
    credit = 0;  // vynuluje kredit
    delay(500);  // krátké zpoždění k odfiltrování vícenásobných stisků (odrážení tlačítka)
    Serial.print("Celkem přijato: ");
    Serial.print(credit);
    Serial.println(" Kč");
  }
}





  void setup() {
    pinMode(buttonPin10, INPUT_PULLUP);  // nastaví pin s tlačítkem jako vstupní s pull-up odporem



    Serial.begin(9600);
    NoteAcceptor.begin(300, SERIAL_8N2);
    pinMode(15, INPUT_PULLUP);

    NoteAcceptor.write(184);  //Acceptor enabled
    NoteAcceptor.write(170);  //Enable serial escrow mode
    NoteAcceptor.write(191);  // verifyAcceptor
    delay(1000);
  }

  void loop() {
    if (NoteAcceptor.available()) {
      byte byteIn = NoteAcceptor.read();
      Serial.print("Výstup: ");
      Serial.println(byteIn);

      if (byteIn == 70) {
        Serial.println("Přerušena úschova");
      } else if (byteIn == 1) {
        Serial.println("Přijato do akceptoru 100 Kč");
        bill(100);
      } else if (byteIn == 2) {
        Serial.println("Přijato do akceptoru 200 Kč");
        bill(200);
      } else if (byteIn == 3) {
        Serial.println("Přijato do akceptoru 300 Kč");
        bill(500);
      }
    }


  press_ko();


 char customKey = customKeypad.getKey();
  
  if (customKey == '#'){
   Serial.println("Vráceno");
    credit = 0;  // vynuluje kredit
    delay(500);  // krátké zpoždění k odfiltrování vícenásobných stisků (odrážení tlačítka)
    Serial.print("Celkem přijato: ");
    Serial.print(credit);
    Serial.println(" Kč");
  }


  }

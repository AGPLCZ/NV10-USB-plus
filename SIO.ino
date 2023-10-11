#include <Arduino.h>

// Nastavení sériového připojení
#define SERIAL_PORT Serial
#define SERIAL_BAUD 9600

// Funkce pro kontrolu chyb
void check_error(uint8_t data) {
  if (data != 0x01) {
    perror("Chyba: ");
  }
}

// Funkce pro zpracování odpovědi
String process_response(uint8_t data) {
  return "Bill accepted";
}

// Funkce pro odeslání příkazu
void send_command(uint8_t command) {
  SERIAL_PORT.write(command);
}

// Odešlete příkaz pro čtení stavu
void read_status() {
  // Odešlete příkaz
  send_command('r');

  // Zkontrolujte chybu
  uint8_t error = SERIAL_PORT.read();
  check_error(error);

  // Zpracujte odpověď
  String response = process_response(SERIAL_PORT.read());

  // Vytiskněte odpověď
  Serial.println(response);
}

void setup() {
  // Nastavte sériové připojení
  SERIAL_PORT.begin(SERIAL_BAUD);
}

void loop() {
  // Načtěte stav
  //read_status();

  Serial.println(SERIAL_PORT.read());
  
}

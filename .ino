C++
// ============================================================
//      IoT BASED CIRCUIT BREAKER USING ARDUINO UNO
// ============================================================

// ---------------- LIBRARIES ----------------
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SoftwareSerial.h>

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- ESP8266 ----------------
SoftwareSerial esp(2, 3);
// RX = 2
// TX = 3

// ---------------- RELAY ----------------
int relayPin = 8;

// ---------------- KEYPAD ----------------
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {4, 5, 6, 7};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ---------------- PASSWORD ----------------
String password = "1234";
String inputPassword = "";

// ============================================================
// SETUP
// ============================================================

void setup() {

  // Relay Pin
  pinMode(relayPin, OUTPUT);

  // Relay OFF Initially
  digitalWrite(relayPin, LOW);

  // Serial Communication
  Serial.begin(9600);
  esp.begin(9600);

  // LCD Start
  lcd.init();
  lcd.backlight();

  // ========================================================
  // PAGE 1 : NAME + NUMBER
  // ========================================================

  lcd.setCursor(0,0);
  lcd.print("Khushi Raikwar");

  lcd.setCursor(0,1);
  lcd.print("6269988206");

  delay(3000);
  lcd.clear();

  // ========================================================
  // PAGE 2 : GMAIL
  // ========================================================

  lcd.setCursor(0,0);
  lcd.print("kr7949693");

  lcd.setCursor(0,1);
  lcd.print("@gmail.com");

  delay(3000);
  lcd.clear();

  // ========================================================
  // PAGE 3 : COLLEGE NAME
  // ========================================================

  lcd.setCursor(0,0);
  lcd.print("Govt Poly");

  lcd.setCursor(0,1);
  lcd.print("College Satna");

  delay(3000);
  lcd.clear();

  // ========================================================
  // PAGE 4 : PROJECT TITLE
  // ========================================================

  lcd.setCursor(0,0);
  lcd.print("IoT Circuit");

  lcd.setCursor(0,1);
  lcd.print("Breaker System");

  delay(3000);
  lcd.clear();

  // ========================================================
  // PASSWORD PAGE
  // ========================================================

  lcd.setCursor(0,0);
  lcd.print("Enter Password");
}

// ============================================================
// LOOP
// ============================================================

void loop() {

  // Read Keypad Input
  char key = keypad.getKey();

  // If Key Pressed
  if (key) {

    // Show * on LCD
    lcd.setCursor(inputPassword.length(),1);
    lcd.print("*");

    // Store Password
    inputPassword += key;

    // ========================================================
    // CHECK PASSWORD
    // ========================================================

    if (inputPassword.length() == 4) {

      lcd.clear();

      // ====================================================
      // CORRECT PASSWORD
      // ====================================================

      if (inputPassword == password) {

        lcd.setCursor(0,0);
        lcd.print("Access Granted");

        // Relay ON
        digitalWrite(relayPin, HIGH);

        // Serial Monitor
        Serial.println("Breaker ON");

        // ESP8266 Message
        esp.println("Breaker ON");

        lcd.setCursor(0,1);
        lcd.print("Breaker ON");
      }

      // ====================================================
      // WRONG PASSWORD
      // ====================================================

      else {

        lcd.setCursor(0,0);
        lcd.print("Wrong Password");

        // Relay OFF
        digitalWrite(relayPin, LOW);

        // Serial Monitor
        Serial.println("Breaker OFF");

        // ESP8266 Message
        esp.println("Breaker OFF");

        lcd.setCursor(0,1);
        lcd.print("Breaker OFF");
      }

      // Wait
      delay(3000);

      // Clear LCD
      lcd.clear();

      // Again Ask Password
      lcd.setCursor(0,0);
      lcd.print("Enter Password");

      // Empty Password
      inputPassword = "";
    }
  }
}

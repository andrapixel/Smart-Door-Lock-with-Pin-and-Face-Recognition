#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const byte ROWS = 4;  //four rows
const byte COLS = 4;  //three columns
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A'},
  { '4', '5', '6', 'B'},
  { '7', '8', '9', 'C'},
  { '*', '0', '#', 'D'}
};
byte rowPins[ROWS] = { 9, 8, 7, 6 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 5, 4, 3, 2 };       //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

Servo servo;
int position = 0;

// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27,16,2);

String password = "1234";
String mypassword;

int greenLed = 12;
int redLed = 13;

int counter = 0;
int attempts = 0;
int max_attempts = 3;

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on

  // Print a message on both lines of the LCD.
  lcd.setCursor(1, 0);   //Set cursor to character 2 on line 0

  pinMode(redLed, OUTPUT);
  digitalWrite(redLed, LOW);

  pinMode(greenLed, OUTPUT);
  digitalWrite(greenLed, LOW);

  servo.attach(10);

  Serial.println("Enter password:");
  lcd.print("Enter Password:");
}

void loop() {

  keypadfunction();
}

void keypadfunction() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    counter = counter + 1;
    lcd.setCursor(counter, 1);
    lcd.print("*");
  }
  
  if (key == '1') {
    mypassword = mypassword + 1;
  }

  if (key == '2') {
    mypassword = mypassword + 2;
  }

  if (key == '3') {
    mypassword = mypassword + 3;
  }

  if (key == '4') {
    mypassword = mypassword + 4;
  }

  if (key == '5') {
    mypassword = mypassword + 5;
  }

  if (key == '6') {
    mypassword = mypassword + 6;
  }

  if (key == '7') {
    mypassword = mypassword + 7;
  }

  if (key == '8') {
    mypassword = mypassword + 8;
  }

  if (key == '9') {
    mypassword = mypassword + 9;
  }

  if (key == '0') {
    mypassword = mypassword + 0;
  }

  if (key == 'D') {

    Serial.println(mypassword);

    if (password == mypassword) {

      lcd.clear();
      lcd.print("Welcome to");
      lcd.setCursor(0, 1);
      lcd.print("our house :)");
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, LOW);

      servo.write(90);
      delay(3000);
      servo.write(-90);

      delay(5000);
      
      mypassword = "";
      counter = 0;


    } else {

      Serial.println("Wrong.");
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, LOW);
      attempts = attempts + 1;
      if (attempts >= max_attempts) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Locked out.");

        digitalWrite(redLed, HIGH);
        delay(5000);
        digitalWrite(redLed, LOW);
        attempts = 0;
      }
      mypassword = "";
      counter = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Wrong password.");
      delay(3000);

      lcd.setCursor(0, 1);
      lcd.print("Max attempts: 3");
      delay(3000);

      lcd.clear();
      lcd.print("Enter password:");
      lcd.setCursor(0, 1);
    }
  }
}
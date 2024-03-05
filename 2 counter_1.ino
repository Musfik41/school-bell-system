#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;

#define CLK_PIN  4
#define DT_PIN 5
#define BUTTON_PIN 3
#define BUZZER_PIN 13

int counter1 = 0; // Global variable for counter 1
int counter2 = 0; // Global variable for counter 2
int currentDTState;
int lastDTState = LOW;
bool encoderHandling = false; // Flag to indicate if encoder handling is in progress
bool switchCounter = false;   // Flag to indicate which counter to control

// Define min and max values for the counters
const int MIN_COUNTER = 0;
const int MAX_COUNTER = 10;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set the button pin as input with internal pull-up resistor
  pinMode(BUZZER_PIN, OUTPUT);       // Set the buzzer pin as output

  lcd.init();         // Initialize the LCD
  lcd.backlight();    // Turn on the backlight
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Press the button");
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Switch between counters when the button is pressed
    switchCounter = !switchCounter;
    delay(200);
  }

  if (!switchCounter) {
    // Control counter 1
    handleCounter(&counter1);
  } else {
    // Control counter 2
    handleCounter(&counter2);
  }
}

void handleCounter(int* pointer) {
  currentDTState = digitalRead(DT_PIN);
  if (currentDTState != lastDTState) {
    if (digitalRead(CLK_PIN) == currentDTState) {
      if (*pointer < MAX_COUNTER) {
        (*pointer)++;
      }
    } else {
      if (*pointer > MIN_COUNTER) {
        (*pointer)--;
      }
    }
    Serial.print("Counter 1: ");
    Serial.println(counter1);
    Serial.print("Counter 2: ");
    Serial.println(counter2);
  }
  lastDTState = currentDTState;
}


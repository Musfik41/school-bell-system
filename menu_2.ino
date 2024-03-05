#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;


#define CLK_PIN  4
#define DT_PIN 5
#define BUTTON_PIN 3
#define BUZZER_PIN 13
String Item_1 = "Back";
String Item_2 = "Set date & Time";
String Item_3 = "Time Table";

int counter = 0; // Global variable to store the counter value
int counter3 =0;
int currentDTState;
int lastDTState = LOW;
int prevCounter = 0;
int prevCounter3 = 0;
bool encoderHandling = false; // Flag to indicate if encoder handling is in progress

// Define min and max values for the counter
const int MIN_COUNTER = 0;
const int MAX_COUNTER = 2; 
const int MIN_COUNTER3 = 0;
const int MAX_COUNTER3 = 2;// Change this to your desired max value

void setup() {
    Serial.begin(9600);

    pinMode(BUTTON_PIN, INPUT_PULLUP); // Set the button pin as input with internal pull-up resistor
    pinMode(BUZZER_PIN, OUTPUT);       // Set the buzzer pin as output

    lcd.init();         // Initialize the LCD
    lcd.backlight();    // Turn on the backlight
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.print("Quicster PVT LTD");
    lcd.setCursor(0, 1);
    lcd.print("SBP v1.0.1");
    delay(2000);       // Clear the LCD screen
    lcd.setCursor(0, 0);
    lcd.print("Press the button");

      // SETUP RTC MODULE
  //   if (!rtc.begin()) {
  //   Serial.println("RTC module is NOT found");
  //   Serial.flush();
  //   while (true);
  // }
}

void loop() {
  
  // Serial.println("entering loop");
    // Serial.println(counter);

    if (digitalRead(BUTTON_PIN) == LOW) {
        // digitalWrite(BUZZER_PIN, HIGH);
        delay(200);
    }
    if(counter == 2 && digitalRead(BUTTON_PIN) == LOW){
        Serial.println("entering ifffffffffffffffffffffffffffffffffffffffff");

                                                                        // currentDTState = digitalRead(DT_PIN);
                                                                        if (currentDTState != lastDTState) {
                                                                            if (digitalRead(CLK_PIN) == currentDTState) {
                                                                                if (counter3 < MAX_COUNTER3) {
                                                                                    counter3++;
                                                                                }
                                                                            } else {
                                                                                if (counter3 > MIN_COUNTER3) {
                                                                                    counter3--;
                                                                                }
                                                                            }
                                                                            if (counter3 == 0) {
                                                                                set3_1();
                                                                            } else if (counter3 == 1) {
                                                                                set3_2();
                                                                            }
                                                                            else if (counter3 == 2) {
                                                                                set3_3();
                                                                            }
                                                                            prevCounter3 = counter3;
                                                                        }
                                                                        // lastDTState = currentDTState;
            Serial.println("exiting ifffffffffffffffffffffffffffffffffffffffff");

    }
    currentDTState = digitalRead(DT_PIN);
    if (currentDTState != lastDTState) {
        if (digitalRead(CLK_PIN) == currentDTState) {
            if (counter < MAX_COUNTER) {
                counter++;
            }
        } else {
            if (counter > MIN_COUNTER) {
                counter--;
            }
        }
        if (counter == 0) {
            handleCW();
        } else if (counter == 1) {
            handleACW();
        }
        else if (counter == 2) {
            handleACW1();
        }
        prevCounter = counter;
    }
    lastDTState = currentDTState;
    // encoderHandling = false; // Reset flag to indicate encoder handling is complete
  // displayDateTime();
  // delay(1000);  // Update every second
}

void handleCW() {
    lcd.clear();        // Clear the LCD screen
    lcd.setCursor(0, 0); // Set cursor to the first line
    lcd.print(">" + Item_1);
    lcd.setCursor(0, 1); // Set cursor to the second line
    lcd.print(" " + Item_2);
}

void handleACW() {
    lcd.clear();        // Clear the LCD screen
    lcd.setCursor(0, 0); // Set cursor to the first line
    lcd.print(" " + Item_1);
    lcd.setCursor(0, 1); // Set cursor to the second line
    lcd.print(">" + Item_2);
}
void handleACW1() {
    lcd.clear();       
    lcd.setCursor(0, 0); 
    lcd.print(" " + Item_2); //set date & time
    lcd.setCursor(0, 1);
    lcd.print(">" + Item_3); // TIme Table
}
void set3_1() {
    lcd.clear();       
    lcd.setCursor(0, 0); 
    lcd.print(" " + Item_2); //set date & time
    lcd.setCursor(0, 1);
    lcd.print(">" + Item_3); // TIme Table
}
void set3_2() {
    lcd.clear();       
    lcd.setCursor(0, 0); 
    lcd.print(" " + Item_1); //set date & time
    lcd.setCursor(0, 1);
    lcd.print(">" + Item_3); // TIme Table
}
void set3_3() {
    lcd.clear();       
    lcd.setCursor(0, 0); 
    lcd.print("sbesbeb"); //set date & time
    lcd.setCursor(0, 1);
    lcd.print(">" + Item_3); // TIme Table
}
void displayDateTime() {
  DateTime now = rtc.now();

  int year = now.year();
  int month = now.month();
  int day = now.day();
  int hour = now.hour();
  int minute = now.minute();
  int second = now.second();

  lcd.clear();
  lcd.setCursor(0, 0);  // start to print at the first row
  lcd.print("Date: ");
  lcd.print(year);
  lcd.print("/");
  if (month < 10) {
    lcd.print("0");
  }
  lcd.print(month);
  lcd.print("/");
  if (day < 10) {
    lcd.print("0");
  }
  lcd.print(day);

  lcd.setCursor(0, 1);  // start to print at the second row
  lcd.print("Time: ");
  if (hour < 10) {
    lcd.print("0");
  }
  lcd.print(hour);
  lcd.print(":");
  if (minute < 10) {
    lcd.print("0");
  }
  lcd.print(minute);
  lcd.print(":");
  if (second < 10) {
    lcd.print("0");
  }
  lcd.print(second);
}

/**************************************************************************************************
 ** Experiment # 6
 ** Using LCD1602 Display with I2C
 * for more tutorials and experiments please support by watching and subscribing on my channel
 * JR Electronics Technology
****************************************************************************************************/
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>          // library for LCD with I2C
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);     // Set the LCD address (0x27) and size of lcd (16 chars and 2 line display)
// Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 4;
 
// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
 
// Connections to Arduino
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
 
// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

char arr[6];
int currentIndex = 0;
char existingArr[6] = {'1', '1', '1', '1', '1', '1'}; // Example existing array
void clearExistingArr() {
  for (int i = 0; i < 6; i++) {
    arr[i] = '\0';
  }
}

 void addCharToArray(char c) {
    if (currentIndex < 6) {
        arr[currentIndex] = c;
        currentIndex++;
    }
}

bool compareArrays() {
    for (int i = 0; i < 6; i++) {
        if (arr[i] != existingArr[i]) {
            return false;
        }
    }
    return true;
}

void setup()
{
  Serial.begin(9600);
  lcd.init();         // initialize the LCD
  lcd.backlight();    // Turn on the blacklight
    lcd.clear();  
}

void loop()
{
  int i = -1;
  while (1)
  {
  lcd.setCursor (0, 0);             // Set the cursor to 1st line
  lcd.print("Enter The Pin");

  char customKey = customKeypad.getKey();
 
  if (customKey) {
    
    // Print key value to serial monitor                    // clear the LCD
  if (customKeypad.getState()==1)
  {
    i++;
    lcd.setCursor(i, 1);
    lcd.print(customKey);
    addCharToArray(customKey);
    if(i==5)
    {
      if (compareArrays())
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pin is correct");
        lcd.setCursor(0, 1);
        lcd.print("{flag10}${GOAL!}");
        delay(2000);
        lcd.clear();
        i = -1;
        currentIndex = 0;
        clearExistingArr();
      }
      else
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Deactivation");
        lcd.setCursor(0, 1);
        lcd.print("Failed!");
        delay(2000);
        lcd.clear();
        i = -1;
        currentIndex = 0;
        clearExistingArr();
      }
      
    }
  }
  }
  }
  
}


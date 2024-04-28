// include the library code:
#include <LiquidCrystal.h> //library for LCD 

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const int RedlED = 5;
const int GreenlED = 4;
const int DCmotor1 = 7;
const int DCmotor2 = 6;

bool isOpen = false;
int count = 0;
char c;
String id;

int wait = 5000;

void setup()
{
  Serial.begin(9600);
  pinMode(RedlED, OUTPUT);
  pinMode(GreenlED, OUTPUT);
  pinMode(DCmotor1, OUTPUT);
  pinMode(DCmotor2, OUTPUT);
  Serial.println("Please scan your RFID Card");

  lcd.begin(20, 4); // set up the LCD's number of columns and rows:
  lcd.setCursor(0, 0);
  lcd.print("  THE BRIGHT LIGHT ");
  lcd.setCursor(0, 1);
  lcd.print(" RFID BASED LOCK SYS");
  lcd.setCursor(0, 2);
  lcd.print(" CARD:   ");
  lcd.setCursor(0, 3);
  lcd.print(" NAME:   ");
}

void loop()
{
  while (Serial.available() > 0)
  {
    c = Serial.read();
    count++;
    id += c;
    if (count == 12)
    {
      Serial.print(id);
      //break;

      if (id == "E280689401A9")
      {
        Serial.println("Valid Card");
        lcd.setCursor(0, 2);
        lcd.print(" CARD: VALID   ");
        lcd.setCursor(0, 3);
        lcd.print(" NAME: ALTAF   ");
        digitalWrite(GreenlED, HIGH);

        //open the door
        digitalWrite(DCmotor1, HIGH);
        delay(100);
        digitalWrite(DCmotor1, LOW);
        isOpen = true;
        delay(4000);

        digitalWrite(GreenlED, LOW);
        lcd.setCursor(0, 2);
        lcd.print(" CARD:           ");
        lcd.setCursor(0, 3);
        lcd.print(" NAME:           ");

        // close the door
        digitalWrite(DCmotor2, HIGH);
        delay(100);
        digitalWrite(DCmotor2, LOW);
        isOpen = false;

      }

      else
      {
        if(isOpen == true){
          digitalWrite(DCmotor2, HIGH);
          delay(100);
          digitalWrite(DCmotor2, LOW);
        }
        Serial.println("Invalid Card");
        lcd.setCursor(0, 2);
        lcd.print(" CARD: INVALID   ");
        lcd.setCursor(0, 3);
        lcd.print(" NAME: UNKNOWN     ");
        digitalWrite(RedlED, HIGH);
        delay(4000);
        digitalWrite(RedlED, LOW);
        lcd.setCursor(0, 2);
        lcd.print(" CARD:           ");
        lcd.setCursor(0, 3);
        lcd.print(" NAME:           ");
      }
    }
  }
  count = 0;
  id = "";
  delay(500);
}

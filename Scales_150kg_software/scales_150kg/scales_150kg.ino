//------------------------------------------
//------Project started --------------------
//------- version 0.1 ----------------------
//--------2018-09-15------------------------
//==========================================
//-------- version 0.2 ---------------------
//---------2019-02-11-----------------------
//==========================================

#include <LiquidCrystal.h>
#include "BigNumbers.h"                    //modified BigNumbers library
#include <HX711_ADC.h>


#define SCALES_FACTOR -12500.0

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);     // initialize the interface pins [ LiquidCrystal(rs, enable, d4, d5, d6, d7)]

BigNumbers bigNum(&lcd);                   // construct BigNumbers object, passing to it the name of our LCD object

HX711_ADC LoadCell(14, 15);                //HX711 constructor (dout pin, sck pin)

const int button_1_Pin = 7;                // the pin number of the pushbutton 1 pin
const int button_2_Pin = 8;                // the pin number of the pushbutton 2 pin
const int LCD_LED_Pin = 9;                 // the pin number of the LCD LED pwm pin
//const int ledPin = 13;                     // the pin number of the LED pin
const int BuzzPin = 13;                    // the pin number of the buzzer

int ledState = HIGH;                       // the current state of the output pin

int button1State;                          // the current reading from the input pin
int button2State;                          // the current reading from the input pin
int lastButton1State = LOW;                // the previous reading from the input pin
int lastButton2State = LOW;                // the previous reading from the input pin
unsigned long lastDebounceTime1 = 0;       // the last time the output pin was toggled
unsigned long lastDebounceTime2 = 0;       // the last time the output pin was toggled
unsigned long debounceDelay = 50;          // the debounce time; increase if the output flickers


long time1, time2;

float weight = 0.0;
float showWeight = 0.0;
float netoWeight = 0.0;
float lastWeight = 0.0;
float tareWeight = 0.0;
float zeroWeight = 0.0;

//--------------------------- SETUP --------------------------------------------------------
void setup()
{
  
  pinMode(ledPin, OUTPUT);
  pinMode(LCD_LED_Pin, OUTPUT);
  pinMode(BuzzPin, OUTPUT);
  pinMode(button_1_Pin, INPUT_PULLUP);
  pinMode(button_2_Pin, INPUT_PULLUP);

  digitalWrite(ledPin, ledState);          // set initial LED state
  
  //TCCR1B = TCCR1B & 0b11111000 | 0x01;   // change the PWM frequency for Arduino Uno PWM pins
  //pinMode(LCD_LED_Pin,OUTPUT);
  //pinMode(10,OUTPUT);
  //analogWrite(LCD_LED_Pin,50);           // set LCD contrast with PWM - change this value if hard to read display
  //analogWrite(10,127);                   // set LCD backlight with PWM


  Serial.begin(9600);
  Serial.println("Wait...");  
 
  lcd.begin(20,2);                         // setup LCD rows and columns
  lcd.clear();                             // clear display
  lcd.setCursor(1, 0);                     // set the cursor to the top left  
  lcd.print("   SVARSTYKLES  ");
  lcd.setCursor(3, 1);                     // set the cursor
  lcd.print(" max  150 kg");
  

  LoadCell.begin();
  long stabilisingtime = 2000;             // tare preciscion can be improved by adding a few seconds of stabilising time
  LoadCell.start(stabilisingtime);
  LoadCell.setCalFactor(SCALES_FACTOR);    // user set calibration factor (float)
 // Serial.println("Startup + tare is complete");  
  LoadCell.update();
  
  lcd.clear();                             // clear display
  lcd.setCursor(1, 0);                     // set the cursor to the top left  
  lcd.print("  KALIBRAVIMAS  ");
  Serial.println("Kalibravimas..");

  LoadCell.tareNoDelay();
  delay(50);
  while (LoadCell.getTareStatus()!= true ) 
    {
      LoadCell.update();
      lcd.setCursor(3, 1);                 // set the cursor
      lcd.print("[          ]");
      lcd.setCursor(4, 1);                 // set the cursor to the top left 
      
      for(int j = 0; j < 11; j++)
        {
          LoadCell.update();
          delay(200);
          LoadCell.getData();
          lcd.print((char)255);
        }
               
    }
    
  lcd.clear();                             // clear display
  
  bigNum.begin();                          // set up BigNumbers

  Serial.println("OK...");
      
}  //setup


//++++++++++++++++++++++++++  LOOP  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void loop()
{

  LoadCell.update();                          //update() should be called at least as often as HX711 sample rate; >10Hz@10SPS   


  if (millis() > time1 + 250) {               //get smoothed value from data set + current calibration factor
    weight = LoadCell.getData();
    Serial.print("weight: ");
    Serial.print(weight);
   // showWeight = (weight - tareWeight) +0.003;
    print_weight_to_lcd();
    
    time1 = millis();

    Serial.print("  showWaight: ");
    Serial.print(showWeight);
        Serial.print("  zeroWeight: ");
    Serial.print(zeroWeight);
        Serial.print("  tareWeight: ");
    Serial.print(tareWeight);
        Serial.print("  lastWeight: ");
    Serial.println(lastWeight);
    
  }//if

  showWeight = (weight - tareWeight) +0.003;


///-------------------------------------------------------------------------------------------
   int reading1 = digitalRead(button_1_Pin);       // read the state of the switch into a local variable

   if (reading1 != lastButton1State) 
   {
    lastDebounceTime1 = millis();                  // reset the debouncing timer
   }  //if

   if ((millis() - lastDebounceTime1) > debounceDelay) 
    {
      if (reading1 != button1State)               // if the button state has changed:
      {
        button1State = reading1;
      
        if (button1State == LOW) 
        {
              ledState = !ledState;
              tareWeight = weight;      ///////////////////// do smth if button pressed ///////////////

              lastWeight = weight;
              lcd.setCursor(0, 0);
              lcd.print("        ");              
        }
      }
    }  //if

  lastButton1State = reading1;
  
///-------------------------------------------------------------------------------------------
   int reading2 = digitalRead(button_2_Pin);       // read the state of the switch into a local variable

   if (reading2 != lastButton2State) 
   {
    lastDebounceTime2 = millis();              // reset the debouncing timer
   }  //if

   if ((millis() - lastDebounceTime2) > debounceDelay) 
    {
      if (reading2 != button2State)             // if the button state has changed:
      {
        button2State = reading2;
      
        if (button2State == LOW) 
        {
              ledState = !ledState;
              // zeroWeight = weight-lastWeight + 0.005; ///////////////////// do smth if button pressed ///////////////
              lastWeight = weight;
              lcd.setCursor(0, 0);
              lcd.print("        ");
        }
      }
    }  //if   
     
 lastButton2State = reading2;  

///-----------------------------------------------------------------------------------
  
  //int currentTime = millis() / 100;           // assigns the current time since boot in tenths of a second to currentTime
  //byte lastDigit = currentTime % 10;
  //currentTime = currentTime /= 10;
  
  zeroWeight = (weight - lastWeight) + 0.003;
  
  lcd.setCursor(0, 0);
  lcd.print(zeroWeight,2);
  lcd.print(" ");

  lcd.setCursor(0, 1);
  lcd.print(weight,2);
  lcd.print(" ");
  
}  //loop



//*************************************************** FUNCTIONS ************************************************************************

void fade_out()
{
  
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5)   // fade in from min to max in increments of 5 points:
  {
    analogWrite(LCD_LED_Pin, fadeValue);                       // sets the value (range from 0 to 255):
    delay(30);                                                 // wait for 30 milliseconds to see the dimming effect
  } //for

}

//-----------------------------------------------------------------------------------------------------------------------------

void print_weight_to_lcd()
{
  
  int whole = showWeight;
  int reminder = (showWeight - whole)*100;
    Serial.print("  whole: ");
    Serial.print(whole);
    Serial.print("  reminder: ");
    Serial.print(reminder);

  whole = abs(whole);
  
if(whole < 10)
  {

    lcd.setCursor(8, 1);
    lcd.write("      ");
    lcd.setCursor(8, 0);
    lcd.write("      ");

    lcd.setCursor(12, 1);
    lcd.write((char)32);
    lcd.write((char)32); 

    bigNum.displayLargeInt(whole, 14, 1, false);    
  
    if(reminder < 0)
      {
        lcd.setCursor(12, 1);
        lcd.write((byte)1);
        lcd.write((byte)1);
    
       // lcd.setCursor(0, 1);  //////////NETO sign
       // lcd.write((byte)4);    
      }
 
  }  // if

      
if(whole >= 10 && whole <100)
 {
    lcd.setCursor(8, 1);
    lcd.write("   ");
    lcd.setCursor(8, 0);
    lcd.write("   ");

    lcd.setCursor(6, 1);
    lcd.write((char)32);
    lcd.write((char)32);        
    lcd.setCursor(10, 1);
    lcd.write((char)32);
    lcd.write((char)32);
    
    bigNum.displayLargeInt(whole, 11, 2, false);
  
    if(reminder < 0)
      {
        lcd.setCursor(9, 1);
        lcd.write((byte)1);
        lcd.write((byte)1);
      }

   }

   
 if(whole >= 100)
  {
    bigNum.displayLargeInt(whole, 8, 3, false);

    if(reminder < 0)
      {
        lcd.setCursor(6, 1);
        lcd.write((byte)1);
        lcd.write((byte)1);
      }
   }  

 reminder = abs(reminder);
  
  lcd.setCursor(17, 1);                       // print out the decimal point and the digit after it
  lcd.write('.');
  if(reminder < 10)
  {
    lcd.write('0');
    }
  lcd.print(reminder);
  lcd.write((char)32);
  
  }

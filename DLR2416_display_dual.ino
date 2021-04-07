//**************************************************************//
//  Name    : DLR2416 Display Driver                                
//  Author  : Wayne K Jones
//  Date    : 21 Oct 2014   
//  Modified: 21 Oct 2014                                
//  Version : 0.2.0                                            
//  Notes   : Code for using a 74HC595 Shift Register           
//          : to drive 2x Siemens DLR2416 intelligentdisplay                          
//**************************************************************//

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;
// Pin connected to "A0 digital select" on display
int digitSel0Pin = 5;
// Pin connected to "A1 digital select" on display 
int digitSel1Pin = 6;
// Pin connected to "WR Write" on display
int displayWritePin = 7;
// Pin connected to CS1 on left display
int displayLeftPin = 4;
// Pin connected to CS1 on right display
int displayRightPin = 3;

// AI for temp sensor
int tempSensPin = 0;

// Global Variables
int charToWrite;
int altCount = 0;

// Functions
void displayChar(char, int);
void displayWord(String);
void scrollWord(String);
void selectDisplay(int);

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(digitSel0Pin, OUTPUT);
  pinMode(digitSel1Pin, OUTPUT);
  pinMode(displayWritePin, OUTPUT); 
  pinMode(displayLeftPin, OUTPUT);
  pinMode(displayRightPin, OUTPUT);
  Serial.begin(9600);
}


void loop() {

  selectDisplay(0);
  displayWord(" Ter");
  selectDisplay(1);
  displayWord("esa ");
  delay(1000);
  
  selectDisplay(0);
  displayWord("  is");
  selectDisplay(1);
  displayWord(" a  ");
  delay(1000);

  selectDisplay(0);
  displayWord("  Fa");
  selectDisplay(1);
  displayWord("rt  ");
  delay(1000);
  
  selectDisplay(0);
  displayWord(" Mag");
  selectDisplay(1);
  displayWord("net ");
  delay(2000);

// function displayChar
void displayChar(char myChar, int myPos)
{
  switch (myPos)
  {
    case 3:
    digitalWrite(digitSel0Pin, LOW);
    digitalWrite(digitSel1Pin, LOW);
    break;
    case 2:
    digitalWrite(digitSel0Pin, HIGH);
    digitalWrite(digitSel1Pin, LOW);
    break;    
    case 1:
    digitalWrite(digitSel0Pin, LOW);
    digitalWrite(digitSel1Pin, HIGH);
    break;
    case 0:
    digitalWrite(digitSel0Pin, HIGH);
    digitalWrite(digitSel1Pin, HIGH);
    break;
  }
  // set shift register
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, myChar);
  digitalWrite(displayWritePin, LOW); delay(2);
  digitalWrite(latchPin, HIGH);
  digitalWrite(displayWritePin, HIGH); //delay(2);
}

void displayWord(String myString)
{
  for (int x = 0; x < 4; x++) {
    displayChar(myString.charAt(x),x);
  }
}

void scrollWord(String myString)
{
  int stringLength = myString.length(); //what is length of string?
  for (int x = 0; x<(stringLength -3); x++)
  {
    displayChar(myString.charAt(x),0); 
    displayChar(myString.charAt(x+1),1);
    displayChar(myString.charAt(x+2),2);
    displayChar(myString.charAt(x+3),3);
    delay(150);
  }
}

void selectDisplay(int myDisplay)
{
  if (myDisplay == 0) {
    digitalWrite(displayLeftPin, LOW);
    digitalWrite(displayRightPin, HIGH);
  } else {
    digitalWrite(displayLeftPin, HIGH);
    digitalWrite(displayRightPin, LOW);
  }
}

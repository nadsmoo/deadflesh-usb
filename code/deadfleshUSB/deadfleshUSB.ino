/*
Copyright 2024 Nadeem Rashid Backus aka Nadoom [nadeem.backus@gmail.com]

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "Keyboard.h"

const bool DEBUG_KEYPRESS =false;
const bool DEBUG_UNKNOWN_KEYS =false;
const bool DEBUG_MONITOR_LINES =true;
const long KEYBOARD_SCAN_DELAY = 40;

const int L1 = 2;
const int L2 = 3;
const int L3 = 4;
const int L4 = 5;
const int L5 = 6;

const int R1 = 7;
const int R2 = 8;
const int R3 = 9;
const int R4 = 15;
const int R5 = 14;
const int R6 = 16;
const int R7 = 18;
const int R8 = 10;
const int VCC = 0;

bool emptyL[5];
bool emptyR[9];

bool L[5];
bool R[9];

bool lastL[5];
bool lastR[9];


bool peekL[5];
bool peekR[9];



bool currentlyPressed = false;

void setup()
{
  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
  pinMode(L3, INPUT);
  pinMode(L4, INPUT);
  pinMode(L5, INPUT);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);

  memset(L, 0, sizeof(L));
  memset(R, 0, sizeof(R));

  memset(lastL, 1, sizeof(lastL));
  memset(lastR, 1, sizeof(lastR));

  Serial.begin(115200);
  Keyboard.begin();


}
  unsigned long startLoop =0l;
  unsigned long keyPressExpired =0l;

long keyboardScanDelay;

void loop()
{
  startLoop = millis();
  keyboardScanDelay = startLoop+ KEYBOARD_SCAN_DELAY;
  
  memset(R, 0, sizeof(R));
  memset(L, 0, sizeof(L));

  getKeyPress(false);
  int r = getInt(R, 9);
  int l = getInt(L, 5);
  int lR = getInt(lastR, 9);
  int lL = getInt(lastL, 5);

  if (isPressed())
  {
    bool isEscapeCharacter =false;
    char outputtedKey;
    bool keyUnknown= false;

    int r = getInt(R, 9);
    int l = getInt(L, 5);

    if ((r == 256) && (l ==  1)) { outputtedKey ='1'; }
    else if ((r == 256) && (l ==  2)) { outputtedKey ='2'; }
    else if ((r == 256) && (l ==  4)) { outputtedKey ='3'; }
    else if ((r == 256) && (l ==  8)) { outputtedKey ='4'; }
    else if ((r == 256) && (l == 16)) { outputtedKey ='5'; }
    else if ((r ==  32) && (l == 16)) { outputtedKey ='6'; }
    else if ((r ==  32) && (l ==  8)) { outputtedKey ='7'; }
    else if ((r ==  32) && (l ==  4)) { outputtedKey ='8'; }
    else if ((r ==  32) && (l ==  2)) { outputtedKey ='9'; }
    else if ((r ==  32) && (l ==  1)) { outputtedKey ='0'; }
    else if ((r == 128) && (l ==  1)) { outputtedKey ='q'; }
    else if ((r == 128) && (l ==  2)) { outputtedKey ='w'; }
    else if ((r == 128) && (l ==  4)) { outputtedKey ='e'; }
    else if ((r == 128) && (l ==  8)) { outputtedKey ='r'; }
    else if ((r == 128) && (l == 16)) { outputtedKey ='t'; }
    else if ((r ==  16) && (l == 16)) { outputtedKey ='y'; }
    else if ((r ==  16) && (l ==  8)) { outputtedKey ='u'; }
    else if ((r ==  16) && (l ==  4)) { outputtedKey ='i'; }
    else if ((r ==  16) && (l ==  2)) { outputtedKey ='o'; }
    else if ((r ==  16) && (l ==  1)) { outputtedKey ='p'; }
    else if ((r ==  64) && (l ==  1)) { outputtedKey ='a'; }
    else if ((r ==  64) && (l ==  2)) { outputtedKey ='s'; }
    else if ((r ==  64) && (l ==  4)) { outputtedKey ='d'; }
    else if ((r ==  64) && (l ==  8)) { outputtedKey ='f'; }
    else if ((r ==  64) && (l == 16)) { outputtedKey ='g'; }
    else if ((r ==   4) && (l == 16)) { outputtedKey ='h'; }
    else if ((r ==   4) && (l ==  8)) { outputtedKey ='j'; }
    else if ((r ==   4) && (l ==  4)) { outputtedKey ='k'; }
    else if ((r ==   4) && (l ==  2)) { outputtedKey ='l'; }
    else if ((r ==   8) && (l ==  2)) { outputtedKey ='z'; }
    else if ((r ==   8) && (l ==  4)) { outputtedKey ='x'; }
    else if ((r ==   8) && (l ==  8)) { outputtedKey ='c'; }
    else if ((r ==   8) && (l == 16)) { outputtedKey ='v'; }
    else if ((r ==   2) && (l == 16)) { outputtedKey ='b'; }
    else if ((r ==   2) && (l ==  8)) { outputtedKey ='n'; }
    else if ((r ==   2) && (l ==  4)) { outputtedKey ='m'; }
    else if ((r ==   2) && (l ==  1)) { outputtedKey =' '; }
    else if ((r == 136) && (l ==   1)) { outputtedKey ='Q'; } //010001000:00001 -     //caps
    else if ((r == 136) && (l ==   3)) { outputtedKey ='W'; } //010001000:00011 - 
    else if ((r == 136) && (l ==   5)) { outputtedKey ='E'; } //010001000:00101 - 
    else if ((r == 136) && (l ==   9)) { outputtedKey ='R'; } //010001000:01001 - 
    else if ((r == 136) && (l ==  17)) { outputtedKey ='T'; } //010001000:10001 - 
    else if ((r ==  24) && (l ==  17)) { outputtedKey ='Y'; } //000011000:10001 - 
    else if ((r ==  24) && (l ==   9)) { outputtedKey ='U'; } //000011000:01001 - 
    else if ((r ==  24) && (l ==   5)) { outputtedKey ='I'; } //000011000:00101 - 
    else if ((r ==  24) && (l ==   3)) { outputtedKey ='O'; } //000011000:00011 - 
    else if ((r ==  24) && (l ==   1)) { outputtedKey ='P'; } //000011000:00001 - 
    else if ((r ==  72) && (l ==   1)) { outputtedKey ='A'; } //001001000:00001 - 
    else if ((r ==  72) && (l ==   3)) { outputtedKey ='S'; } //001001000:00011 - 
    else if ((r ==  72) && (l ==   5)) { outputtedKey ='D'; } //001001000:00101 - 
    else if ((r ==  72) && (l ==   9)) { outputtedKey ='F'; } //001001000:01001 - 
    else if ((r ==  72) && (l ==  17)) { outputtedKey ='G'; } //001001000:10001 - 
    else if ((r ==  12) && (l ==  17)) { outputtedKey ='H'; } //000001100:10001 - 
    else if ((r ==  12) && (l ==   9)) { outputtedKey ='J'; } //000001100:01001 - 
    else if ((r ==  12) && (l ==   5)) { outputtedKey ='K'; } //000001100:00101 - 
    else if ((r ==  12) && (l ==   3)) { outputtedKey ='L'; } //000001100:00011 - 
    else if ((r ==   8) && (l ==   3)) { outputtedKey ='Z'; } //000001000:00011 - 
    else if ((r ==   8) && (l ==   5)) { outputtedKey ='X'; } //000001000:00101 - 
    else if ((r ==   8) && (l ==   9)) { outputtedKey ='C'; } //000001000:01001 - 
    else if ((r ==   8) && (l ==  17)) { outputtedKey ='V'; } //000001000:10001 - 
    else if ((r ==  10) && (l ==  17)) { outputtedKey ='B'; } //000001010:10001 - 
    else if ((r ==  10) && (l ==   9)) { outputtedKey ='N'; } //000001010:01001 - 
    else if ((r ==  10) && (l ==   5)) { outputtedKey ='M'; } //000001010:00101 - 
    else if ((r ==  10) && (l ==   1)) { outputtedKey =' '; } //000001010:00001 -  //punctuation   
    else if ((r ==   2) && (l ==   6)) { outputtedKey ='.'; } //000000010:00110 - 
    else if ((r ==  18) && (l ==   2)) { outputtedKey =';'; } //000010010:00010 - 
    else if ((r ==  18) && (l ==   3)) { outputtedKey ='"'; } //000010010:00011 - 
    else if ((r == 258) && (l ==   3)) { outputtedKey ='!'; } //100000010:00011 - // 1-0 punctionation (with symbolshift key)
    else if ((r == 258) && (l ==   2)) { outputtedKey ='@'; } //100000010:00010 - 
    else if ((r == 258) && (l ==   6)) { outputtedKey ='#'; } //100000010:00110 - 
    else if ((r == 258) && (l ==  10)) { outputtedKey ='$'; } //100000010:01010 - 
    else if ((r == 258) && (l ==  18)) { outputtedKey ='%'; } //100000010:10010 - 
    else if ((r ==  34) && (l ==  18)) { outputtedKey ='&'; } //000100010:10010 - 
    else if ((r ==  34) && (l ==  10)) { outputtedKey ='\'';} //000100010:01010 - 
    else if ((r ==  34) && (l ==   6)) { outputtedKey ='('; } //000100010:00110 - 
    else if ((r ==  34) && (l ==   2)) { outputtedKey =')'; } //000100010:00010 - 
    else if ((r ==  34) && (l ==   3)) { outputtedKey ='_'; } //000100010:00011 - 
    else if ((r ==  40) && (l ==   1)) { isEscapeCharacter =true; Keyboard.press(KEY_BACKSPACE);Keyboard.release(KEY_BACKSPACE); } //000101000:00001 - Delete
    else if ((r ==   4) && (l ==   1)) { isEscapeCharacter =true; Keyboard.press(KEY_RETURN); Keyboard.release(KEY_RETURN);} //000000100:00001 - Enter
    else if ((r == 264) && (l ==  17)) { isEscapeCharacter =true; Keyboard.press(KEY_LEFT_ARROW);Keyboard.release(KEY_LEFT_ARROW); } //100001000:10001 - 
    else if ((r ==  40) && (l ==   5)) { isEscapeCharacter =true; Keyboard.press(KEY_RIGHT_ARROW);Keyboard.release(KEY_RIGHT_ARROW); } //000101000:00101 - 
    else if ((r ==  40) && (l ==   9)) { isEscapeCharacter =true; Keyboard.press(KEY_UP_ARROW); Keyboard.release(KEY_UP_ARROW);} //000101000:01001 - 
    else if ((r ==  40) && (l ==  17)) { isEscapeCharacter =true; Keyboard.press(KEY_DOWN_ARROW);Keyboard.release(KEY_DOWN_ARROW); } //000101000:10001 - 
    else {
      keyUnknown =true;
     }

    if (!keyUnknown){
      
     if(!isEscapeCharacter){
      Keyboard.write(outputtedKey);
     
      if(DEBUG_KEYPRESS) {
        Serial.println((String) "Key:" + pad(getInt(R, 9)) + "." + pad(getInt(L, 5)) +" => " +outputtedKey);
        }
    
     }else{
     
      if(DEBUG_KEYPRESS) {
        Serial.println((String) "Key: non printing key press del etc.");
        }

     }
    }
    else{
        if(DEBUG_UNKNOWN_KEYS) {
          Serial.println((String) "if ((r == " + pad(getInt(R, 9)) + ") && (l == " + pad(getInt(L, 5)) + ")) { outputtedKey =' '; } //" + debugR() + ":" + debugL() + " - " +"");
          }
    }
   
    for (int i = 0; i < 5; i++) lastL[i] = L[i];
    for (int i = 0; i < 9; i++) lastR[i] = R[i];
  }


//spectrum scans every 20ms
while (millis()< keyboardScanDelay){
  delay(1);
}

}

String pad(int value)
{
  if (value < 10)
  {
    return "  " +  String(value);
  }
  else if (value < 100)
  {
    return " " + String(value);
  }
  else
  {
    return  String(value);
  }
}



bool isPressed()
{
   int r = getInt(R, 9);
   int l = getInt(L, 5);
   int lR = getInt(lastR, 9);
   int lL = getInt(lastL, 5);


   //not pressed if not pressed!
   if ((r == 0) && (l == 0)) { //000000000:00000 - not pressed
    keyPressExpired=0ul;
    memset(lastL, 1, sizeof(lastL));
    memset(lastR, 1, sizeof(lastR));

    return false;
   } 

   if(!keyboardModifierOverrides(r,l)){
     keyPressExpired=0ul;
     return false;     
   }

  if ((r == lR) && (l == lL)) { //same as last key           
   
   //set a timer if required
   if (keyPressExpired==0ul){
     keyPressExpired = startLoop +140ul;
   }

   //until timer has been reached, do not press key
    if (millis() < keyPressExpired) { 
      
    
      return false;
    }
    else{    
      keyPressExpired=0ul;
    }
  }
   return true;
}

bool setPressed(int rhs, bool doNotSet)
{

  memset(peekL, 0, sizeof(peekL));
  memset(peekR, 0, sizeof(peekR));

  bool keyPressed = false;

  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(R3, LOW);
  digitalWrite(R4, LOW);
  digitalWrite(R5, LOW);
  digitalWrite(R6, LOW);
  digitalWrite(R7, LOW);
  digitalWrite(R8, LOW);  
  
  
  //VCC is always high and isnt a real pin
  if (rhs!=VCC){
   digitalWrite(rhs, HIGH);
  }

  int rPosition = 0;

  switch (rhs)
  {
  case R1:
    rPosition = 1;
    break;
  case R2:
    rPosition = 2;
    break;
  case R3:
    rPosition = 3;
    break;
  case R4:
    rPosition = 4;
    break;
  case R5:
    rPosition = 5;
    break;
  case R6:
    rPosition = 6;
    break;
  case R7:
    rPosition = 7;
    break;
  case R8:
    rPosition = 8;
    break; 
  case VCC:
    rPosition = 0;
    break;
  default:
    return false; // impossible so no key press
    break;
  }
 
  if (digitalRead(L1) == HIGH)
  {
    if (!doNotSet)
    {
      L[0] = true;      
      R[rPosition] = true;
    }

    peekL[0] = true;
    peekR[rPosition] = true;
    keyPressed = true;
  }
  
   if (digitalRead(L2) == HIGH)
  {
    if (!doNotSet)
    {
      L[1] = true;
      R[rPosition] = true;
    }     
      peekL[1] = true;
      peekR[rPosition] = true;
    
    keyPressed = true;
  }
  
   if (digitalRead(L3) == HIGH)
  {
    if (!doNotSet)
    {
      L[2] = true;
      R[rPosition] = true;
    }    
      peekL[2] = true;
      peekR[rPosition] = true;
    
    keyPressed = true;
  }
  
   if (digitalRead(L4) == HIGH)
  {
    if (!doNotSet)
    {
      L[3] = true;
      R[rPosition] = true;
    }
      peekL[3] = true;
      peekR[rPosition] = true;
     
    keyPressed = true;
  }
  
   if (digitalRead(L5) == HIGH)
  {
    if (!doNotSet)
    {
      L[4] = true;
      R[rPosition] = true;
    }     
    peekL[4] = true;
    peekR[rPosition] = true;
    
    keyPressed = true;
  } 


  return keyPressed;
}

bool isSame(bool c1[], bool c2[])
{
  bool same = true;
  int i = 0;
  while (i < 6 && same)
  {
    same = c1[i] == c2[i];
    i++;
  }
  return same;
}

bool getKeyPress(bool doNotSet)
{
  bool pressed;
  pressed |= setPressed(R1, doNotSet);
  pressed |= setPressed(R2, doNotSet); 
  pressed |= setPressed(R3, doNotSet); 
  pressed |= setPressed(R4, doNotSet); 
  pressed |= setPressed(R5, doNotSet);
  pressed |= setPressed(R6, doNotSet);
  pressed |= setPressed(R7, doNotSet);
  pressed |= setPressed(R8, doNotSet);
//  pressed |= setPressed(VCC, doNotSet);

  

  if(DEBUG_MONITOR_LINES) Serial.println(debugR() + " " + debugL());

  int r = getInt(peekR, 9);
  int l = getInt(peekL, 5);
 

   //not pressed if not pressed!
   if ((r == 0) && (l == 0)) { //000000000:00000 - not pressed
    return false;
   } 


 if (!keyboardModifierOverrides(r,l)){
   return false;
 }

  return pressed;
}


bool keyboardModifierOverrides(int r, int l){

   //not pressed if caps shift key is pressed!
   if ((r == 8) && (l == 1)) { //000001000:00001 - caps shift key
    return false;
   } 

   //not pressed if symbol shift key is pressed!
   if ((r ==   2) && (l ==   2)) { //000000010:00010 - symbolshift
    return false;
}  

return true;
}

int getInt(bool array[], int length)
{
  int sum = 0;
  for (int i = 0; i < length; i++)
  {
    sum |= array[i] << i;
  }
  return sum;
}

String debugL()
{

String output="";
  if (L[4])
  {
   output+='1';
  }
  else
  {
    output+='0';
  }

  if (L[3])
  {
   output+='1';
  }
  else
  {
    output+='0';
  }
  if (L[2])
   {
   output+='1';
  }
  else
  {
    output+='0';
  }

  if (L[1])
  {
   output+='1';
  }
  else
  {
    output+='0';
  }
  if (L[0])
   {
   output+='1';
  }
  else
  {
    output+='0';
  }

  return output;
}

String debugR()
{
String output="";

  if (R[8])
  {
   output+='1';
  }
  else
  {
    output+='0';
  }

  if (R[7])
    {
   output+='1';
  }
  else
  {
    output+='0';
  }

  if (R[6])
  {
   output+='1';
  }
  else
  {
    output+='0';
  }

  if (R[5])
    {
   output+='1';
  }
  else
  {
    output+='0';
  }

  if (R[4])
  {
   output+='1';
  }
  else
  {
    output+='0';
  }

  if (R[3])
    {
   output+='1';
  }
  else
  {
    output+='0';
  }

  if (R[2])
   {
   output+='1';
  }
  else
  {
    output+='0';
  }

  if (R[1])
   {
   output+='1';
  }
  else
  {
    output+='0';
  }
  if (R[0])
   {
   output+='1';
  }
  else
  {
    output+='0';
  }

  return output;
}
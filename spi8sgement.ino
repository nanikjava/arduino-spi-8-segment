#include "LedControl.h"

// Arduino Pin 7 to DIN, 6 to Clk, 5 to LOAD, no.of devices is 1

LedControl lc = LedControl(7, 6, 5, 1);
unsigned long delaytime = 250;

String msg = "android lollipop and M";

int maxstr = 8;
int pos = 0;

void setup() {

  // Initialize the MAX7219 device
  lc.shutdown(0, false);

  // Enable display

  lc.setIntensity(0, 10);

  // Set brightness level (0 is min, 15 is max)
  lc.clearDisplay(0);

  // Clear display register

  Serial.begin(9600);
}

void scroll() {
  int strlength = msg.length();
  String toprint;
  int startpos = 7;

  if (pos > strlength) {
    pos = 0;
  }

  if ((pos + maxstr) > strlength) {
    toprint = msg.substring(pos);
  } else {
    toprint = msg.substring(pos, maxstr + pos);
  }


  char loopstr[toprint.length()];
  toprint.toCharArray(loopstr, toprint.length() + 1);

  for (int i = 0; i < sizeof(loopstr); i++) {

    if(  (loopstr[i]=='R') || (loopstr[i]=='r') ){
       lc.setRow(0,startpos,0x05);  
    } else if (  (loopstr[i]=='U') || (loopstr[i]=='u') ) {
       lc.setRow(0,startpos,0x1c);
    } else {
      lc.setChar(0, startpos, loopstr[i], false);
    }

    startpos--;
  }

  // remove any trailer
  if ((sizeof(loopstr) < maxstr)) {
    int looptoclear = maxstr - sizeof(loopstr);
    Serial.print("---- looptoclear ---" ); Serial.println(looptoclear);
    for (int i = 0; i < looptoclear; i++) {
      lc.setChar(0, i, ' ', false);
    }
  }

  delay(delaytime);


  pos++;
}

void loop() {
  scroll();
}

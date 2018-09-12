/*-------------------------------------------------------------------------------------
 * Template file for 4-pin I2C OLED display, e.g. from Geekcreit
 * using Adafruit SSD1306 driver and GFX libraries.
 * Tutorial:
 * https://startingelectronics.org/tutorials/arduino/modules/OLED-128x64-I2C-display/
 *-------------------------------------------------------------------------------------*/

#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Adafruit_SPITFT.h>
#include <Wire.h>

//Needed for OLED
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// OLED display TWI address
#define OLED_ADDR   0x3C

// reset pin not used on 4-pin OLED module
Adafruit_SSD1306 display(-1);  // -1 = no reset pin

// 128 x 64 pixel display
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  // Each char is 5 pixels wide

  textDisplay("This");
  delay(1000);
  textDisplay("is");
  delay(1000);
  textDisplay("how");
  delay(1000);
  textDisplay("you");
  delay(1000);
  textDisplay("call");
  delay(1000);
  textDisplay("this");
  delay(1000);
  textDisplay("function.");
  delay(1000);
  textDisplay(" ");
  delay(500);
  textDisplay(":)");
  delay(500);
  textDisplay("This is what happens with a string that contains multiple lines");
  delay(500);
  textDisplay("This is what happens with a string that is too long for the OLED screen to contain a b c d e f g h i j k l m n o p q r s t u v s w x y z 0 1 2 3 4 5 6 7 8 9 , . / ; ' # [ ] = - ? > < ~ @ : } { + _");
  delay(500);
  textDisplay("And this is what happens after the too long string has been displayed");
  delay(500);
  textDisplay("No of chars per line = 21");
  delay(2000);
  textDisplay("No of lines = 8");
  delay(2000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  textDisplay("No of chars per line = 21");
  delay(2000);
  textDisplay("No of lines = 8");
  delay(2000);
  textDisplay("I still work :D");
  delay(2000);
}


void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }    
  display.display();
  delay(1);
}

//*************** Fifo String Display***************//
// No. of lines = 8
// Max char per line = 21
void textDisplay(String msg) {
  static String OLEDstrings[8]= "";
  int len[8] = {0};
  int linecalc = 0;
  int startStr = 0;

//  flashes display when updated
//  display.display();
//  delay(1);
  
  if (msg == "") msg = " ";
  // fills fifo array with input strings
  if (OLEDstrings[7] == "") {      
    for (int line = 0; line<8; line++){
      if (OLEDstrings[line] == "") {
        OLEDstrings[line] = msg;
        len[line] = OLEDstrings[line].length(); // fills array with length of corresponding string
        break;
      }
    }
  }else{               
    for (int line=0; line<7; line++){ 
      OLEDstrings[line] = OLEDstrings[line+1];
      len[line] = OLEDstrings[line].length(); // fills array with length of corresponding string
    }
  OLEDstrings[7] = msg;
  len[7] = msg.length();
  }
  
  // works out which string in OLEDstrings to start displaying from
  for (int i=7; i>=0; i--){             // starting with the last input working up
    if (OLEDstrings[i] != ""){
      linecalc += (len[i]/21);          // sums number of lines until either...
      if(len[i]%21 != 0) linecalc++;
    }
    if(linecalc == 8) {                 // ...the right number of lines is hit (start with current string no)
      startStr = i;
      break;
    }else if(linecalc > 8){             // OR it goes over the number of lines (start with previous string no)
      if (i = 1) startStr = i;
      startStr = i+1;
      break;
    }
  }

  //Displays array
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  for (int line=startStr; line<8; line++){
    display.println(OLEDstrings[line]);
  }
  display.display();
  delay(1);
  display.clearDisplay();
}


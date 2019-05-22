// Based on the work by DFRobot

#include "LiquidCrystal_I2C_Hangul.h"
#include <inttypes.h>
#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#define printIIC(args)	Wire.write(args)
inline size_t LiquidCrystal_I2C_Hangul::write(uint8_t value) {
	send(value, Rs);
	return 1;
}

#else
#include "WProgram.h"

#define printIIC(args)	Wire.send(args)
inline void LiquidCrystal_I2C_Hangul::write(uint8_t value) {
	send(value, Rs);
}

#endif
#include "Wire.h"



// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set: 
//    DL = 1; 8-bit interface data 
//    N = 0; 1-line display 
//    F = 0; 5x8 dot character font 
// 3. Display on/off control: 
//    D = 0; Display off 
//    C = 0; Cursor off 
//    B = 0; Blinking off 
// 4. Entry mode set: 
//    I/D = 1; Increment by 1
//    S = 0; No shift 
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// LiquidCrystal constructor is called).

LiquidCrystal_I2C_Hangul::LiquidCrystal_I2C_Hangul(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows)
{
  _Addr = lcd_Addr;
  _cols = lcd_cols;
  _rows = lcd_rows;
  _backlightval = LCD_NOBACKLIGHT;
}

void LiquidCrystal_I2C_Hangul::init(){
	init_priv();
}

void LiquidCrystal_I2C_Hangul::init_priv()
{
	Wire.begin();
	_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
	begin(_cols, _rows);  
}

void LiquidCrystal_I2C_Hangul::begin(uint8_t cols, uint8_t lines, uint8_t dotsize) {
	if (lines > 1) {
		_displayfunction |= LCD_2LINE;
	}
	_numlines = lines;

	// for some 1 line displays you can select a 10 pixel high font
	if ((dotsize != 0) && (lines == 1)) {
		_displayfunction |= LCD_5x10DOTS;
	}

	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
	delay(50); 
  
	// Now we pull both RS and R/W low to begin commands
	expanderWrite(_backlightval);	// reset expanderand turn backlight off (Bit 8 =1)
	delay(1000);

  	//put the LCD into 4 bit mode
	// this is according to the hitachi HD44780 datasheet
	// figure 24, pg 46
	
	  // we start in 8bit mode, try to set 4 bit mode
   write4bits(0x03 << 4);
   delayMicroseconds(4500); // wait min 4.1ms
   
   // second try
   write4bits(0x03 << 4);
   delayMicroseconds(4500); // wait min 4.1ms
   
   // third go!
   write4bits(0x03 << 4); 
   delayMicroseconds(150);
   
   // finally, set to 4-bit interface
   write4bits(0x02 << 4); 


	// set # lines, font size, etc.
	command(LCD_FUNCTIONSET | _displayfunction);  
	
	// turn the display on with no cursor or blinking default
	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	display();
	
	// clear it off
	clear();
	
	// Initialize to default text direction (for roman languages)
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	
	// set the entry mode
	command(LCD_ENTRYMODESET | _displaymode);
	
	home();
  
}

/********** high level commands, for the user! */
void LiquidCrystal_I2C_Hangul::clear(){
	command(LCD_CLEARDISPLAY);// clear display, set cursor position to zero
	delayMicroseconds(2000);  // this command takes a long time!
}

void LiquidCrystal_I2C_Hangul::home(){
	command(LCD_RETURNHOME);  // set cursor position to zero
	delayMicroseconds(2000);  // this command takes a long time!
}

void LiquidCrystal_I2C_Hangul::setCursor(uint8_t col, uint8_t row){
	int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	if ( row > _numlines ) {
		row = _numlines-1;    // we count rows starting w/0
	}
	command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void LiquidCrystal_I2C_Hangul::noDisplay() {
	_displaycontrol &= ~LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_I2C_Hangul::display() {
	_displaycontrol |= LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void LiquidCrystal_I2C_Hangul::noCursor() {
	_displaycontrol &= ~LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_I2C_Hangul::cursor() {
	_displaycontrol |= LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void LiquidCrystal_I2C_Hangul::noBlink() {
	_displaycontrol &= ~LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_I2C_Hangul::blink() {
	_displaycontrol |= LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void LiquidCrystal_I2C_Hangul::scrollDisplayLeft(void) {
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void LiquidCrystal_I2C_Hangul::scrollDisplayRight(void) {
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void LiquidCrystal_I2C_Hangul::leftToRight(void) {
	_displaymode |= LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void LiquidCrystal_I2C_Hangul::rightToLeft(void) {
	_displaymode &= ~LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void LiquidCrystal_I2C_Hangul::autoscroll(void) {
	_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void LiquidCrystal_I2C_Hangul::noAutoscroll(void) {
	_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LiquidCrystal_I2C_Hangul::createChar(uint8_t location, uint8_t charmap[]) {
	location &= 0x7; // we only have 8 locations 0-7
	command(LCD_SETCGRAMADDR | (location << 3));
	for (int i=0; i<8; i++) {
		write(charmap[i]);
	}
}

// Turn the (optional) backlight off/on
void LiquidCrystal_I2C_Hangul::noBacklight(void) {
	_backlightval=LCD_NOBACKLIGHT;
	expanderWrite(0);
}

void LiquidCrystal_I2C_Hangul::backlight(void) {
	_backlightval=LCD_BACKLIGHT;
	expanderWrite(0);
}



/*********** mid level commands, for sending data/cmds */

inline void LiquidCrystal_I2C_Hangul::command(uint8_t value) {
	send(value, 0);
}


/************ low level data pushing commands **********/

// write either command or data
void LiquidCrystal_I2C_Hangul::send(uint8_t value, uint8_t mode) {
	uint8_t highnib=value&0xf0;
	uint8_t lownib=(value<<4)&0xf0;
       write4bits((highnib)|mode);
	write4bits((lownib)|mode); 
}

void LiquidCrystal_I2C_Hangul::write4bits(uint8_t value) {
	expanderWrite(value);
	pulseEnable(value);
}

void LiquidCrystal_I2C_Hangul::expanderWrite(uint8_t _data){                                        
	Wire.beginTransmission(_Addr);
	printIIC((int)(_data) | _backlightval);
	Wire.endTransmission();   
}

void LiquidCrystal_I2C_Hangul::pulseEnable(uint8_t _data){
	expanderWrite(_data | En);	// En high
	delayMicroseconds(1);		// enable pulse must be >450ns
	
	expanderWrite(_data & ~En);	// En low
	delayMicroseconds(50);		// commands need > 37us to settle
} 


// Alias functions

void LiquidCrystal_I2C_Hangul::cursor_on(){
	cursor();
}

void LiquidCrystal_I2C_Hangul::cursor_off(){
	noCursor();
}

void LiquidCrystal_I2C_Hangul::blink_on(){
	blink();
}

void LiquidCrystal_I2C_Hangul::blink_off(){
	noBlink();
}

void LiquidCrystal_I2C_Hangul::load_custom_character(uint8_t char_num, uint8_t *rows){
		createChar(char_num, rows);
}

void LiquidCrystal_I2C_Hangul::setBacklight(uint8_t new_val){
	if(new_val){
		backlight();		// turn backlight on
	}else{
		noBacklight();		// turn backlight off
	}
}

void LiquidCrystal_I2C_Hangul::printstr(const char c[]){
	//This function is not identical to the function used for "real" I2C displays
	//it's here so the user sketch doesn't have to be changed 
	print(c);
}

void LiquidCrystal_I2C_Hangul::setDelayTime(int t){
  delayTime = t;
}

int LiquidCrystal_I2C_Hangul::getchoAndJongIndex(char key){ //초성과 종성의 key로 배열 인덱스를 얻는다.
  for(int i=0; i<19; i++){
    if(key==choAndJongKey[i]){
      return i;
    }
  }
  return -1;
}
int LiquidCrystal_I2C_Hangul::getUFormIndex(char key){ //ㅡ형 모음의 key로 배열 인덱스를 얻는다.
  for(int i=0; i<5; i++){
    if(key==uFormKey[i]){
      return i;
    }
  }
  return -1;
}
int LiquidCrystal_I2C_Hangul::getYiFormIndex(char key){ //ㅣ형 모음의 key로 배열 인덱스를 얻는다.
  for(int i=0; i<9; i++){
    if(key==yiFormKey[i]){
      return i;
    }
  }
  return -1;
}

void LiquidCrystal_I2C_Hangul::mergeChoJung(byte* cho, byte* jung, byte* mergedArr){ //합칠 자음(초성), 중성 입력
  for(int i=0; i<8; i++){
    if(i<5){ //초성 범위
      mergedArr[i] = cho[i]; //초성을 저장
    }else if(i>=5){ //중성 범위
      mergedArr[i] = jung[i]; //중성을 저장
    }
  }
} 

//파싱 함수
void LiquidCrystal_I2C_Hangul::printHangul(String txt, byte startPoint)
{  
  char chArr[1000] = {0}; //문자들을 저장할 배열을 선언한다. (공백 포함 1천자)
  char temp[5] = {0}; //임시 저장 배열
  byte tempIndex = 0; //temp 배열 인덱스
  txt+=' ';
  txt.toCharArray(chArr, txt.length()); //매개인자를 chArr에 저장한다.
  int printPoint = startPoint;
  for(int i=0; i<1000; i++){
      if(chArr[i] == ' ' or chArr[i]=='\0'){ //해당 문자가 공백일 경우        
        switch(printing(temp[0],temp[1],temp[2],temp[3],temp[4],tempIndex,printPoint)){
          case 1:
            if(printPoint==15){
              printPoint = 0;
            }else{
              printPoint++;
            }
            break;
          case 2:
            if(printPoint>=14){
              printPoint = 0;
            }else{
              printPoint+=2;
            }
            break;
        }
        //temp 배열 초기화
        for(byte j=0; j<5; j++){
          temp[j] = 0;
        }
        tempIndex = 0; //temp 배열 인덱스 초기화
        if(chArr[i]=='\0'){
          return;
        }
      }else{
        temp[tempIndex] = chArr[i]; //temp 배열에 값 저장
        tempIndex++; //tempIndex 증가
      }
  }
}

int LiquidCrystal_I2C_Hangul::printing(char a1, char a2, char a3, char a4, char a5, byte tempIndex, byte hanCursor){ //으,이,의,응,잉,읭,읇,읿,읣
  if(tempIndex == 2){ //받침없는 ㅡ형, ㅣ형
    int cho = getchoAndJongIndex(a1);
    int u = getUFormIndex(a2);
    int yi = getYiFormIndex(a2);
    if(u>=0){
      byte mergedArr[8];
      mergeChoJung(choAndJongValue[cho], uFormValue[u], mergedArr);
      createChar(enrollNum, mergedArr);
      if(enrollNum==0){
        clear();
      }
      setCursor(hanCursor, 0);
      write(enrollNum);
      if(enrollNum<7){
        enrollNum++;
      }else if(enrollNum==7){
        enrollNum=0;
      }
      
      delay(delayTime);
      return 1;
    }else if(yi>=0){
      if(enrollNum==7 or enrollNum==0){
        enrollNum=0;
        clear();
      }
      createChar(enrollNum, choAndJongValue[cho]);
      createChar(enrollNum+1, yiFormValue[yi]);
      setCursor(hanCursor, 0);
      write(enrollNum);
      setCursor(hanCursor+1, 0);
      write(enrollNum+1);
      
      if(enrollNum<6){
        enrollNum+=2;
      }else if(enrollNum==6){
        enrollNum=0;
      }
      delay(delayTime);
      return 2;
    }
  }else if(tempIndex == 3){ //받침없는 ㅢ형 또는 받침있는 ㅡ형, ㅣ형 
    int cho = getchoAndJongIndex(a1);
    int jong = getchoAndJongIndex(a3);
    int u = getUFormIndex(a2);
    int yi = getYiFormIndex(a2);
    int iswa = getYiFormIndex(a3);
    if(u>=0 and iswa>=0){
      byte mergedArr[8];
      mergeChoJung(choAndJongValue[cho], uFormValue[u],mergedArr);
      if(enrollNum==7 or enrollNum==0){
        enrollNum=0;
        clear();
      }
      createChar(enrollNum, mergedArr);
      createChar(enrollNum+1, yiFormValue[iswa]);
      setCursor(hanCursor, 0);
      write(enrollNum);
      setCursor(hanCursor+1, 0);
      write(enrollNum+1);
      
      if(enrollNum<6){
        enrollNum+=2;
      }else if(enrollNum==6){
        enrollNum=0;
      }
      delay(delayTime);
      return 2;
    }else if(u>=0){
      byte mergedArr[8];
      mergeChoJung(choAndJongValue[cho], uFormValue[u], mergedArr);
      
      if(enrollNum==7 or enrollNum==0){
        clear();
        enrollNum = 0;
      }
      
      createChar(enrollNum, mergedArr);
      createChar(enrollNum+1, choAndJongValue[jong]);
      
      setCursor(hanCursor, 0);
      write(enrollNum);
      setCursor(hanCursor, 1);
      write(enrollNum+1);
      
      if(enrollNum<6){
        enrollNum+=2;
      }else if(enrollNum==6){
        
        enrollNum=0;
      }
      delay(delayTime);
      return 1;
    }else if(yi>=0){
      if(enrollNum>=6 or enrollNum==0){
        enrollNum=0;
        clear();
      }
      createChar(enrollNum, choAndJongValue[cho]);
      createChar(enrollNum+1, yiFormValue[yi]);
      createChar(enrollNum+2, choAndJongValue[jong]);
      setCursor(hanCursor, 0);
      write(enrollNum);
      setCursor(hanCursor+1, 0);
      write(enrollNum+1);
      setCursor(hanCursor, 1);
      write(enrollNum+2);
      
      if(enrollNum<5){
        enrollNum+=3;
      }else if(enrollNum==5){
        enrollNum=0;
      }
      delay(delayTime);
      return 2;
    }
  }else if(tempIndex == 4){ //받침있는 ㅢ형 또는 쌍받침있는 ㅡ형, ㅣ형 
    int cho = getchoAndJongIndex(a1);
    int jong1 = getchoAndJongIndex(a3);
    int jong2 = getchoAndJongIndex(a4);
    int u = getUFormIndex(a2);
    int yi = getYiFormIndex(a2);
    int iswa = getYiFormIndex(a3);
    if(u>=0 and iswa>=0){
      byte mergedArr[8];
      mergeChoJung(choAndJongValue[cho], uFormValue[u], mergedArr);
      if(enrollNum>4 or enrollNum==0){
        enrollNum=0;
        clear();
      }
      createChar(enrollNum, mergedArr);
      createChar(enrollNum+1, yiFormValue[iswa]);
      createChar(enrollNum+2, choAndJongValue[jong2]);
      setCursor(hanCursor, 0);
      write(enrollNum);
      setCursor(hanCursor+1, 0);
      write(enrollNum+1);
      setCursor(hanCursor, 1);
      write(enrollNum+2);
      
      if(enrollNum<5){
        enrollNum+=3;
      }else if(enrollNum==5){
        enrollNum=0;
      }
      delay(delayTime);
      return 2;
    }else if(u>=0){
      byte mergedArr[8];
      mergeChoJung(choAndJongValue[cho], uFormValue[u], mergedArr);
      
      if(enrollNum==7 or enrollNum==0){
        clear();
        enrollNum = 0;
      }
      
      createChar(enrollNum, mergedArr);
      createChar(enrollNum+1, choAndJongValue[jong1]);
      createChar(enrollNum+2, choAndJongValue[jong2]);
      setCursor(hanCursor, 0);
      write(enrollNum);
      setCursor(hanCursor, 1);
      write(enrollNum+1);
      setCursor(hanCursor+1, 1);
      write(enrollNum+2);
      
      if(enrollNum<5){
        enrollNum+=3;
      }else if(enrollNum==5){
        
        enrollNum=0;
      }
      delay(delayTime);
      return 2;
    }else if(yi>=0){
      if(enrollNum>=4 or enrollNum==0){
        enrollNum=0;
        clear();
      }
      createChar(enrollNum, choAndJongValue[cho]);
      createChar(enrollNum+1, yiFormValue[yi]);
      createChar(enrollNum+2, choAndJongValue[jong1]);
      createChar(enrollNum+3, choAndJongValue[jong2]);
      setCursor(hanCursor, 0);
      write(enrollNum);
      setCursor(hanCursor+1, 0);
      write(enrollNum+1);
      setCursor(hanCursor, 1);
      write(enrollNum+2);
      setCursor(hanCursor+1, 1);
      write(enrollNum+3);
      
      if(enrollNum<4){
        enrollNum+=4;
      }else if(enrollNum==4){
        enrollNum=0;
      }
      delay(delayTime);
      return 2;
    }
  }else if(tempIndex==5){
    int cho = getchoAndJongIndex(a1);
    int u = getUFormIndex(a2);
    int yi = getYiFormIndex(a3);
    int jong1 = getchoAndJongIndex(a4);
    int jong2 = getchoAndJongIndex(a5);

    byte mergedArr[8];
    mergeChoJung(choAndJongValue[cho], uFormValue[u], mergedArr);
    if(enrollNum>3 or enrollNum==0){
      enrollNum=0;
      clear();
    }
    createChar(enrollNum, mergedArr);
    createChar(enrollNum+1, yiFormValue[yi]);
    createChar(enrollNum+2, choAndJongValue[jong1]);
    createChar(enrollNum+3, choAndJongValue[jong2]);
    
    setCursor(hanCursor, 0);
    write(enrollNum);
    setCursor(hanCursor+1, 0);
    write(enrollNum+1);
    setCursor(hanCursor, 1);
    write(enrollNum+2);
    setCursor(hanCursor+1, 1);
    write(enrollNum+3);
    
    if(enrollNum<3){
      enrollNum+=3;
    }else if(enrollNum==3){
      enrollNum=0;
    }
    delay(delayTime);
    return 2;
  }
}

// unsupported API functions
void LiquidCrystal_I2C_Hangul::off(){}
void LiquidCrystal_I2C_Hangul::on(){}
void LiquidCrystal_I2C_Hangul::setDelay (int cmdDelay,int charDelay) {}
uint8_t LiquidCrystal_I2C_Hangul::status(){return 0;}
uint8_t LiquidCrystal_I2C_Hangul::keypad (){return 0;}
uint8_t LiquidCrystal_I2C_Hangul::init_bargraph(uint8_t graphtype){return 0;}
void LiquidCrystal_I2C_Hangul::draw_horizontal_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end){}
void LiquidCrystal_I2C_Hangul::draw_vertical_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_row_end){}
void LiquidCrystal_I2C_Hangul::setContrast(uint8_t new_val){}

	

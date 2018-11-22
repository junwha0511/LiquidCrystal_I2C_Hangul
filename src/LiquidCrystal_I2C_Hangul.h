//YWROBOT
#ifndef LiquidCrystal_I2C_Hangul_h
#define LiquidCrystal_I2C_Hangul_h

#include <inttypes.h>
#include "Print.h" 
#include <Wire.h>
#include "Arduino.h"


// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En B00000100  // Enable bit
#define Rw B00000010  // Read/Write bit
#define Rs B00000001  // Register select bit

class LiquidCrystal_I2C_Hangul : public Print {
public:
    LiquidCrystal_I2C_Hangul(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows);
    void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS );
    void clear();
    void home();
    void noDisplay();
    void display();
    void noBlink();
    void blink();
    void noCursor();
    void cursor();
    void scrollDisplayLeft();
    void scrollDisplayRight();
    void printLeft();
    void printRight();
    void leftToRight();
    void rightToLeft();
    void shiftIncrement();
    void shiftDecrement();
    void noBacklight();
    void backlight();
    void autoscroll();
    void noAutoscroll(); 
    void createChar(uint8_t, uint8_t[]);
    void setCursor(uint8_t, uint8_t); 
    void setDelayTime(int t);
    void printHangul(String txt, byte startPoint);
#if defined(ARDUINO) && ARDUINO >= 100
    virtual size_t write(uint8_t);
#else
    virtual void write(uint8_t);
#endif
    void command(uint8_t);
    void init();

////compatibility API function aliases
void blink_on();						// alias for blink()
void blink_off();       					// alias for noBlink()
void cursor_on();      	 					// alias for cursor()
void cursor_off();      					// alias for noCursor()
void setBacklight(uint8_t new_val);				// alias for backlight() and nobacklight()
void load_custom_character(uint8_t char_num, uint8_t *rows);	// alias for createChar()
void printstr(const char[]);

////Unsupported API functions (not implemented in this library)
uint8_t status();
void setContrast(uint8_t new_val);
uint8_t keypad();
void setDelay(int,int);
void on();
void off();
uint8_t init_bargraph(uint8_t graphtype);
void draw_horizontal_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);
void draw_vertical_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);
	 

private:
    int printing(char a1, char a2, char a3, char a4, char a5, byte tempIndex, byte hanCursor);
    void init_priv();
    void send(uint8_t, uint8_t);
    void write4bits(uint8_t);
    void expanderWrite(uint8_t);
    void pulseEnable(uint8_t);
    uint8_t _Addr;
    uint8_t _displayfunction;
    uint8_t _displaycontrol;
    uint8_t _displaymode;
    uint8_t _numlines;
    uint8_t _cols;
    uint8_t _rows;
    uint8_t _backlightval;
    int getchoAndJongIndex(char key);
    byte* getUFormIndex(char key);
    byte* getYiFormIndex(char key);
    void mergeChoJung(byte* cho, byte* jung, byte* mergedArr);
    int enrollNum = 0;
    int delayTime = 500;

    byte space[8] = {
            B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000
    };
    //초성/종성 자음
    byte r[8] = {//ㄱ
            B11111,B00001,B00001,B00001,B00000,B00000,B00000,B00000
    };
    byte s[8] = {//ㄴ
            B10000,B10000,B10000,B11111,B00000,B00000,B00000,B00000
    };
    byte e[8] = {//ㄷ
            B11111,B10000,B10000,B11111,B00000,B00000,B00000,B00000
    };
    byte f[8] = {//ㄹ
            B11111,B00001,B11111,B10000,B11111,B00000,B00000,B00000
    };
    byte a[8] = {//ㅁ
            B11111,B10001,B10001,B11111,B00000,B00000,B00000,B00000
    };
    byte q[8] = {//ㅂ
            B01010,B01110,B01010,B01110,B00000,B00000,B00000,B00000
    };
    byte t[8] = {//ㅅ
            B00100,B00100,B01010,B10001,B00000,B00000,B00000,B00000
    };
    byte d[8] = {//ㅇ
            B01110,B11011,B10001,B11011,B01110,B00000,B00000,B00000
    };
    byte w[8] = {//ㅈ
            B11111,B00100,B01010,B10001,B00000,B00000,B00000,B00000
    };
    byte c[8] = {//ㅊ
            B00100,B11111,B00100,B01010,B10001,B00000,B00000,B00000
    };
    byte z[8] = {//ㅋ
            B11111,B00001,B01111,B00001,B00001,B00000,B00000,B00000
    };
    byte x[8] = {//ㅌ
            B11111,B10000,B11111,B10000,B11111,B00000,B00000,B00000
    };
    byte  v[8] = {//ㅍ
            B11111,B01010,B01010,B11111,B00000,B00000,B00000,B00000
    };
    byte g[8] = {//ㅎ
            B00100,B11111,B00100,B01010,B00100,B00000,B00000,B00000
    };
    byte R[8] = {//ㄲ
            B11111,B00101,B00101,B00101,B00000,B00000,B00000,B00000
    };
    byte E[8] = {//ㄸ
            B11111,B10100,B10100,B11111,B00000,B00000,B00000,B00000
    };
    byte Q[8] = {//ㅃ
            B10101,B11111,B10101,B11111,B00000,B00000,B00000,B00000
    };
    byte T[8] = {//ㅆ
            B01010,B01010,B10101,B10101,B00000,B00000,B00000,B00000
    };
    byte W[8] = {//ㅉ
            B11111,B01010,B10101,B10101,B00000,B00000,B00000,B00000
    };
    //ㅡ형 모음
    byte m[8] = {//ㅡ
            B00000,B00000,B00000,B00000,B00000,B00000,B11111,B00000
    };
    byte h[8] = {//ㅗ
            B00000,B00000,B00000,B00000,B00000,B00100,B11111,B00000
    };
    byte y[8] = {//ㅛ
            B00000,B00000,B00000,B00000,B00000,B01010,B11111,B00000
    };
    byte n[8] = {//ㅜ
            B00000,B00000,B00000,B00000,B00000,B00000,B11111,B00100
    };
    byte b[8] = {//ㅠ   
            B00000,B00000,B00000,B00000,B00000,B00000,B11111,B01010
    };
    //ㅣ형 모음
    byte k[8] = { //ㅏ
            B00000,B10000,B10000,B10000,B11000,B10000,B10000,B00000
    };
    byte i[8] = { //ㅑ
            B00000,B10000,B10000,B11000,B10000,B11000,B10000,B00000
    };
    byte j[8] = { //ㅓ
            B00000,B01000,B01000,B01000,B11000,B01000,B01000,B00000
    };
    byte u[8] = { //ㅕ
            B00000,B01000,B01000,B11000,B01000,B11000,B01000,B00000
    };
    byte l[8] = { //ㅣ
            B00000,B10000,B10000,B10000,B10000,B10000,B10000,B00000
    };
    byte o[8] = { //ㅐ
            B00000,B10100,B10100,B10100,B11100,B10100,B10100,B00000
    };
    byte O[8] = { //ㅒ
            B00000,B10100,B10100,B11100,B10100,B11100,B10100,B00000
    };
    byte p[8] = {//ㅔ
            B00000,B01010,B01010,B01010,B11010,B01010,B01010,B00000
    };
    byte P[8] = { //ㅖ
            B00000,B01010,B01010,B11010,B01010,B11010,B01010,B00000
    };

    //딕셔너리 자료형의 Key 배열과 Value 배열
    char choAndJongKey[19] = { //len:19
    'r','s','e','f','a','q','t','d','w','c','z','x','v','g','R','E','Q','T','W'
    };
    byte* choAndJongValue[19] = {//ㄱ,ㄴ,ㄷ,ㄹ,ㅁ,ㅂ,ㅅ,ㅇ,ㅈ,ㅊ,ㅋ,ㅌ,ㅍ,ㅎ,ㄲ,ㄸ,ㅃ,ㅆ,ㅉ len:19
    r,s,e,f,a,q,t,d,w,c,z,x,v,g,R,E,Q,T,W
    };
    char uFormKey[5] = { //len:5
    'm','h','y','n','b'
    };
    byte* uFormValue[5] = {//ㅡ,ㅗ,ㅛ,ㅜ,ㅠ len:5
    m,h,y,n,b
    };
    char yiFormKey[9] = { //len:9
    'k','i','j','u','l','o','O','p','P'
    };
    byte* yiFormValue[9] = {//ㅏ,ㅑ,ㅓ,ㅕ,ㅣ,ㅐ,ㅒ,ㅔ,ㅖ len:9
    k,i,j,u,l,o,O,p,P
    };
};

#endif

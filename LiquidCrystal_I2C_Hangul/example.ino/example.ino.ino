#include<LiquidCrystal_I2C_Hangul.h>
#include<Wire.h>

LiquidCrystal_I2C_Hangul lcd(0x3F,16,2); //LCD 클래스 초기화

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setDelayTime(1000);
  lcd.printHangul("dP wp vk dlf dlq sl ek",0);
  lcd.clear();
  lcd.print("completed!");
}

void loop() {
  // put your main code here, to run repeatedly:

}

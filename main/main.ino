#include<Wire.h> //LCD를 위한 라이브러리
#include<LiquidCrystal_I2C.h> //LCD를 위한 라이브러리
 
LiquidCrystal_I2C lcd(0x3F,16,2); //LCD 클래스 초기화

//1. 공백 단위로 영어로 입력
//2. 공백 단위로 파싱, 배열에 저장
//3. 각각 함수의 인자로 넘김
//4. 받은 인자를 ㅡ형 ㅣ형 ㅢ형에 따라 처리
//5. 바로 출력

void setup() {
  lcd.init(); 
  lcd.backlight();
  while(true){
    printHangul("wk tmq tl wkr", 0);
  }
}

void loop() {

}
# LiquidCrystal_I2C_Hangul : LCD 한글 출력 라이브러리

 이 라이브러리는 I2C 통신을 사용하는 16x2 LCD 또는 20x4 LCD에서 한글을 출력하고자 하는 분들을 위해 제작된 라이브러리입니다.
 
 아두이노 Library Manager에 본 라이브러리를 검색하여 다운받거나 직접 Clone 해주세요.


 LiquidCrystal_I2C_Hangul 라이브러리에서는 기존 LiquidCrystal_I2C 라이브러리에 포함된 함수들과 아래의 함수들을 사용하실 수 있습니다.
 
 1. printHangul(wchar_t txt, byte firstPoint, byte len) 함수: 첫번째 인자로 wchar_t형의 한글 문자열을 입력하세요. 두번째 인자는 글자가 시작하는 위치(0~15), 세번째 인자는 글자의 길이입니다.
 *공백 문자 및 특수문자는 지원되지 않습니다.(print 함수를 사용해주세요)
 *'ㅡ'형 문자는 좌우 1칸을, 'ㅣ'형 문자는 좌우 2칸을 사용합니다.
 
 2. setDelayTime(int t) 함수: 글자가 출력되는 속도를 설정하세요 (기본값: 1000ms)

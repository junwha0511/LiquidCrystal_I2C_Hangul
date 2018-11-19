# LiquidCrystal_I2C-print-hangul

 이 코드는 I2C 통신을 사용하는 16x2 LCD 또는 20x4 LCD에서 한글을 출력하고자 하는 분들을 위해 제작된 코드입니다.
 코드를 다운 받으신 후 아래와 같은 사용법을 참조해주세요.
 
 1. printHangul(String txt, byte firstPoint) 함수: 첫번째 인자로 키보드에서 한글과 대응되는 영문을 친 후 한 글자마다 공백으로 구분하여 입력하세요.
    두번째 인자는 글자가 시작하는 위치입니다. (0~15)
 2. setDelayTime(int t) 함수: 글자가 출력되는 속도를 설정하세요 (기본값: 1000ms)

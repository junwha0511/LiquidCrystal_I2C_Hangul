# LiquidCrystal_I2C_Hangul : LCD 한글 출력 라이브러리

 이 라이브러리는 I2C 통신을 사용하는 16x2 LCD 또는 20x4 LCD에서 한글을 출력하고자 하는 분들을 위해 제작된 라이브러리입니다.
 
 main 폴더를 다운 받으시면 추가적인 라이브러리 없이 main 파일에서 함수를 실행하실 수 있으며,
 
 LiquidCrystal_I2C_Hangul 라이브러리를 다운 받으시면 기존 LiquidCrystal_I2C 라이브러리에 포함된 함수들과 아래의 함수들을 사용하실 수 있습니다.
 
 1. printHangul(String txt, byte firstPoint) 함수: 첫번째 인자로 키보드에서 한글과 대응되는 영문을 한 글자마다 공백으로 구분하여 입력하세요. 
 예) 한글 출력 라이브러리 => gks rmf cnf fur fk dl qm fj fl
    두번째 인자는 글자가 시작하는 위치입니다. (0~15)
 2. setDelayTime(int t) 함수: 글자가 출력되는 속도를 설정하세요 (기본값: 1000ms)

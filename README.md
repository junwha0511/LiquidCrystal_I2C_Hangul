# LiquidCrystal_I2C_Hangul : LCD 한글 출력 라이브러리

## Introduction

 이 라이브러리는 I2C 통신을 사용하는 16x2 LCD 또는 20x4 LCD에서 한글을 출력할 수 있는 라이브러리입니다.
 
 This library is a library that prints hangul(Korean) on 16x2 LCD or 20x4 LCD that uses I2C comunication.
 
## Getting started
### from Arduino Library Manager
 Arduino IDE -> 스케치(Sketch) -> 라이브러리 포함하기(Include Library) -> 라이브러리 관리(Library Manager)에서 'LiquidCrystal_I2C_Hangul'을 검색하여 간편하게 설치할 수 있습니다.
 
### from zip file from Github
 현재 Repository에서 Releases 창의 마지막 Release를 다운로드 하여,  Arduino IDE -> 스케치(Sketch) -> 라이브러리 포함하기(Include Library) -> .ZIP 라이브러리 추가 메뉴를 통해 라이브러리를 설치할 수 있습니다.

 
### Documentation: Standard API
LiquidCrystal_I2C_Hangul 라이브러리에서는 
기존 LiquidCrystal_I2C 라이브러리에 포함된 함수들을 지원합니다.

This Library supports the functions in 'LiquidCrystal_I2C' also.

[https://www.arduino.cc/reference/en/libraries/liquidcrystal]([https://www.arduino.cc/reference/en/](https://www.arduino.cc/reference/en/libraries/liquidcrystal/))

  
### Documentation: Non-Standard API
한글 출력을 위해 다음과 같은 함수를 지원합니다.
 
- `printHangul(wchar_t* txt, byte firstPoint, byte len)`: 첫번째 인자로 wchar_t형의 한글 문자열을 입력하세요. 두번째 인자는 글자가 시작하는 위치(0~15), 세번째 인자는 글자의 길이입니다.

  ※ 공백 문자 및 특수문자는 지원되지 않습니다.(print 함수를 사용해주세요)

  ※ 'ㅡ'형 문자는 좌우 1칸을, 'ㅣ'형 문자는 좌우 2칸을 사용합니다.

- `setDelayTime(int t)`: 글자가 출력되는 속도를 설정합니다. (기본값: 1000ms)

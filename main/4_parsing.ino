//파싱 함수
void printHangul(String txt, byte startPoint)
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
            printPoint++;
            break;
          case 2:
            printPoint+=2;
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

//파싱 함수
void parseTxt(String txt)
{  
  char chArr[1000] = {0}; //문자들을 저장할 배열을 선언한다. (공백 포함 1천자)
  char temp[5] = {0}; //임시 저장 배열
  int tempIndex = 0; //temp 배열 인덱스
  txt.toCharArray(chArr, txt.length()); //매개인자를 chArr에 저장한다.
  
  boolean isBeforeSpace = false; //이전 문자의 공백 여부 플래그
  
  for(int i=0; i<1000; i++){
    if(!isBeforeSpace){
      if(chArr[i] == ' '){ //해당 문자가 공백일 경우
        if(isYi(temp)){
          
        }else if(isWa(temp)){
          
        }else if(isU(temp)){
          
        }
        //temp 배열 초기화
        for(int i=0; i<5; i++){
          temp[i] = 0;
        }
        tempIndex = 0; //temp 배열 인덱스 초기화
        isBeforeSpace=true; 
      }else{
        temp[tempIndex] = chArr[i]; //temp 배열에 값 저장
        tempIndex++; //tempIndex 증가
        isBeforeSpace=false;
      }
    }else if(isBeforeSpace){
      break;
    }
  }
}

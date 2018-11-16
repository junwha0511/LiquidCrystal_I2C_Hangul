//딕셔너리 자료형을 완성하는 함수. key값으로 비교해 value에 대응시킨다.
byte* getValue(char key, char* keyArr, byte** valueArr, int len){ //매개인자: key 값, key 배열, value 배열, 배열 길이
  for(int i=0; i<len; i++){
    if(key==keyArr[i]){
      return valueArr[i];
    }
  }
  return "";
}

int getchoAndJongIndex(char key){ //초성과 종성의 key로 배열 인덱스를 얻는다.
  for(int i=0; i<19; i++){
    if(key==choAndJongKey[i]){
      return i;
    }
  }
  return -1;
}
byte* getUFormIndex(char key){ //ㅡ형 모음의 key로 배열 인덱스를 얻는다.
  for(int i=0; i<5; i++){
    if(key==uFormKey[i]){
      return i;
    }
  }
  return -1;
}
byte* getYiFormIndex(char key){ //ㅣ형 모음의 key로 배열 인덱스를 얻는다.
  for(int i=0; i<9; i++){
    if(key==yiFormKey[i]){
      return i;
    }
  }
  return -1;
}

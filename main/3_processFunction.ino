void mergeChoJung(byte* cho, byte* jung, byte* mergedArr){ //합칠 자음(초성), 중성 입력
  for(int i=0; i<8; i++){
    if(i<5){ //초성 범위
      mergedArr[i] = cho[i]; //초성을 저장
    }else if(i>=5){ //중성 범위
      mergedArr[i] = jung[i]; //중성을 저장
    }
  }
} 

void copyArray(byte* before, byte* after){
  for(int i=0; i<8; i++){
    after[i] = before[i];
  }
}

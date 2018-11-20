int printing(char a1, char a2, char a3, char a4, char a5, byte tempIndex, byte hanCursor){ //으,이,의,응,잉,읭,읇,읿,읣
  if(tempIndex == 2){ //받침없는 ㅡ형, ㅣ형
    int cho = getchoAndJongIndex(a1);
    int u = getUFormIndex(a2);
    int yi = getYiFormIndex(a2);
    if(u>=0){
      byte mergedArr[8];
      mergeChoJung(choAndJongValue[cho], uFormValue[u], mergedArr);
      lcd.createChar(enrollNum, mergedArr);
      if(enrollNum==0){
        lcd.clear();
      }
      lcd.setCursor(hanCursor, 0);
      lcd.write(enrollNum);
      if(enrollNum<7){
        enrollNum++;
      }else if(enrollNum==7){
        enrollNum=0;
      }
      
      delay(delayTime);
      return 1;
    }else if(yi>=0){
      if(enrollNum==7 or enrollNum==0){
        enrollNum=0;
        lcd.clear();
      }
      lcd.createChar(enrollNum, choAndJongValue[cho]);
      lcd.createChar(enrollNum+1, yiFormValue[yi]);
      lcd.setCursor(hanCursor, 0);
      lcd.write(enrollNum);
      lcd.setCursor(hanCursor+1, 0);
      lcd.write(enrollNum+1);
      
      if(enrollNum<6){
        enrollNum+=2;
      }else if(enrollNum==6){
        enrollNum=0;
      }
      delay(delayTime);
      return 2;
    }
  }else if(tempIndex == 3){ //받침없는 ㅢ형 또는 받침있는 ㅡ형, ㅣ형 
    int cho = getchoAndJongIndex(a1);
    int jong = getchoAndJongIndex(a3);
    int u = getUFormIndex(a2);
    int yi = getYiFormIndex(a2);
    int iswa = getYiFormIndex(a3);
    if(u>=0 and iswa>=0){
      byte mergedArr[8];
      mergeChoJung(choAndJongValue[cho], uFormValue[u],mergedArr);
      if(enrollNum==7 or enrollNum==0){
        enrollNum=0;
        lcd.clear();
      }
      lcd.createChar(enrollNum, mergedArr);
      lcd.createChar(enrollNum+1, yiFormValue[iswa]);
      lcd.setCursor(hanCursor, 0);
      lcd.write(enrollNum);
      lcd.setCursor(hanCursor+1, 0);
      lcd.write(enrollNum+1);
      
      if(enrollNum<6){
        enrollNum+=2;
      }else if(enrollNum==6){
        enrollNum=0;
      }
      delay(delayTime);
      return 2;
    }else if(u>=0){
      byte mergedArr[8];
      mergeChoJung(choAndJongValue[cho], uFormValue[u], mergedArr);
      
      if(enrollNum==7 or enrollNum==0){
        lcd.clear();
        enrollNum = 0;
      }
      
      lcd.createChar(enrollNum, mergedArr);
      lcd.createChar(enrollNum+1, choAndJongValue[jong]);
      
      lcd.setCursor(hanCursor, 0);
      lcd.write(enrollNum);
      lcd.setCursor(hanCursor, 1);
      lcd.write(enrollNum+1);
      
      if(enrollNum<6){
        enrollNum+=2;
      }else if(enrollNum==6){
        
        enrollNum=0;
      }
      delay(delayTime);
      return 1;
    }else if(yi>=0){
      if(enrollNum>=6 or enrollNum==0){
        enrollNum=0;
        lcd.clear();
      }
      lcd.createChar(enrollNum, choAndJongValue[cho]);
      lcd.createChar(enrollNum+1, yiFormValue[yi]);
      lcd.createChar(enrollNum+2, choAndJongValue[jong]);
      lcd.setCursor(hanCursor, 0);
      lcd.write(enrollNum);
      lcd.setCursor(hanCursor+1, 0);
      lcd.write(enrollNum+1);
      lcd.setCursor(hanCursor, 1);
      lcd.write(enrollNum+2);
      
      if(enrollNum<5){
        enrollNum+=3;
      }else if(enrollNum==5){
        enrollNum=0;
      }
      delay(delayTime);
      return 2;
    }
  }else if(tempIndex == 4){ //받침있는 ㅢ형 또는 쌍받침있는 ㅡ형, ㅣ형 
    int cho = getchoAndJongIndex(a1);
    int jong1 = getchoAndJongIndex(a3);
    int jong2 = getchoAndJongIndex(a4);
    int u = getUFormIndex(a2);
    int yi = getYiFormIndex(a2);
    int iswa = getYiFormIndex(a3);
    if(u>=0 and iswa>=0){
      byte mergedArr[8];
      mergeChoJung(choAndJongValue[cho], uFormValue[u], mergedArr);
      if(enrollNum>4 or enrollNum==0){
        enrollNum=0;
        lcd.clear();
      }
      lcd.createChar(enrollNum, mergedArr);
      lcd.createChar(enrollNum+1, yiFormValue[iswa]);
      lcd.createChar(enrollNum+2, choAndJongValue[jong2]);
      lcd.setCursor(hanCursor, 0);
      lcd.write(enrollNum);
      lcd.setCursor(hanCursor+1, 0);
      lcd.write(enrollNum+1);
      lcd.setCursor(hanCursor, 1);
      lcd.write(enrollNum+2);
      
      if(enrollNum<5){
        enrollNum+=3;
      }else if(enrollNum==5){
        enrollNum=0;
      }
      delay(delayTime);
      return 2;
    }else if(u>=0){
      byte mergedArr[8];
      mergeChoJung(choAndJongValue[cho], uFormValue[u], mergedArr);
      
      if(enrollNum==7 or enrollNum==0){
        lcd.clear();
        enrollNum = 0;
      }
      
      lcd.createChar(enrollNum, mergedArr);
      lcd.createChar(enrollNum+1, choAndJongValue[jong1]);
      lcd.createChar(enrollNum+2, choAndJongValue[jong2]);
      lcd.setCursor(hanCursor, 0);
      lcd.write(enrollNum);
      lcd.setCursor(hanCursor, 1);
      lcd.write(enrollNum+1);
      lcd.setCursor(hanCursor+1, 1);
      lcd.write(enrollNum+2);
      
      if(enrollNum<5){
        enrollNum+=3;
      }else if(enrollNum==5){
        
        enrollNum=0;
      }
      delay(delayTime);
      return 2;
    }else if(yi>=0){
      if(enrollNum>=4 or enrollNum==0){
        enrollNum=0;
        lcd.clear();
      }
      lcd.createChar(enrollNum, choAndJongValue[cho]);
      lcd.createChar(enrollNum+1, yiFormValue[yi]);
      lcd.createChar(enrollNum+2, choAndJongValue[jong1]);
      lcd.createChar(enrollNum+3, choAndJongValue[jong2]);
      lcd.setCursor(hanCursor, 0);
      lcd.write(enrollNum);
      lcd.setCursor(hanCursor+1, 0);
      lcd.write(enrollNum+1);
      lcd.setCursor(hanCursor, 1);
      lcd.write(enrollNum+2);
      lcd.setCursor(hanCursor+1, 1);
      lcd.write(enrollNum+3);
      
      if(enrollNum<4){
        enrollNum+=4;
      }else if(enrollNum==4){
        enrollNum=0;
      }
      delay(delayTime);
      return 2;
    }
  }else if(tempIndex==5){
    int cho = getchoAndJongIndex(a1);
    int u = getUFormIndex(a2);
    int yi = getYiFormIndex(a3);
    int jong1 = getchoAndJongIndex(a4);
    int jong2 = getchoAndJongIndex(a5);

    byte mergedArr[8];
    mergeChoJung(choAndJongValue[cho], uFormValue[u], mergedArr);
    if(enrollNum>3 or enrollNum==0){
      enrollNum=0;
      lcd.clear();
    }
    lcd.createChar(enrollNum, mergedArr);
    lcd.createChar(enrollNum+1, yiFormValue[yi]);
    lcd.createChar(enrollNum+2, choAndJongValue[jong1]);
    lcd.createChar(enrollNum+3, choAndJongValue[jong2]);
    
    lcd.setCursor(hanCursor, 0);
    lcd.write(enrollNum);
    lcd.setCursor(hanCursor+1, 0);
    lcd.write(enrollNum+1);
    lcd.setCursor(hanCursor, 1);
    lcd.write(enrollNum+2);
    lcd.setCursor(hanCursor+1, 1);
    lcd.write(enrollNum+3);
    
    if(enrollNum<3){
      enrollNum+=3;
    }else if(enrollNum==3){
      enrollNum=0;
    }
    delay(delayTime);
    return 2;
  }
}


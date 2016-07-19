//*******1*********2*********3*********4*********4*********5*********6*********7*********8
#include "Arduino.h"
#include "KmMelody.h"

KmMelody::KmMelody(int pout){
  PinOut=pout;
  S[0]=110; S[1]=116; S[2]=123; S[3]=131; S[4]=138; S[5]=147;
  S[6]=155; S[7]=165; S[8]=174; S[9]=185; S[10]=196; S[11]=207;
  S[12]=220; S[13]=233; S[14]=247; S[15]=262; S[16]=277; S[17]=294;
  S[18]=311; S[19]=330; S[20]=349; S[21]=370; S[22]=392; S[23]=415;
  S[24]=440; S[25]=466; S[26]=494; S[27]=524; S[28]=564; S[29]=588;
  S[30]=622; S[31]=660; S[32]=698; S[33]=740; S[34]=784; S[35]=830;
  S[36]=0;
}

void KmMelody::begin(int tempo){
  Max=0; Index=-1; Last=0;
  int i; for(i=0; i<DATA_SIZE; i++){Freq[i]=0; Secs[i]=0; Duty[i]=0;}
  Base=60000/tempo;
  if(DEBUG){
    Serial.println("Play Melody");
    analogWrite(PinOut, 500);
    analogWriteFreq(262); delay(500);
    analogWriteFreq(294); delay(500);
    analogWriteFreq(330); delay(500);
    analogWrite(PinOut, 0);
  }
}

//##### play
//##### playコマンドの分解
void KmMelody::play(String req){
  unsigned int i, j; String x, y;
  if(DEBUG){Serial.println(req);}
  unsigned int s, f, d, c;
  s=Base; f=3; d=400; c=1;
  Max=0; //  KmMelody::clear();

  j=Max; x=""; y="";
  for(i=0; i<req.length(); i++){
    x=req.charAt(i);
    
    if(x==","){
      Secs[j]=s; if(f==15){Freq[j]=36;}else{Freq[j]=(c*12)+f;} Duty[j]=d; Max=j+1;
      j++; if(j>DATA_SIZE){break;}
      s=Base; f=3; d=400; c=1;
    }else{
    
      if(x=="."){s=Base/4;} else if(x=="/"){s=Base/2;} else if(x=="1"){s=Base;}
      else if(x=="2"){s=Base*2;} else if(x=="3"){s=Base*3;} else if(x=="4"){s=Base*4;}

      else if(x=="a"){f=0;} else if(x=="b"){f=2;} else if(x=="c"){f=3;} else if(x=="d"){f=5;}
      else if(x=="e"){f=7;} else if(x=="f"){f=8;} else if(x=="g"){f=10;}
      else if(x=="+"){f=f+1;} else if(x=="-"){f=f-1;}
      else if(x=="H"){c=2;} else if(x=="L"){c=0;} else if(x=="O"){c=3;}
      else if(x=="x"){f=15;}
    
      else if(x=="A"){d=1;} else if(x=="B"){d=10;} else if(x=="C"){d=40;}
      else if(x=="D"){d=60;} else if(x=="E"){d=80;}

    }
    Secs[j]=s; if(f==15){Freq[j]=36;}else{Freq[j]=(c*12)+f;} Duty[j]=d; Max=j+1;
    if(Max>0){Index=0;}
  }

  Save=micros();
}


void KmMelody::clear(){
  int i, j; if(Index<0){return;}

  for(i=0; i<DATA_SIZE; i++){
    if(i<Index){
      Freq[i]=0; Secs[i]=0; Duty[i]=0;
    }else{
      j=i-Index; if(i>Max){Max=j; break;} 
      Freq[j]=Freq[i]; Secs[j]=Secs[i]; Duty[j]=Duty[i];
    }
  }

}


//##### cont
//#####
void KmMelody::cont(bool cont){

  long tm, nw; nw=micros();
  if(Index<0){return;}
  tm=(nw-Save)/1000;
  if(cont){if(tm<Last){return;}}
  if(Index>=Max){analogWrite(PinOut, 0); Index=-1; return;}
  analogWriteFreq(S[Freq[Index]]);
  analogWrite(PinOut, Duty[Index]);
  Save=nw; Last=Secs[Index];
  if(DEBUG){
    Serial.print("#"); Serial.print(S[Freq[Index]]);
    Serial.print(","); Serial.print(Secs[Index]);
    Serial.print(","); Serial.println(Duty[Index]);
  }
  Index++;

}

void KmMelody::tempo(String txt){
  Base=60000/atoi(txt.c_str());
}

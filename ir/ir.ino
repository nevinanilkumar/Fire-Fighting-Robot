int startpin=6;
int lastpin=13;
int data=0;
int bitStart=2;
int bitLast=5;
int bitVal[4]={0,0,0,0};
void setup() {
  for(int i=startpin;i<=lastpin;i++){
    pinMode(i,INPUT);
    }
  for(int j=bitStart;j<=bitLast;j++){
    pinMode(j,OUTPUT);
    }
  for(int k=bitStart;k<=bitLast;k++){
    digitalWrite(k,HIGH);
    }
  Serial.begin(9600);
  
}

void loop() {
  data=0;//data is reset at every loop
  for(int i=startpin;i<=lastpin;i++){
    if(irRead(i)==1){
      data=i-4;
      }
    }
    
    Serial.println(data);
  dec2bin(data,bitVal);
  for(int i=bitStart;i<=bitLast;i++){
    if(bitVal[i-2]==1){
      digitalWrite(i,LOW);
      }else{
      digitalWrite(i,HIGH);
    }
//    Serial.println(i,bitVal[i]);
  }
}

int irRead(int irPin){
  int flame;
  flame=digitalRead(irPin);
  if(flame==1){
    return 1;
    }else{
      return 0;
      }
  }
 void dec2bin(int d,int* bitVal){
  switch(d){
    case 0:
      bitVal[0]=0;
      bitVal[1]=0;
      bitVal[2]=0;
      bitVal[3]=0;
      break;
    case 1:
      bitVal[0]=0;
      bitVal[1]=0;
      bitVal[2]=0;
      bitVal[3]=1;
      break;
    case 2:
      bitVal[0]=0;
      bitVal[1]=0;
      bitVal[2]=1;
      bitVal[3]=0;
      break;
    case 3:
      bitVal[0]=0;
      bitVal[1]=0;
      bitVal[2]=1;
      bitVal[3]=1;
      break;
    case 4:
      bitVal[0]=0;
      bitVal[1]=1;
      bitVal[2]=0;
      bitVal[3]=0;
      break;
    case 5:
      bitVal[0]=0;
      bitVal[1]=1;
      bitVal[2]=0;
      bitVal[3]=1;
      break;
    case 6:
      bitVal[0]=0;
      bitVal[1]=1;
      bitVal[2]=1;
      bitVal[3]=0;
      break;
    case 7:
      bitVal[0]=0;
      bitVal[1]=1;
      bitVal[2]=1;
      bitVal[3]=1;
      break;
    case 8:
      bitVal[0]=1;
      bitVal[1]=0;
      bitVal[2]=0;
      bitVal[3]=0;
      break;
    case 9:
      bitVal[0]=1;
      bitVal[1]=0;
      bitVal[2]=0;
      bitVal[3]=1;
      break;
    }
  }

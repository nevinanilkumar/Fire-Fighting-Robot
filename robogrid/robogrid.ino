#include<Servo.h>
const int s1=A0;
const int s2=A1;
const int s3=A2;
const int s4=A3;
const int s5=A4;

//wheel pins
const int leftwheelsf=13;
const int leftwheelsb=12;
const int rightwheelsf=11;
const int rightwheelsb=10;

//pump
const int pump=9;

//bitpins
const int b1=2;
const int b2=3;
const int b3=4;
const int b4=5;

int b1_read,b2_read,b3_read,b4_read;
int sensorNo=0;
int gridCoord[2];
int flame_data[2]={0,0};
void setup() {
  // all the wheel motors are defined as outputs
  pinMode(leftwheelsf,OUTPUT);
  pinMode(rightwheelsf,OUTPUT);
  pinMode(leftwheelsb,OUTPUT);
  pinMode(rightwheelsb,OUTPUT);
  pinMode(pump,OUTPUT);
  Serial.begin(9600);
  digitalWrite(pump,HIGH);

}

void loop() {
  sensorNo=0;
  b1_read=digitalRead(b1);
  b2_read=digitalRead(b2);
  b3_read=digitalRead(b3);
  b4_read=digitalRead(b4);
  sensorNo=bin2dec(b1_read,b2_read,b3_read,b4_read);
  Serial.print("Sensor : ");
  Serial.print(sensorNo);
  Serial.print("\n");
  if(sensorNo>0){
    findPosition(sensorNo,gridCoord);
    forward();
    delay((gridCoord[0])*1400);
    hault();
    tankleft();
    delay(785);//find 90 degree value of delay
    hault();
    forward();
    delay((gridCoord[1])*1350);
    hault();
    delay(2000);
    delay(1000);
    flame_dir(flame_data);
    Serial.println(flame_data[0]);
    robot_align(flame_data[0]);
    flame_data[0]=0;
    delay(1000);
    digitalWrite(pump,LOW);
    delay(5000);
    digitalWrite(pump,HIGH);
    delay(1000);
    }
}
 int bin2dec(int a, int b, int c, int d){
    if(a==0 & b==1 & c==1 &d==0){
      return 9;
      }else if(a==0 & b==1 & c==1 & d==1){
        return 8;
      }else if(a==1 & b==0 & c==0 & d==0){
        return 7;
      }else if(a==1 & b==0 & c==0 & d==1){
        return 6;
      }else if(a==1 & b==0 & c==1 & d==0){
        return 5;
      }else if(a==1 & b==0 & c==1 & d==1){
        return 4;
      }else if(a==1 & b==1 & c==0 & d==0){
        return 3;
      }else if(a==1 & b==1 & c==0 & d==1){
        return 2;
        }else if(a==1 & b==1 & c==1 & d==0){
        return 1;
      }else if(a==1 & b==1 & c==1 & d==1){
        return 0;
        }
        
    }
void findPosition(int s,int* gridCoord){
  switch(s){
    case 1:
      gridCoord[0]=0;
      gridCoord[1]=0;
      break;
    case 2:
      gridCoord[0]=0;
      gridCoord[1]=1;
      break;
    case 3:
      gridCoord[0]=0;
      gridCoord[1]=2;
      break;
    case 4:
      gridCoord[1]=1;
      gridCoord[0]=0;
      break;
    case 5:
      gridCoord[0]=1;
      gridCoord[1]=1;
      break;
    case 6:
      gridCoord[0]=1;
      gridCoord[1]=2;
      break;
    case 7:
      gridCoord[0]=2;
      gridCoord[1]=0;
      break;
    case 8:
      gridCoord[0]=2;
      gridCoord[1]=1;
      break;
    case 9:
      gridCoord[0]=2;
      gridCoord[1]=2;
      break;
    }
  }
  int flame_dir(int* flame_data){
  int S1=analogRead(s1);
  int S2=analogRead(s2);
  int S3=analogRead(s3);
  int S4=analogRead(s4);
  int S5=analogRead(s5);
  int threshold=700;
  int* degree,val;
  if(S1>threshold&&S2>threshold&&S3>threshold&&S4>threshold&&S5>threshold){
//    Serial.println("60 degree");
    degree=0;
    val=S3;
    flame_data[0]=degree;
    flame_data[1]=val;
  }
  if(S1>threshold&&S2>threshold){
//    Serial.println("15 degree");
    degree=45;
    val=S2;
    flame_data[0]=degree;
    flame_data[1]=val;
  }
  
//  if(S2>threshold&&S3>threshold){
////    Serial.println("45 degree");
//    degree=15;
//    val=S3;
//    flame_data[0]=degree;
//    flame_data[1]=val;
//  }
//  
//  if(S3>threshold&&S4>threshold){
////    Serial.println("75 degree");
//    degree=-15;
//    val=S4;
//    flame_data[0]=degree;
//    flame_data[1]=val;
//  }
  if(S4>threshold&&S5>threshold){
//    Serial.println("105 degree");
    degree=-45;
    val=S4;
    flame_data[0]=degree;
    flame_data[1]=val;
  }
//  if(S1>threshold){
////    Serial.println("0 degree");
//    degree=60;
//    val=S1;
//    flame_data[0]=degree;
//    flame_data[1]=val;
//  }
//  if((S2>threshold)){
////    Serial.println("30 degree");
//    degree=30;
//    val=S2;
//    flame_data[0]=degree;
//    flame_data[1]=val;
//  }
//  
//  if((S3>threshold)){
////    Serial.println("60 degree");
//    degree=0;
//    val=S3;
//    flame_data[0]=degree;
//    flame_data[1]=val;
//  }
//  if((S4>threshold)){
////    Serial.println("105 degree");
//    degree=-30;
//    val=S4;
//    flame_data[0]=degree;
//    flame_data[1]=val;
//  }
//  if(S5>threshold){
////    Serial.println("120 degree");
//    degree=-60;
//    val=S5;
//    flame_data[0]=degree;
//    flame_data[1]=val;
//  }
}
  int robot_align(int angle){
  switch(angle){
    case 0:
      break;
    case 15:
      tankleft();
      delay(160);
      hault();
      break;
    case 30:
      tankleft();
      delay(320);
      hault();
      break;
    case 45:
      tankleft();
      delay(320);
      hault();
      break;
    case 60:
      tankleft();
      delay(640);
      hault();
      break;
    case -15:
      tankright();
      delay(160);
      hault();
      break;
    case -30:
      tankright();
      delay(320);
      hault();
      break;
    case -45:
      tankright();
      delay(320);
      hault();
      break;
    case -60:
      tankright();
      delay(640);
      hault();
      break;
    }
    
  }

 void forward(){
  digitalWrite(leftwheelsf,LOW);
  digitalWrite(leftwheelsb,HIGH);
  digitalWrite(rightwheelsf,LOW);
  digitalWrite(rightwheelsb,HIGH);
  Serial.println("FORWARD");
  }
void hault(){
  digitalWrite(leftwheelsf,LOW);
  digitalWrite(leftwheelsb,LOW);
  digitalWrite(rightwheelsf,LOW);
  digitalWrite(rightwheelsb,LOW);
  Serial.println("HAULT");
  }
void backward(){
  digitalWrite(leftwheelsf,HIGH);
  digitalWrite(leftwheelsb,LOW);
  digitalWrite(rightwheelsf,HIGH);
  digitalWrite(rightwheelsb,LOW);
  Serial.println("BACK");
  }
void tankleft(){
  digitalWrite(leftwheelsf,LOW);
  digitalWrite(leftwheelsb,HIGH);
  digitalWrite(rightwheelsf,HIGH);
  digitalWrite(rightwheelsb,LOW);
  Serial.println("LEFT");
  }
void tankright(){
  digitalWrite(leftwheelsf,HIGH);
  digitalWrite(leftwheelsb,LOW);
  digitalWrite(rightwheelsf,LOW);
  digitalWrite(rightwheelsb,HIGH);
  Serial.println("RIGHT");
  }

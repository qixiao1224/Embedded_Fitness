/************************************************************/
/*      Name:Qixiao Zhang                 NetID:qz1108      */
/*           Basic function description                     */
/*Left button is used to convert between random & fixed mode*/
/*Right button is used to go to next exercise in fixed mode */
/*Right button is not used in random mode                   */
/************************************************************/
/*Red   LED represents Sit-up                               */
/*Green LED represents Push-up                              */
/*Blue  LED represnets Jumping jack                         */
/*Violet LED represents Squat                               */
/*Single color shining means this exercise is done          */
/*Rainbow blinking means it's finished                      */
/************************************************************/
/*The times you want to do in an exercise can be changed    */
/*  by changing value of variable "total"                   */
/************************************************************/
#include <Adafruit_CircuitPlayground.h>
#define total 10.0

float baseline[3];
float x,y,z;

bool S0[4]={0,0,0,0};// for sit-up
bool S1[3]={0,0,0};// for push-up
bool S2[5]={0,0,0,0,0};// for jumping jack
bool S3[5]={0,0,0,0,0};// for squat
bool SITUP_0,PUSHUP_0,JUMPJ_0,SQUAT_0;//to know what exercise we are doing
bool SITUP_1,PUSHUP_1,JUMPJ_1,SQUAT_1;//to know what exercise we are doing
bool Mode;//

char count[4];//put four counters in an array

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
  memset(count,total,4);

  SITUP_0=0;//for random mode
  PUSHUP_0=0;
  JUMPJ_0=0;
  SQUAT_0=0;

  SITUP_1=1;//for fixed mode
  PUSHUP_1=0;
  JUMPJ_1=0;
  SQUAT_1=0;
  Mode=0;;//random mode is 0(OFF)
          //fixed mode is 1(ON)
  pinMode(13, OUTPUT);
}

void loop() {
  /*read the accelerometer*/
  read_motion(&x,&y,&z);
  
  /*       Choose Detection Mode       */
  if(CircuitPlayground.leftButton()==1){
    delay(500);
    //random mode is 0(OFF)
    //fixed  mode is 1(ON)
    if(Mode==0){
      Mode=1;
    }
    else{
      Mode=0;
    }
  }
  
  /* Main Dectection procedure*/
  if (Mode==0){
    digitalWrite(13, LOW);
    /*Random Sequence*/
    random_sequence_mode();
  }
  else{
    digitalWrite(13, HIGH);
   /*Fixed sequence*/
    fixed_sequence_mode();
   /*right button function in fixed sequence mode*/
    right_button_function();
  }
  /*TESTING IN SERIAL*/
  Serial.print("X: ");
  Serial.print(x);
  Serial.print("  Y: ");
  Serial.print(y);
  Serial.print("  Z: ");
  Serial.println(z);
  Serial.println(count[0],DEC);
  Serial.println(count[1],DEC);
  Serial.println(count[2],DEC);
  Serial.println(count[3],DEC);
//  Serial.print(SITUP);
//  Serial.print(PUSHUP);
//  Serial.print(JUMPJ);
//  Serial.println(SQUAT);
//  Serial.println(Mode);
  /*Delay to slow down refreshing*/
  delay(50);
  
  /*finish*/
  if (count[0]==0&&count[1]==0&&count[2]==0&&count[3]==0){
    LED_finish();
    delay(1000);
    setup();
  }
}

void fixed_sequence_mode(){
      if (start_count_situp()==0&&SITUP_1==1){
      SITUP_1=0;
      PUSHUP_1=1;
      LED_flash(255,0,0);
    }
    if (PUSHUP_1==1){
      if(start_count_pushup()==0){
        PUSHUP_1=0;
        JUMPJ_1=1;
        LED_flash(0,255,0);
      }
    }
    if (JUMPJ_1==1){
      if (start_count_jumpjack()==0){
        JUMPJ_1=0;
        SQUAT_1=1;
        LED_flash(0,0,255);
      }
    }
    if (SQUAT_1==1){
      if (start_count_squat()==0){
        SQUAT_1=0;
        LED_flash(255,0,255); 
      }
    }
}

void random_sequence_mode(){
    if(start_count_situp()==0&&SITUP_0==0){
      LED_flash(255,0,0);
      SITUP_0=1;
    }
    if (start_count_pushup()==0&&PUSHUP_0==0){
      LED_flash(0,255,0);
      PUSHUP_0=1;
    }
    if (start_count_jumpjack()==0&&JUMPJ_0==0){
      LED_flash(0,0,255);
      JUMPJ_0=1;
    }
    if (start_count_squat()==0&SQUAT_0==0){
      LED_flash(255,0,255);
      SQUAT_0=1;
    }
}

void right_button_function(){
    if(SITUP_1==1&&CircuitPlayground.rightButton()==1){
    SITUP_1=0;
    PUSHUP_1=1;
    //count[0]=0;
    CircuitPlayground.clearPixels();
    delay(500);
  }
  if(PUSHUP_1==1&&CircuitPlayground.rightButton()==1){
    PUSHUP_1=0;
    JUMPJ_1=1;
    //count[1]=0;
    CircuitPlayground.clearPixels();
    delay(500);
  }
  if(JUMPJ_1==1&&CircuitPlayground.rightButton()==1){
    JUMPJ_1=0;
    SQUAT_1=1;
    //count[2]=0;
    CircuitPlayground.clearPixels();
    delay(500);
  }
  if(SQUAT_1==1&&CircuitPlayground.rightButton()==1){
    SQUAT_1=0;
    SITUP_1=1;
    //count[3]=0;
    CircuitPlayground.clearPixels();
    delay(500);
  }
}

/*count and LED setting for four exercises*/
bool start_count_situp(){
  char i;
     if (SITUP_1==1&&Mode==1){
        for (i=0;i<=9.0*count[0]/total;i++){
          CircuitPlayground.setPixelColor(i, 255, 0,  0);
                   }
        for (i=9.0*count[0]/total+1;i<=9;i++){
          CircuitPlayground.setPixelColor(i, 0, 0,  0);
        }
     }
     if (count[0]==0){
      return 0;
     }
     if (is_situp()){
        count[0]=count[0]-1;
        for (i=0;i<=9.0*count[0]/total;i++){
          CircuitPlayground.setPixelColor(i, 255, 0,  0);
                   }
        for (i=9.0*count[0]/total+1;i<=9;i++){
          CircuitPlayground.setPixelColor(i, 0, 0,  0);
        }
     }
     return 1;
}

bool start_count_pushup(){
  char i;
     if (PUSHUP_1==1&&Mode==1){
        for (i=0;i<=9.0*count[1]/total;i++){
          CircuitPlayground.setPixelColor(i, 0, 255,  0);
        }
        for (i=9.0*count[1]/total+1;i<=9;i++){
          CircuitPlayground.setPixelColor(i, 0, 0,  0);
        }
     }
     if (count[1]==0){
      return 0;
     }
     if (is_pushup()){
        count[1]=count[1]-1;
        for (i=0;i<=9.0*count[1]/total;i++){
          CircuitPlayground.setPixelColor(i, 0, 255,  0);
        }
        for (i=9.0*count[1]/total+1;i<=9;i++){
          CircuitPlayground.setPixelColor(i, 0, 0,  0);
        }
     }
     return 1;  
}

bool start_count_jumpjack(){
  char i;
     if (JUMPJ_1==1&&Mode==1){
        for (i=0;i<=9.0*count[2]/total;i++){
          CircuitPlayground.setPixelColor(i, 0, 0,  255);
        }
        for (i=9.0*count[2]/total+1;i<=9;i++){
          CircuitPlayground.setPixelColor(i, 0, 0,  0);
        }
     }
     if (count[2]==0){
      return 0;
     }
     if (is_jumpjack()){
        count[2]=count[2]-1;
        for (i=0;i<=9.0*count[2]/total;i++){
          CircuitPlayground.setPixelColor(i, 0, 0,  255);
        }
        for (i=9.0*count[2]/total+1;i<=9;i++){
          CircuitPlayground.setPixelColor(i, 0, 0,  0);
        }
     }
     return 1;
}

bool start_count_squat(){
  char i;
     if (SQUAT_1==1&&Mode==1){
        for (i=0;i<=9.0*count[3]/total;i++){
          CircuitPlayground.setPixelColor(i, 255, 0,  255);
        }
        for (i=9.0*count[3]/total+1;i<=9;i++){
          CircuitPlayground.setPixelColor(i, 0, 0,  0);
        }
     }
     if (count[3]==0){
      return 0;
     }
     if (is_squat()){
        count[3]=count[3]-1;
        for (i=0;i<=9.0*count[3]/total;i++){
          CircuitPlayground.setPixelColor(i, 255, 0,  255);
        }
        for (i=9.0*count[3]/total+1;i<=9;i++){
          CircuitPlayground.setPixelColor(i, 0, 0,  0);
        }
     }
     return 1;
}

/**************************************/
/*situp Detection*/
bool is_situp(){
  bool SSU1,SSU2,SSU3,SSU4;//State of Sit-Up 1
  SSU1 = (x<0&&z>8)?1:0;
  SSU2 = (x>8&&y>1&&z<1)?1:0;
  SSU3 = (z>=10)?1:0;
  SSU4 = (x<=-2)?1:0;
  if (SSU1){S0[0]=1;}
  if (S0[0]==1){if (SSU2){S0[1]=1;}}
  if (S0[1]==1){if (SSU3){S0[2]=1;}}
  if (S0[2]==1){if (SSU4){S0[3]=1;}}
  if (S0[3]==1){memset(S0,0,4);return 1;}
  return 0;
  }
/**************************************/

/**************************************/
/*push up detection*/
bool is_pushup(){
  bool SPU1,SPU2,SPU3;
  SPU1=(x>7&&x<10&&z<-5)?1:0;
  SPU2 =(x>6&&z<-8) ?1:0;
  SPU3 = (x>7&&z>-5)?1:0;
  if (SPU1){S1[0]=1;}
  if (S1[0]==1){if (SPU2){S1[1]=1;}}
  if (S1[1]==1){if (SPU3){S1[2]=1;}}
  if (S1[2]==1){memset(S1,0,4);return 1;}
  return 0;
  }
/**************************************/

/**************************************/
/*Jumping Jack Detection*/
bool is_jumpjack(){
bool SJJ1,SJJ2;//State of Jumping Jack 1 and 2
SJJ1=(x>=19.5)?1:0;
SJJ2=(x <= 5) ?1:0;//Determine the state right now
if (SJJ1){S2[0]=1;}
if (S2[0]==1){if(SJJ2){S2[1]=1;}}
if (S2[1]==1){if(SJJ1){S2[2]=1;}}
if (S2[2]==1){if(SJJ2){S2[3]=1;}}
if (S2[3]==1){if(SJJ1){S2[4]=1;}}
if (S2[4]==1){memset(S2,0,5);return 1;}
return 0;
}
/**************************************/

/**************************************/
/*Squat Detection*/
bool is_squat(){
  bool SSQ0,SSQ1,SSQ2,SSQ3,SSQ4,SSQ5;//State of Squat
  SSQ0 = (x<18&&x>4)?1:0;
  SSQ1 = (x>8&&z>1)?1:0;
  SSQ2 = (x<7) ?1:0;
  SSQ3 = (z<-1)?1:0;
  SSQ4 = (x>14)?1:0;
  SSQ5 = (z>1) ?1:0;
  if (SSQ0 == 0){memset(S3,0,5);return 0;}
  if (SSQ1){S3[0]=1;}
  if (S3[0]==1){if(SSQ2){S3[1]=1;}}
  if (S3[1]==1){if(SSQ3){S3[2]=1;}}
  if (S3[2]==1){if(SSQ4){S3[3]=1;}}
  if (S3[3]==1){if(SSQ4){S3[4]=1;}}
  if (S3[4]==1){memset(S3,0,5);return 1;}
  return 0;
  }
/**************************************/


/*Works when we finish our exercises*/
void LED_finish(){
  char i;
  for (i=1;i<5;i++){
      CircuitPlayground.setPixelColor(0, 255,   0,  0);delay(50);
      CircuitPlayground.setPixelColor(1, 255, 180,  0);delay(50);
      CircuitPlayground.setPixelColor(2, 255, 255,  0);delay(50);
      CircuitPlayground.setPixelColor(3, 130, 255,  0);delay(50);
      CircuitPlayground.setPixelColor(4,   0, 255,  0);delay(50);
      CircuitPlayground.setPixelColor(5,   0, 255,166);delay(50);
      CircuitPlayground.setPixelColor(6,   0, 136,255);delay(50);
      CircuitPlayground.setPixelColor(7,   0,   0,255);delay(50);
      CircuitPlayground.setPixelColor(8, 130, 0,  255);delay(50);
      CircuitPlayground.setPixelColor(9, 253,  19,248);delay(50);
      delay(200);
      CircuitPlayground.clearPixels();
  }
}

/*flashing after one entire set of exercises*/
void LED_flash(int x, int y, int z){
  char i;
  for (i=0;i<10;i++){
    CircuitPlayground.setPixelColor(i, x, y,  z);
    delay(50);
        }
  for (i=9;i>=0;i--){
    CircuitPlayground.setPixelColor(i, 0, 0,  0);
    delay(50);
        }
  for (i=0;i<10;i++){
    CircuitPlayground.setPixelColor(i, x, y,  z);
    delay(50);
        }
  for (i=0;i<10;i++){
    CircuitPlayground.setPixelColor(i, x, y,  z);
        }
  delay(100);
  CircuitPlayground.clearPixels();
  delay(500);
}

/*read motion from accelorameter*/
void read_motion(float *x,float *y,float *z){
  *x=CircuitPlayground.motionX();
  *y=CircuitPlayground.motionY();
  *z=CircuitPlayground.motionZ();
}

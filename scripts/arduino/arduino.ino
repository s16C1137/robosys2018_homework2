#include<MsTimer2.h>
#include<Arduino.h>
#include<ros.h>
#include<std_msgs/Int16.h>
ros::NodeHandle nh;

volatile boolean tim1msF = false;
const int pin5=11, pin6=12, pin7=6, pin8=7; // pin5,6=right　//pin6,7=left
int count_time=0;

void timer1mS(){
  tim1msF = true;
}
int Timer(int n){
  MsTimer2::set(1, timer1mS);
  MsTimer2::start();
  while(count_time <= n){
    if(tim1msF){
      count_time = count_time + 1;
      tim1msF = false;
    }
  }
  MsTimer2::stop();
  tim1msF = false;
  count_time = 0;
  return 0;
}

void STOP(){
     analogWrite(pin5,0);
     analogWrite(pin6,0);
     analogWrite(pin7,0);
     analogWrite(pin8,0); 
}

void straight(){
     analogWrite(pin5,90);
     analogWrite(pin6,0);
     analogWrite(pin7,115);
     analogWrite(pin8,0);  
}

void back(){
     analogWrite(pin5,0);
     analogWrite(pin6,90);
     analogWrite(pin7,0);
     analogWrite(pin8,115);  
}

void turn_right(){
     analogWrite(pin5,90);
     analogWrite(pin6,0);
     analogWrite(pin7,185);
     analogWrite(pin8,0); 
}

void turn_left(){
     analogWrite(pin5,160);
     analogWrite(pin6,0);
     analogWrite(pin7,115);
     analogWrite(pin8,0); 
}

void twist_right(){
     analogWrite(pin5,0);
     analogWrite(pin6,160);
     analogWrite(pin7,185);
     analogWrite(pin8,0); 
}

void twist_left(){
     analogWrite(pin5,185);
     analogWrite(pin6,0);
     analogWrite(pin7,0);
     analogWrite(pin8,160); 
}

void order1(const std_msgs::Int16 &message){
  const int control = message.data;
  if(control == 0){
    STOP();
  }
  else if(control == 1){
    straight();
  }
  else if(control == 2){
    back();
  }
  else if(control == 3){
    turn_right();
  }
  else if(control == 4){
    turn_left();
  }
  else if(control == 5){
    twist_right();
  }
  else if(control == 6){
    twist_left();
  }
}
ros::Subscriber<std_msgs::Int16> Destination("/control", &order1);

void setup(){
  pinMode(pin5,OUTPUT); 
  pinMode(pin6,OUTPUT); 
  pinMode(pin7,OUTPUT); 
  pinMode(pin8,OUTPUT); 
  nh.initNode();
  nh.subscribe(Destination);
}

void loop(){
  nh.spinOnce();
  Timer(1);
}

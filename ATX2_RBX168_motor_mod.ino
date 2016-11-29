/*
 * Inex with POP-168 Mod Test
 * by: gHil / www.circuit-help.com.ph
 * 
 * Test code for Inex with moded 15A motor driver
 * Inex with POP - 168 config
 * PINOUT of Mod
 * 3 | 5 | 6 | 5V | GND | 9 | NOT USE PINS 
 * PIN 5 & 6 are PWM pins
 * 
 * 11/29/2016
 * {
 * Added Mod for ATX2 
 * Use the middle Motor Driver control pins
 * PINOUT of Mod
 * GND | DIR2 | VCC | DIR1 | PWM2 | VCC | PWM1 | VCC
 * PIN 5 & 6 are PWM pins
 */
 
// pin configurations
// for POP-168
// uint8_t MTR_PWM_CTRL_1 = 5;     //MTR_DIR_CTRL_1 Speed Control
// uint8_t MTR_PWM_CTRL_2 = 6;     //MTR_DIR_CTRL_2 Speed Control
// uint8_t MTR_DIR_CTRL_1 = 3;    //MTR_DIR_CTRL_1 Direction Control
// uint8_t MTR_DIR_CTRL_2 = 9;    //MTR_DIR_CTRL_2 Direction Control 

// pin configurations
uint8_t MTR_PWM_CTRL_1 = 20;     //MTR_DIR_CTRL_1 Speed Control
uint8_t MTR_PWM_CTRL_2 = 19;     //MTR_DIR_CTRL_2 Speed Control
uint8_t MTR_DIR_CTRL_1 = 17;    //MTR_DIR_CTRL_1 Direction Control
uint8_t MTR_DIR_CTRL_2 = 16;    //MTR_DIR_CTRL_2 Direction Control 

uint8_t motorPins[]={
  MTR_PWM_CTRL_1,
  MTR_PWM_CTRL_2,
  MTR_DIR_CTRL_1,
  MTR_DIR_CTRL_1
};

// switching delay for motor driver protection
unsigned long SW_DELAY_PROTECT = 200;

// function prototypes
void stop();
void advance(uint8_t speedLeft, uint8_t speedRight);
void backOff(uint8_t speedLeft, uint8_t speedRight);
void turnLeft(uint8_t speedLeft, uint8_t speedRight);
void turnRight(uint8_t speedLeft, uint8_t speedRight);

// setup pins
void setup(void) {
  for (uint8_t x = 0; x < 4; x++){
    pinMode(motorPins[x], OUTPUT);     
  }
} 

// main program loop
void loop(void) 
{ 
  //motor test loop
  advance(150, 150);
  delay(2000);
  
  stop();
  // delay for short time to avoid damage on motor driver
  delay(SW_DELAY_PROTECT);
  
  backOff(150,150);
  delay(2000);

  stop();
  // delay for short time to avoid damage on motor driver
  delay(SW_DELAY_PROTECT);
  
  turnLeft(150,150);
  delay(2000);

  stop();
  // delay for short time to avoid damage on motor driver
  delay(SW_DELAY_PROTECT);
  
  turnRight(150,150);
  delay(2000); 
  
  stop();
  // delay for short time to avoid damage on motor driver
  delay(SW_DELAY_PROTECT);
}

// function definitions
// stop motors
void stop(void){
  digitalWrite(MTR_PWM_CTRL_1,LOW);   
  digitalWrite(MTR_PWM_CTRL_2,LOW);      
}

// forward motors
void advance(uint8_t speedLeft, uint8_t speedRight)          //Move forward
{
  analogWrite (MTR_PWM_CTRL_1,speedLeft);      //PWM Speed Control
  digitalWrite(MTR_DIR_CTRL_1,HIGH);    
  analogWrite (MTR_PWM_CTRL_2,speedRight);    
  digitalWrite(MTR_DIR_CTRL_2,HIGH);
}  

// move backwards
void backOff (uint8_t speedLeft, uint8_t speedRight)          //Move backward
{
  analogWrite (MTR_PWM_CTRL_1,speedLeft);
  digitalWrite(MTR_DIR_CTRL_1,LOW);   
  analogWrite (MTR_PWM_CTRL_2,speedRight);    
  digitalWrite(MTR_DIR_CTRL_2,LOW);
}

// turn left
void turnLeft (uint8_t speedLeft, uint8_t speedRight)             //Turn Left
{
  analogWrite (MTR_PWM_CTRL_1,speedLeft);
  digitalWrite(MTR_DIR_CTRL_1,LOW);    
  analogWrite (MTR_PWM_CTRL_2,speedRight);    
  digitalWrite(MTR_DIR_CTRL_2,HIGH);
}

// turn right
void turnRight (uint8_t speedLeft, uint8_t speedRight)             //Turn Right
{
  analogWrite (MTR_PWM_CTRL_1,speedLeft);
  digitalWrite(MTR_DIR_CTRL_1,HIGH);    
  analogWrite (MTR_PWM_CTRL_2,speedRight);    
  digitalWrite(MTR_DIR_CTRL_2,LOW);
}

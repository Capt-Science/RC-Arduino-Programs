/**
 * NAV LIGHTS!
 * By Capt Science
 * See this in action: https://youtu.be/zY_mo5g1awY
 * designed to have 3 strobes, one on each wing tip and one in the rear (STROBE A B C)
 * designed to have 2 fading marker lights on each wing tip (NAV A B)
 * designed to have 1 landing lights trigger fwd facing white light
 * Ver 2
 * This version has variables that can be changed at the begining to affect the whole program
 * Changed the fading effect of nav lights to solid when landing 
 */

// Pin Definitions---------------- pin arrangement can change on board build
  #define NAV_A_PIN 6
  #define NAV_B_PIN 5
  #define STROBE_A_PIN 7
  #define STROBE_B_PIN 4
  #define STROBE_C_PIN 9
  #define LANDING_PIN 8
  
  #define LIGHTS_INPUT 2
  #define LIGHTS_IRQ 0 // IRQ attached to input pin


// PWM settings---------------------------- calibrate in debug mode
  double channel;
  #define NO_LIGHTS_THRESH 1000 //threshold for no lights to turn on
  #define RUNN_LIGHTS_THRESH 1375 // threshold for nav lights on
  #define ALL_LIGHTS_ON 1900 // threshold for all lights on

// Fade Settings------------------
  #define FADE_MIN 0 // Minimum fade level for beacon (0-255) will varry based on FET used to drive lights lower is dimmer
  #define FADE_MAX 150 // Maximum fade level for beacon (0-255) will vary based on fets used to drive lights higher is brighter
  #define FADE_INTERVAL 2000 // Fade step interval, in microseconds (lower numbers = faster fade)
  #define FADE_RATE 5 // adjustment to even out fade and use full inteval (changes the increment)
  #define RATE 10 // slows things down with bigger number adds a delay at the end of the fade routine in millis
  #define LANDING_LEVEL 150 // sets the nav lights to solid, not full power to keep from melting the leds
// Strobe Settings---------------
  #define STROBE_BLINK_INTERVAL 1500 // Blink interval for strobe light in milliseconds
  #define STROBE_ON_TIME 60  // this number is half the desired 120
  #define STROBE_GAP_TIME 120
  
// Variables Declerations---------
  unsigned long currentTime;
  unsigned long lastFadeTime = 0;
  int currentFade = FADE_MIN;
  int fadeDirection = 1;
  unsigned long lastStrobeTime = 0;
  unsigned long lastStrobeCTime = 0;




void setup() {
  // put your setup code here, to run once:

// Declare Output Pins---------------------
  pinMode(NAV_A_PIN, OUTPUT);
  pinMode(NAV_B_PIN, OUTPUT);
  pinMode(STROBE_A_PIN, OUTPUT);
  pinMode(STROBE_B_PIN, OUTPUT);
  pinMode(STROBE_C_PIN, OUTPUT);
  pinMode(LANDING_PIN, OUTPUT);

// Declare input pins--------------------------
  pinMode(LIGHTS_INPUT, INPUT); //nav lights channel


// DEBUG LOOP TO send values to serial monitor
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

unsigned long currentTime = millis();
channel = pulseIn(LIGHTS_INPUT, HIGH);

//DEBUG LOOP to send values to serial monitor
  Serial.println("main_loop");
  Serial.println(channel);
  Serial.println(currentFade);
  Serial.println(fadeDirection);


// check switch poition no lights+++++++++++++++++++++++++++++++++++++++++++
  while(channel <= NO_LIGHTS_THRESH){
    channel = pulseIn(LIGHTS_INPUT, HIGH);
//    Serial.println(channel);
//    Serial.println("while loop");
    digitalWrite(13,HIGH);
    delay(60);
    digitalWrite(13,LOW);
    digitalWrite(LANDING_PIN, LOW); //turn off 
    digitalWrite(STROBE_A_PIN, LOW); //turn off 
    digitalWrite(STROBE_B_PIN, LOW); //turn off 
    digitalWrite(STROBE_C_PIN, LOW); //turn off 
    digitalWrite(NAV_A_PIN, LOW); //turn off 
    digitalWrite(NAV_B_PIN, LOW); //turn off
    delay(300);
    digitalWrite(13,HIGH);
    delay(60);
    digitalWrite(13,LOW);
    delay(300);
  }
 //END check switch poition no lights+++++++++++++++++++++++++++++++++++++

//check for landing lights---------------------------------------
while (channel > ALL_LIGHTS_ON){
  channel = pulseIn(LIGHTS_INPUT, HIGH);
  unsigned long currentTime = millis();
  digitalWrite(LANDING_PIN, HIGH);
  digitalWrite(NAV_A_PIN, LANDING_LEVEL);
  digitalWrite(NAV_B_PIN, LANDING_LEVEL);
  if ((currentTime - lastStrobeTime) > STROBE_BLINK_INTERVAL) {
  digitalWrite(STROBE_A_PIN, HIGH);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_B_PIN, HIGH);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_A_PIN, LOW);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_B_PIN, LOW);
    delay(STROBE_GAP_TIME);
    digitalWrite(STROBE_A_PIN, HIGH);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_B_PIN, HIGH);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_A_PIN, LOW);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_B_PIN, LOW);
    digitalWrite(STROBE_C_PIN, HIGH);
    delay(STROBE_ON_TIME);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_C_PIN, LOW);
    delay(STROBE_GAP_TIME);
    digitalWrite(STROBE_C_PIN, HIGH);
    delay(STROBE_ON_TIME);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_C_PIN, LOW);
  lastStrobeTime = currentTime;
    }
}
if (channel < ALL_LIGHTS_ON){
  digitalWrite(LANDING_PIN, LOW);
}

// run a fade loop -------------------------
  doFade();

// check to see if we need to strobe--------
  if ((currentTime - lastStrobeTime) > STROBE_BLINK_INTERVAL) {
  doStrobe();
  lastStrobeTime = currentTime;
    }


//END continuous loop
}
// _+_+_+_+_+_+_+_+_+_+_+_+_define functions_+_+_+_+_+_+_+_+_+_+

// DO THE FADE+++++++++++++++++++++++++++++++++++++++
void doFade()
{
  currentFade += fadeDirection*FADE_RATE;
  // if we have hit the max - flash beacon and flip
  if (currentFade >= FADE_MAX || currentFade <= FADE_MIN){
    if (fadeDirection == 1) {
//    analogWrite(NAV_A_PIN, 255);
//    analogWrite(NAV_B_PIN, 0);
//    delay(360);
    analogWrite(NAV_A_PIN, FADE_MAX-currentFade+FADE_MIN);
    analogWrite(NAV_B_PIN, FADE_MIN);
    } else {
//    analogWrite(NAV_B_PIN, 255);
//    analogWrite(NAV_A_PIN, 0);
//    delay(360);
    analogWrite(NAV_B_PIN, FADE_MAX-currentFade);
    analogWrite(NAV_A_PIN, FADE_MIN);
    }
  fadeDirection *= -1;
  }
  analogWrite(NAV_A_PIN, currentFade);
  analogWrite(NAV_B_PIN, FADE_MAX-currentFade+FADE_MIN);
  delay(RATE);
}

// Do STROBE Function----------------------
void doStrobe(){
    digitalWrite(STROBE_A_PIN, HIGH);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_B_PIN, HIGH);
    delay(STROBE_ON_TIME);
    doFade();
    digitalWrite(STROBE_A_PIN, LOW);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_B_PIN, LOW);
    delay(STROBE_GAP_TIME);
    doFade();
    digitalWrite(STROBE_A_PIN, HIGH);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_B_PIN, HIGH);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_A_PIN, LOW);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_B_PIN, LOW);
    doFade();
    doFade();
    digitalWrite(STROBE_C_PIN, HIGH);
    delay(STROBE_ON_TIME);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_C_PIN, LOW);
    delay(STROBE_GAP_TIME);
    digitalWrite(STROBE_C_PIN, HIGH);
    delay(STROBE_ON_TIME);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_C_PIN, LOW);
    channel = pulseIn(LIGHTS_INPUT, HIGH);
}


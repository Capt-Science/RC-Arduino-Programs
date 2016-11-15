/**
 * NAV LIGHTS!
 * By Capt Science
 * My Youtube channel: https://www.youtube.com/channel/UCzMBuRdlzq0uCY1ky17SZiA
 */

// Pin Definitions---------------- pin arrangement can change on board build

  #define STROBE_A_PIN 7
  #define STROBE_B_PIN 4

// Strobe Settings---------------
  #define STROBE_BLINK_INTERVAL 1500 // Blink interval for strobe light in milliseconds
  #define STROBE_ON_TIME 120
  #define STROBE_GAP_TIME 90
  
// Variables Declerations---------
  unsigned long currentTime;
  unsigned long lastStrobeTime = 0;
  unsigned long lastStrobeCTime = 0;




void setup() {
  // put your setup code here, to run once:

// Declare Output Pins---------------------

  pinMode(STROBE_A_PIN, OUTPUT);
  pinMode(STROBE_B_PIN, OUTPUT);


// Declare input pins--------------------------



// DEBUG LOOP TO send values to serial monitor
//  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

unsigned long currentTime = millis();

//DEBUG LOOP to send values to serial monitor
//  Serial.println("main_loop");
//  Serial.println(channel);

// check to see if we need to strobe--------
  if ((currentTime - lastStrobeTime) > STROBE_BLINK_INTERVAL) {
  doStrobe();
  lastStrobeTime = currentTime;
    }


//END continuous loop
}
// _+_+_+_+_+_+_+_+_+_+_+_+_define functions_+_+_+_+_+_+_+_+_+_+

// Do STROBE Function----------------------
void doStrobe(){
    digitalWrite(STROBE_A_PIN, HIGH);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_B_PIN, HIGH);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_A_PIN, LOW);
    delay(STROBE_GAP_TIME);
    digitalWrite(STROBE_B_PIN, LOW);
    delay(STROBE_GAP_TIME);
    digitalWrite(STROBE_A_PIN, HIGH);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_B_PIN, HIGH);
    delay(STROBE_ON_TIME);
    digitalWrite(STROBE_A_PIN, LOW);
    delay(STROBE_GAP_TIME);
    digitalWrite(STROBE_B_PIN, LOW);
    delay(STROBE_GAP_TIME);
    digitalWrite(13,HIGH);
    delay(STROBE_ON_TIME);
    digitalWrite(13,LOW);
    delay(STROBE_GAP_TIME);
    digitalWrite(13,HIGH);
    delay(STROBE_ON_TIME);
    digitalWrite(13,LOW);
    
}


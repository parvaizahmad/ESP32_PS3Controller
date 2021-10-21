#include <Ps3Controller.h>

#define in1       23   //14 
#define in2       22   //12 
#define in3       19   //13 
#define in4       18  //15 
#define enA       17   //17 
#define enB       16   //16 

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int ledChannel2 = 1;
const int resolution = 8;
int speedSet = 100;

void moveControl(int x, int y)
{
  int analogWriteX = map(abs(x), 0, 127, 10, speedSet);
  int analogWriteY = map(abs(y), 0, 127, 10, speedSet);
//Move Forward
    if(y <= -10)
    {
        Serial.println("Moving Forward");
        ledcWrite(ledChannel, analogWriteY);
        ledcWrite(ledChannel2, analogWriteY);
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
    }


//Move Forward Right
    if(x >= 10 && y <= -10)
    {
        Serial.println("Moving Forward Right");
        ledcWrite(ledChannel, analogWriteX);
        ledcWrite(ledChannel2, analogWriteY);
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
    }

//Move Forward Left
    if(x <= -10 && y <= -10)
    {
        Serial.println("Moving Forward Left");
        ledcWrite(ledChannel, analogWriteY);
        ledcWrite(ledChannel2, analogWriteX);
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
    }

//No Move
    if(y == 0 && x ==0)
    {
        Serial.println("STOP");
        ledcWrite(ledChannel, analogWriteY);
        ledcWrite(ledChannel2, analogWriteY);
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
    }

//Move Backward
    if(y >= 10 && x <= 10)
    {
        Serial.println("Moving Backward");
        ledcWrite(ledChannel, analogWriteY);
        ledcWrite(ledChannel2, analogWriteY);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
    }

//Move Backward Right
    else if(y >= 10 && x >= 10)
    {
        Serial.println("Moving Backward Right");
        ledcWrite(ledChannel, analogWriteX);
        ledcWrite(ledChannel2, analogWriteY);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
    }

//Move Backward Left
    if(y >= 10 && x <= -10)
    {
        Serial.println("Moving Backward Left");
        ledcWrite(ledChannel, analogWriteY);
        ledcWrite(ledChannel2, analogWriteX);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
    }
}


typedef struct buttonsState {
  // Right side buttons data
  bool crossBtn = false;
  bool squareBtn = false;
  bool triangleBtn = false;
  bool circleBtn = false;
  // Left side buttons data
  bool upBtn = false;
  bool rightBtn = false;
  bool downBtn = false;
  bool leftBtn = false;
  // Right shoulder and trigger buttons
  bool rShoulderBtn = false;
  bool rShoulderTrigBtn = false;
  
  //Left shoulder and trigger buttnons
  bool lShoulderBtn = false;
  bool lShoulderTrigBtn = false;

  // Right Joy Stick
  int rightXAxis = 0;
  int rightYAxis = 0;
  bool rightJoyBtn = false;

  // Left Joy Stick
  int leftXAxis = 0;
  int leftYAxis = 0;
  bool leftJoyBtn = false;

  // Special buttons
  bool selectBtn = false;
  bool startBtn = false;
  bool ps3Btn = false;

  // Battery Level
  int batteryLevel = 0;
  
  
  
};

struct buttonsState currentState;

void notify()
{
    //--- Digital cross/square/triangle/circle button events ---
    if( Ps3.event.analog_changed.button.cross > 200 ) currentState.crossBtn = true;
    if( Ps3.event.analog_changed.button.cross < 100 ) currentState.crossBtn = false;

    if( Ps3.event.analog_changed.button.square > 200 ) currentState.squareBtn = true;
    if( Ps3.event.analog_changed.button.square < 100 < 100 ) currentState.squareBtn = false;

    if( Ps3.event.analog_changed.button.triangle > 200 ) currentState.triangleBtn = true;
    if( Ps3.event.analog_changed.button.triangle < 100 ) currentState.triangleBtn = false;

    if( Ps3.event.analog_changed.button.circle > 200 ) currentState.circleBtn = true;
    if( Ps3.event.analog_changed.button.circle < 100 ) currentState.circleBtn = false;

    //--------------- Digital D-pad button events --------------
    if( Ps3.event.analog_changed.button.up > 200 ) currentState.upBtn = true;
    if( Ps3.event.analog_changed.button.up < 100 ) currentState.upBtn = false;

    if( Ps3.event.analog_changed.button.right > 200 ) currentState.rightBtn = true;
    if( Ps3.event.analog_changed.button.right < 100 ) currentState.rightBtn = false;

    if( Ps3.event.analog_changed.button.down > 200 ) currentState.downBtn = true;
    if( Ps3.event.analog_changed.button.down < 100 ) currentState.downBtn = false;

    if( Ps3.event.analog_changed.button.left > 200 ) currentState.leftBtn = true;
    if( Ps3.event.analog_changed.button.left < 100 ) currentState.leftBtn = false;

    //------------- Digital shoulder button events -------------
    if( Ps3.event.analog_changed.button.l1 > 200 ) currentState.lShoulderBtn = true;
    if( Ps3.event.analog_changed.button.l1 < 100 ) currentState.lShoulderBtn = false;

    if( Ps3.event.analog_changed.button.r1 > 200 ) currentState.rShoulderBtn = true;
    if( Ps3.event.analog_changed.button.r1 < 100 ) currentState.rShoulderBtn = false;

    //-------------- Digital trigger button events -------------
    if( Ps3.event.analog_changed.button.l2 > 200 ) currentState.lShoulderTrigBtn = true;
    if( Ps3.event.analog_changed.button.l2 < 100 ) currentState.lShoulderTrigBtn = false;

    if( Ps3.event.analog_changed.button.r2 > 200 ) currentState.rShoulderTrigBtn = true;
    if( Ps3.event.analog_changed.button.r2 < 100 ) currentState.rShoulderTrigBtn = false;

    //--------------- Digital stick button events --------------
    if( Ps3.event.button_down.l3 ) currentState.leftJoyBtn = true;
    if( Ps3.event.button_up.l3 ) currentState.leftJoyBtn = false;

    if( Ps3.event.button_down.r3 ) currentState.rightJoyBtn = true;
    if( Ps3.event.button_up.r3 ) currentState.rightJoyBtn = false;


    //---------- Digital select/start/ps button events ---------
    if( Ps3.event.button_down.select ) currentState.selectBtn = true;
    if( Ps3.event.button_up.select ) currentState.selectBtn = false;

    if( Ps3.event.button_down.start ) currentState.startBtn = true;
    if( Ps3.event.button_up.start ) currentState.startBtn = false;

    if( Ps3.event.button_down.ps ) currentState.ps3Btn = true;
    if( Ps3.event.button_up.ps ) currentState.ps3Btn = false;

    //---------------- Analog stick value events ---------------
    // Left joy stick
   //if( abs(Ps3.event.analog_changed.stick.lx) > 0 || abs(Ps3.event.analog_changed.stick.ly) > 0 ) {
        currentState.leftXAxis = Ps3.data.analog.stick.lx;
        currentState.leftYAxis = Ps3.data.analog.stick.ly;
//        Serial.print("Left X: ");
//        Serial.println(currentState.leftXAxis);
//        Serial.print("Left Y: ");
//        Serial.println(currentState.leftYAxis);
    //}

    //Right joy stick
   //if( abs(Ps3.event.analog_changed.stick.rx) > 0 || abs(Ps3.event.analog_changed.stick.ry) > 0 ) {
       currentState.rightXAxis = Ps3.data.analog.stick.rx;
       currentState.rightYAxis = Ps3.data.analog.stick.ry;
       Serial.print("Right X: ");
       Serial.println(currentState.rightXAxis);
       Serial.print("Right Y: ");
       Serial.println(currentState.rightYAxis);
   //}

   //---------------------- Battery events ---------------------
    if( currentState.batteryLevel != Ps3.data.status.battery ){
        currentState.batteryLevel = Ps3.data.status.battery;
        Serial.print("The controller battery is ");
        if( currentState.batteryLevel == ps3_status_battery_charging )      Serial.println("charging");
        else if( currentState.batteryLevel == ps3_status_battery_full )     Serial.println("FULL");
        else if( currentState.batteryLevel == ps3_status_battery_high )     Serial.println("HIGH");
        else if( currentState.batteryLevel == ps3_status_battery_low)       Serial.println("LOW");
        else if( currentState.batteryLevel == ps3_status_battery_dying )    Serial.println("DYING");
        else if( currentState.batteryLevel == ps3_status_battery_shutdown ) Serial.println("SHUTDOWN");
        else Serial.println("UNDEFINED");
    }
    

    // printing the state of all the button
    if(currentState.rShoulderBtn) {
      speedSet += 10;
      Serial.print("Speed is : ");
      Serial.println(speedSet);
      if (speedSet >= 255) speedSet = 255;
    }
    if(currentState.rShoulderTrigBtn) {
      speedSet -= 10;
      Serial.print("Speed is : ");
      Serial.println(speedSet);
      if (speedSet <= 100) speedSet = 100;
    }
    moveControl(currentState.rightXAxis, currentState.rightYAxis); // x, y
}

void onConnect(){
    Serial.println("Connected.");
    Ps3.setPlayer(1);
}

void setup()
{
    Serial.begin(115200);

    // configure LED PWM functionalitites
    ledcSetup(ledChannel, freq, resolution);
  
    // attach the channel to the GPIO to be controlled
    ledcAttachPin(enA, ledChannel);
    ledcAttachPin(enB, ledChannel2);

    pinMode(in1, OUTPUT);
    pinMode(in3 , OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in4, OUTPUT);

    digitalWrite(in1, LOW);
    digitalWrite(in3 , LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in4, LOW);

    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);
    Ps3.begin("01:02:03:04:05:06");

    Serial.print("Ready, Waiting for connection");
}

void loop()
{
    if(!Ps3.isConnected()) {
        Serial.print(".");
        delay(1000);
    }

    //delay(2000);
}

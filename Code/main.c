//Mechatronics - Hoppobotamus
//Date - 4/22/16
//Omkar Reddy and Rishabh Berlia

// Libraries
#include "mbed.h"
#include "InterruptIn.h"
#include "device.h"

// Global Variables
Serial pc(USBTX, USBRX);

// Macro Definitions
// Drive System; Motors
#define bot360_steps           260      // Full bot rotation; Sharp turns
#define wheel360_steps         88       // Steps for full wheel revolution

// Vaccuum Gate Servo
#define V_Gate_Period_ms        20
#define V_Gate_Open_width_ms    1.0
#define V_Gate_Close_width_ms   3.0

// Beacon Detector
#define beaconDetectRotateAngle 10
#define BEACON_FREQ_TEST        1200
#define BEACON_BW_TEST          200
#define BEACON_FREQ_CENTER      500
#define BEACON_BW_CENTER        40
#define BEACON_FREQ_RED         1200
#define BEACON_BW_RED           100
#define BEACON_FREQ_BLUE        3000
#define BEACON_BW_BLUE          200
#define BEACON_SCANINTERVAL_MS  3
#define BEACON_SCANINTERVAL_S   0.003
// GPIO Pin Declarations
#define Motor1_A                PTB23
#define Motor1_B                PTA2
#define Motor2_A                PTC2
#define Motor2_B                PTC3
#define Motor_Encoder           PTB9

#define Vaccuum_Switch          PTD1
#define Vaccuum_Gate            PTA1

#define Shooter_A               PTC16
#define Shooter_B               PTC17

#define Beacon                  PTC4

#define TapeFollower_front      PTD0
#define TapeFollower_center     PTD2
#define TapeFollower_back       PTD3

#define Stepper_A               PTB18
#define Stepper_B               PTB19
#define Stepper_C               PTC1
#define Stepper_D               PTC8

// Global Variables; Pin setup
// Motor
DigitalOut M1_A(Motor1_A);
DigitalOut M1_B(Motor1_B);
DigitalOut M2_A(Motor2_A);
DigitalOut M2_B(Motor2_B);
InterruptIn Encoder(Motor_Encoder);
// Vaccuum Switch
//DigitalOut V_Switch(Vaccuum_Switch);
PwmOut V_Switch(Vaccuum_Switch);
// Vaccuum Gate Servo
PwmOut V_Gate(Vaccuum_Gate);
// Shooter
DigitalOut S_A(Shooter_A);
DigitalOut S_B(Shooter_B);
// Beacon Detector
DigitalOut led_RED(LED_RED);
DigitalOut led_GREEN(LED_GREEN);
InterruptIn beaconDetector(Beacon);
Timer beaconTimer;
int detectedFreq;
// Stepper
DigitalOut stepperA(Stepper_A);
DigitalOut stepperB(Stepper_B);
DigitalOut stepperC(Stepper_C);
DigitalOut stepperD(Stepper_D);
// Line follower
InterruptIn linefollower_1(PTD0);
InterruptIn linefollower_2(PTD2);
InterruptIn linefollower_3(PTD3);
bool BLACK_DETECTED = false;
int count = 0;                      // Initializing the count to 0
int requiredSteps = 0;
bool count_done = false;

void stop(){
    M1_A = 0;
    M1_B = 0;
    M2_A = 0;
    M2_B = 0;
}    

/*// decoder IRQ
void triggerTest(){
    if (count <= bot360_steps)
        count++;        // increment the counter and count number of falling edges; because frequency is nothing but a count
    else
        stop();
}
// Turn the Encoder on; Enable interrupts on the encoder pin
void motorEncoderTest(){
    Encoder.fall(&triggerTest);
}*/
void triggerCount(){
    if (count <= requiredSteps)
        count++;        // increment the counter and count number of falling edges; because frequency is nothing but a count
    else{
        stop();
        count = 0;
        //Encoder.fall(NULL);
    }
}
void motorEncoderOn(){
    Encoder.fall(&triggerCount);
}
void forward(int steps){
    requiredSteps = steps;
    motorEncoderOn();
    // M1 clockwise
    M1_A = 1;
    M1_B = 0;
    // M2 anticlockwise
    M2_A = 0;
    M2_B = 1;
}
void backward(int steps){
    requiredSteps = steps;
    motorEncoderOn();    
    // M1 anticlockwise
    M1_A = 0;
    M1_B = 1;
    // M2 clockwise
    M2_A = 1;
    M2_B = 0;
}
void left(int angle){
    int angle_steps = 0;
    // M1 clockwise
    M1_A = 1;
    M1_B = 0;
    // M2 stop
    M2_A = 0;
    M2_B = 0;
}
void sharp_left(int angle){
    requiredSteps = angle * (260/360);
    motorEncoderOn();
    // M1 clockwise
    M1_A = 1;
    M1_B = 0;
    // M2 clockwise
    M2_A = 1;
    M2_B = 0;
}
void right(int angle){
    requiredSteps = angle * (260/360);
    motorEncoderOn();
    // M1 stop
    M1_A = 0;
    M1_B = 0;
    // M2 anticlockwise
    M2_A = 0;
    M2_B = 1;
}
void sharp_right(int angle){
    requiredSteps = angle * (260/360);
    motorEncoderOn();
    // M1 anticlockwise
    M1_A = 0;
    M1_B = 1;
    // M2 anticlockwise
    M2_A = 0;
    M2_B = 1;    
}

void driveSystemTest(){
    forward(10);
    wait(1);
    backward(10);
    wait(1);
    sharp_left(30);
    wait(1);
    sharp_right(30);
    wait(1);
}

// Vaccuum Switch Routines
// Test Routine
void vaccuumSwitchTest(){
    V_Switch = 0.5f;
    /*V_Switch = 1;
    wait(3);
    V_Switch = 0;
    wait(3);*/
}
// Vaccuum On
void vaccuumOn(){
    V_Switch = 1;
}
// Vaccuum Off
void vaccuumOff(){
    V_Switch = 0;
}

// Vaccuum Gate Routines
// Test Routine
void vaccuumGateTest(){
    static bool pwmSet = true;
    if (pwmSet)
        V_Gate.period_ms(V_Gate_Period_ms);
    V_Gate.pulsewidth_ms(V_Gate_Open_width_ms);
    wait(3);
    V_Gate.pulsewidth_ms(V_Gate_Close_width_ms);
    wait(3);
    pwmSet = false;
}
// Setup the PWM of the Vaccuum Gate Servo
void vaccuumGateSetup(){
    V_Gate.period_ms(V_Gate_Period_ms);    
}
// Open the Vaccuum Gate
void vaccuumGateOpen(){
    V_Gate.pulsewidth_ms(V_Gate_Open_width_ms);
}
// Close the Vaccuum Gate
void vaccuumGateClose(){
    V_Gate.pulsewidth_ms(V_Gate_Close_width_ms);
}

// Shooter Routines
// Test Routine
void shooterTest(){
    S_A = 1;
    S_B = 0;
    wait(10);
/*    S_A = 0;
    S_B = 1;
    wait(1);*/
    S_A = 0;
    S_B = 0;
    wait(5);
}
// Shooter On
void shooterOn(){
    S_A = 1;
}
// Shooter Off
void shooterOff(){
    S_A = 0;
}

void testRun(){
        // Scan for Center beacon
    // Rotate towards the center
        sharp_right(2);
    //forward();
            // Forward until the center is reached;
            // When circle reached; Stop movement and Align the line follower sensors; Based on the sensor position- detection and rotation about the wheel has to be figured out
        // Sample Routine
        forward(2);
        sharp_left(2); // assuming, we have sensors on the left side of the Bot; If we have them on the right, use a right();
    vaccuumOn();
    // linefollower();
        forward(4);
        sharp_left(2);
        forward(4);
        sharp_left(2);
        forward(4);
        sharp_left(2);
        forward(2);
        sharp_left(2);
        forward(2);
        sharp_left(2);
    vaccuumOff();
    // stepperAlignment();        
    shooterOn();
    wait(2);
    vaccuumGateOpen();
    wait(15);
    shooterOff();
    vaccuumGateClose();
}

void blackDetected(){
    linefollower_1.fall(NULL);
    stop();
    BLACK_DETECTED = true;
}

void goToCenter(){
    linefollower_1.fall(&blackDetected);
    forward(4);
    while(!BLACK_DETECTED){
    }
}

void rotateBack(int steps){
    int seq_r[8][4] = {
        {1,0,0,1},
        {0,0,0,1},
        {0,0,1,1},
        {0,0,1,0},
        {0,1,1,0},
        {0,1,0,0},
        {1,1,0,0},
        {1,0,0,0}
    };
    int i,j,k;
    // Rotate back
    for (k = 0; k < steps; k++){
        for (i = 0; i < 8 ; i++){
            j = 0;
            stepperA = seq_r[i][j];
            stepperB = seq_r[i][j+1];
            stepperC = seq_r[i][j+2];
            stepperD = seq_r[i][j+3];
            wait_ms(1);
        }
    }
    // End
    stepperA = 0;
    stepperB = 0;
    stepperC = 0;
    stepperD = 0;
}

void rotateStepper(int steps, bool direction){  // direction = true => clockwise(seq_f); direction = false => Counter-clockwise(seq_r);
    int seq_f[8][4] = {
        {1,0,0,0},
        {1,1,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,0,1,0},
        {0,0,1,1},
        {0,0,0,1},
        {1,0,0,1}
    };
    int i,j,k;
    if (direction){
        // Rotate clockwise
        for (k = 0; k < steps; k++){
            for (i = 0; i < 8 ; i++){
                j = 0;
                stepperA = seq_f[i][j];
                stepperB = seq_f[i][j+1];
                stepperC = seq_f[i][j+2];
                stepperD = seq_f[i][j+3];
                wait_ms(1);
            }
        }
    }
    else{
        // Rotate counter-clockwise
        for (k = 0; k < steps; k++){
            for (i = 7; i >= 0 ; i--){
                j = 0;
                stepperA = seq_f[i][j];
                stepperB = seq_f[i][j+1];
                stepperC = seq_f[i][j+2];
                stepperD = seq_f[i][j+3];
                wait_ms(1);
            }
        }
    }
}

void beaconIRQ(){
    detectedFreq++;
}    

void detectBeacon(int frequency, int bandwidth){
    int angleFound = 0, countSteps = 0;
    bool direction;
    int upperCutoff = 0, lowerCutoff = 0;
    upperCutoff = BEACON_SCANINTERVAL_S * (frequency + (bandwidth/2));
    lowerCutoff = BEACON_SCANINTERVAL_S * (frequency - (bandwidth/2));
    // Rotate and Scan
    while(1){
        // Rotate the stepper
            /* if(until steps = 0 to 512)
                    rotate clockwise;           Use seq_f
               else if (steps reached 512) 
                    rotate counter-clockwise;   Use seq_r
                and keep track of the steps to be rotated for the stepper to go to zero point; Send this as arguments to rotateBack() routine
            */
            
        // Scan the beacon
        detectedFreq = 0;
        beaconDetector.fall(&beaconIRQ);
        // check if beacon detected
        wait_ms(BEACON_SCANINTERVAL_MS);
        beaconDetector.fall(NULL);
        if((detectedFreq >= lowerCutoff) && (detectedFreq <= upperCutoff)){
            // return the countSteps angle in degrees; For the Robot to rotate
            break;
        }
        // If Beacon not detected in current direction; Rotate the Beacon
        if (countSteps >= 512)
            direction = false;
        else if (countSteps <= 0)
            direction = true;
        rotateStepper(4, direction);
        if (direction)
            countSteps += 4;
        else
            countSteps -= 4;
    }
    //pc.printf("Angle : %d",&countSteps);
    rotateBack(countSteps);
}

void lineFollower(){
    forward(3);
    sharp_right(3);
    forward(3);
    sharp_right(3);
    forward(5);
}

void alignWithCircle(){
    sharp_right(90);
}

  void hippobotamus(){
    detectBeacon(BEACON_FREQ_CENTER, BEACON_BW_CENTER);
    goToCenter();
    alignWithCircle();
    vaccuumGateClose();
    vaccuumOn();
    lineFollower();
    vaccuumOff();
    shooterOn();
    wait(3);
    vaccuumGateOpen();
    wait(10);
    shooterOff();
    vaccuumGateClose();
    detectBeacon(BEACON_FREQ_RED, BEACON_BW_RED);
    // Repeat
}

void stepperTest(int steps){
    int seq_f[8][4] = {
        {1,0,0,0},
        {1,1,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,0,1,0},
        {0,0,1,1},
        {0,0,0,1},
        {1,0,0,1}
    };
    int seq_r[8][4] = {
        {1,0,0,1},
        {0,0,0,1},
        {0,0,1,1},
        {0,0,1,0},
        {0,1,1,0},
        {0,1,0,0},
        {1,1,0,0},
        {1,0,0,0}
    };
    int i,j,k;
    for (k = 0; k < steps; k++){
        for (i = 0; i < 8; i++){
            j = 0;
            stepperA = seq_f[i][j];
            stepperB = seq_f[i][j+1];
            stepperC = seq_f[i][j+2];
            stepperD = seq_f[i][j+3];
            wait_ms(1);
        }
    }
    // Rotate back
    for (k = 0; k < steps; k++){
        for (i = 7; i >= 0 ; i--){
            j = 0;
            stepperA = seq_f[i][j];
            stepperB = seq_f[i][j+1];
            stepperC = seq_f[i][j+2];
            stepperD = seq_f[i][j+3];
            wait_ms(1);
        }
    }
    // End
    stepperA = 0;
    stepperB = 0;
    stepperC = 0;
    stepperD = 0;
}

// Main routine
int main(){
    printf("Welcome\r\n");
   
    while (1){
        // Test Codes
        //driveSystemTest();
        //vaccuumSwitchTest();
        //vaccuumGateTest();
        //shooterTest();
        //motorEncoderTest();
        hippobotamus();
       
    }
}

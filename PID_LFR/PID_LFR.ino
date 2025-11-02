#define lms 5  // Left Motor Speed (PWM)
#define lmf 6  // Left Motor Forward
#define lmb 7  // Left Motor Backward
#define rmf 8  // Right Motor Forward
#define rmb 9  // Right Motor Backward
#define rms 10 // Right Motor Speed (PWM)

int s[6];     
int sum;      
float avg;    
int position[6] = { 1, 2, 3, 4, 5, 6 }; 
int threshold = 512; 

int lbase = 200; // Base speed for left motor (0-255)
int rbase = 200; // Base speed for right motor (0-255)
int lmotor, rmotor; 


float kp = 50;  
float kd = 1000; 


int PID; 
float error = 0;
float last_error = 0;


void setup() {
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(lms, OUTPUT); 
  pinMode(rms, OUTPUT); 
  Serial.begin(9600); 
}

void loop() {
  PID_follow(); 
}

void PID_follow() {
  PID_reading();

  if (sum == 0) {
    if (last_error > 0) { 
      error = 2.5;  
    } else { 
      error = -2.5; 
    }
  } 
  
  else {
    error = avg - 3.5;
  }

  PID = (kp * error) + (kd * (error - last_error));

  last_error = error;
  lmotor = lbase - PID;
  rmotor = rbase + PID;
  motor(lmotor, rmotor);
}

void PID_reading() {
  float sensor_sum = 0; 
  sum = 0;
  
  for (byte i = 0; i < 6; i++) {
    s[i] = analogRead(i); 
    
    if (s[i] > threshold) {
      s[i] = 1; 
    } else {
      s[i] = 0; 
    }
    
    
    if (s[i] == 1) {
      sensor_sum += position[i];
      sum++; 
    }
  }

  if (sum > 0) {
    avg = sensor_sum / sum; 
  }
}

void motor(int a, int b) {
  if (a > 0) { 
    digitalWrite(lmf, 1);
    digitalWrite(lmb, 0);
  }
  else { 
    a = -a; 
    digitalWrite(lmf, 0);
    digitalWrite(lmb, 1);
  }
  if (b > 0) { 
    digitalWrite(rmf, 1);
    digitalWrite(rmb, 0);
  } else { 
    b = -b; 
    digitalWrite(rmf, 0);
    digitalWrite(rmb, 1);
  }

  if (a > 255) a = 255;
  if (b > 255) b = 255;

  analogWrite(lms, a);
  analogWrite(rms, b);
}
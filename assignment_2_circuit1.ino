// Define pins for single LEDs
int red_LED = 9;
int yellow_LED = 6;
int green_LED = 5;

// Define pins for range sensor
int trigger = 12;
int echo = 11;

// Set max distance for range sensor
int max_dist = 200;

// Set timeout and sound velocity for range sensor
float time_out = max_dist * 60;
int sound_velocity = 340; // define sound speed=340m/s

// LED states
bool red_on = false;
bool yellow_on = false;
bool green_on = false;


void setup() {
  pinMode(trigger,OUTPUT);// set trigPin to output mode
  pinMode(echo,INPUT); // set echoPin to input mode
  
  // set all LEDs to output mode
  pinMode(red_LED, OUTPUT);
  pinMode(yellow_LED, OUTPUT);
  pinMode(green_LED, OUTPUT);
}

void loop() {
  float cur_distance;
  delay(100); // Wait 100ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  cur_distance = getSonar();
  
  // change which light is on based on current distance
  if (cur_distance <= 5.0) {
    digitalWrite(green_LED, HIGH);
    green_on = true;
    if (yellow_on) {
      digitalWrite(yellow_LED, LOW);
      yellow_on = false;
    }
    if (red_on) {
      digitalWrite(red_LED, LOW);
      red_on = false;
    }
  }
  else if (cur_distance > 5.0 && cur_distance <= 10.0)  {
    digitalWrite(yellow_LED, HIGH);
    yellow_on = true;
    if (green_on) {
      digitalWrite(green_LED, LOW);
      green_on = false;
    }
    if (red_on) {
      digitalWrite(red_LED, LOW);
      red_on = false;
    }
  }
  else {
    digitalWrite(red_LED, HIGH);
    red_on = true;
    if (green_on) {
      digitalWrite(green_LED, LOW);
      green_on = false;
    }
    if (yellow_on) {
      digitalWrite(yellow_LED, LOW);
      yellow_on = false;
    }
  }
  
}

float getSonar() {
  unsigned long pingTime;
  float distance;
  digitalWrite(trigger, HIGH); // make trigPin output high level lasting for 10μs to triger HC_SR04,
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  pingTime = pulseIn(echo, HIGH, time_out); // Wait HC-SR04 returning to the high level and measure out this waitting time
  distance = (float)pingTime * sound_velocity / 2 / 10000; // calculate the distance according to the time
  return distance; // return the distance value
}
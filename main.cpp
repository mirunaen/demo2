// Include Adafruit sensor library:
#include <Adafruit_Sensor.h> //https://github.com/adafruit/Adafruit_Sensor
// Include Adafruit DHT library:
#include <DHT.h> //https://github.com/adafruit/DHT-sensor-library

// Defined Pins
#define GREENLED 2
#define YELLOWLED 3
#define REDLED 4
#define TRIGGER 9
#define ECHO 10

// Define DHT sensor type:
#define DHTType DHT11

// Create a DHT sensor object:
DHT dht = DHT(DHTPin,DHTType);

// parameters
const float sound = 34300.0; // Sound speed in cm / s
const float parameter1 = 30.0;
const float parameter2 = 20.0;
const float parameter3 = 10.0;


void setup() {
  dht.begin();
  // Start the serial monitor
  Serial.begin(9600);
  
  // Pin input / output mode
  pinMode(GREENLED, OUTPUT);
  pinMode(YELLOWLED, OUTPUT);
  pinMode(REDLED, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);
  

  // Turn off all the LEDs
  turnOffLEDs();

}

void loop() {
  // Prepare the ultrasound sensor
  startTrigger();

  // Obtain Distance
  float distance = calculateDistance();

  // Turn off all the LEDs
  turnOffLEDs();


  // We launch an alert if we are within the danger range
  if (distance < parameter1)
  {
    // Lunch alerts
    alerts(distance);
  }

  // Read the temperature:
  float temperature = dht.readTemperature();
}

// Turn Off All the LEDs
void turnOffLEDs()
{
  // First, we turn off all the LEDs
  digitalWrite(GREENLED, LOW);
  digitalWrite(YELLOWLED, LOW);
  digitalWrite(REDLED, LOW);
}

// Function that checks if a visual or sound alert needs to be launched
void alerts(float distance)
{
  if (distance < parameter1 && distance >= paremeter2)
  {
    // Turn on GREEN LED
    digitalWrite(GREENLED, HIGH);
    
  }
  else if (distance < parameter2 && distance > parameter3)
  {
    // Turn on YELLOW LED
    digitalWrite(YELLOWLED, HIGH);
    
  }
  else if (distance <= parameter3)
  {
    // Turn on RED LED
    digitalWrite(REDLED, HIGH);
   
  }
}

// Method that calculates the distance an object is located.
// Returns a float variable that contains the distance.
float calculateDistance()
{
  // The pulseIn function gets the time it takes to switch between states, in this case HIGH
  unsigned long times = pulseIn(ECHO, HIGH);

  // We obtain the distance in cm, we have to convert the time in seconds since it is in microseconds
  // so multiply by 0.000001
  float distance = times * 0.000001 * sonido / 2.0;
   Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.print(" Celsius");
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  delay(500);

  return distance;
}

// Method that starts the Trigger sequence to start measuring
void startTrigger()
{
  // Put the Trigger in low state and wait 2 ms
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  // Put the Trigger pin high and wait 10 ms
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);

  // Start by putting the Trigger pin in low state
  digitalWrite(TRIGGER, LOW);
}
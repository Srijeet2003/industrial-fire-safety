#include <SimpleDHT.h>
 #define MQ135 A5              //smoke sensor pin connecetd to pin A0 of Arduino Uno
 #define BUZZER_PIN 12           //buzzer pin connecetd to pin 8 of Arduino Uno 
 #define LED 8               //LED pin connecetd to pin 9 of Arduino Uno       
 #define flamePin A4
 #define DHTPin 2
 #define DHTTYPE DHT11   // DHT 11
 #define GAS_THRESHOLD 10  
 #define TEMP_THRESHOLD 20

 SimpleDHT11 dht;

 int Flame = HIGH;
 int value1;                   //integer value is define to store the output of MQ135 sensor
 int value2;
 
  void setup() 
{
   pinMode(MQ135, INPUT);       //Set MA3 as INPUT device
   pinMode(BUZZER_PIN, OUTPUT);     //Set Buzzer as INPUT device
   pinMode(LED, OUTPUT);        //Set LED  as INPUT device
  pinMode(flamePin, INPUT);
  Serial.begin(9600);
}
void mq135() {
   value1 = analogRead(MQ135);           // reads the analog value from smoke sensor
   Serial.println(value1);
  if ( value1 > GAS_THRESHOLD )             //if smoke is detected
   {
     digitalWrite ( LED , HIGH );     // turns the LED on
     digitalWrite(BUZZER_PIN,HIGH);       // turns the buzzer on  

 }
 else {
     digitalWrite(LED, LOW);          //  turns the LED off
     digitalWrite(BUZZER_PIN,LOW);        //  turns off 
     }
    delay (500);                      
 }

void flamesensor() 
{
  Flame = digitalRead(flamePin);
  if (Flame== LOW)
  {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED , HIGH);
  
  }
  else
  {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED , HIGH);
  }
}
void loop(){
    // Read data from DHT11 sensor
  byte temperature = 0;
  byte humidity = 0;
  if (dht.read(DHTPin, &temperature, &humidity, NULL)) {
    Serial.print("Read DHT11 failed.");
    delay(1000);
    return;
  }

  // Read data from MQ135 sensor
  int gasValue = analogRead(MQ135);

  // Print temperature, humidity, and gas values
  Serial.print("Temperature: ");
  Serial.print((int)temperature);
  Serial.print(" *C, Humidity: ");
  Serial.print((int)humidity);
  Serial.print(" %, Gas Value: ");
  Serial.println(gasValue);

  // Check if the gas level is above the threshold
  if (gasValue > GAS_THRESHOLD) {
    // Blink LED and trigger buzzer
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500); // Adjust the duration of the alarm as needed
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Check if the temperature is above the threshold
  if (temperature > TEMP_THRESHOLD) {
    // Blink LED and trigger buzzer
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500); // Adjust the duration of the alarm as needed
    digitalWrite(LED, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Delay before the next loop
  delay(2000);  // Adjust the delay based on your application
  }

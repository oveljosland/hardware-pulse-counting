#include <Arduino.h>

const int hardware_counter_pin = 5;    // Input fixed to internal timer
const int led_pin = LED_BUILTIN;

const int sample_period = 1000;        // Sample period in milliseconds
unsigned int count;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);

  // Hardware counter setup
  TCCR1A = 0;                          // Reset timer/counter control register A 
}

void loop() {
  digitalWrite(led_pin, LOW);
  delay(sample_period);
  digitalWrite(led_pin, HIGH);

  // Start the counting
  bitSet(TCCR1B, CS12);                // Counter clock source is external pin
  bitSet(TCCR1B, CS11);                // Clock on rising edge
  delay(sample_period);

  // Stop the counting
  TCCR1B = 0;                          // Stop the clock
  count = TCNT1;                       // Read the hardware counter
  TCNT1 = 0;                           // Reset the hardware counter
  if (count > 0) {
    Serial.print("Count: ");
    Serial.println(count);
  }
}
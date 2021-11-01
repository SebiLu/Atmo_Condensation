#include <Arduino.h>
#include <Ticker.h>

//Pin definitions
#define NTC_pin A0

//Constants definition
// Value of dividing resistor
#define R0 100000
//Maximum value of the ADC
#define adcMax 1023
//NTC spcific Beta value
#define BETA 3950
//number of samples over which the average is computed
#define samples 5

const double kelvin = 273.15;
const double ROOM_TEMP = 298.15;
double temp_avg_arr[samples];
double temp_avg;

//Loop counter value for temp averaging
int cnt = 0;

void updateTemp(void);
Ticker timer1(updateTemp, 100);

void setup() {
  pinMode(NTC_pin, INPUT);
  Serial.begin(9600);
  delay(150);
  timer1.start();
}

void loop() {
  timer1.update();
}

void updateTemp()
{
  double adcVal = analogRead(NTC_pin);
  double Rt = R0 * ((adcMax / adcVal) -1);
  double celsius = (BETA * ROOM_TEMP) / (BETA + (ROOM_TEMP * log(Rt / R0))) - kelvin;

  temp_avg = temp_avg + celsius;

  cnt++;

  if(cnt == samples)
  {
    cnt = 0;
    temp_avg = temp_avg / samples;
    Serial.println(temp_avg);
    temp_avg = 0;
  }
}
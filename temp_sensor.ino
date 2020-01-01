
const int temperaturePin = 0;
const int LEDll = 2;
const int LEDb = 3;
const int LEDdp = 4;
const int LEDlr = 5;
const int LEDm = 6;
const int LEDto4 = 7;
const int LEDur = 8;
const int LEDto3 = 9;
const int LEDto2= 10;
const int LEDul = 11;
const int LEDt = 12;
const int LEDto1 = 13;

const int ledMap[] = {12,11,8,6,2,5,3};
const int ledMapDigits[] = {13,10,9,7};

const uint8_t digitsMap[][4] = {
  {LOW, HIGH, HIGH, HIGH},
  {HIGH, LOW, HIGH, HIGH},
  {HIGH, HIGH, LOW, HIGH},
  {HIGH, HIGH, HIGH, LOW}
};

const uint8_t numMap[][7] = {
    {HIGH,HIGH,HIGH,LOW,HIGH,HIGH,HIGH},
    {LOW,HIGH,LOW,LOW,HIGH,LOW,LOW},
    {HIGH,LOW,HIGH,HIGH,HIGH,LOW,HIGH},
    {HIGH,LOW,HIGH,HIGH,LOW,HIGH,HIGH},
    {LOW,HIGH,HIGH,HIGH,LOW,HIGH,LOW},
    {HIGH,HIGH,LOW,HIGH,LOW,HIGH,HIGH},
    {HIGH,HIGH,LOW,HIGH,HIGH,HIGH,HIGH},
    {HIGH,LOW,HIGH,LOW,LOW,HIGH,LOW},
    {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH},
    {HIGH,HIGH,HIGH,HIGH,LOW,HIGH,HIGH}
  };
  
int voltMeasureTimer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Assign modes for each pin
  pinMode(LEDto1, OUTPUT);
  pinMode(LEDto2, OUTPUT);
  pinMode(LEDto3, OUTPUT);
  pinMode(LEDto4, OUTPUT);
  pinMode(LEDt, OUTPUT);
  pinMode(LEDul, OUTPUT);
  pinMode(LEDur, OUTPUT);
  pinMode(LEDm, OUTPUT);
  pinMode(LEDll, OUTPUT);
  pinMode(LEDlr, OUTPUT);
  pinMode(LEDb, OUTPUT);
  pinMode(LEDdp, OUTPUT);

  voltMeasureTimer = 10000;
}

void loop() {

  // Temperature Reading
  float voltage, degreesC;
  voltMeasureTimer++;

  if(voltMeasureTimer >= 10000)
  {
    voltage = getVoltage(temperaturePin);
    // Temperature Calculation
    degreesC = (voltage - 0.5) * 100.0;
    voltMeasureTimer = 0;
  }
  


  // Show the temperature on the LED display
  printTempToLED(degreesC);

}

float getVoltage(int pin)
{
  return (analogRead(pin) * 0.004882814);
}

void writeNumber(const uint8_t* num)
{
  for(int i=0; i<7; i++)
  {
    digitalWrite(ledMap[i], num[i]);
  }
}

void setDigit(const uint8_t* digit)
{
  for(int i=0; i<4; i++)
  {
    digitalWrite(ledMapDigits[i], digit[i]);
  }
}

void clearLED()
{
  for( int i=0; i<7; i++)
  {
    digitalWrite(ledMap[i], LOW);
  }

}

void printTempToLED(float t)
{
  float fraction = t - static_cast<int>(t);
  int temperature = static_cast<int>(t);
  int currentDigit = 3;

  while(temperature >= 1)
  {
    printDigit(temperature % 10, currentDigit);
    currentDigit--;
    temperature = temperature / 10;
  }
  
}

void printDigit(int value, int dig)
{
  setDigit(digitsMap[dig]);
  writeNumber(numMap[value]);
  delay(1);
}

#include <ATTCloudClient.h>
#include "Timer.h"

// Longest variable is 32 chars
PROGMEM const prog_uchar   M2MIO_USERNAME[]    = "<username>";
PROGMEM const prog_uchar   M2MIO_PASSWORD[]    = "<MD5 sum of password (32 characters)>";
PROGMEM const prog_uchar  M2MIO_DOMAIN[]       = "<domain>;
PROGMEM const prog_uchar  M2MIO_DEVICE_TYPE[]  = "<device type>";
PROGMEM const prog_uchar  M2MIO_DEVICE_ID[]    = "<device ID>";

#define REPORTING_INTERVAL_MS  3000

ATTCloudClient acc;
ATT3GModemClient c;

Timer t;

int sensorPin = A0;   // Sensing voltage on analog pin 0
int sensorValue = 0;  // sensor reading

void cmdCallBack(char *topic, uint8_t* payload, unsigned int len);

void setup() {

  while(!Serial);
  delay(1500);

  Serial.begin(9600); // port to communicate to PC
  Serial1.begin(115200); // port that talks to 3G modem

  Serial.println(F("Sensor Loop"));

  c = ATT3GModemClient();
  acc = ATTCloudClient(cmdCallBack,c);

  if (!acc.connect(M2MIO_DEVICE_ID,M2MIO_USERNAME,M2MIO_PASSWORD) ) {
   Serial.println(F("Unable to connect to network (12)"));
    //return;
  }

  acc.setDomainStuffThing(M2MIO_DOMAIN,M2MIO_DEVICE_TYPE,M2MIO_DEVICE_ID);

  //acc.registerForCommands();
  
  int sensorEvent = t.every(REPORTING_INTERVAL_MS, getSensorValue);
}

void loop() {
  delay(200);
  acc.loop();
  t.update();
}

void cmdCallBack(char *topic, uint8_t* payload, unsigned int len) {
  Serial.println(F("In the cmdCallBack()"));
  Serial.println((char*)payload);
}

void getSensorValue() {
  Serial.println(F("sensor read"));

  // read value from sensor
  sensorValue = analogRead(sensorPin);    
  
  acc.sendKV("sensor_val", sensorValue);
}

/*
* INFINITAG - open source laser tag
* Authors: Jani Taxidis, Tobias Stewen & Florian Kleene
* Website: www.infinitag.io
*
* All files are published under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)
* License: https://creativecommons.org/licenses/by-nc-sa/4.0/
*/
#include <Wire.h>

#define ArrayCount(Array) (sizeof(Array)/sizeof(Array[0]))
#define MASTER_ADDRESS 0x20
#define SLAVE_ADDRESS 0x21

enum i2c_client_type
{
  NO_CLIENT,
  SENSOR_CLIENT
};

struct i2c_client
{
  bool connected;
  i2c_client_type type;
};

i2c_client Clients[128];
bool scanScheduled;
int nextFreeClient;

void setup() {
  scanScheduled = true;
  nextFreeClient = SLAVE_ADDRESS + 1;
  for(int i = 0; i < ArrayCount(Clients); ++i)
  {
    Clients[i].connected = false;
    Clients[i].type = NO_CLIENT;
  }
  Wire.begin(MASTER_ADDRESS);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  
  Serial.begin(9600);

  delay(1000);
}

void loop() {
  byte error, address;

  if(scanScheduled)
  {
    nextFreeClient = SLAVE_ADDRESS + 1;
    Serial.println("Scanning...");
 
    for(address = 0; address < 127; address++ )
    {
      //Serial.println(address, HEX);
      
      Wire.beginTransmission(address);
      error = Wire.endTransmission();
 
      if (error == 0)
      {
        Serial.print("I2C device found at address 0x");
        if (address<16)
          Serial.print("0");
        Serial.print(address,HEX);
        Serial.println("  !");
      
        Clients[address].connected = true;
        Clients[address].type = SENSOR_CLIENT;
      
      }
      else if (error==4)
      {
        Serial.print("Unknow error at address 0x");
        if (address<16)
          Serial.print("0");
        Serial.println(address,HEX);
      }   
      else
      {
        Clients[address].connected = false;
        Clients[address].type = NO_CLIENT;
      } 
    }

    while(Clients[nextFreeClient].connected)
    {
      nextFreeClient++;  
    }

    //scanScheduled = false;
    Serial.println("done\n");
  }
 
  delay(1000);           // wait 5 seconds for next scan
}

void requestEvent() {
  //maybe we have enough time to look for the next free address?
  Wire.write(nextFreeClient);
  Clients[nextFreeClient].connected = true;
  Clients[nextFreeClient].type = SENSOR_CLIENT;
  
  while(Clients[nextFreeClient].connected && (nextFreeClient < ArrayCount(Clients)))
  {
      nextFreeClient++;  
  }
  scanScheduled = true;
}

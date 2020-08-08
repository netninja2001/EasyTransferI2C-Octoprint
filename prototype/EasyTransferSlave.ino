#include <Wire.h>
#include <EasyTransferI2C.h>

//create object
EasyTransferI2C ET;

struct DATA_STRUCTURE{ //25 bytes total
  float t1;       //4 bytes
  float h1;       //4 bytes
  float t2;       //4 bytes
  float h2;       //4 bytes
  uint8_t fanp;   //2 bytes
  int rpm;        //2 bytes
  int8_t mode;    //2 bytes
  uint8_t color;  //2 bytes
  bool door;      //1 byte
};

//give a name to the group of data
DATA_STRUCTURE mydata;

//define slave i2c address
#define I2C_SLAVE_ADDRESS 9
#define I2C_MASTER_ADDRESS 8

//define some initial vars
float t1;             // Printer/Enclosure temperature
float h1;             // Printer/Enclosure humidity
float t2;             // Filament Temperature
float h2;             // Filament room humidity
int rpm;             // RPM measurement from fan
uint8_t fanp;         // Fan power (0-100)
int8_t mode;    // LED mode (0=Rainbow,1=Solid,2=Temp,3=Breath,4=Heatbeat,5=Alarm)
uint8_t color;  // LED Color (0=Black,1=Purple,2=Blue,3=Green,4=Red,5=Orange,6=Yellow,7=White)
bool door;      // door state

void setup(){
  Serial.begin(9600);
  Wire.begin(I2C_SLAVE_ADDRESS);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(mydata), &Wire);
  //define handler function on receiving data
  //Wire.onReceive(receiveData);
}

void loop() {
  Serial.println("starting loop");
  mydata.t1 = random(100);       // Printer/Enclosure temperature
  mydata.h1 = random(100);       // Printer/Enclosure humidity
  mydata.t2 = random(100);       // Filament Temperature
  mydata.h2 = random(100);       // Filament room humidity
  mydata.rpm = random(1000);     // RPM measurement from fan
  mydata.fanp  = random(100);  // Fan power (0-100)
  mydata.mode  = random(5);  // LED mode (0=Rainbow,1=Solid,2=Temp,3=Breath,4=Heatbeat,5=Alarm)
  mydata.color = random(7); // LED Color (0=Black,1=Purple,2=Blue,3=Green,4=Red,5=Orange,6=Yellow,7=White)
  mydata.door = random(1);   // door state
  Serial.println("done setting vars");
  delay(3000);
  Serial.println("Sending data...");
  sendData();
  Serial.println("Data sent...");
  delay(2000);
}

void receiveData(int numBytes) {}

void sendData() {
  Serial.println("Sending data!");
  Serial.print("Printer/Enclosure temperature: ");
  Serial.println(mydata.t1);
  Serial.print("Printer/Enclosure humidity: ");
  Serial.println(mydata.h1);
  Serial.print("Filament temperature: ");
  Serial.println(mydata.t2);
  Serial.print("Filament humidity: ");
  Serial.println(mydata.h2);
  Serial.print("Fan power: ");
  Serial.println(mydata.fanp);
  Serial.print("Fan RPM: ");
  Serial.println(mydata.rpm);
  Serial.print("LED mode: ");
  Serial.println(mydata.mode);
  Serial.print("LED color: ");
  Serial.println(mydata.color);
  Serial.print("Door state: ");
  Serial.println(mydata.door);
  ET.sendData(I2C_MASTER_ADDRESS);
  Serial.println("Done transmitting!");
}

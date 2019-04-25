/*  
 *   Smart Plant Pot by Lewis at DIY Machines
 *   
 *   Find the build instructions and CAD data here: https://youtu.be/T_tpKoNCVYw
 *   My Youtube channel: www.youtube.com/c/diymachines
 *   
 *   List of items used in this project and where to find them (the links are Amazon affiliate links and help support this channel at no cost to you):

■ Arduino Nano: https://geni.us/ArduinoNanoV3
■ Mini submersible pump: https://geni.us/MiniPump
■ 5mm tubing: https://geni.us/5mmTubing
■ Transistor: https://geni.us/2npn2222
■ Resistors (1k and 4.7k): https://geni.us/Ufa2s
■ Wire: https://geni.us/22AWGWire
■ 3mm LED: https://geni.us/LEDs
■ Water level sensor: https://geni.us/WaterLevelSensor
■ Nuts and Bolts: http://geni.us/NutsAndBolts
■ Soil moisture sensor: https://geni.us/MoistureSensor
■ Half Perma-proto board: https://geni.us/HalfPermaProto
■ PLA Filament: https://geni.us/PLAFilament

■ Battery powered glue gun: http://geni.us/BoschBatteryGlueGun
■ Battery powered soldering iron: http://bit.ly/SealeySDL6

 */

// These constants won't change. They're used to give names to the pins used:
const int ledPin = 2;                                             // Digital output pin that the LED is attached to
const int pumpPin = 12;                                           // Digital output pin that the water pump is attached to
const int waterLevelPin = A3;                                      // Analoge pin water level sensor is connected to
const int moistureSensorPin = 7;                                  // Digital input pin used to check the moisture level of the soil


// These are the values to edit - see the instructional video to find out what needs adjusting and why:

double checkInterval = 1800;                                      //time to wait before checking the soil moisture level - default it to an hour = 1800000
int waterLevelThreshold = 380;                                    // threshold at which we flash the LED to warn you of a low water level in the pump tank - set this as per the video explains
int emptyReservoirTimer = 90;                                     // how long the LED will flash to tell us the water tank needs topping up - default it to 900 = 30mins
int amountToPump = 300;                                           // how long the pump should pump water for when the plant needs it

// Global temp values

int sensorWaterLevelValue = 0;                                      // somewhere to store the value read from the waterlevel sensor
int moistureSensorValue = 0;                                       //somewhere to store the value read from the soil moisture sensor
  
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);  
    pinMode(ledPin, OUTPUT);
    pinMode(pumpPin, OUTPUT);
    pinMode(moistureSensorPin, INPUT);

                                                                  //flash the LED five times to confirm power on and operation of code:
     for (int i=0; i <= 4; i++){
        digitalWrite(ledPin, HIGH);
        delay(300);
        digitalWrite(ledPin, LOW);
        delay(300);
      }
      delay(2000);

    digitalWrite(ledPin, HIGH);                                   // turn the LED on 
}

void loop() {
  // put your main code here, to run repeatedly:
  
  sensorWaterLevelValue = analogRead(waterLevelPin);              //read the value of the water level sensor
  Serial.print("Water level sensor value: ");                     //print it to the serial monitor
  Serial.println(sensorWaterLevelValue);

  if (sensorWaterLevelValue < waterLevelThreshold){               //check if we need to alert you to a low water level in the tank
      for (int i=0; i <= emptyReservoirTimer; i++){  
        digitalWrite(ledPin, LOW);
        delay(1000);
        digitalWrite(ledPin, HIGH);
        delay(1000);
      }
  }
  else {
    digitalWrite(ledPin, HIGH);
    delay(checkInterval);                                         //wait before checking the soil moisture level
  }


// check soil moisture level

      moistureSensorValue = digitalRead(moistureSensorPin);       //read the moisture sensor and save the value
      Serial.print("Soil moisture sensor is currently: ");
      Serial.print(moistureSensorValue);
      Serial.println(" ('1' means soil is too dry and '0' means the soil is moist enough.)");

      if (moistureSensorValue == 1){
                                                                 //pulse the pump 
        digitalWrite(pumpPin, HIGH);
          Serial.println("pump on");
        delay(amountToPump);                                      //keep pumping water
        digitalWrite(pumpPin, LOW);
         Serial.println("pump off");
        delay(800);                                              //delay to allow the moisture in the soil to spread through to the sensor
      }



}

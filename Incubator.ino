/*  Temperature and Humidity monitor using I2C LCD and DHT11 sensor

YourDuino.com Example Software Sketch modified
16 character 2 line I2C Display
Backpack Interface labelled "A0 A1 A2" at lower right.
..and
Backpack Interface labelled "YwRobot Arduino LCM1602 IIC V1"
MOST use address 0x27, a FEW use 0x3F */

/* Install DHT sensor library by Adafruit 
 *  and Adafruit unified sensor from Arduino library pool
 *  Tools > Manage Libraries */
 
/*  Connect LCD
 *  SDA pin -> UNO Analog 4 pin
 *  SCL pin -> UNO Analog 5 pin */
 
/*—–( Import needed libraries )—–*/
#include <Wire.h> // Comes with Arduino IDE
#include <LCD.h>
#include "DHT.h"

#define DHTPIN 2 // what digital pin we’re connected to
// Uncomment whatever type you’re using!
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

/* Get the LCD I2C Library here:
* https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
* Move any other LCD libraries to another folder or delete them
* See Library "Docs" folder for possible commands etc. */
#include <LiquidCrystal_I2C.h>

/*—–( Declare Constants )—–*/
/*—–( Declare objects )—–*/
// set the LCD address to 0x27 for a 16 chars 2 line display
// A FEW use address 0x3F
// Set the pins on the I2C chip used for LCD connections:
// addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set the LCD I2C address

/*—–( Declare Variables )—–*/
//NONE

void setup() /*—-( SETUP: RUNS ONCE )—-*/
{
Serial.begin(9600); // Used to type in characters

lcd.begin(16,2); // initialize the lcd for 16 chars 2 lines, turn on backlight
dht.begin();

Serial.println("DHTxx test!");
//——– Write characters on the display ——————
// NOTE: Cursor Position: (CHAR, LINE) start at 0
lcd.setCursor(0,0); //Start at character 4 on line 0
lcd.print("Hello, world!");
delay(1000);
lcd.setCursor(0,1);
lcd.print("Incubator starting...");
delay(8000);

// Wait and then tell user they can start the Serial Monitor and type in characters to
// Display. (Set Serial Monitor option to "No Line Ending")
lcd.clear();
lcd.setCursor(0,0); //Start at character 0 on line 0
lcd.print("Use Serial Mon");
lcd.setCursor(0,1);
lcd.print("Type to display");
}/*–(end setup )—*/
void loop() /*—-( LOOP: RUNS CONSTANTLY )—-*/
{

// Wait a few seconds between measurements.
delay(2000);

// Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds ‘old’ (its a very slow sensor)
float h = dht.readHumidity();
// Read temperature as Celsius (the default)
float t = dht.readTemperature();
// Read temperature as Fahrenheit (isFahrenheit = true)
float f = dht.readTemperature(true);

// Check if any reads failed and exit early (to try again).
if (isnan(h) || isnan(t) || isnan(f)) {
Serial.println("Failed to read from DHT sensor!");
return;
}

// Compute heat index in Fahrenheit (the default)
float hif = dht.computeHeatIndex(f, h);
// Compute heat index in Celsius (isFahreheit = false)
float hic = dht.computeHeatIndex(t, h, false);

Serial.print("Humidity: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperature: ");
Serial.print(t);
Serial.print(" *C ");
Serial.print(f);
Serial.print(" *F\t");
Serial.print("Heat index: ");
Serial.print(hic);
Serial.print(" *C ");
Serial.print(hif);
Serial.println(" *F");

lcd.setCursor(0,0);
lcd.print("Temp: ");
lcd.print(t);
lcd.print((char)223);
lcd.print("C");
lcd.setCursor(0,1);
lcd.print("Humidity: ");
lcd.print(h);
lcd.print("%");
delay(1000);

}/* –(end main loop )– */
/* ( THE END ) */


/* 
3D printed smart shelving with a giant hidden digital clock in the front edges of the shelves - DIY Machines

==========

Edited by Techsider

Works with 24h Time, 4x 7 Segment Displays (4 Leds each)
*/





#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#endif

#include <DS3231_Simple.h>
DS3231_Simple Clock;

// Create a variable to hold the time data 
DateTime MyDateAndTime;

// Which pin on the Arduino is connected to the NeoPixels?
#define LEDCLOCK_PIN    3
#define LEDDOWNLIGHT_PIN    5

// How many NeoPixels are attached to the Arduino?
#define LEDCLOCK_COUNT 200
#define LEDDOWNLIGHT_COUNT 12

  //(red * 65536) + (green * 256) + blue ->for 32-bit merged colour value so 16777215 equals white
int clockMinuteColour = 51200; //1677
int clockHourColour =  140000000; //7712

int clockFaceBrightness = 0;

// Declare our NeoPixel objects:
Adafruit_NeoPixel stripClock(LEDCLOCK_COUNT, LEDCLOCK_PIN, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel stripDownlighter(LEDDOWNLIGHT_COUNT, LEDDOWNLIGHT_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


//Smoothing of the readings from the light sensor so it is not too twitchy
const int numReadings = 12;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
long total = 0;                  // the running total
long average = 0;                // the average



void setup() {

  Serial.begin(9600);
  Clock.begin();

  stripClock.begin();           // INITIALIZE NeoPixel stripClock object (REQUIRED)
  stripClock.show();            // Turn OFF all pixels ASAP
  stripClock.setBrightness(100); // Set inital BRIGHTNESS (max = 255)
 

  stripDownlighter.begin();           // INITIALIZE NeoPixel stripClock object (REQUIRED)
  stripDownlighter.show();            // Turn OFF all pixels ASAP
  stripDownlighter.setBrightness(255); // Set BRIGHTNESS (max = 255)

  //smoothing
    // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  
}

void loop() {
  
  //read the time
  readTheTime();

  //display the time on the LEDs
  displayTheTime();

  //Record a reading from the light sensor and add it to the array
  readings[readIndex] = analogRead(A0); //get an average light level from previouse set of samples
  Serial.print("Light sensor value added to array = ");
  Serial.println(readings[readIndex]);
  readIndex = readIndex + 1; // advance to the next position in the array:

  // if we're at the end of the array move the index back around...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  //now work out the sum of all the values in the array
  int sumBrightness = 0;
  for (int i=0; i < numReadings; i++)
    {
        sumBrightness += readings[i];
    }
  Serial.print("Sum of the brightness array = ");
  Serial.println(sumBrightness);

  // and calculate the average: 
  int lightSensorValue = sumBrightness / numReadings;
  Serial.print("Average light sensor value = ");
  Serial.println(lightSensorValue);


  //set the brightness based on ambiant light levels
  clockFaceBrightness = map(lightSensorValue,50, 1000, 200, 1); 
  stripClock.setBrightness(clockFaceBrightness); // Set brightness value of the LEDs
  Serial.print("Mapped brightness value = ");
  Serial.println(clockFaceBrightness);
  
  stripClock.show();

   //(red * 65536) + (green * 256) + blue ->for 32-bit merged colour value so 16777215 equals white
  stripDownlighter.fill(16777215, 0, LEDDOWNLIGHT_COUNT);
  stripDownlighter.show();

  delay(1000);   //this 5 second delay to slow things down during testing

}


void readTheTime(){
  // Ask the clock for the data.
  MyDateAndTime = Clock.read();
  
  // And use it
  Serial.println("");
  Serial.print("Time is: ");   Serial.print(MyDateAndTime.Hour);
  Serial.print(":"); Serial.print(MyDateAndTime.Minute);
  Serial.print(":"); Serial.println(MyDateAndTime.Second);
  Serial.print("Date is: 20");   Serial.print(MyDateAndTime.Year);
  Serial.print(":");  Serial.print(MyDateAndTime.Month);
  Serial.print(":");    Serial.println(MyDateAndTime.Day);
}

void displayTheTime(){

  stripClock.clear(); //clear the clock face 

  
  int firstMinuteDigit = MyDateAndTime.Minute % 10; //work out the value of the first digit and then display it
  displayNumber(firstMinuteDigit, 0, clockMinuteColour);


  int secondMinuteDigit = floor(MyDateAndTime.Minute / 10); //work out the value for the second digit and then display it
  displayNumber(secondMinuteDigit, 28, clockMinuteColour);  

  int firstHourDigit = MyDateAndTime.Hour  % 10; //work out the value for the third digit and then display it
  displayNumber(firstHourDigit, 56, clockHourColour);


  int secondHourDigit = floor(MyDateAndTime.Hour / 10); //work out the value for the fourth digit and then display it
  displayNumber(secondHourDigit, 84, clockHourColour);   

}


void displayNumber(int digitToDisplay, int offsetBy, int colourToUse){
    switch (digitToDisplay){
    case 0:
    digitZero(offsetBy,colourToUse);
      break;
    case 1:
      digitOne(offsetBy,colourToUse);
      break;
    case 2:
    digitTwo(offsetBy,colourToUse);
      break;
    case 3:
    digitThree(offsetBy,colourToUse);
      break;
    case 4:
    digitFour(offsetBy,colourToUse);
      break;
    case 5:
    digitFive(offsetBy,colourToUse);
      break;
    case 6:
    digitSix(offsetBy,colourToUse);
      break;
    case 7:
    digitSeven(offsetBy,colourToUse);
      break;
    case 8:
    digitEight(offsetBy,colourToUse);
      break;
    case 9:
    digitNine(offsetBy,colourToUse);
      break;
    default:
     break;
  }
}
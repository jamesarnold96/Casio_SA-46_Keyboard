
/*
int pin[7];           // Arduino pins connected to the matrix
int outputPin;       // Pin configured as an output
int arrayNo =         // Number of connected pins - 1 
int outputArrayNo = 0; // current array number of the output pin

void setup() {
  Serial.begin(9600);
  outputP
}

void loop() {
  if (outputPin <= pin[arrayNo]) {
        pinMode(outputPin, OUTPUT);
        Serial.println("Output: " + outputPin);
   delay(500);
   digitalWrite(outputPin, HIGH);
  for(int setPin = 0; setPin <= arrayNo; setPin++) {
   if(pin[setPin] != outputPin) {
     pinMode(setPin, INPUT_PULLUP);
     delay(500);
    if(digitalRead(setPin == HIGH) {
      Serial.println("Input: " + setPin);
      delay(100);
    }
   }
  }
  outputArrayNo++;
  outputPin = pin[outputArrayNo]
  }
}

*/

//Pin connected to SH_CP of 74HC595
const int clockPin = 8;
//Pin connected to DS of 74HC595
const int dataPin = 10; 
//Pin connected to ST_CP of 74HC595
const int latchPin = 11;
//The arrangement outputted by the shift register
byte output = 0;
//The number of inputs connected to the Arduino
int inputNo = 0;
//The pin numbers of the inputs (20 is probably larger than needed)
int inputs[20];
boolean buttonState[128]; 

void setup() {
  //Set the main shift register pins as outputs
  Serial.begin(9600);
  Serial.println("Does it work?");
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  //Recieve the number of inputs from the user
  Serial.println("Type in what is requested in this window.\nPress enter when finished\nSeperate numbers with commmas"); 
  Serial.println("How many inputs do you have?");
  //Stops the computer moving on without a user input
  while (true) {
    //This has to be true for the computer to move on
    boolean dontYouDare = false;
    //Checking for Serial input
  while(Serial.available() > 0) {
    //Recieve the user input
    inputNo = Serial.parseInt();
    Serial.println(inputNo);
    dontYouDare = true;
  }
  //Exit loop if user input recieved
  if (dontYouDare == true) {
    break;
  }
  }
  // Ask for the input pin numbers
  Serial.println("What are the numbers of the input pins?");
  // Stops the computer moving on without a user input
  while(true) {
    boolean dontYouDare = false; 
    //Check for user input
  while(Serial.available() > 0) {
    // Recieve user inpute
    for(int i = 0; i < inputNo; i++) {
      inputs[i] = Serial.parseInt();
      // Set up the input pins based on user input
      pinMode(inputs[i], INPUT);
      delay(40);
    }
    // Exit loop
    dontYouDare = true;
  }
  if(dontYouDare == true) {
    Serial.print("Input pins: ");
    for(int i = 0; i < inputNo; i++) {
      Serial.print(inputs[i]);
    }
    Serial.println();
    break;
  }
  }
}
   
  void loop() {
    // loop procedure for all 8 outputs
   for(int o = 0; o < 8; o++) {
     // Reset putput pins to low
     output = 0;
     // Only switch on one pin (the current one in the loop)
     bitSet(output, o);
     digitalWrite(latchPin, LOW);
     shiftOut(dataPin, clockPin, MSBFIRST, output);
     digitalWrite(latchPin, HIGH);
     delay(5);
     for(int i = 0; i < inputNo; i++) {
       int currentInput = digitalRead(inputs[i]);
       if(buttonState[(i*8)+o] != currentInput) {
         buttonState[(i*8)+o] = currentInput;
         if(currentInput == 1) {
            Serial.print("Input pin: ");
            Serial.println(inputs[i]);
            Serial.print("Output pin: ");
            Serial.println(o);
         }
       }
     delay(5);
   }
  }
  }
     
         
    
    
    
  

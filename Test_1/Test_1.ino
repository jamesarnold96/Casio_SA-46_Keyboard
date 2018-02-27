int inputs[2] = {2,3};
int outputs[2] = {5,6};

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 2; i++) {
    pinMode(inputs[i], INPUT);
    pinMode(outputs[i], OUTPUT);
  }
}
  
void loop() {
  for(int i = 0; i < 2; i++) {
    digitalWrite(outputs[i], HIGH);
    delay(100);
    for(int j = 0; j < 2; j++) {
      if(digitalRead(inputs[j]) == HIGH) {
        Serial.print("Input pin: ");
        Serial.println(inputs[j]);
        Serial.print("Output pin: ");
        Serial.println(outputs[i]);
        delay(50);
    }
    
    
    }
    digitalWrite(outputs[i], LOW);
    delay(50);
  }
}

const int ledPin = 12;
unsigned int freq = 0;
char incomingByte;

void setup(){
pinMode(ledPin, OUTPUT);
Serial.begin(9600);
}

void loop(){
  if (Serial.available()){
    freq = Serial.read() - '0';
//    freq = 0;
//    while(1){
//      incomingByte = Serial.read();
//      if(incomingByte == 'A'){
//        Serial.println("FUCK");
//        break;
//      }
//      if(incomingByte == -1) continue;
//      freq *= 10;
//      freq = ((incomingByte - 48) + freq);
//    }
    Serial.println("YOU");
  }
}


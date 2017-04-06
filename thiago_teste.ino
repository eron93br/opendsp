int EEG_Value;
float mytime = 0;
 
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(57200);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
 }
  Serial.println("START");
}
 
// the loop routine runs over and over again forever:
void loop() {
 int EEG_Value = analogRead(A0);
 Serial.print(EEG_Value);
 Serial.print(",");
 Serial.println(mytime);
 mytime = mytime + 3.90;
  delay(3900);  
}

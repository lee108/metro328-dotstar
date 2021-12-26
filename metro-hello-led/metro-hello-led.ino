void setup() {
  // put your setup code here, to run once:

  // initilize the UART to operate at 9600 BAUD
  Serial.begin(9600);
  Serial.println("Serial Port: Inialized for 9600 BAUD");

  // initialize digital pin LEDBUILTIN as an output
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("LED_BUILTIN: Inialized as OUTPUT");
}

void loop() {
  // put your main code here, to run repeatedly

  // blink led
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);
}

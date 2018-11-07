void setup() {
    pinMode(16, OUTPUT);    //GPIO16 (D0) sea como salida
}

void loop() {
    digitalWrite(16, HIGH); //GPIO16 en uno lógico
    delay(80);
    digitalWrite(16, LOW); //GPIO16 en cero lógico
    delay(120);
    digitalWrite(16, HIGH); //GPIO16 en uno lógico
    delay(80);
    digitalWrite(16, LOW); //GPIO16 en cero lógico
    delay(700);
}

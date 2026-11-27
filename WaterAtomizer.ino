/*
  Demo code for grove  atomization.
  Touch to start atomizing.
  Last modified by he
  by xiaohe
*/
#define LED 34 // 



// the setup function runs once when you press reset or power the board
void setupAtomizer() {
    // initialize digital pin 13 as an output.
    pinMode(35, OUTPUT);// Set A5 as OUTPUT
    pinMode(5, INPUT); // Use digital pin 5 as output port
    pinMode(34, OUTPUT);
}

// the loop function runs over and over again forever
void loopAtomizer() {
    int D2Sig = digitalRead(5);// read pin 5 signal
    if (D2Sig == 1)
    {
        /* code */
        digitalWrite(35, HIGH);   // atomize
        //digitalWrite(34, HIGH); // red or yellow leds turn on and off
        delay(10000);              // wait for 10 seconds
        digitalWrite(35, LOW);    // atomization stopped
        digitalWrite(34, LOW);

    }
}
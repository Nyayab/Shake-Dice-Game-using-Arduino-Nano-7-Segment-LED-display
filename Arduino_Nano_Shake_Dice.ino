/*

OBJECTIVE 1.3: Generate a random number (1-6) and display it on a 7-segment display 
until the button is pressed again to generate a new number.
Common Cathode 7 segment display used
Common Cathode is connected to Arduino Nano'a GND pin using a 1 ohm resistance

pin numbering the different segments of the 7 segment LED display

_____a/4____
|           |
|           |
f/3         b/5
|           |
|____g/2____|
|           |
|           |
e/6         c/8
|           |
|____d/7____|

NOTE: The toggle button is the tilt switch module

*/

const int a = 4; 
const int b = 5;
const int c = 8;
const int d = 7;
const int e = 6;
const int f = 3;
const int g = 2;

// switch case variable num
int num = 0;

// pin numbering of push button
const int button = 9;

// pin numbering of buzzer
const int buzz = 10;

// Variables for button press handling
int lastButtonState = HIGH;  // Previous state of the button (start with unpressed)
int buttonState;             // Current state of the button
unsigned long lastDebounceTime = 0;  // To handle debounce
unsigned long debounceDelay = 50;    // Debounce delay in milliseconds

// setup function
void setup() 
{
  // Set pinMode of all the 7-segment pins from 2 to 8 as output
  for(int i = 2; i <= 8; i++)
  {
    pinMode(i, OUTPUT);
  }
  
  randomSeed(analogRead(A0));

  // Set pinMode of buzzer as output and button as input
  pinMode(buzz, OUTPUT);
  pinMode(button, INPUT_PULLUP);  // Use internal pull-up resistor

  // Serial monitor for debugging
  Serial.begin(9600);
  Serial.println("Random Number Generator ready. Press button to generate a number.");
  
  // Display initial number (0) on the 7-segment display
  zero();
}

// loop function
void loop() 
{
  // Read the current state of the button
  int reading = digitalRead(button);
  
  // Check if the button state has changed (i.e., pressed or released)
  if (reading != lastButtonState) {
    lastDebounceTime = millis();  // Reset debounce timer
  }

  // Check if enough time has passed since the last state change (debouncing)
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Only change the button state if it is different
    if (reading != buttonState) {
      buttonState = reading;
      
      // If the button has been pressed (button state goes LOW)
      if (buttonState == LOW) {
        // Generate a new random number between 1 and 6
        num = (random() % 6) + 1;
        Serial.print("New random number: ");
        Serial.println(num);

        //loading screen
        loading();

        // Display the number on the 7-segment display
        displayNumber(num);

        // Play a beep sound using the buzzer
        digitalWrite(buzz, HIGH);
        delay(200);
        digitalWrite(buzz, LOW);
      }
    }
  }
  
  // Save the current state for the next loop iteration
  lastButtonState = reading;
}



//Function to display a loading animation and sound before showing the random number
void loading()
{
  one();
  digitalWrite(buzz, HIGH);
  delay(50);
  digitalWrite(buzz,LOW);delay(50);
  two();
  digitalWrite(buzz, HIGH);
  delay(50);
  digitalWrite(buzz,LOW);delay(50);
  three();
  digitalWrite(buzz, HIGH);
  delay(50);
  digitalWrite(buzz,LOW);delay(50);
  four();
  digitalWrite(buzz, HIGH);
  delay(50);
  digitalWrite(buzz,LOW);delay(50);
  five();
  digitalWrite(buzz, HIGH);
  delay(50);
  digitalWrite(buzz,LOW);delay(50);
  six();
  digitalWrite(buzz, HIGH);
  delay(50);
  digitalWrite(buzz,LOW);delay(50);

}


// Function to display a number on the 7-segment display
void displayNumber(int num) {
  switch(num) {
    case 1:   
      one();
      break;
    case 2:
      two();
      break;
    case 3:
      three();
      break;
    case 4:
      four();
      break;
    case 5:
      five();
      break;
    case 6:
      six();
      break;
    default:
      zero();  // Fallback to displaying zero if needed
      break;
  }
}

// Functions to display digits on the 7-segment display
void zero() {
   digitalWrite(a, HIGH);
   digitalWrite(b, HIGH);
   digitalWrite(c, HIGH);
   digitalWrite(d, HIGH);
   digitalWrite(e, HIGH);
   digitalWrite(f, HIGH);
   digitalWrite(g, LOW);
}

void one() {
   digitalWrite(a, LOW);
   digitalWrite(b, HIGH);
   digitalWrite(c, HIGH);
   digitalWrite(d, LOW);
   digitalWrite(e, LOW);
   digitalWrite(f, LOW);
   digitalWrite(g, LOW);
}

void two() {
   digitalWrite(a, HIGH);
   digitalWrite(b, HIGH);
   digitalWrite(c, LOW);
   digitalWrite(d, HIGH);
   digitalWrite(e, HIGH);
   digitalWrite(f, LOW);
   digitalWrite(g, HIGH);
}

void three() {
   digitalWrite(a, HIGH);
   digitalWrite(b, HIGH);
   digitalWrite(c, HIGH);
   digitalWrite(d, HIGH);
   digitalWrite(e, LOW);
   digitalWrite(f, LOW);
   digitalWrite(g, HIGH);
}

void four() {
   digitalWrite(a, LOW);
   digitalWrite(b, HIGH);
   digitalWrite(c, HIGH);
   digitalWrite(d, LOW);
   digitalWrite(e, LOW);
   digitalWrite(f, HIGH);
   digitalWrite(g, HIGH);
}

void five() {
   digitalWrite(a, HIGH);
   digitalWrite(b, LOW);
   digitalWrite(c, HIGH);
   digitalWrite(d, HIGH);
   digitalWrite(e, LOW);
   digitalWrite(f, HIGH);
   digitalWrite(g, HIGH);
}

void six() {
   digitalWrite(a, HIGH);
   digitalWrite(b, LOW);
   digitalWrite(c, HIGH);
   digitalWrite(d, HIGH);
   digitalWrite(e, HIGH);
   digitalWrite(f, HIGH);
   digitalWrite(g, HIGH);
}

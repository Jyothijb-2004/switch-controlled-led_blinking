const int ledPin = 9;
const int buttonPin = 2;

int mode = 0;                 // 0=OFF, 1=0.5Hz, 2=1Hz, 3=2Hz
bool ledState = LOW;

unsigned long previousMillis = 0;
unsigned long interval = 0;

// Button debounce
bool lastButtonState = HIGH;
bool buttonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(ledPin, LOW);
}

void loop() {
  handleButton();
  handleBlink();
}

void handleButton() {
  bool reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // Button pressed (LOW because INPUT_PULLUP)
      if (buttonState == LOW) {
        mode++;
        if (mode > 3) mode = 0;

        switch (mode) {
          case 0: interval = 0; break;       // OFF
          case 1: interval = 1000; break;    // 0.5 Hz
          case 2: interval = 500; break;     // 1 Hz
          case 3: interval = 250; break;     // 2 Hz
        }

        digitalWrite(ledPin, LOW);
        ledState = LOW;
      }
    }
  }

  lastButtonState = reading;
}

void handleBlink() {
  if (mode == 0) {
    digitalWrite(ledPin, LOW);
    return;
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}

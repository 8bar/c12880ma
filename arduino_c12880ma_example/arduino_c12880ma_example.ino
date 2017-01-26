/*
   Macro Definitions
*/
#define SPEC_TRG         A0
#define SPEC_ST          A1
#define SPEC_CLK         A2
#define SPEC_VIDEO       A3
#define WHITE_LED        A4
#define LASER_404        A5

#define SPEC_CHANNELS    288 // New Spec Channel
uint16_t data[SPEC_CHANNELS];

unsigned long int_time = 4096;
int incomingByte = 0;

void setup() {
  
  //Set desired pins to OUTPUT
  pinMode(SPEC_CLK, OUTPUT);
  pinMode(SPEC_ST, OUTPUT);
  pinMode(LASER_404, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);

  digitalWrite(SPEC_CLK, HIGH); // Set SPEC_CLK High
  digitalWrite(SPEC_ST, LOW); // Set SPEC_ST Low

  Serial.begin(115200); // Baud Rate set to 115200
}

/*
   This functions reads spectrometer data from SPEC_VIDEO
   Look at the Timing Chart in the Datasheet for more info
*/
void readSpectrometer() {
  
  // Start clock cycle
  for (int i = 0; i < 10; i++) {
    digitalWrite(SPEC_CLK, LOW);
    digitalWrite(SPEC_CLK, HIGH);
  }

  // set START high and do four clock cycles
  digitalWrite(SPEC_CLK, LOW);
  digitalWrite(SPEC_ST, HIGH);
  for (int i = 0; i < 4; i++) {
    digitalWrite(SPEC_CLK, HIGH);
    digitalWrite(SPEC_CLK, LOW);
  }

  //Clock cycles for integration time
  for (int i = 0; i < int_time; i++) {
    digitalWrite(SPEC_CLK, HIGH);
    digitalWrite(SPEC_CLK, LOW);
  }

  //Set SPEC_ST to low
  digitalWrite(SPEC_ST, LOW);

  //Sample for a period of time
  for (int i = 0; i < 88; i++) {
    digitalWrite(SPEC_CLK, HIGH);
    digitalWrite(SPEC_CLK, LOW);
  }

  //Read from SPEC_VIDEO
  for (int i = 0; i < SPEC_CHANNELS; i++) {
    data[i] = analogRead(SPEC_VIDEO);
    digitalWrite(SPEC_CLK, HIGH);
    digitalWrite(SPEC_CLK, LOW);
  }

  //Run clock for a small amount of time
  for (int i = 0; i < 7; i++) {
    digitalWrite(SPEC_CLK, HIGH);
    digitalWrite(SPEC_CLK, LOW);
  }
  digitalWrite(SPEC_CLK, HIGH);
}

/*
   The function below prints out data to the
   terminal or processing plot
*/
void printData() {
  
  for (int i = 0; i < SPEC_CHANNELS; i++) {
    Serial.print(data[i]);
    Serial.print(',');
  }
  Serial.print("\n");
}

void loop() {
  
  readSpectrometer();
  printData();
  delay(100);

  // check for incoming data
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    if (incomingByte==93) {
      int_time=min(int_time*2,1048576);
    }
    if (incomingByte==91) {
      int_time=max(int_time/2,2);
    }
  }
}

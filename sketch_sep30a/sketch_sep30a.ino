// Pin assignments
const int rowPins[4] = {5, 4, 14, 12}; // Row GPIOs
const int colPins[8] = {13, 16, 0, 2, 15, 10, 9, 3}; // Column GPIOs

// Define the corresponding MIDI note numbers for each key
int midiNotes[4][8] = {
  {60, 61, 62, 63, 64, 65, 66, 67},  // Row 1 (C4 to G4)
  {68, 69, 70, 71, 72, 73, 74, 75},  // Row 2 (G#4 to D5)
  {76, 77, 78, 79, 80, 81, 82, 83},  // Row 3 (D#5 to A#5)
  {84, 85, 86, 87, 88, 89, 90, 91}   // Row 4 (B5 to F6)
};

// State tracking for key presses
bool keyStates[4][8] = {false}; // Keeps track of current key states

void setup() {
  Serial.begin(115200); // Open serial at high baud rate

  // Set row pins as inputs
  for (int i = 0; i < 4; i++) {
    pinMode(rowPins[i], INPUT);
  }

  // Set column pins as inputs
  for (int i = 0; i < 8; i++) {
    pinMode(colPins[i], INPUT);
  }
}

void loop() {
  // Scan through rows
  for (int row = 0; row < 4; row++) {
    // Check if the row is active (signal detected)
    if (digitalRead(rowPins[row]) == HIGH) {
      
      // Scan through columns
      for (int col = 0; col < 8; col++) {
        bool keyPressed = digitalRead(colPins[col]) == HIGH;
        if (keyPressed && !keyStates[row][col]) {
          // A key was pressed, and it wasn't previously pressed
          int midiNote = midiNotes[row][col];
          sendMIDIMessage(0x90, midiNote, 127); // Note on with velocity 127
          keyStates[row][col] = true; // Update state
        } else if (!keyPressed && keyStates[row][col]) {
          // A key was released
          int midiNote = midiNotes[row][col];
          sendMIDIMessage(0x80, midiNote, 0); // Note off with velocity 0
          keyStates[row][col] = false; // Update state
        }
      }
    }
  }
}

// Function to send MIDI message over Serial
void sendMIDIMessage(byte command, byte pitch, byte velocity) {
  Serial.write(command);  // Send the MIDI command byte (status byte)
  Serial.write(pitch);    // Send the pitch byte (note number)
  Serial.write(velocity); // Send the velocity byte
}

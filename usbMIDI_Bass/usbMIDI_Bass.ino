/*
 * REFERENCES:
 * [1] Teensy 3.2 usbMIDI library function reference (https://www.pjrc.com/teensy/td_midi.html)
 * [2] Teensy 3.2 pinout diagram (https://www.pjrc.com/teensy/pinout.html)
 * [3] Teensyduino Addon download page (https://www.pjrc.com/teensy/td_download.html)
 * [4] Teensyduino Addon install directions (https://www.pjrc.com/teensy/teensyduino.html)
 * [5] REAPER Digital Audio Workstation (DAW) download page (http://www.reaper.fm/download.php)
 * [6] MIDI message packet structure (https://www.midi.org/specifications/item/table-1-summary-of-midi-message)
 * [7] MIDI note numbers, organized by octave (http://www.electronics.dit.ie/staff/tscarff/Music_technology/midi/midi_note_numbers_for_octaves.htm)
 *
 *
 *                                  * * * * * * * !!!WARNING!!! * * * * * * *
 *
 *                                    THE TEENSY 3.2 IS NOT 5V DC COMPLIANT!
 *                                  DO NOT APPLY MORE THAN 3.3V DC TO ANY PINS
 *                                             OR RISK DAMAGING THE BOARD!
 *
 *                                  * * * * * * * * * * * * * * * * * * * * *
 *
 * README:
 * This code is a template for controlling the Teensy 3.2 using MIDI messages.
 * It contains the basic functions to allow the Teensy 3.2 to receive messages from a MIDI source.
 * Please refer to the Teensy usbMIDI library function reference and tutorial [1] for additional functions and examples.
 * Please refer to the Teensy 3.2 pinout diagram [2] for directions on how to connect peripheral devices like servos and motors.
 *
 * COMPILING THE CODE:
 * First, make sure that the the Teensyduino Addon is installed [3]. Follow the directions in [4] to install the application.
 * You will see a list of PJRC boards by selecting:
 *
 *     Tools -> Board
 *
 * If the Teensyduino Addon is installed, you will see a list of Teensy 2.x and 3.x boards under the "Teensyduino" heading.
 * Select the Teensy 3.2/3.1 board under:
 *
 *     Tools -> Board -> Teensy 3.2/3.1
 *
 * Also, select the USB type as "Serial + MIDI" under:
 *
 *     Tools -> USB Type -> "Serial + MIDI"
 *
 * Both of these settings must be selected in order to include the usbMIDI during compilation. Otherwise, the code WILL NOT compile!
 * This configuration will allow the Teensy 3.2 to connect to a computer as a MIDI device but will also allow serial messages to pass between the Teensy 3.2 and the Arduino IDE during debugging.
 * A successful compilation will open the Teensyduino loader application.
 * You may be required to press the white button on the Teensy 3.2 to intiate the upload to the board.
 *
 * MIDI COMMUNICATION:
 * After the code has successfully uploaded, you may use any application that detects MIDI devices to send messages to your Teensy.
 * One such example is REAPER [5], a Digital Audio Workstation (DAW) application that can be used to compose and play MIDI files, as well as handle communication between MIDI peripherals like keyboards and control surfaces.
 *
 * MIDI MESSAGE PROTOCOL:
 * An overview of the MIDI message protocol is detailed in [6]. While it is not necessary to know how to parse the packets while using usbMIDI, it is beneficial to understand the types of messages and the accompanying range of values.
 * A list of MIDI notes can be found in [7]. It is important to know which MIDI note numbers correspond to their respective musical notes.
 *
 */

// Add #include statements, #define statements, variables, etc. below ...
int f1 = 1;

const int STRING_1;
const int STRING_2;
const int STRING_3;
const int STRING_4;



// End definitions.

/*
 * Standard SETUP function.
 * Runs once.
 */
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);           // Set the built-in LED on pin 13 to output voltage (ON/OFF, HIGH/LOW).

    usbMIDI.setHandleNoteOn(onNoteOn);      // Set the NOTE ON message event handler.
    usbMIDI.setHandleNoteOff(onNoteOff);    // Set the NOTE OFF message event handler.

    // Initialize user-defined variables below ...
    pinMode(f1,OUTPUT);


    // End initialization here.
    digitalWrite(f1, LOW);


    // Because there is no power/status LED, we blink the built-in LED on pin 13 to show that the board is functioning.
    digitalWrite(LED_BUILTIN, HIGH);        // Turn ON the built-in LED.
    delay(1000);                            // Wait for one second (1000 milliseconds).
    digitalWrite(LED_BUILTIN, LOW);         // Turn OFF the built-in LED.
    delay(1000);                            // Wait for one second (1000 milliseconds).
}

/*
 * Standard LOOP function.
 * Runs continuously.
 */
void loop() {
    usbMIDI.read(); // Read each incoming MIDI message as fast as possible.
    // Please DO NOT include any instrument control code within LOOP.
    // The only functions that should contain control code are the CALLBACK FUNCTIONS (e.g. onNoteOn, onNoteOff).
}

/*
 * Callback function to handle NOTE ON (0x90) control messages.
 * CHANNEL  (0 to 15 decimal; 0x00 to 0x0F hexadecimal)  The MIDI channel number.
 * NOTE     (0 to 127 decimal; 0x00 to 0x7F hexadecimal) The MIDI note number.
 * VELOCITY (0 to 127 decimal; 0x00 to 0x7F hexadecimal) The volume of the note.
 */
void onNoteOn(byte channel, byte note, byte velocity) {
    digitalWrite(LED_BUILTIN, HIGH);   // Turn ON the built-in LED
    // Add NOTE ON instrument control code below ...
    switch (note) {
      case 60:
        digitalWrite(f1, HIGH);

    }

    // End NOTE OFF instrument control code here.
}

/*
 * Callback function to handle NOTE OFF (0x80) messages
 * CHANNEL  (0 to 15 decimal; 0x00 to 0x0F hexadecimal)  The MIDI channel number.
 * NOTE     (0 to 127 decimal; 0x00 to 0x7F hexadecimal) The MIDI note number.
 * VELOCITY (0 to 127 decimal; 0x00 to 0x7F hexadecimal) The volume of the note.
 */
void onNoteOff(byte channel, byte note, byte velocity) {
    digitalWrite(LED_BUILTIN, LOW);    // Turn OFF the built-in LED
    // Add NOTE OFF instrument control code below ...
        switch (note) {
      case 60:
        digitalWrite(f1, LOW);
        break;
    }


    // End NOTE OFF instrument control code here.
}

void strumNote(int string) {
  digitalWrite(string, !digitalRead(string));
}

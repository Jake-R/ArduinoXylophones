#include <midi_Settings.h>
#include <midi_Defs.h>
#include <midi_Namespace.h>
#include <midi_Message.h>
#include <MIDI.h>
#include <Servo.h>

Servo servo;

MIDI_CREATE_DEFAULT_INSTANCE();
void handleNoteOn(byte channel, byte pitch, byte vel){
  switch(pitch)
  {
    // 60C 62d 64e 65F 67G 69A 71B 72C
  }
}

void setup(){
  MIDI.setHandleNoteOn(handleNoteOn);
  servo.attach(12);
  servo.write(90);
}

void loop(){
 
  byte thing = 0x0B;
  
  switch(thing)
  {
    case 11:
        servo.write(180);
        delay(150);
        break;
    default:
      break;
  }
  MIDI.read();
}

void writeServo(int num, int value) { 
}

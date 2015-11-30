#include <midi_Settings.h>
#include <midi_Defs.h>
#include <midi_Namespace.h>
#include <midi_Message.h>
#include <MIDI.h>
#include <Servo.h>


#define NOTE_C 0
#define NOTE_C_INDEX 0
#define NOTE_D 2
#define NOTE_D_INDEX 1
#define NOTE_E 4
#define NOTE_E_INDEX 2
#define NOTE_F 5
#define NOTE_F_INDEX 3
#define NOTE_G 7
#define NOTE_G_INDEX 4
#define NOTE_A 9
#define NOTE_A_INDEX 5
#define NOTE_B 11
#define NOTE_B_INDEX 6
#define NOTE_C2 12
#define NOTE_C2_INDEX 7
#define NUM_SERVOS 4

Servo servos[4];

const int servoPins[4] = {2, 3, 4, 5};    //defines which pin each servo attaches to
const int center[4] = {90, 90, 90, 90};    //defines the true center value for the servo
const int noteServo[8] = {0, 0, 1, 1, 2, 2, 3, 3};    //defines which note maps to which servo
const int noteValue[8] = {180, 0, 180, 0, 180, 0, 180, 0};   //defines which direction to swing the servo to hit the note
const int noteDelay[8] = {100, 100, 100, 100, 100, 100, 100, 100};  //defines the number of milliseconds it takes to hit the note
int octaveOffset = 60;    //must increment or decrement by 12 to shift one octave

MIDI_CREATE_DEFAULT_INSTANCE();

void handleNoteOn(byte channel, byte pitch, byte vel){
  switch(pitch - octaveOffset)
  {
    case NOTE_C:
      strikeNote(NOTE_C_INDEX);
      break;
    case NOTE_D:
      strikeNote(NOTE_D_INDEX);
      break;
    case NOTE_E:
      strikeNote(NOTE_E_INDEX);
      break;
    case NOTE_F:
      strikeNote(NOTE_F_INDEX);
      break;
    case NOTE_G:
      strikeNote(NOTE_G_INDEX);
      break;
    case NOTE_A:
      strikeNote(NOTE_A_INDEX);
      break;
    case NOTE_B:
      strikeNote(NOTE_B_INDEX);
      break;
    case NOTE_C2:
      strikeNote(NOTE_C2_INDEX);
      break;
    default:
      //do nothing
      break;
  }
}

void setup(){
  MIDI.setHandleNoteOn(handleNoteOn);

  //attach servos to pins and center them
  for(int i = 0; i < NUM_SERVOS; i++){
    servos[i].attach(servoPins[i]);
    servos[i].write(center[i]);
  }
}

void loop(){
  MIDI.read();
}
//strikes a note according to noteNum and constants defined above
void strikeNote(int noteNum) {
  servos[noteServo[noteNum]].write(noteValue[noteNum]);
  delay(noteDelay[noteNum]);
  servos[noteServo[noteNum]].write(center[noteServo[noteNum]]);
}

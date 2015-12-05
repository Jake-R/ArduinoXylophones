#include <Timer.h>
#include <Event.h>
#include <midi_Settings.h>
#include <midi_Defs.h>
#include <midi_Namespace.h>
#include <midi_Message.h>
#include <MIDI.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include "pitches.h"

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

#define PIEZO_PIN 10
#define DO_PIEZO
#define LEDPIN 7
//#define NDEBUG

Servo servos[NUM_SERVOS];
Timer t;
const int servoPins[NUM_SERVOS] = {5, 6, 7, 11};    //defines which pin each servo attaches to
const int center[NUM_SERVOS] = {90, 90, 90, 90};    //defines the true center value for the servo
const int noteServo[8] = {0, 0, 1, 1, 2, 2, 3, 3};    //defines which note maps to which servo
const int noteValue[8] = {180, 0, 180, 0, 180, 0, 180, 0};   //defines which direction to swing the servo to hit the note
const int noteDelay[8] = {100, 100, 100, 100, 100, 100, 100, 100};  //defines the number of milliseconds it takes to hit the note
const int notePWM[8]={NOTE_C5,NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int octaveOffset = 60;    //must increment or decrement by 12 to shift one octave
SoftwareSerial SoftSerial(8, 9);
MIDI_CREATE_INSTANCE(SoftwareSerial, SoftSerial, MIDI);

void handleNoteOn(byte channel, byte pitch, byte vel){
#ifndef NDEBUG
  char output[35];
  sprintf(output, "NoteOn:ch=%02X, pitch=%02X/%d, vel=%02X", channel, pitch, pitch, vel);
  Serial.println(output);
#endif
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
#ifdef DO_PIEZO
void handleNoteOff(byte channel, byte pitch, byte vel) {
#ifndef NDEBUG
  char output[35];
  sprintf(output, "NoteOff:ch=%02X, pitch=%02X/%d, vel=%02X", channel, pitch, pitch, vel);
  Serial.println(output);
#endif
  noTone(PIEZO_PIN);
}
#endif
void setup(){
  MIDI.setHandleNoteOn(handleNoteOn);
#ifdef DO_PIEZO
  MIDI.setHandleNoteOff(handleNoteOff);
#endif
  MIDI.begin(MIDI_CHANNEL_OMNI);
#ifndef NDEBUG
  Serial.begin(9600);
  Serial.println("Setting up.");
#endif
  pinMode(PIEZO_PIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  //attach servos to pins and center them
  for(int i = 0; i < NUM_SERVOS; i++){
    servos[i].attach(servoPins[i]);
    servos[i].write(center[i]);
  }
}

void loop(){
  MIDI.read();
  t.update();
}
//strikes a note according to noteNum and constants defined above
void strikeNote(int noteNum) {
#ifdef DO_PIEZO
  tone(PIEZO_PIN, notePWM[noteNum]);
#endif
  servos[noteServo[noteNum]].write(noteValue[noteNum]);
  setTimer(noteNum);
}
int setTimer(int noteNum) {
  switch(noteNum) {
    case NOTE_C_INDEX:
      return t.after(noteDelay[noteNum], timerStopC);
    case NOTE_D_INDEX:
      return t.after(noteDelay[noteNum], timerStopD);;
    case NOTE_E_INDEX:
      return t.after(noteDelay[noteNum], timerStopE);
    case NOTE_F_INDEX:
      return t.after(noteDelay[noteNum], timerStopF);
    case NOTE_G_INDEX:
      return t.after(noteDelay[noteNum], timerStopG);
    case NOTE_A_INDEX:
      return t.after(noteDelay[noteNum], timerStopA);
    case NOTE_B_INDEX:
      return t.after(noteDelay[noteNum], timerStopB);
    case NOTE_C2_INDEX:
      return t.after(noteDelay[noteNum], timerStopC2);
    default:
      //do nothing
      break;
  }
}

void timerStopC() {
#ifndef NDEBUG
  Serial.println("Timer Stopped note C");
#endif
  servos[servoPins[NOTE_C_INDEX]].write(center[servoPins[NOTE_C_INDEX]]);
}
void timerStopD() {
#ifndef NDEBUG
  Serial.println("Timer Stopped note D");
#endif
  servos[servoPins[NOTE_D_INDEX]].write(center[servoPins[NOTE_D_INDEX]]);
}
void timerStopE() {
#ifndef NDEBUG
  Serial.println("Timer Stopped note E");
#endif
  servos[servoPins[NOTE_E_INDEX]].write(center[servoPins[NOTE_E_INDEX]]);
}
void timerStopF() {
#ifndef NDEBUG
  Serial.println("Timer Stopped note F");
#endif
  servos[servoPins[NOTE_F_INDEX]].write(center[servoPins[NOTE_F_INDEX]]);
}
void timerStopG() {
#ifndef NDEBUG
  Serial.println("Timer Stopped note G");
#endif
  servos[servoPins[NOTE_G_INDEX]].write(center[servoPins[NOTE_G_INDEX]]);
}
void timerStopA() {
#ifndef NDEBUG
  Serial.println("Timer Stopped note A");
#endif
  servos[servoPins[NOTE_A_INDEX]].write(center[servoPins[NOTE_A_INDEX]]);
}
void timerStopB() {
#ifndef NDEBUG
  Serial.println("Timer Stopped note B");
#endif
  servos[servoPins[NOTE_B_INDEX]].write(center[servoPins[NOTE_B_INDEX]]);
}
void timerStopC2() {
#ifndef NDEBUG
  Serial.println("Timer Stopped note C2");
#endif
  servos[servoPins[NOTE_C2_INDEX]].write(center[servoPins[NOTE_C2_INDEX]]);
}

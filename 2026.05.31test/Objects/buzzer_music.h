#ifndef __BUZZER_MUSIC_H__
#define __BUZZER_MUSIC_H__

#include "Delay.h"

#define NOTE_REST   0
#define NOTE_L1     262
#define NOTE_L2     294
#define NOTE_L3     330
#define NOTE_L4     349
#define NOTE_L5     392
#define NOTE_L6     440
#define NOTE_L7     494
#define NOTE_1      523
#define NOTE_2      587
#define NOTE_3      659
#define NOTE_4      698
#define NOTE_5      784
#define NOTE_6      880
#define NOTE_7      988
#define NOTE_H1     1047

#define TEMPO_MS    300

typedef struct {
    unsigned int freq;
    unsigned char beat;
} Note;

void Set_Note(unsigned int freq);
void Delay_Beat(unsigned char beat);
void Play_Music(void);
void Buzzer_Loop(void);
void Buzzer_Init(void);

#endif

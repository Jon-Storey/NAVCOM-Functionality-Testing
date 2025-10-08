/**
 * buzzer.h
 *
 * Created on: 20 May 2025
 * Author: JonathanStorey
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include <stdint.h>

// Note frequencies in Hz
typedef enum {
    NOTE_C4  = 262,  // Middle C
    NOTE_D4  = 294,  // D
    NOTE_E4  = 330,  // E
    NOTE_F4  = 349,  // F
    NOTE_G4  = 392,  // G
    NOTE_A4  = 440,  // A
    NOTE_B4  = 494,  // B
    NOTE_C5  = 523,  // C (octave)
    NOTE_C6  = 1047,  // Very High C
    NOTE_C7  = 2093,  // Extremely High C
    NOTE_OFF = 0     // Silence
} note_t;

// Function prototypes
void buzzer_init(void);
void buzzer_play_note(note_t note, uint32_t duration_ms);

// Optional additional functions you might want:
// void buzz_one_second(void);
// void set_buzz_frequency(int freq);
// void buzz_sweep(void);

#endif /* BUZZER_H_ */

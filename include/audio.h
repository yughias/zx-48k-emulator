#ifndef __AUDIO_H__
#define __AUDIO_H__

#define AUDIO_FREQUENCY   44100
#define AUDIO_SAMPLES      1024
#define AUDIO_BUFFER_SIZE  2048

void initAudio();
void freeAudio();
void emulateAudio();

#endif
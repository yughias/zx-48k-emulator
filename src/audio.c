#include <hardware.h>
#include <SDL_MAINLOOP.h>

SDL_AudioSpec audioSpec;
SDL_AudioDeviceID audioDev;

uint8_t buffer[AUDIO_BUFFER_SIZE];
int bufIdx = 0;

int audio_request_rate;
int audio_counter;

void initAudio(){
    SDL_memset(&audioSpec, 0, sizeof(audioSpec));
    audioSpec.freq = AUDIO_FREQUENCY;
    audioSpec.format = AUDIO_U8;
    audioSpec.channels = 1;
    audioSpec.samples = AUDIO_SAMPLES;
    audioSpec.callback = NULL;
    audioDev = SDL_OpenAudioDevice(NULL, 0, &audioSpec, &audioSpec, 0);

    audio_request_rate = CLOCK_PER_FRAME * REFRESH_RATE / AUDIO_FREQUENCY;
    audio_counter = 0;

    SDL_PauseAudioDevice(audioDev, 0);
}

void emulateAudio(){
    if(!audio_counter && bufIdx != AUDIO_BUFFER_SIZE){
        uint8_t sample = (ULA & 0b10000) ? 255 : 0;
        buffer[bufIdx++] = sample;
        audio_counter = audio_request_rate;
    } 

    if(bufIdx >= AUDIO_SAMPLES && SDL_GetQueuedAudioSize(audioDev) < AUDIO_BUFFER_SIZE){
        SDL_QueueAudio(audioDev, &buffer, bufIdx);
        bufIdx = 0;
    }

    if(audio_counter)
        audio_counter--;
}

void freeAudio(){
    SDL_CloseAudioDevice(audioDev);
}
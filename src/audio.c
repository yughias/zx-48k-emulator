#include <hardware.h>
#include <SDL_MAINLOOP.h>

SDL_AudioSpec audioSpec;
SDL_AudioDeviceID audioDev;

uint8_t buffer[AUDIO_BUFFER_SIZE];
size_t bufIdx = 0;

size_t audio_request_rate;
size_t audio_counter;

size_t queued_samples;
size_t queued_check_counter;
size_t queued_check_rate; 

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

    queued_check_rate = audio_request_rate * AUDIO_SAMPLES;
    queued_check_counter = 0;

    SDL_PauseAudioDevice(audioDev, 0);
}

void emulateAudio(){
    if(!audio_counter && bufIdx < AUDIO_BUFFER_SIZE){
        uint8_t sample = (ULA & 0b10000) ? SDL_MAX_UINT8 : audioSpec.silence;
        buffer[bufIdx++] = sample;
        audio_counter = audio_request_rate;
    } 

    if(bufIdx >= AUDIO_SAMPLES && queued_samples < AUDIO_SAMPLES*2){
        SDL_QueueAudio(audioDev, &buffer, bufIdx);
        bufIdx = 0;
    }

    if(!queued_check_counter){
        queued_samples = SDL_GetQueuedAudioSize(audioDev);
        queued_check_counter = queued_check_rate;
    }

    if(audio_counter)
        audio_counter--;

    if(queued_check_counter)
        queued_check_counter--;
}

void freeAudio(){
    SDL_CloseAudioDevice(audioDev);
}
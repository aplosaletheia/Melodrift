#include "types.h"
#include "config.h"

#include <stdio.h>
#include <Windows.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define DFT_SC 10

typedef struct
{
    size_t freqCount;
    float* x;
    float* y;
} fdd_s;

static freqDomainST_s fft(audioInfo_s);
static fdd_s dft(audioInfo_s, float);


freqDomain_s stft(audioInfo_s audioInfo)
{
    freqDomain_s result;
    result.intervalCount = audioInfo.sampleDuration/ST;
    result.intervals = malloc(result.intervalCount*sizeof(*result.intervals));

    audioInfo_s fftPass = { audioInfo.sampleDuration / ST, audioInfo.sampleRate, ST};
    fftPass.samples = malloc(fftPass.sampleCount*sizeof(*(fftPass.samples)));

    for (size_t i = 0; i < audioInfo.sampleCount; i += fftPass.sampleCount)
    {
        memcpy(fftPass.samples, audioInfo.samples + i, fftPass.sampleCount*sizeof(*fftPass.samples));
        result.intervals[i/fftPass.sampleCount] = fft(fftPass);
    }

    free(fftPass.samples);
    return result;
}

static freqDomainST_s fft(audioInfo_s audioInfo)
{
    freqDomainST_s result;
    result.freqCount = ((float)F_MAX) / F_RES;
    result.amps = malloc(result.freqCount*sizeof(*result.amps));

    fdd_s fd = {result.freqCount};
    fd.x = malloc(result.freqCount*sizeof(*result.amps));
    fd.y = malloc(result.freqCount*sizeof(*result.amps));

    //reorder the smaples
    


    //apply dft

    

    // assembly of data



    
    free(fd.x);
    free(fd.y);
    return result;
}

static fdd_s dft(audioInfo_s audioInfo, float phase)
{
    fdd_s result = {audioInfo.sampleCount/2};
    result.x = malloc(result.freqCount*sizeof(*result.x));
    result.y = malloc(result.freqCount*sizeof(*result.y));
    size_t i = 0;
    for (float f = 1/audioInfo.sampleDuration; f <= audioInfo.sampleRate/2 ; f += 1/audioInfo.sampleDuration, i++)
    {
        float x = 0;
        float y = 0;

        float delta = (2*M_PI*f)/audioInfo.sampleRate; //increase per sample
        float deltaSin = sinf(delta);
        float deltaCos = cosf(delta);
        float currSin = sinf(phase*2*M_PI*f);
        float currCos = cosf(phase*2*M_PI*f);
        float sinTemp;
        for (size_t j = 0; j < audioInfo.sampleCount; j++)
        {
            x += audioInfo.samples[j]*currSin;
            y += audioInfo.samples[j]*currCos;
            sinTemp = currSin;
            currSin = currSin*deltaCos + currCos*deltaSin;
            currCos = currCos*deltaCos - sinTemp*deltaSin;
        }
        result.x[i] = x;
        result.y[i] = y;
        //printf("%f - %f\n", f, result.amps[i]);
    }
    return result;
}


int main()
{
    audioInfo_s hundhz;
    hundhz.sampleRate = 100;
    hundhz.sampleCount =100;
    hundhz.sampleDuration = 1;
    hundhz.samples = malloc(hundhz.sampleCount*sizeof(*hundhz.samples));

    for (size_t i = 0; i < hundhz.sampleCount; i++)
    {
        hundhz.samples[i] = sinf(2*M_PI*101 * i/hundhz.sampleRate);
    }


    // printf("%zu\n", res.freqCount);
    for (size_t i = 0; i < res.freqCount; i++)
    {
        if (res.amps[i] > 0.1)
        {
            printf("%.0f -> %.3f\n", (i+1)*F_RES, res.amps[i]);
        }
    }
}

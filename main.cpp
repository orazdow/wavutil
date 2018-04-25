#include <stdio.h>
#include "wavutil.h"
#include <math.h>
#include "pa.h"

double phase = 0, phase2 = 0; 
double step = 3.141592653589*440/44100.0;
double step2 = 3.141592653589*400/44100.0;

void writeCallBack(uint16_t* data, unsigned long num_frames, unsigned int frame_size){

    for(unsigned int i = 0; i < num_frames; i+=frame_size){
         uint16_t sig = (uint16_t)(sin(phase)*5000);
         phase += step;      
         uint16_t sig2 = (uint16_t)(sin(phase2)*5000);
         phase2 += step2;
         //left
         *data++ = sig;
         // right
         *data++ = sig2;
    }   
    
}

int main(int argc, char** argv) {     
    writeWav("thewav.wav", writeCallBack, 2, 16, 44100, 3000);
    struct WavHeader wh;
    getWav("thewav.wav", &wh);
    // printHeader(wh,0);
    return 0;
}


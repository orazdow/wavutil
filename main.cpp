#include <stdio.h>
#include "wavutil.h"
#include <math.h>
#include "pa.h"

const double PI = acos(-1);
const double srate = 44100;
const float downcvt = (float)1/32768.0;


double phase = 0, phase2 = 0; 
double step = 2*PI*220/srate;
double step2 = 2*PI*400/srate;

typedef struct{

  short* data;
  size_t length;
  unsigned long long index;

}wavbuff;


void writeCallBack(uint16_t* data, unsigned long num_frames, unsigned int frame_size){

    for(unsigned int i = 0; i < num_frames; i+=frame_size){
         uint16_t sig = (uint16_t)(sin(phase)*5000);
         phase += step;      
         // uint16_t sig2 = (uint16_t)(sin(phase2)*5000);
         // phase2 += step2;
         //left
         *data++ = sig;
         // right
        // *data++ = sig2;
    }   
    
}

void pafunc(const float* in, float* out, unsigned long frames, void* data){

        wavbuff* w = (wavbuff*)data;
          for(unsigned long i = 0; i < frames; i++ ){

            *out++ = (float)w->data[w->index]*downcvt;
            if(w->index < w->length-1)
              w->index++;
             // phase += step;
             // *out++ = sin(phase)*0.5;
         }
}

int main(int argc, char** argv) {     
     // writeWav("thewav.wav", writeCallBack, 1, 16, srate, 3000);
     WavHeader wh;
     wavbuff wb;
     getWav("out.wav", &wh);
     wb.data = (short*)wh.data;
     wb.length = wh.numsamples;
     wb.index = 0;
     printHeader(wh,0);
    Pa a(pafunc, &wb);
    a.start(Pa::waitForKey);
    return 0;
}

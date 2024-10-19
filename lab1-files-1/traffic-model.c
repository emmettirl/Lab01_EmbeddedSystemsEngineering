#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>
#include <string.h>
#include "traffic-model.h"


struct State {
  unsigned long Out;
  unsigned long Time;
  unsigned long Next[4];};
typedef const struct State STyp;

#define goN   0
#define waitN 1
#define goE   2
#define waitE 3

STyp FSM[4]={
 {0x21,3000,{goN,waitN,goN,waitN}},
 {0x22, 500,{goE,goE,goE,goE}},
 {0x0C,3000,{goE,goE,waitE,waitE}},
 {0x14, 500,{goN,goN,goN,goN}}};

unsigned long S;  // index to the current state

unsigned long Input=0;




// cc.byexamples.com calls this int kbhit(), to mirror the Windows console
//  function of the same name.  Otherwise, the code is the same.
int inputAvailable()
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return (FD_ISSET(0, &fds));
}

int traffic_model_main()
{
    char data[200];
    int oldOutput = 0;

    S = goN;
    while(1){
        usleep(100);

        /* add in  here your emulation of the code */


        //LIGHT = FSM[S].Out;
        int bits = 6;
        for (int i = bits; i >= 0; i--) {
            unsigned long bit = (FSM[S].Out >> i) & 1;
            switch (i) {
                case 5:
                    printf("%d : %lu", i, bit);
                    break;
                case 4:
                    printf("%d : %lu", i, bit);
                    break;
                case 3:
                    printf("%d : %lu", i, bit);
                    break;
                case 2:
                    printf("%d : %lu", i, bit);
                    break;
                case 1:
                    printf("%d : %lu", i, bit);
                    break;
                case 0:
                    printf("%d : %lu", i, bit);
                    break;
            }
            printf("\n");
            fflush(stdout);

        }
        printf("\n");
        fflush(stdout);



        //  SysTick_Wait10ms(FSM[S].Time);   // no need of this line in initial testing
                                     // use usleep() instead of Syst=Tick_Wait

        //Input = SENSOR;             // read sensors the input value is set in the
                                // if statement below

        if (inputAvailable()) {
            Input =0;
            scanf("%s" , data);
            printf("you entered %s\n",data);
            fflush(stdout);

            if (strcmp(data, "N") == 0 || strcmp(data, "n" )== 0) { Input = 0b10;}
            else if (strcmp(data, "E") == 0 || strcmp(data, "e" )== 0) {Input = 0b01;}
            else if (strcmp(data, "B") == 0 || strcmp(data, "b" )== 0) {Input = 0b11;}
            else {Input = 0b00;}

            printf("Input is %d\n", Input);
       }

        S = FSM[S].Next[Input];     // keep this line as is
   }

}

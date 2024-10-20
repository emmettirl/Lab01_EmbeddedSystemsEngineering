#include <unistd.h>
#include <stdio.h>
#include <sys/select.h>
#include <string.h>

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
    {0x14, 500,{goN,goN,goN,goN}}
};

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
//    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
//    return (FD_ISSET(0, &fds));
    return 1;
}

int main()
{
    char data[200];
    int oldOutput = 0;
    S = goN;

    while(1){
//        usleep(100);

        for (volatile unsigned int i = 0; i < 100 * 1000; i++);

        // if the output has changed, print the new state of the traffic lights
        if (oldOutput != FSM[S].Out) {
            oldOutput = FSM[S].Out;

            // print the current state of the traffic lights
            // I'm doing this by checking the value of each bit in the Out field of the FSM,
            // based on the position of the bit printing the corresponding light colour if the bit is 1.
            // It has dawned on me, that I have made this more complicated than it needs to be.
            // I should have just compare the decimal number in one switch statement, not bit by bit
            // its working now though, so I'm not going to change it.

            int bits = 6;
            for (int i = bits; i >= 0; i--) {
                unsigned long bit = (FSM[S].Out >> i) & 1;
                switch (i) {
                    case 5:
                        if (bit == 1) {
                            printf("%s : ", "East Red");
                        }
                        break;
                    case 4:
                        if (bit == 1) {
                            printf("%s : ", "East Yellow");
                        }
                        break;
                    case 3:
                        if (bit == 1) {
                            printf("%s : ", "East Green");
                        }
                        break;
                    case 2:
                        if (bit == 1) {
                            printf("%s : ", "North Red");
                        }
                        break;
                    case 1:
                        if (bit == 1) {
                            printf("%s : ", "North Yellow");
                        }
                        break;
                    case 0:
                        if (bit == 1) {
                            printf("%s : ", "North Green");
                        }
                        break;
                }
            }
            printf("\n");
            fflush(stdout);
        }

        //  SysTick_Wait10ms(FSM[S].Time);   // no need of this line in initial testing
                                     // use usleep() instead of Syst=Tick_Wait

        //Input = SENSOR;             // read sensors the input value is set in the
                                // if statement below

        if (inputAvailable()) {
            Input = 0;
            scanf("%s", data);

            if (strcmp(data, "N") == 0 || strcmp(data, "n") == 0) { Input = 0b10; }
            else if (strcmp(data, "E") == 0 || strcmp(data, "e") == 0) { Input = 0b01; }
            else if (strcmp(data, "B") == 0 || strcmp(data, "b") == 0) { Input = 0b11; }
            else { Input = 0b00; }

            printf("Input is %d\n", Input);

            S = FSM[S].Next[Input];     // keep this line as is
            Input = 0;                  // reset the input
        }
   }

}

void c_entry(void) {
    main();
}
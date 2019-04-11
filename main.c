#include <stdio.h>
#include <stdlib.h>	// for random numbers, and system() function
#include <time.h>	// for randomisation
#include <signal.h>
#include "screen.h"
#include "sound.h"
#include "comm.h"

int main(int argc, char **argv){
	if(argc>1){						// if user has given some command line segments
		printf("Test tone generator\n");
		int fR, fL, ch;
		float duration;

		printf("No. of channels (1 or 2): ");
		scanf("%d", &ch);
		if(ch == 1){
			printf("Mono Frequency: ");
			scanf("%d", &fL);
		}else if(ch == 2){
            printf("Give me Left and Right freq: ");
            scanf("%d %d", &fL, &fR);
		}else{
			printf("Wrong number of channels\n");
			return 1;
		}
		printf("Duration of sound: ");
		scanf("%f", &duration);
		testTone(ch, fL, fR, duration);
		return 0;
	}
	FILE *f;
	short sd[RATE];
	for(;;){
		int ret = system(RCMD);
		if(ret == SIGINT) break;
		f = fopen("test.wav", "r");
		if(f==NULL){
			printf("Cannot open the file\n");
			return 1;
		}
//	int dec[COL], i;					//80 pieces of sound decibels

//	srand(time(NULL));
//	for(i=0; i<COL; i++) dec[i]= rand()%70+30;

		clearScreen();
//	barChart(dec);

		struct WAVHDR hdr;
		fread(&hdr, sizeof(hdr), 1, f);		// read WAV header
		fread(&sd, sizeof(sd), 1, f);		// read WAV data
		fclose(f);

		displayWAVHDR(hdr);
		displayWAVDATA(sd);

		sendDATA(sd);
	}
	resetColors();
//	getchar();
}

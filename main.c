#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "sound.h"


int main(){
	FILE *f;
	short sd[80000];
	for(;;){
	system(RCMD);
	f = fopen("test.wav", "r");
		if(f==NULL){
			printf("Cannot open the file\n");
			return 1;
		}
//	int dec[COL], i;					//80 pieces of sound decibels

//	srand(time(NULL));
//	for(i=0; i<COL; i++) dec[i]= rand()%70+30;

		clearScreen();
		setColors(RED, bg(PINK));
//	barChart(dec);

		struct WAVHDR hdr;
		fread(&hdr, sizeof(hdr), 1, f);		// read WAV header
		fread(&sd, sizeof(sd), 1, f);		// read WAV data
		fclose(f);

		displayWAVHDR(hdr);
		displayWAVDATA();
	}
	resetColors();
	getchar();
}

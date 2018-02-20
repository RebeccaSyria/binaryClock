#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define NORM	"\x1B[0m"
#define RED	"\x1B[31m"
#define GREEN	"\x1B[32m"
#define YELLOW	"\x1B[33m"
#define BLUE	"\x1B[34m"
#define MAGENTA	"\x1B[35m"
#define CYAN	"\x1B[36m"
#define WHITE	"\x1B[37m"

#define CLEAR	"\033[2J"

void printBin( int s ){
	printf("%d\n",s);
	char bin[] = "00000\0";
	int i = 5;
	while (s > 0){
		//printf("s: %d\n",s);
		bin[i] = (s % 2) + '0';
		//printf("%d",binSec[i]);
		s = s / 2;
		i--;
	}
	
	printf("%s",bin);
	
	printf("\n");
}

void printTime(){
	time_t t;
	struct tm *timeinfo;
	time(&t);
	timeinfo = localtime(&t);
	//printf("Time: %s\n",asctime(timeinfo));
	printBin(timeinfo->tm_hour);
	printBin(timeinfo->tm_min);
	printBin(timeinfo->tm_sec);
}

void changeColor(int c){
	switch( c ){
		case 0:
			printf("%s",NORM);
			break;
		case 1:
			printf("%s",RED);
			break;
		case 2:
			printf("%s",GREEN);
			break;
		case 3:
			printf("%s",YELLOW);
			break;
		case 4:
			printf("%s",BLUE);
			break;
		case 5:
			printf("%s",MAGENTA);
			break;
		case 6:
			printf("%s",CYAN);
			break;
		case 7:
			printf("%s",WHITE);
			break;
		}
}

int main( int argc, char * argv[] ){
	int opt;
	int color = 0;
	while( (opt = getopt(argc, argv, "c:h" )) != -1 ){
		switch( opt ){
			case 'c':
				color = atoi(optarg);
				changeColor( color );
				break;
			case 'h':
				printf("usage: \n");
				break;
			case '?':
				printf("usage: \n");
				break;
		}
	}

	printf("%s",CLEAR);
	fflush(stdout);
	while(1){
		printf("\033[6A");
		printTime();
		sleep(1);
	}
	printf("%s\n", NORM);
	return 0;
}

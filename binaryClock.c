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

void printTime(int seconds, int labels, int decimal){
	time_t t;
	struct tm *timeinfo;
	time(&t);
	timeinfo = localtime(&t);
	int s = timeinfo->tm_sec;
	int m = timeinfo->tm_min;
	int h = timeinfo->tm_hour;
	//printf("Time: %s\n",asctime(timeinfo));
	if( labels ){
		printf("Hour:   ");
	}	
	printBin(h);
	if( labels ){
		printf("Minute: ");
	}
	printBin(m);
	if( seconds ){
		if( labels ){
			printf("Second: ");
		}
		printBin(s);
	}
	if( decimal ){
		if( h < 10 ){
			printf("0%d:",h);
		}else{
			printf("%d:",h);
		}
		if( m < 10 ){
			printf("0%d",m);
		}else{
			printf("%d",m);
		}
		if( seconds ){
			if( s < 10 ){
				printf(":0%d",s);
			}else{
				printf(":%d",s);
			}
		}
		printf("\n");
	}
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

void printUsage(){
	printf("usage: binaryClock [-c [0..7]] [-s]\n");
	printf("\t -c [0..7] \t Set color\n");
	printf("\t -h \t\t Show this page\n");
	printf("\t -s \t\t Toggle seconds\n");
	printf("\t -l \t\t Toggle labels\n");	
	printf("\t -d \t\t Toggle decimal view\n");
}

int main( int argc, char * argv[] ){
	int lines = 2;
	int seconds = 0; //1 when seconds active
	int labels = 0; //1 when labels active
	int decimal = 0; //1 when decimal view active
	int opt;
	int color = 0;
	while( (opt = getopt(argc, argv, "c:hsld" )) != -1 ){
		switch( opt ){
			case 'c':
				color = atoi(optarg);
				changeColor( color );
				break;
			case 'h':
				printUsage();
				return 0;
				break;
			case 's':
				seconds = 1;
				lines += 1;
				break;
			case 'l':
				labels = 1;
				break;
			case 'd':
				decimal = 1;
				lines += 1;
				break;
			case '?':
				printUsage();
				return 1;
				break;
		}
	}

	printf("%s",CLEAR);
	fflush(stdout);

	while(1){
		printf("\033[%dA",lines);
		printTime(seconds, labels, decimal);
		sleep(1);
	}
	printf("%s\n", NORM);
	return 0;
}

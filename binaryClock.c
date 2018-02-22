#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#define NORM	"\x1B[0m"
#define RED	"\x1B[31m"
#define GREEN	"\x1B[32m"
#define YELLOW	"\x1B[33m"
#define BLUE	"\x1B[34m"
#define MAGENTA	"\x1B[35m"
#define CYAN	"\x1B[36m"
#define WHITE	"\x1B[37m"

#define CLEAR	"\033[2J"
#define HIDE	"\e[?25l"
#define SHOW	"\e[?25h"
#define BOLD	"\e[1m"

void printBin( int s, char on, char off ){
	char bin[] = "000000";
	for( int n = 0; n < 5; n++){
		bin[n] = off;
	}
	//bin[6] = '\0';
	int i = 5;
	while (s > 0){
		//printf("s: %d\n",s);
		if( (s%2) == 0){
			bin[i] = off;
		}else{
			bin[i] = on;
		}
		//bin[i] = (s % 2) + '0';
		//printf("%d",binSec[i]);
		s = s / 2;
		i--;
	}
	//for(int i = 0; i < 6; i++){
	//	switch(bin[i]){
	//		case '0':
	//			printf("%c",off);
	//			break;
	//		case '1':
	//			printf("%c",on);
	//			break;
	//}
	//	if( bin[i] == '0'){
	//		printf("%lc",off);
	//	}else{
	//		printf("%lc",on);
	//	}
	//}
	printf("%s",bin);
	printf("\n");
}

void printTime(int seconds, int labels, int decimal, char on, char off){
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
	printBin(h, on, off);
	if( labels ){
		printf("Minute: ");
	}
	printBin(m, on, off);
	if( seconds ){
		if( labels ){
			printf("Second: ");
		}
		printBin(s, on, off);
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
	printf("usage: binaryClock [arguments]\n");
	printf("Arguments:\n");
	printf("   -c [0..7] \t Set color\n");
	printf("   -h \t\t Show this page\n");
	printf("   -s \t\t Toggle seconds\n");
	printf("   -l \t\t Toggle labels\n");	
	printf("   -b \t\t Toggle bold font\n");
	printf("   -d \t\t Toggle decimal view\n");
	printf("   -o [char]\t Set on character (default: 1)\n");
	printf("   -f [char]\t Set off character (default: 0)\n");
	printf("%s%s\n",NORM,SHOW);	
}

static void hdl(int signum){
	printf("%s%s\n",NORM,SHOW);
	exit(signum);
}

int main( int argc, char * argv[] ){
	setlocale(LC_ALL, "en_US.utf8");
	signal(SIGINT, hdl);
	int lines = 2;
	int seconds = 0; //1 when seconds active
	int labels = 0; //1 when labels active
	int decimal = 0; //1 when decimal view active
	char on = '1';
	char off = '0';
	int opt;
	int color = 0;
	int bold = 0; //1 when bold
	while( (opt = getopt(argc, argv, "c:bhsldo:f:" )) != -1 ){
		switch( opt ){
			case 'c':
				color = atoi(optarg);
				break;
			case 'b':
				bold = 1;
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
			case 'o':
				on = *optarg;
				break;
			case 'f':
				off = *optarg;
				break;
			case '?':
				printUsage();
				return 1;
				break;
		}
	}

	printf("%s%s",CLEAR,HIDE);
	changeColor( color );
	if( bold ){
		printf("%s",BOLD);
	}
	fflush(stdout);
	
	while(1){
		printf("\033[%dA",lines);
		printTime(seconds, labels, decimal, on, off);
		sleep(1);
	}
	return 0;
}

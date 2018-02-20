#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NORM	"\x1B[0m"
#define RED	"\x1B[31m"
#define GREEN	"\x1B[32m"
#define YELLOW	"\x1B[33m"
#define BLUE	"\x1B[34m"
#define MAGENTA	"\x1B[35m"
#define CYAN	"\x1B[36m"
#define WHITE	"\x1B[37m"

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
	printf("Test! %s\n", NORM);
	return 0;
}

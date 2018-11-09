#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXLOOP 1000
#define MANY 0
#define FEW 1

double expdev(double);
int choose_pp(void);

static int toilet[MAXLOOP];

int main(int argc, char *argv[]){
	int buf;
	int time = 0;
	double pp1 = 600;
	double pp2 = 600;
	double use_pp = 80;
	int i, itemp, itemp2;
	int cln_arr = 360;
	double usr_arr = 15.0;

	itemp2 = 0;
	do {
		itemp = (int)(expdev(usr_arr));
		itemp2 += itemp;
	} while (itemp2 < MAXLOOP && ( toilet[itemp2] = 1 ));

	while(1){
		if(toilet[time] == 1){
			if(choose_pp == MANY) pp1 > pp2 ? pp1 - use_pp : pp2 - use_pp;
			if(choose_pp ==  FEW) pp2 > pp1 ? pp1 - use_pp : pp2 - use_pp;
		}
		

		time++;

		printf("\nNext(Enter) or (Q)uit?");
		scanf("%c", &buf);
		if(buf == 'q' || buf == 'Q') break;
	}
	return 0;
}

double expdev(double ave){
	double r;
	double alpha;

	alpha = 1/ave;
	r = (float)rand()/(RAND_MAX + 1.0) * 1.0;
	return -(1.0/alpha)*log(1.0-r) + 1.0;
}

int choose_pp(void){
	double x;
	x = (float)rand()/(RAND_MAX + 1.0) * 1.0;
	if (x < 0.3) return MANY;
	if (0.7 < x) return FEW;
}

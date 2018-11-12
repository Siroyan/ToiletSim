#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXLOOP 3600
#define MANY 0
#define FEW 1
#define USR_ARR 30.0

double expdev(double);
int choose_pp(void);

static int many;
static int few;
static int oh;
static double selectRatio = 0.0;

int main(int argc, char *argv[]){
	int pp1 = 600;
	int pp2 = 600;
	int use_pp = 80;
	int *pp_h, *pp_l;
	FILE *fd;
	fd = fopen("data.d","w");
	while(selectRatio < 1.0){
		int time = 0;
		int toilet[MAXLOOP] = {};
		int itemp;
		int itemp2 = 0;
		do {
			itemp = (int)(expdev(USR_ARR));
			itemp2 += itemp;
		} while (itemp2 < MAXLOOP && ( toilet[itemp2] = 1 ));

		int icln = 0;
		while(time < MAXLOOP){
	    //Cleaner set pp.
		    if(icln == 120){
		      if(pp1 == 0) pp1 = 600;
		      if(pp2 == 0) pp2 = 600;
		      icln = 0;
		    }

		    if(pp1 > pp2) {
		      pp_h = &pp1;
		      pp_l = &pp2;
		    } else {
		      pp_h = &pp2;
		      pp_l = &pp1;
		    }
			if(toilet[time] == 1){
				if(choose_pp() == MANY){
					if(*pp_h > use_pp){
						*pp_h -= use_pp;
					}else{
						if(*pp_l > use_pp){
							*pp_l -= (use_pp - *pp_h);
							*pp_h = 0;
						}else{
							*pp_l = 600;
							*pp_h = 600;
							oh++;
						}
					}
				}else{
					if(*pp_l > use_pp){
						*pp_l -= use_pp;
					}else{
						if(*pp_h > use_pp){
							*pp_h -= (use_pp - *pp_l);
							*pp_l = 0;
						}else{
							*pp_h = 600;
							*pp_l = 600;
							oh++;
						}
					}
				}
			}
		    time++;
		    icln++;
		}
		printf("--- R E S U L T ---\n");
		printf("    MANY: %d\n", many);
		printf("     FEW: %d\n", few);
		printf("SELRATIO: %1.1f\n", selectRatio);
		printf("   RATIO: %1.2f %%\n", (double) oh / (many + few) * 100);
		fprintf(fd, "%f %f\n", selectRatio * 100, (double) oh / (many + few) * 100);
		icln = 0;
		pp1 = 0;
		pp2 = 0;
		many = 0;
		few = 0;
		oh = 0;
		selectRatio += 0.01;
	}
	fclose(fd);
	return 0;
}

double expdev(double ave){
	double r;
	double alpha;
	alpha = 1/ave;
	r = (double)rand()/(RAND_MAX + 1.0) * 1.0;
	return -(1.0/alpha)*log(1.0 - r) + 1.0;
}

int choose_pp(void){
	double x;
	x = (double)rand()/(RAND_MAX + 1.0) * 1.0;
	if (x <= selectRatio) {
    	many++;
		return MANY;
	} else {
    	few++;
		return FEW;
	}
}

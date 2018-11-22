#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXLOOP 1000000
#define MANY 0
#define FEW 1
#define USEPP 80

double expdev(double);
int choose_pp(void);

static int many;
static int few;
static int oh;
static double selectRatio = 0.0;

int main(int argc, char *argv[]){
	srand((unsigned) time(NULL));
	int pp1, pp2, *pp_h, *pp_l;
	int itemp, itemp2;
	int time;
	int cnt = 0;
	char filename[16];
	FILE *fd;

	sprintf(filename, "average/%s.csv", argv[1]);
	fd = fopen(filename,"w");
	while(selectRatio < 1.0){
		pp1 = 600;
		pp2 = 600;
		time = 0;
		itemp2 = 0;
		int toilet[MAXLOOP] = {};
		do {
			itemp = (int)(expdev(atoi(argv[1])));
			itemp2 += itemp;
		} while (itemp2 < MAXLOOP && ( toilet[itemp2] = 1 ));
		while(time < MAXLOOP){
		    if(time % 300 == 0){
		    	if(pp1 == 0) pp1 = 600;
		    	if(pp2 == 0) pp2 = 600;
		    }

		    if(pp1 > pp2) {
		    	pp_h = &pp1;
		    	pp_l = &pp2;
		    }else{
		    	pp_h = &pp2;
		    	pp_l = &pp1;
		    }

			if(toilet[time] == 1){
				if(choose_pp() == MANY){
					if(*pp_h > USEPP){
						*pp_h -= USEPP;
					}else{
						if(*pp_l > USEPP){
							*pp_l -= (USEPP - *pp_h);
							*pp_h = 0;
						}else{
							*pp_l = 600;
							*pp_h = 600;
							oh++;
						}
					}
				}else{
					if(*pp_l > USEPP){
						*pp_l -= USEPP;
					}else{
						if(*pp_h > USEPP){
							*pp_h -= (USEPP - *pp_l);
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
		}
		printf("--- R E S U L T ---\n");
		printf(" MANY: %d\n", many);
		printf("  FEW: %d\n", few);
		printf("   Oh: %d\n", oh);
		fprintf(fd, "%f,%f\n", selectRatio * 100, (double) oh / (many + few) * 100);
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

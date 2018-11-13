#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXLOOP 1000
#define MANY 0
#define FEW 1

double expdev(double);
int choose_pp(void);

static int toilet[MAXLOOP];
static int many;
static int few;

int main(int argc, char *argv[]){
  int buf;
  int time = 0;
  int flag = 0;
  int icln = 0;
  int pp1 = 600;
  int pp2 = 600;
  int use_pp = 80;
  int *pp_h, *pp_l;
  int i, itemp, itemp2;
  double usr_arr = 40.0;
  FILE *fd;

  fd = fopen("data1.d","w");
  itemp2 = 0;
  do {
    itemp = (int)(expdev(usr_arr));
    itemp2 += itemp;
  } while (itemp2 < MAXLOOP && ( toilet[itemp2] = 1 ));

  while(time < MAXLOOP){
    //Cleaner set pp.
    if(icln == 60){
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
            *pp_l = 0;
            *pp_h = 0;
            printf("Oh...\n");
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
            *pp_h = 0;
            *pp_l = 0;
            printf("Oh...\n");
          }
        }
      }
    }
    /*
    int i,j;
    printf("pp1 [");
    for(i=0;i<pp1;i=i+20){
      printf("#");
    }
    printf("]\n");
    printf("pp2 [");
    for(j=0;j<pp2;j=j+20){
      printf("#");
    }
    printf("]\n");
    */
    fprintf(fd,"%d %d %d\n", time, pp1, pp2);
    time++;
    icln++;
    /*
    printf("\nNext(Enter) or (Q)uit?");
    scanf("%c", &buf);
    if(buf == 'q' || buf == 'Q') break;
    */
  }
  fclose(fd);
  printf("--- R E S U L T ---\n");
  printf("MANY: %d\n",many);
  printf(" FEW: %d\n",few);
  return 0;
}

double expdev(double ave){
	double r;
	double alpha;
	alpha = 1/ave;
	srand((unsigned int) time(NULL));
	r = (float)rand()/(RAND_MAX + 1.0) * 1.0;
	return -(1.0/alpha)*log(1.0 - r) + 1.0;
}

int choose_pp(void){
	double x;
	srand((unsigned int) time(NULL));
	x = (float)rand()/(RAND_MAX + 1.0) * 1.0;
	if (x <= 0.7) {
		printf("MANY\n");
    many++;
		return MANY;
	}
	if (0.7 < x) {
		printf("FEW\n");
    few++;
		return FEW;
	}
}

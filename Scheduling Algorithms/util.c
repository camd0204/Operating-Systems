
#include "./util.h"

double rand_probability(){
  return rand() / (double) (RAND_MAX);
}

double rand_range(double min, double max){
    return min + rand_probability() * (max - min);
}

int int_rand_range(int min, int max){
    return min + rand_probability() * (max - min + 1);
}
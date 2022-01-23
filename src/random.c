#include "rtc.h"

static int _random_seed = 72;

int rand(int max){
	_random_seed = (_random_seed*2123+17122005)&0x7fffff;
	return (int)_random_seed%max;
}

void rand_init(){
	_random_seed = (_random_seed+(read_rtc(0)*21)/read_rtc(4)%6*2)*3;
	rand(rand(rand(72)));
	rand(3);
}

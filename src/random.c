static int _random_seed = 72;

int rand(int max){
	_random_seed = (_random_seed*278123+17122005)&0x7fffff;
	return (int)_random_seed%max;
}

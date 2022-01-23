#ifndef RTC_H
#define RTC_H
#include <stdint.h>

typedef struct {
	char hr;
	char sec;
	char min;
	char dy;
	char mn;
	char yr;
} time_t;

uint8_t read_rtc(int r);
void rtc_init();
time_t read_time();
int rtc_isupd();
char *gettimestr();

#endif

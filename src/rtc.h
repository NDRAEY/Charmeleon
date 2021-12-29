#ifndef RTC_H
#define RTC_H

typedef struct {
	short hr;
	short min;
	short sec;
} time;

typedef struct {
	char hr[4];
	char min[4];
	char sec[4];
} time_c;

char read_rtc(int r);
time_c gettime_c();
time gettime();

#endif

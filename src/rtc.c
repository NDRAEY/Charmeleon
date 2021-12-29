#include "ports.h"
#include "string.h"
#include "rtc.h"

char read_rtc(int r){
	outb(0x70,r);
	return inb(0x71);
}

time gettime(){
	static time time;
	short second = read_rtc(0);
	short minute = read_rtc(2);
	short hour = read_rtc(4);
	if(!(read_rtc(0x0b)&0x04)){
		time.hr = (short)(((hour&0x0f)+((hour&0x70)/16)*10) | (hour & 0x80));
		time.sec = (short)((second&0x0f)+(second/16)*10);
		time.min = (short)((minute&0x0f)+(minute/16)*10);
	}else{
		time.sec = second;
		time.min = minute;
		time.hr = hour;
	}
	return time;
}

time_c gettime_c(){
	static time_c time;
	short second = read_rtc(0);
	short minute = read_rtc(2);
	short hour = read_rtc(4);
	if(!(read_rtc(0x0b)&0x04)){
		itoa(((hour&0x0f)+((hour&0x70)/16)*10) | (hour & 0x80),time.hr);
		itoa((second&0x0f)+(second/16)*10,time.sec);
		itoa((minute&0x0f)+(minute/16)*10,time.min);
	}else{
		itoa(second,time.sec);
		itoa(minute,time.min);
		itoa(hour,time.hr);
	}
	return time;
}

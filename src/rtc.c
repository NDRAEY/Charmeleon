#include "ports.h"
#include "string.h"
#include "rtc.h"

unsigned char read_rtc(int r){
	outb(0x70,r);
	return inb(0x71);
}

int rtc_isupd() {
    outb(0x70, 0x0A);
    return (inb(0x71) & 0x80);
}

time_t read_time(){
	time_t tm;
	unsigned char breg;
	while(rtc_isupd());
	tm.sec = read_rtc(0x00);
	tm.min = read_rtc(0x02);
	tm.hr = read_rtc(0x04);
	tm.dy = read_rtc(0x07);
	tm.mn = read_rtc(0x08);
	tm.yr = read_rtc(0x09);

	breg = read_rtc(0x0b);
	
	if(!(breg&0x04)){
		tm.hr = ((tm.hr&0x0f)+(((tm.hr&0x70)/16)*10)) | (tm.hr & 0x80);
		tm.min = (tm.min&0x0f)+((tm.min/16)*10);
		tm.sec = (tm.sec&0x0f)+((tm.sec/16)*10);
		tm.dy = (tm.dy&0x0f)+((tm.dy/16)*10);
		tm.mn = (tm.mn&0x0f)+((tm.mn/16)*10);
		tm.yr = (tm.yr&0x0f)+((tm.yr/16)*10);
	}
	return tm;
}

void rtc_init(){
	read_time();
}

char* getstrtime(){
	char sec = read_rtc(0);
	char min = read_rtc(2);
	char hour = read_rtc(4);
	char sc[6];
	char mn[6];
	char hr[6];
	/*
	if(!(read_rtc(0x0b)&0x04)){
		itoa((int)(((hour&0x0f)+((hour&0x70)/16)*10) | (hour & 0x80)),hr);
		itoa((int)((sec&0x0f)+(sec/16)*10),sc);
		itoa((int)((min&0x0f)+(min/16)*10),mn);
	}else{*/
		itoa(sec,sc);
		itoa(min,mn);
		itoa(hour,hr);
	//}
	static char ti[(6*3)+2];
	strcpy(ti,hr);
	strcat(ti,":");
	strcat(ti,mn);
	strcat(ti,":");
	strcat(ti,sc);
	return (char*)(&ti);
}

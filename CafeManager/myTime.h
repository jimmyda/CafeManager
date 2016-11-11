// 시 분 초 처리를 쉽게하기 위한 헤더 (사용법은 main에 test()에 있음)
#pragma once
#include <string>
using namespace std;

class myTime {
private:
	int hour;
	int min;
	int sec;
public:
	myTime() {
		hour = 0;
		min = 0;
		sec = 0;
	}
	
	// hh:mm:ss 형식으로 받은 string을 int형 시, 분, 초로 분리해 생성해준다
	myTime(string time) {
		hour = (time[0] - '0') * 10 + (time[1] - '0');
		min = (time[3] - '0') * 10 + (time[4] - '0');;
		sec = (time[6] - '0') * 10 + (time[7] - '0');;
	}

	// accessor
	int getHour();
	int getMin();
	int getSec();


	//mutator
	void setTime(string time);

	// ostream 연산자 << 오버로딩(출력을 쉽게)
	friend ostream& operator<<(ostream& out, const myTime& t) {
		
		if (t.hour < 10)
			out << "0" << t.hour;
		else
			out << t.hour;
		if (t.min < 10)
			out << ":0" << t.min;
		else
			out << ":" << t.min;
		if (t.sec < 10)
			out << ":0" << t.sec;
		else
			out << ":" << t.sec;
		return out;
	}

	// myTime type간의 ==(equal) 비교연산자 오버로딩
	bool operator==(myTime &t);

	//myTime& operator+(int num);
	myTime& operator++();
};

// accessor
int myTime::getHour() {
	if (hour > 23)
		hour -= 24;
	return hour; 
}

int myTime::getMin() {
	if (min > 59) {
		hour++;
		min -= 60;
	}
	getHour();
	return min; 
}

int myTime::getSec() {
	if (sec > 59){
		min++;
		sec -= 60;
	}
	getMin();
	return sec; 
}

void myTime::setTime(string time) {
	hour = (time[0] - '0') * 10 + (time[1] - '0');
	min = (time[3] - '0') * 10 + (time[4] - '0');;
	sec = (time[6] - '0') * 10 + (time[7] - '0');;
}

// 연산자 오버로딩
bool myTime::operator==(myTime &t) {
	if (hour != t.hour || min != t.min || sec != t.sec)
		return false;
	return true;
}
/*
myTime& myTime::operator+(int num) {
	myTime temp(hour, min, sec);
	return temp;
}
*/
myTime& myTime::operator++() {
	min++;
	if (min > 59) {
		hour++;
		min -= 60;
	}
	if (hour > 23)
		hour -= 24;

	return *this;
}

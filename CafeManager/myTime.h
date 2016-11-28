// 시 분 초 처리를 쉽게하기 위한 헤더 (사용법은 main에 test()에 있음)
#pragma once
#include <string>
using namespace std;

class myTime {
private:
	int hour;
	int min;
	int sec;
	int timeSec;
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

	// hh:mm:ss 형식으로 받은 string을 int형 시, 분, 초로 분리해 생성해준다
	myTime(int h, int m, int s) {
		hour = h;
		min = m;
		sec = s;
	}

	// accessor
	int getHour();
	int getMin();
	int getSec();
	int getTimeSec();


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
	bool operator>(myTime &t);
	bool operator<(myTime &t);

	myTime operator+(int num);
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

int myTime::getTimeSec() {
	return sec + min * 60 + hour * 360;
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

bool myTime::operator>(myTime &t) {
	if (hour > t.hour)
		return true;
	else if (min > t.min)
		return true;
	else if (sec > t.sec)
		return true;
	else
		return false;
}

bool myTime::operator<(myTime &t) {
	if (hour < t.hour)
		return true;
	else if (min < t.min)
		return true;
	else if (sec < t.sec)
		return true;
	else
		return false;
}

myTime myTime::operator+(int num) {
	myTime temp(hour, min, sec);
	temp.min += num;
	if (temp.min > 59) {
		temp.hour++;
		temp.min -= 60;
	}
	if (temp.hour > 23)
		temp.hour -= 24;
	return temp;
}



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

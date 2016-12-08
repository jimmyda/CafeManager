#pragma once
#include "myTime.h"

class barista {
private:
	int totalMade;		// �ٸ���Ÿ�� ���� �� Ŀ���� ��
	int numOfCofMade;	// ���� ���� Ŀ���� ��
	int rank;	// �ٸ���Ÿ�� ��ũ (0 ~ 5, �������� ��ư� �� �ٲ�)
	bool doing; // flag(�ٸ���Ÿ�� ���Ḧ ����� ���̸� true �ƴϸ� false)
	myTime finishMakingTime;

public:
	// ������
	barista() {	//  ����Ʈ ������
		totalMade = -1;
		numOfCofMade = -1;
		rank = -1;
		doing = false;
		finishMakingTime.setTime("06:00:00");
		// to do something
	}
	barista(int prof) {
		totalMade = 0;
		numOfCofMade = 0;
		rank = prof;
		doing = false;
	}

	// accessor
	int getNumOfCofMade() { return numOfCofMade; }
	int getRank() { return rank; }
	int getTotalMade() { return totalMade; }
	bool getDoing() { return doing; }	// ���Ḧ ���������� Ȯ��
	myTime getFinishMakingTime() { return finishMakingTime; }

	// mutator
	void setRank(int prof) { rank = prof; }
	void setFinishMakingTime(myTime t) { finishMakingTime = t; }
	void incNumOfCofMade() { numOfCofMade++; }	// numOfCofMade++
	void incNumOfCofMade(int numOfCof) { numOfCofMade += numOfCof; }

	// function
	void doWork() { doing = true; }	// �ٸ���Ÿ�� ���������� ����
	void endWork() { doing = false; }	// �ٸ���Ÿ�� ���������� �Ϸ�
	int currentWork();
	void endOfDay();
};

// �Ϸ簡 ������ �������� ������� �� Ŀ�Ǽ��� ���ø��� Ŀ�Ǽ��� �����ش�
void barista::endOfDay() {
	totalMade += numOfCofMade;
	numOfCofMade = 0;
}

int barista::currentWork() {
	return numOfCofMade;
}
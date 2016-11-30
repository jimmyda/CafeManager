#pragma once
#include <iostream>
#include "resultObserver.h"
#include "myTime.h"

using namespace std;

extern resultObserver *observer;

class Reader {
public:
	virtual void read() {
		cout << "read something" << endl;
		readData();
		readCondition();
	}
protected:
	void readData() { cout << "read something data" << endl; }
	void readCondition() { cout << "read something condition" << endl; }
};

class Writer {
public:
	virtual void write() {
		cout << "write something" << endl;
		writeData();
		writeResult();
	}
protected:
	void writeData() { cout << "write something Data" << endl; }
	void writeResult() { cout << "write something Result" << endl; }
};

class Computer {
public:
	virtual void compute() { cout << "compute something" << endl; }
private:

};

// Reader �����ؼ� ���ϴµ��� ���� ���� �ε� �뷱�̿��� Reader �޾Ƽ� read��
class ReaderSample : public Reader {
public:
	void read() {
		cout << "Reader Sample" << endl;
		readCondition();
		readData();
	}
	void readData() { cout << "Read Data Sample" << endl; }
	void readCondition() { cout << "read something condition" << endl; }
};

class WriterSample : public Writer {
public:
	void write() {
		cout << "Writer Sample" << endl;
		this->writeData(); // Ȥ�� �θ� ��������� 
		this->writeResult();
	}
private:
};

class ExtendedLoadBalancing {
public:
	Reader* reader;
	Writer* writer;
	Computer* computer;
	

public:
	ExtendedLoadBalancing() {
		reader = new Reader;
		writer = new Writer;
		computer = new Computer;
		init();
	}
	ExtendedLoadBalancing(Reader* reader) {
		writer = new Writer;
		computer = new Computer;
		this->reader = reader;
		init();
	}
	ExtendedLoadBalancing(Writer* writer) {
		writer = new Writer;
		computer = new Computer;
		this->writer = writer;
		init();
	}
	ExtendedLoadBalancing(Computer* computer) {
		reader = new Reader;
		writer = new Writer;
		this->computer = computer;
		init();
	}
	ExtendedLoadBalancing(Reader* reader, Writer* writer)
	{
		computer = new Computer;
		this->reader = reader;
		this->writer = writer;
		init();
	}
	ExtendedLoadBalancing(Reader* reader, Writer* writer, Computer* computer) {
		this->reader = reader;
		this->writer = writer;
		this->computer = computer;
		init();
	}
	~ExtendedLoadBalancing() {
		delete reader;
		delete writer;
		delete computer;
	}

	void init() {
		reader->read();
		computer->compute();
		writer->write();
	}
};

extern vector<menu> men;
extern vector<barista> bari;
extern queue<order> ord;

extern void load();
extern void test();

// Basic �ܰ� ���� �ð� ���� ���� �� �ε�뷱�� 
// ���� �ð� �� �ٸ� ���� �߰��� ���� �ε� �뷱�̵� ����� ���� ���� 
// ���Ѵٸ� ����� ���� Ȯ����� ������ �� �ְ� �ϱ⸦ ��ǥ�� �ϰ�����

class BasicReader : public Reader {
public:
	void read() {
		load();
	}
};

class BasicComputer : public Computer {
	
public:
	
	void compute() {
		loadBalancing();
	}

	void loadBalancing() {
		
		observer = new resultObserver(ord.size());	//����� ����� ���� Observer��ü ����

		while (!isEmptyOrder()) {
			order curOrd = selectOrder();

			for (int i = 0; i < curOrd.getNumOfDrink(); i++)
			{
				int selected_barista = selectBarista();
				observer->insertResult(curOrd.getOrderNum(), selected_barista);
				distributeOrder(selected_barista);
			}
		}
	}

	bool isEmptyOrder() {
		return ord.empty();
	}

	order selectOrder() {
		return ord.front();
	}

	void distributeOrder(int selected) {
		bari[selected].incNumOfCofMade();
		ord.pop();
	}

	int selectBarista() {
		int min = 1000;
		barista curBari;
		int bariId;
		for (int i = 0; i < bari.size(); i++)
			if (min > bari[i].getNumOfCofMade())
			{
				min = bari[i].getNumOfCofMade();
				curBari = bari[i];
				bariId = i;
			}
		return bariId;
	}

};

class BasicWriter : public Writer {
public:
	void write() {
		//test();
		observer->showResult();
	}
};

// read , write ū ���� ���� basic �� �̹� �ð��� ���ؼ� �ٷ���� ����
class ReaderWithTime : public BasicReader {

};

class WriterWithTime : public BasicWriter {

};

class ComputerWithTime : public BasicComputer {
private:
	int rankedMakingTime[5] = { 15,13,10,7,3 };	// rank �� ���� ���� �Ϸ� �ð�

public:
	void compute() {
		loadBalancingWithTime();
	}

	void loadBalancingWithTime() {
		observer = new resultObserver(ord.size());	//����� ����� ���� Observer��ü ����

		while (!isEmptyOrder()) {
			order curOrd = selectOrder();

			for (int i = 0; i < curOrd.getNumOfDrink(); i++)
			{
				int selected_barista = selectBarista(curOrd);
				observer->insertResult(curOrd.getOrderNum(), selected_barista);
				distributeOrder(selected_barista, curOrd);
			}
		}
	}

	int selectBarista(order& curOrd) {
		int min = 1000;
		barista curBari;
		int bariId;
		for (int i = 0; i < bari.size(); i++)
			if (min > bari[i].getNumOfCofMade() 
				&& curOrd.getOrderTime() > bari[i].getFinishMakingTime())
			{
				min = bari[i].getNumOfCofMade();
				curBari = bari[i];
				bariId = i;
			}
		return bariId;
	}

	void distributeOrder(int selected, order& curOrd) {
		bari[selected].incNumOfCofMade();
		bari[selected].setFinishMakingTime(
			curOrd.getOrderTime() + rankedMakingTime[bari[selected].getRank()]);
		ord.pop();
	}
};
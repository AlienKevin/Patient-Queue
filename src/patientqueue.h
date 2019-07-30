// This is the H file you will edit and turn in. (TODO: Remove this comment!)

#ifndef _patientqueue_h
#define _patientqueue_h

#include <iostream>
#include <string>
#include "patient.h"
using namespace std;

class PatientQueue {
public:
    PatientQueue(bool isMinHeap = true);
    ~PatientQueue();
    void changePriority(string value, int newPriority);
    void clear();
    void debug();
    string dequeue();
    void enqueue(string value, int priority);
    bool isEmpty() const;
    string peek() const;
    int peekPriority() const;
    int size() const;
    friend ostream& operator <<(ostream& out, const PatientQueue& queue);

private:
    Patient *patients;
    int patientsSize;
    int patientsCapacity;
    bool isMinHeap;
    void swap(int &parentPos, int childPos);
    bool swapDown(int &currentPos, int parentPos);
    bool swapUp(int &currentPos, int childPos);
    void bubbleUp(int currentPos);
    void bubbleDown(int currentPos);
    void resize();
};

#endif

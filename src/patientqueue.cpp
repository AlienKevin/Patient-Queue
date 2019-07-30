// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)
#include "patientqueue.h"

PatientQueue::PatientQueue(bool isMinHeap) {
    patientsCapacity = 10;
    patientsSize = 0;
    patients = new Patient[patientsCapacity];
}

PatientQueue::~PatientQueue() {
    // TODO: write this destructor

}

void PatientQueue::changePriority(string value, int newPriority) {
    // TODO: write this function

}

void PatientQueue::clear() {
    // TODO: write this function

}

void PatientQueue::debug() {
}

string PatientQueue::dequeue() {
    return "";
}

void PatientQueue::enqueue(string value, int priority) {
    Patient *newPatient = new Patient(value, priority);
    int newPos = patientsSize + 1; // 0-th index is not used
    patients[newPos] = *newPatient;
    while (newPos >= 2) {
        int parentPos = newPos / 2;
        Patient parent = patients[parentPos];
        if (newPatient->priority < parent.priority) { // new patient has lower priority value than parent
            // swap new patient and their parent
            patients[newPos] = parent;
            patients[parentPos] = *newPatient;
        }
        newPos /= 2;
    }
    patientsSize ++;
}

bool PatientQueue::isEmpty() const {
    // TODO: write this function
    return false;   // remove this
}

string PatientQueue::peek() const {
    return patients[1].name;
}

int PatientQueue::peekPriority() const {
    // TODO: write this function
    return 0;   // remove this
}

int PatientQueue::size() const {
    return patientsSize;
}

// {Anat (4), Rein (6), Sasha (8),	Ben (9), Wu (7), Eve (10)}
ostream& operator <<(ostream& out, const PatientQueue& queue) {
    out << "{";
    for (int i = 1; i < queue.patientsSize + 1; i ++) {
        Patient patient = queue.patients[i];
        out << patient.name << " (" << patient.priority << ")";
        if (i < queue.patientsSize) { // before the last element
            out << ", ";
        }
    }
    out << "}";
    return out;
}

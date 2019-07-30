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
    // empty
}

string PatientQueue::dequeue() {
    // TODO: write this function
    return "";   // remove this
}

void PatientQueue::enqueue(string value, int priority) {
    // TODO: write this function

}

bool PatientQueue::isEmpty() const {
    // TODO: write this function
    return false;   // remove this
}

string PatientQueue::peek() const {
    // TODO: write this function
    return "";   // remove this
}

int PatientQueue::peekPriority() const {
    // TODO: write this function
    return 0;   // remove this
}

int PatientQueue::size() const {
    // TODO: write this function
    return 0;   // remove this
}

// {Anat (4), Rein (6), Sasha (8),	Ben (9), Wu (7), Eve (10)}
ostream& operator <<(ostream& out, const PatientQueue& queue) {
    out << "{";
    for (int i = 0; i < queue.patientsSize; i ++) {
        Patient patient = queue.patients[i];
        out << patient.name << " (" << patient.priority << ")";
        if (i < queue.patientsSize - 1) { // before the last element
            out << ", ";
        }
    }
    out << "}";
    return out;
}

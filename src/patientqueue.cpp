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
    if (isEmpty()) {
        throw "Cannot dequeue an empty queue!";
    }
    Patient frontPatient = patients[1];
    Patient backPatient = patients[patientsSize];
    int newPos = 1;
    patients[newPos] = backPatient;
    while ((newPos * 2 <= patientsSize &&
           patients[newPos].priority > patients[newPos * 2].priority) ||
           (newPos * 2 + 1 <= patientsSize &&
           patients[newPos].priority > patients[newPos * 2 + 1].priority)) {
        int firstChildPos = newPos * 2;
        int secondChildPos = newPos * 2 + 1;
        if (secondChildPos <= patientsSize) { // both children exists
            // first child's priority value lower than second child
            if (patients[firstChildPos].priority < patients[secondChildPos].priority) {
                // swap parent and first child
                swap(newPos, firstChildPos);
            } else if (patients[firstChildPos].priority == patients[secondChildPos].priority){
                // first child's priority value is equal to second child
                // Compare name alphabetically
                if (patients[firstChildPos].name >= patients[secondChildPos].name) {
                    swap(newPos, firstChildPos);
                } else {
                    swap(newPos, secondChildPos);
                }
            } else {
                // swap parent and second child
                swap(newPos, secondChildPos);
            }
        } else if (newPos * 2 <= patientsSize) { // only first child exists
            // swap parent and first child
            swap(newPos, firstChildPos);
        }
    }
    patientsSize --;
    return frontPatient.name;
}

void PatientQueue::swap(int &parentPos, int childPos) {
    Patient parent = patients[parentPos];
    // swap parent position with child position
    patients[parentPos] = patients[childPos];
    patients[childPos] = parent;
    // move current position to position of the child
    parentPos = childPos;
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
    return patientsSize == 0;
}

string PatientQueue::peek() const {
    return patients[1].name;
}

int PatientQueue::peekPriority() const {
    return patients[1].priority;
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

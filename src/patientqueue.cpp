// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)
#include "patientqueue.h"

PatientQueue::PatientQueue(bool isMinHeap) {
    this->isMinHeap = isMinHeap;
    clear();
}

PatientQueue::~PatientQueue() {
    delete[] patients;
}

void PatientQueue::changePriority(string value, int newPriority) {
    for (int i = 1; i < patientsSize + 1; i ++) {
        Patient patient = patients[i];
        if (patient.name == value) { // first occurance of name
            // change priority
            patients[i].priority = newPriority;
            // bubble down or up
            int currentPos = i;
            bubbleDown(currentPos);
            bubbleUp(currentPos);
            return;
        }
    }
    throw "Patient " + value + " is not found in the patients queue!";
}

void PatientQueue::clear() {
    patientsCapacity = 10;
    patientsSize = 0;
    patients = new Patient[patientsCapacity];
}

void PatientQueue::debug() {
}

void PatientQueue::bubbleDown(int currentPos) {
    int parentPos = currentPos / 2;
    while (parentPos >= 1 &&
           hasHigherOrEqualPriority(currentPos, parentPos)) {
        if (swapDown(currentPos, parentPos) == false) {
            return; // break the while loop
        }
        parentPos = currentPos / 2;
    }
}

void PatientQueue::bubbleUp(int currentPos) {
    while ((currentPos * 2 <= patientsSize &&
            hasLowerOrEqualPriority(currentPos, currentPos * 2)) ||
           (currentPos * 2 + 1 <= patientsSize &&
            hasLowerOrEqualPriority(currentPos, currentPos * 2 + 1))) {
        int firstChildPos = currentPos * 2;
        int secondChildPos = currentPos * 2 + 1;
        bool hasSwapSucceeded = false;
        if (secondChildPos <= patientsSize) { // both children exists
            // first child's priority value lower than second child
            if (hasHigherPriority(firstChildPos, secondChildPos)) {
                // swap parent and first child
                hasSwapSucceeded = swapUp(currentPos, firstChildPos);
            } else if (patients[firstChildPos].priority == patients[secondChildPos].priority){
                // first child's priority value is equal to second child
                // Compare name alphabetically
                if ((isMinHeap && patients[firstChildPos].name <= patients[secondChildPos].name) ||
                    (!isMinHeap && patients[firstChildPos].name > patients[secondChildPos].name)) {
                    hasSwapSucceeded = swapUp(currentPos, firstChildPos);
                } else {
                    hasSwapSucceeded = swapUp(currentPos, secondChildPos);
                }
            } else {
                // swap parent and second child
                hasSwapSucceeded = swapUp(currentPos, secondChildPos);
            }
        } else if (currentPos * 2 <= patientsSize) { // only first child exists
            // swap parent and first child
            hasSwapSucceeded = swapUp(currentPos, firstChildPos);
        }
        if (hasSwapSucceeded == false) {
            return; // break the while loop
        }
    }
}

string PatientQueue::dequeue() {
    if (isEmpty()) {
        throw "Cannot dequeue an empty queue!";
    }
    Patient frontPatient = patients[1];
    Patient backPatient = patients[patientsSize];
    int newPos = 1;
    patients[newPos] = backPatient;
    // bubble up
    bubbleUp(newPos);
    patientsSize --;
    return frontPatient.name;
}

bool PatientQueue::hasHigherPriority(int pos1, int pos2) {
    if (isMinHeap) {
        return patients[pos1].priority < patients[pos2].priority ||
                (patients[pos1].priority == patients[pos2].priority &&
                patients[pos1].name < patients[pos2].name);
    } else {
        return patients[pos1].priority > patients[pos2].priority ||
                (patients[pos1].priority == patients[pos2].priority &&
                patients[pos1].name > patients[pos2].name);
    }
}

bool PatientQueue::hasHigherOrEqualPriority(int pos1, int pos2) {
    return !hasLowerPriority(pos1, pos2);
}

bool PatientQueue::hasLowerPriority(int pos1, int pos2) {
    if (isMinHeap) {
        return patients[pos1].priority > patients[pos2].priority ||
                (patients[pos1].priority == patients[pos2].priority &&
                patients[pos1].name > patients[pos2].name);
    } else {
        return patients[pos1].priority < patients[pos2].priority ||
                (patients[pos1].priority == patients[pos2].priority &&
                patients[pos1].name < patients[pos2].name);
    }
}

bool PatientQueue::hasLowerOrEqualPriority(int pos1, int pos2) {
    return !hasHigherPriority(pos1, pos2);
}

void PatientQueue::swap(int &pos1, int pos2) {
    Patient pos1Patient = patients[pos1];
    // swap pos1 position with pos2 position
    patients[pos1] = patients[pos2];
    patients[pos2] = pos1Patient;
    // move pos1 to position of pos2
    pos1 = pos2;
}

// swap current position (pos1) with parent (pos2)
bool PatientQueue::swapDown(int &currentPos, int parentPos) {
    if (hasHigherPriority(currentPos, parentPos)) {
        swap(currentPos, parentPos);
        return true;
    }
    return false;
}

bool PatientQueue::swapUp(int &currentPos, int childPos) {
    int childPosCopy = childPos;
    if (swapDown(childPosCopy, currentPos)) {
        currentPos = childPos;
        return true;
    }
    return false;
}

void PatientQueue::resize() {
    // double the capacity
    patientsCapacity *= 2;
    Patient *newPatients = new Patient[patientsCapacity];
    for (int i = 1; i < patientsSize + 1; i ++) {
        newPatients[i] = patients[i];
    }
    delete[] patients;
    patients = newPatients;
}

void PatientQueue::enqueue(string value, int priority) {
    if (patientsSize + 1 == patientsCapacity) { // patients queue full
        resize();
    }
    Patient *newPatient = new Patient(value, priority);
    int newPos = patientsSize + 1; // 0-th index is not used
    patients[newPos] = *newPatient;
    bubbleDown(newPos);
    patientsSize ++;
}

bool PatientQueue::isEmpty() const {
    return patientsSize == 0;
}

string PatientQueue::peek() const {
    if (isEmpty()) {
        throw "Cannot peek at an empty queue!";
    }
    return patients[1].name;
}

int PatientQueue::peekPriority() const {
    if (isEmpty()) {
        throw "Cannot peek at an empty queue!";
    }
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

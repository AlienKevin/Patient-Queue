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
    // TODO: write this function

}

void PatientQueue::debug() {
}

void PatientQueue::bubbleDown(int currentPos) {
    int parentPos = currentPos / 2;
    while (parentPos >= 1 && patients[currentPos].priority < patients[parentPos].priority) {
        swap(currentPos, parentPos);
    }
}

void PatientQueue::bubbleUp(int currentPos) {
    while ((currentPos * 2 <= patientsSize &&
           patients[currentPos].priority > patients[currentPos * 2].priority) ||
           (currentPos * 2 + 1 <= patientsSize &&
           patients[currentPos].priority > patients[currentPos * 2 + 1].priority)) {
        int firstChildPos = currentPos * 2;
        int secondChildPos = currentPos * 2 + 1;
        if (secondChildPos <= patientsSize) { // both children exists
            // first child's priority value lower than second child
            if (patients[firstChildPos].priority < patients[secondChildPos].priority) {
                // swap parent and first child
                swap(currentPos, firstChildPos);
            } else if (patients[firstChildPos].priority == patients[secondChildPos].priority){
                // first child's priority value is equal to second child
                // Compare name alphabetically
                if (patients[firstChildPos].name <= patients[secondChildPos].name) {
                    swap(currentPos, firstChildPos);
                } else {
                    swap(currentPos, secondChildPos);
                }
            } else {
                // swap parent and second child
                swap(currentPos, secondChildPos);
            }
        } else if (currentPos * 2 <= patientsSize) { // only first child exists
            // swap parent and first child
            swap(currentPos, firstChildPos);
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

void PatientQueue::swap(int &pos1, int pos2) {
    Patient pos1Patient = patients[pos1];
    // swap pos1 position with pos2 position
    patients[pos1] = patients[pos2];
    patients[pos2] = pos1Patient;
    // move pos1 to position of pos2
    pos1 = pos2;
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

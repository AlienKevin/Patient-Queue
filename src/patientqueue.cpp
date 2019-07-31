/**
 * Patient Queue assignment for CS106B at Stanford Summer Session 2019
 * Author: Kevin Li
 * Description:
 * This program stores a patient queue that manages a waiting line of patients
 * to be processed at a hospital. As each new patient checks in at the hospital,
 * the staff assesses their injuries and gives that patient an integer priority
 * rating, with smaller integers representing greater urgency (a min heap).
 * You can switch the order and make larger integers representing
 * greater urgency (a max heap) by passing true to PatientQueue constructor.
 * Note that a min heap always has the patient with the smallest priority value in front
 * and a max heap always has patient with the largest priority value in front.
 * Usually, smaller priority value indicates more urgency but max heap is justified
 * because less urgent patients may be treated more quickly.
 */
#include "patientqueue.h"

/**
 * @brief Constructor for the PatientQueue
 * @param isMinHeap indicate whether to use min heap or max heap
 */
PatientQueue::PatientQueue(bool isMinHeap) {
    this->isMinHeap = isMinHeap;
    clear();
}

/**
 * @brief Destructor for the PatientQueue
 */
PatientQueue::~PatientQueue() {
    delete[] patients;
}

/**
 * @brief Change a patient's priority by:
 *  1. finding the patient by their name
 *  2. bubble the patient up or down depending on the new priority
 * @param value the patient's name
 * @param newPriority the patient's new priority
 * @throw string error if patient name if not found in the queue
 */
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

/**
 * @brief Clear the patients queue by reseting private member variables
 */
void PatientQueue::clear() {
    patientsCapacity = 10;
    patientsSize = 0;
    patients = new Patient[patientsCapacity];
}

/**
 * @brief Function for printing debugging messages
 */
void PatientQueue::debug() {
}

/**
 * @brief Bubble the patient at currentPos down by
 * comparing the patient's priority with their parent's
 * @param currentPos the current position of the patient to bubble down
 */
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

/**
 * @brief Bubble the patient at currentPos up by
 * comparing the patient's priority with their children's
 * @param currentPos the current position of the patient to bubble up
 */
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

/**
 * @brief Dequeue the front patient who has the most urgent priority by
 *  1. popping the front patient and move the last patient to the front
 *  2. Bubble the last patient down
 * @return the name of the front patient
 * @throw string error if queue is empty
 */
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

/**
 * @brief Test if the patient at pos1 has a higher priority than the patient at pos2
 * @param pos1 the index position of the first patient
 * @param pos2 the index position of the second patient
 * @return if the patient at pos1 has a higher priority than the patient at pos2
 */
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

/**
 * @brief Test if the patient at pos1 has a higher or equal priority than the patient at pos2
 * @param pos1 the index position of the first patient
 * @param pos2 the index position of the second patient
 * @return if the patient at pos1 has a higher priority or equal than the patient at pos2
 */
bool PatientQueue::hasHigherOrEqualPriority(int pos1, int pos2) {
    return !hasLowerPriority(pos1, pos2);
}

/**
 * @brief Test if the patient at pos1 has a lower priority than the patient at pos2
 * @param pos1 the index position of the first patient
 * @param pos2 the index position of the second patient
 * @return if the patient at pos1 has a lower priority than the patient at pos2
 */
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

/**
 * @brief Test if the patient at pos1 has a lower or equal priority than the patient at pos2
 * @param pos1 the index position of the first patient
 * @param pos2 the index position of the second patient
 * @return if the patient at pos1 has a lower or equal priority than the patient at pos2
 */
bool PatientQueue::hasLowerOrEqualPriority(int pos1, int pos2) {
    return !hasHigherPriority(pos1, pos2);
}

/**
 * @brief Swap the patient at pos1 with the patient at pos2
 * @param pos1 the index position of the first patient
 * @param pos2 the index position of the second patient
 */
void PatientQueue::swap(int &pos1, int pos2) {
    Patient pos1Patient = patients[pos1];
    // swap pos1 position with pos2 position
    patients[pos1] = patients[pos2];
    patients[pos2] = pos1Patient;
    // move pos1 to position of pos2
    pos1 = pos2;
}

/**
 * @brief Swap current position with parent if current has a higher priority
 * @param currentPos the index position of the current patient
 * @param parentPos the index position of current patient's parent
 * @return the swap is successful or not
 */
bool PatientQueue::swapDown(int &currentPos, int parentPos) {
    if (hasHigherPriority(currentPos, parentPos)) {
        swap(currentPos, parentPos);
        return true;
    }
    return false;
}

/**
 * @brief Swap current position with a child if current's child has a higher priority
 * @param currentPos the index position of the current patient
 * @param childPos the index position of current patient's child
 * @return the swap is successful or not
 */
bool PatientQueue::swapUp(int &currentPos, int childPos) {
    int childPosCopy = childPos;
    if (swapDown(childPosCopy, currentPos)) {
        currentPos = childPos;
        return true;
    }
    return false;
}

/**
 * @brief Resize the patients queue represented by an array to fit more patients by
 *  1. Copy all patients in the current array to a new array
 *  2. Delete the old array
 */
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

/**
 * @brief Enqueue a new patient to the patient queue by
 *  1. Put the patient at the end of the queue
 *  2. Bubble the patient up
 * @param value the name of the new patient
 * @param priority the priority of the new patient
 */
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

/**
 * @brief Test if the patient queue is empty or not by
 * testing if the size of the array representing the queue is equal to 0
 * @return if the patient queue is empty or not
 */
bool PatientQueue::isEmpty() const {
    return patientsSize == 0;
}

/**
 * @brief Peek at the front patient of the queue and return their name
 * Note the the patient queue starts at index 1 not index 0 for calculation convenience
 * @return the name of the front patient
 * @throw string error if queue is empty
 */
string PatientQueue::peek() const {
    if (isEmpty()) {
        throw "Cannot peek at an empty queue!";
    }
    return patients[1].name;
}

/**
 * @brief Peek at the front patient of the queue and return their priority value
 * Note the the patient queue starts at index 1 not index 0 for calculation convenience
 * @return the priority value of the front patient
 */
int PatientQueue::peekPriority() const {
    if (isEmpty()) {
        throw "Cannot peek at an empty queue!";
    }
    return patients[1].priority;
}

/**
 * @brief return the size of the patient queue
 * @return the size of the patient queue
 */
int PatientQueue::size() const {
    return patientsSize;
}

/**
 * Print the patient queue in a nice format:
 * e.g. {Anat (4), Rein (6), Sasha (8),	Ben (9), Wu (7), Eve (10)}
 */
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

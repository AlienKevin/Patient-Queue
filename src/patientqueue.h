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

#ifndef _patientqueue_h
#define _patientqueue_h

#include <iostream>
#include <string>
#include "patient.h"
using namespace std;

class PatientQueue {
public:
    /**
     * @brief PatientQueue constructor
     * @param isMinHeap indicates whether to use a min heap or max heap
     */
    PatientQueue(bool isMinHeap = true);
    /**
     * @brief PatientQueue destructor
     * Deallocates used heap memory
     */
    ~PatientQueue();
    /**
     * @brief Change the priority of a patient in the queue
     * changePriority affect only a single occurrence of
     * a patient's name (the first one found)
     * @param value the name of the patient
     * @param newPriority the new priority value
     */
    void changePriority(string value, int newPriority);
    /**
     * @brief Clear the patient queue
     */
    void clear();
    /**
     * @brief Method used for debuggin
     */
    void debug();
    /**
     * @brief Give back the front patient with the most urgent priority
     * @return the name of the front patient
     */
    string dequeue();
    /**
     * @brief Add a new patient to the queue
     * @param value the name of the patient
     * @param priority the priority value of the patient
     */
    void enqueue(string value, int priority);
    /**
     * @brief Return is the patient queue is empty or not
     * @return the patient queue is empty or not
     */
    bool isEmpty() const;
    /**
     * @brief Return the front patient's name
     * @return the front patient's name
     */
    string peek() const;
    /**
     * @brief Return the front patient's priority
     * @return the front patient's priority
     */
    int peekPriority() const;
    /**
     * @brief Return the size of the patient queue
     * @return the size of the patient queue
     */
    int size() const;
    /**
     * @brief Print the patient queue in a nice format
     * @param out the out stream for printing
     * @param queue the patient queue to print
     * @return the out stream for printing
     */
    friend ostream& operator <<(ostream& out, const PatientQueue& queue);

private:
    /**
     * @brief the patient queue implemented as an array
     */
    Patient *patients;
    /**
     * @brief the size of the patient queue
     */
    int patientsSize;
    /**
     * @brief the capacity of the patient queue array
     */
    int patientsCapacity;
    /**
     * @brief Whether to use a min heap or max heap
     */
    bool isMinHeap;
    bool hasHigherPriority(int pos1, int pos2);
    bool hasHigherOrEqualPriority(int pos1, int pos2);
    bool hasLowerPriority(int pos1, int pos2);
    bool hasLowerOrEqualPriority(int pos1, int pos2);
    void swap(int &parentPos, int childPos);
    bool swapDown(int &currentPos, int parentPos);
    bool swapUp(int &currentPos, int childPos);
    void bubbleUp(int currentPos);
    void bubbleDown(int currentPos);
    void resize();
};

#endif

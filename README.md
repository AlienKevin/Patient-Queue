# Patient Queue
Patient Queue assignment for CS106B at Stanford Summer Session 2019.
This program stores a patient queue that manages a waiting line of patients to be processed at a hospital. As each new patient checks in at the hospital, the staff assesses their injuries and gives that patient an integer priority rating, with smaller integers representing greater urgency (a min heap). You can switch the order and make larger integers representing greater urgency (a max heap) by passing true to PatientQueue constructor. Note that a min heap always has the patient with the smallest priority value in front and a max heap always has patient with the largest priority value in front. Usually, smaller priority value indicates more urgency but max heap is justified because less urgent patients may be treated more quickly.

![Patients waiting in hospital](./res/hospital-queue-1.png)

# Installation
1. Download or clone this project.
2. Load this project into Qt Creator.
3. Build and run in Qt Creator.

# Credits
Assignment by Marty Stepp. Based on Priority Queue assignment by Jerry Cain. This project uses various modules from [the Stanford C++ Libraries](http://web.stanford.edu/~stepp/cppdoc/).
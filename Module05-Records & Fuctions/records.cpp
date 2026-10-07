#include <iostream>
#include <string>
#include "records.h"

double calculateAverage(double scores[], int count) {
    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += scores[i];
    }
    return sum / count;
}

void displayRecords(string ids[], double scores[], char grades[], int count) {
    cout << "===Student Records===" << endl;
    for (int i = 0; i < count; i++) {
        cout << "ID: " << ids[i] << ", Score: " << scores[i]
             << ", Grade: " << grades[i] << endl;
    }
}

void addRecord(string ids[], double scores[], char grades[], int& count) {
    cout << "Enter student ID: ";
    getline(cin, ids[count]);

    cout << "Enter exam score: ";
    cin >> scores[count];

    cout << "Enter letter grade: ";
    cin >> grades[count];

    count++;
    cout << "Record added." << endl;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "records.h"
using namespace std;

int main() {
    string ids[20];
    double scores[20];
    char grades[20];
    int count = 0;

    ifstream inputFile("students.csv");
    if (!inputFile) {
        cout << "could not open input file" << endl;
        return 1;
    }

    string line;
    getline(inputFile, line);
    while (getline(inputFile, line) && count < 20) {
        stringstream ss(line);
        string idPart, scorePart, gradePart;
        getline(ss, idPart, ',');
        getline(ss, scorePart, ',');
        getline(ss, gradePart);
        ids[count] = idPart;
        scores[count] = stod(scorePart);
        grades[count] = gradePart[0];
        count++;
    }
    inputFile.close();

    displayRecords(ids, scores, grades, count);
    cout << "Average score: " << calculateAverage(scores, count) << endl;
    addRecord(ids, scores, grades, count);
    displayRecords(ids, scores, grades, count);

    double* ptr = &scores[0];
    cout << "Value through pointer: " << *ptr << endl;
    cout << "Address: " << ptr << endl;

    return 0;
}

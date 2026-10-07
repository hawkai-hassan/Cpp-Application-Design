#ifndef RECORDS_H
#define RECORDS_H
#include <string>
using namespace std;

double calculateAverage(double scores[], int count);
void displayRecords(string ids[], double scores[], char grades[], int count);
void addRecord(string ids[], double scores[], char grades[], int& count);

#endif

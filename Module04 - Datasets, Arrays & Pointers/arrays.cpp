#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
int main() {
    string ids[10];
    double scores[10];
    char grades[10];
    int count = 0;

    ifstream inputFile("../students.csv");
    if (!inputFile) {
        cout<< "could not open input file" << endl;
        return 1;
    }
    cout << "===Student Records===" << endl;
    string line;
    getline(inputFile, line);
    while (getline(inputFile, line) && count < 10) {
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

    for (int i = 0; i < count; i++) {
        cout << "ID: " << ids[i] << ", Score: " << scores[i] << ", Grade: " << grades[i] << endl;
    }
    double* ptr = &scores[0];
    cout << "Value through pointer: " << *ptr << endl;
    cout << "Address: " << ptr << endl;
    return 0;
    //ofstream outputFile("output.txt");
}
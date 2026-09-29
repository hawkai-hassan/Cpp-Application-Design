#include <iostream>   
#include <string>
using namespace std;

int main() {

    string userName;
    cout << "Enter your name" << endl;
    getline(cin, userName);
    string appName = "Gradebook";
    double versionNum = 1.1;
    cout << "Student Name: " << userName << endl;
    cout << "Application Name: " << appName << endl;
    cout << "Version Number: " << versionNum << endl;
    bool active = true;
    cout << "Active: " << boolalpha << active << endl;
    int studentId = 1001;
    cout << "Student ID: " << studentId << endl;
    char letterGrade = 'A';
    cout << "Grade: " << letterGrade << endl;
    double gpa = 3.5;
    cout << "GPA: " << gpa << endl;
    cout << endl;
    cout << "=== MY APPLICATION ===" << endl;
    cout << "1. Add Record" << endl;
    cout << "2. View Records" << endl;
    cout << "3. Search" << endl;
    cout << "4. Exit" << endl;

    return 0;

}   

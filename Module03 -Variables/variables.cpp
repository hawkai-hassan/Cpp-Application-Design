#include <iostream>   
#include <string>
using namespace std;

int main() {

    cout << "Enter your name" << endl;
    string userName;
    cin >> userName;
    string appName = "Gradebook";
    double versionNum = 1.1;
    cout << "Student Name: " << userName << endl;
    cout << "Application Name: " << appName << endl;
    cout << "Version Number: " << versionNum << endl;
    bool active = true;
    cout << "Active: " << boolalpha << active << endl;
    int age = 23;
    cout << "Age: " << age << endl;
    char letterGrade = 'A';
    cout << "Grade: " << letterGrade << endl;
    cout << endl;
    cout << "=== MY APPLICATION ===" << endl;
    cout << "1. Add Record" << endl;
    cout << "2. View Records" << endl;
    cout << "3. Search" << endl;
    cout << "4. Exit" << endl;

    return 0;

}   

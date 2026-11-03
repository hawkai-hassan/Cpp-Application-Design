/*
 * Student Record Management System
 * Student: Abdulwahab Hassan
 * Date: 2026-10-31
 * Program reads student records from a csv file and allows users to view and add records.
 * Supports binary search for quick record retrieval.
 * Provides input validation for scores, IDs, and grades.
 * 
 */


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;
// Represents a single student record with ID, score, and grade.
class Student {
private:
    string id;
    double score;
    char grade;

public:
    Student(){
        id = "";
        score = 0.0;
        grade = 'N';

    };
    Student(string studentId, double studentScore, char studentGrade){
        id = studentId;
        score = studentScore;
        grade = studentGrade;

    }
    void displayStudent() const {
        cout << "Student ID: " << id << endl;
        cout << "Student Score: " << score << endl;
        cout << "Student Grade: " << grade << endl;
    }
// Calculates the letter grade based on the student's score.
    char calculateLetterGrade() {
        if (score >= 90) {
            return 'A';
        } else if (score >= 80) {
            return 'B';
        } else if (score >= 70){
            return 'C';
        } else if (score >= 60){
            return 'D';
        } else {
            return 'F';
        }
    }
    void setId(string id) {
        this->id = id;
    }
    void setScore(double score) {
        this->score = score;
    }
    void setGrade(char grade) {
        this->grade = grade;
    }
    string getId() const {
        return id;
    }
    double getScore() const {
        return score;
    }
    char getGrade() const {
        return grade;
    }
};

// Represents a user with a username and the ability to view records.

class User {
protected:
    string username;
public:
    User(string name) : username(name) {}
    void viewRecords() { cout << "View Records" << endl; }
};
// Represents an admin user with the ability to add student records.
class Admin : public User {
public:
    Admin(string name) : User(name) {}
    void addRecord() { cout << "Add Record" << endl;}
};

// Locates a student record by ID using binary search.
// Returns the index of the student if found, otherwise returns -1.

int binarySearch(Student student[], int size, string target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (student[mid].getId() == target) return mid;
        if (student[mid].getId() < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
// Retrieves a valid score from the user, ensuring it is between 0 and 100.
double getValidScore() {
    double score;
    while (true) {
        cout << "Enter a score between 0 and 100: ";
        cin >> score;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
        } 
        else if (score < 0 || score > 100){
            cout << "Score must be between 0 and 100." << endl;
        }
        else {
            return score;
        }
    }
}
// Retrieves a valid student ID from the user, ensuring it is not empty.
string getValidId() {
    string id;
    while (true) {
        cout << "Enter a student ID: ";
        getline(cin, id);
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid ID." << endl;
        } 
        else if (id.empty()) {
            cout << "ID cannot be empty." << endl;
        }
        else {
            return id;
        }
    }
}
// Retrieves a valid grade from the user, ensuring it is one of A, B, C, D, or F.
char getValidGrade() {
    char grade;
    while (true) {
        cout << "Enter a grade (A, B, C, D, F): ";
        cin >> grade;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid grade." << endl;
        } else if (grade != 'A' && grade != 'B' && grade != 'C' && grade != 'D' && grade != 'F') {
            cout << "Grade must be A, B, C, D, or F." << endl;
        } else {
            return grade;
        }
    }
}

int main() {
    
    // Initialize an array of students and a counter for the number of students.
    Student student[20]; 
    int count = 0;
    string line; // Variable to store each line read from the CSV file.

    // Open the CSV file for reading student records.
    ifstream inputFile("../students.csv");
    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }
    // Read the header line from the CSV file and discard it.
    getline(inputFile, line);
    while (getline(inputFile, line) && count < 20) {
        stringstream ss(line);
        string idPart, scorePart, gradePart;
        getline(ss, idPart, ',');
        getline(ss, scorePart, ',');
        getline(ss, gradePart);
        student[count] = Student(idPart, stod(scorePart), gradePart[0]);
        count++;
    }
    // Display the first student record using a pointer to demonstrate pointer usage.
    Student* ptr = &student[0];
    cout << "Via Pointer: "<< ptr->getId() << endl;
    inputFile.close();

    for (int i = 0; i < count; i++) {
        student[i].displayStudent();
    }
    cout << "\n--- Add a Student ---" << endl; 
    string newId = getValidId();
    double newScore = getValidScore();
    char newGrade = getValidGrade();
    student[count] = Student(newId, newScore, newGrade);
    count++;

// Demonstrate user roles and their actions on student records.
    User regular("Sam");
    Admin boss("Abdulwahab");

    regular.viewRecords();
    boss.viewRecords();
    boss.addRecord();
    
    // Sort the student records by ID before performing binary search
    // This ensures that the binary search algorithm can correctly locate the student by ID.
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count - 1; j++) {
            if (student[j].getId() > student[j + 1].getId()) {
                Student temp = student[j];
                student[j] = student[j + 1];
                student[j + 1] = temp;
            }
        }
    }
    cout << "\n--- Search for a Student ---" << endl;
    string target = getValidId();

    int found = binarySearch(student, count, target); // Search for a student by ID using binary search
   
    // Display the student record if found, otherwise print "Not Found"
    if (found != -1) student[found].displayStudent();
    else cout << "Not Found" << endl;

    return 0;

}

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
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

class User {
protected:
    string username;
public:
    User(string name) : username(name) {}
    void viewRecords() { cout << "View Records" << endl; }
};

class Admin : public User {
public:
    Admin(string name) : User(name) {}
    void addRecord() { cout << "Add Record" << endl;}
    void deleteRecord() { cout << "Delete Record" << endl; }
};

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

int main() {
    
    
    Student student[20]; 
    int count = 0;

    string line;
    ifstream inputFile("../students.csv");
    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }
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
    inputFile.close();

    for (int i = 0; i < count; i++) {
        student[i].displayStudent();
    }



    User regular("Sam");
    Admin boss("Abdulwahab");

    regular.viewRecords();
    boss.viewRecords();
    boss.addRecord();
    boss.deleteRecord();
    
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count - 1; j++) {
            if (student[j].getId() > student[j + 1].getId()) {
                Student temp = student[j];
                student[j] = student[j + 1];
                student[j + 1] = temp;
            }
        }
    }
    int found = binarySearch(student, count, "STU_000005");
   

    if (found != -1) student[found].displayStudent();
    else cout << "Not Found" << endl;

    return 0;

}

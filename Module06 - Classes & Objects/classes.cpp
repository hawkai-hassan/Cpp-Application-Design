#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string id;
    double score;
    char grade;

public:
    /*Student();*/
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

int main() {
    Student student1("STU_000001", 90.4, 'A');
    Student student2("STU_000002", 86.21, 'A');

    student1.displayStudent();
    cout << "Calculated Grade: " << student1.calculateLetterGrade() << endl;
    cout << endl;
    student2.displayStudent();
    cout << "Calculated Grade: " << student2.calculateLetterGrade() << endl;
    cout << endl;
    return 0;
}

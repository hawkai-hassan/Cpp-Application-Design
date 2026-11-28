#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cctype>


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
            cout << "Invalid input. Please enter a valid grade." << endl;
        } else if (grade != 'A' && grade != 'B' && grade != 'C' && grade != 'D' && grade != 'F') {
            cout << "Grade must be A, B, C, D, or F." << endl;
        } else {
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return grade;
        }
    }
}
bool isValidDate(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        cout << "Date format must be YYYY-MM-DD." << endl;
        return false;
    }

    for (int i = 0; i < date.size(); ++i) {
        if (i == 4 || i == 7) continue; // Skip the '-' characters
        if (!isdigit(date[i])) {
            cout << "Date must contain only digits and '-'." << endl;
            return false;
        }
    }
    int  month = stoi(date.substr(5, 2));
    int  day = stoi(date.substr(8, 2));
    if (month < 1 || month > 12) {
        cout << "Month must be between 01 and 12." << endl;
        return false;
    }

    if (day < 1 || day > 31) {
        cout << "Day must be between 01 and 31." << endl;
        return false;
    }
    return true;
}

// ===== NEW: AI feature: natural-language search (mock) =====

// The result the "AI service" sends back: a set of filters.
struct SearchFilter {
    bool understood = false;
    double minScore = -1;    // exclusive lower bound
    double maxScore = 101;   // exclusive upper bound
    char grade = 0;          // 0 = any grade
    bool failedOnly = false, passedOnly = false;
    bool top = false, lowest = false;
};

// MOCK AI SERVICE: keyword rules stand in for a real language model.
SearchFilter mockAiInterpret(const string& query) {
    SearchFilter f;

    // Prepare data: lowercase, turn punctuation into spaces.
    string clean;
    for (char c : query) {
        unsigned char u = static_cast<unsigned char>(c);
        if (isalnum(u) || c == '.') clean += static_cast<char>(tolower(u));
        else clean += ' ';
    }

    stringstream ss(clean);
    string word, prev;
    while (ss >> word) {
        while (!word.empty() && word.back() == '.') word.pop_back();
        if (word.empty() || word == "than") continue;

        // The mock does not handle negation, so it refuses instead of guessing.
        if (word == "not" || word == "no" || word == "never" || word == "didn" ||
            word == "don" || word == "doesn" || word == "isn") {
            return SearchFilter();
        }

        if (word == "failed" || word == "fail" || word == "failing") {
            f.failedOnly = true; f.understood = true;
        } else if (word == "passed" || word == "pass" || word == "passing") {
            f.passedOnly = true; f.understood = true;
        } else if (word == "top" || word == "best" || word == "highest") {
            f.top = true; f.understood = true;
        } else if (word == "lowest" || word == "worst") {
            f.lowest = true; f.understood = true;
        } else if (word == "all" || word == "everyone") {
            f.understood = true;
        } else if (prev == "grade" && word.size() == 1 &&
                   string("abcdf").find(word[0]) != string::npos) {
            f.grade = static_cast<char>(toupper(static_cast<unsigned char>(word[0])));
            f.understood = true;
        } else if (prev == "above" || prev == "over" || prev == "below" || prev == "under") {
            try {
                size_t pos = 0;
                double n = stod(word, &pos);
                if (pos == word.size()) {
                    if (prev == "above" || prev == "over") f.minScore = n;
                    else f.maxScore = n;
                    f.understood = true;
                }
            } catch (...) {}
        }
        prev = word;
    }
    return f;
}

// VALIDATE RESULT: never trust the AI's answer blindly.
bool validateFilter(const SearchFilter& f) {
    if (!f.understood) return false;
    if (!(f.minScore >= -1 && f.minScore <= 100)) return false;
    if (!(f.maxScore >= 0 && f.maxScore <= 101)) return false;
    if (f.failedOnly && f.passedOnly) return false;
    if (f.top && f.lowest) return false;
    return true;
}

bool matchesFilter(const Student& s, const SearchFilter& f) {
    if (s.getScore() <= f.minScore || s.getScore() >= f.maxScore) return false;
    if (f.grade && s.getGrade() != f.grade) return false;
    if (f.failedOnly && s.getGrade() != 'F') return false;
    if (f.passedOnly && s.getGrade() == 'F') return false;
    return true;
}

// Sends the request to the "AI", validates the result, displays the matches.
void aiSearch(Student student[], int count, const string& query) {
    SearchFilter f = mockAiInterpret(query);
    if (!validateFilter(f)) {
        cout << "Sorry, I didn't understand that. Try \"students who failed\", "
                "\"grade A\", \"score above 80\", or \"top student\"." << endl;
        return;
    }

    double best = -1, worst = 101;
    for (int i = 0; i < count; i++) {
        if (!matchesFilter(student[i], f)) continue;
        if (student[i].getScore() > best) best = student[i].getScore();
        if (student[i].getScore() < worst) worst = student[i].getScore();
    }

    int matches = 0;
    for (int i = 0; i < count; i++) {
        if (!matchesFilter(student[i], f)) continue;
        if (f.top && student[i].getScore() != best) continue;
        if (f.lowest && student[i].getScore() != worst) continue;
        student[i].displayStudent();
        cout << endl;
        matches++;
    }
    if (matches == 0) cout << "No students matched." << endl;
    else cout << matches << " student(s) found." << endl;
}

// ===== end of AI feature =====

int main() {
    
    // Initialize an array of students and a counter for the number of students.
    Student student[21];   // CHANGED: 20 from the file + 1 added student
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

    // NEW: AI search (mock)
    cout << "\n--- AI Search (mock) ---" << endl;
    cout << "Try: \"students who failed\", \"grade A\", \"score above 80\", \"top student\"" << endl;
    cout << "Search: ";
    string query;
    if (getline(cin, query)) {
        aiSearch(student, count, query);
    }

    cout << "\n --- Date Check ---" << endl;
    string testDate;
    do {
        cout << "Enter a date (YYYY-MM-DD): ";
        getline(cin, testDate);
    } while (!isValidDate(testDate));
    cout << "Valid date entered: " << testDate << endl;

    cout << "\n--- Search for a Student ---" << endl;
    string target = getValidId();

    int found = binarySearch(student, count, target); // Search for a student by ID using binary search
   
    // Display the student record if found, otherwise print "Not Found"
    if (found != -1) student[found].displayStudent();
    else cout << "Not Found" << endl;

    return 0;

}
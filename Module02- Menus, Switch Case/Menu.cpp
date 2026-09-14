#include <iostream>
#include <limits>
using namespace std;

void addRecord() {
    cout << "Add Record selected." << endl;
}

void viewRecords() {
    cout << "View Records selected." << endl;
}

void searchRecords() {
    cout << "Search selected." << endl;
}

void updateRecords() {
    cout << "Update selected." << endl;
}

void deleteRecords() {
    cout << "Delete selected." << endl;
}
int main() {
    int choice = 0;
    do {
       
        cout << "1. Add Records" << endl;
        cout << "2. View Records" << endl;
        cout << "3. Search Records" << endl;
        cout << "4. Update Records" << endl;
        cout << "5. Delete Records" << endl;
        cout << "6. Exit" << endl;
        cout << "Select Menu: ";
        cin >> choice; 

         // external help from tutor was used to fix the issue of 
            //the program crashing when a letter was entered instead 
            //of a number. The solution was to use cin.fail() to check
            //if the input failed, and if so, clear the error state and
            //ignore the rest of the line. This prevents the program 
            //from crashing and allows the user to enter a valid number.
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }



        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                viewRecords();
                break;
            case 3:
                searchRecords();
                break;
            case 4:
                updateRecords();
                break;
            case 5:
                deleteRecords();
                break;
            case 6:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
    return 0;

}

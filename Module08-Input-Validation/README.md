
About Program
--------------
This program is a small student-record manager. It loads up to 20 students (ID, score, grade) from ../students.csv and prints them. It then asks you to add one more, repeating each question until the ID isn't empty, the score is 0 to 100, and the grade is A to F. Next it sorts the students by ID, asks for a date in YYYY-MM-DD format until you enter a valid one, and finally searches for a student by ID with binary search.

The CSV Format is 
''''''''

|id|score|grade|

|STU000010| 98.0| A|

|STU000011| 72.0| C

'''''''''

How it Works
-------------
* The program reads the csv file and prints every student, plus the first student's ID through a pointer.
* It asks for a new student's ID, score, and grade. The ID can't be empty, the score must be a number from 0 to 100, the grade must be A,B,C,D, or F.

Program Structure
------------------
* 'Student' - stores an ID,score, and grade. it tend calculates the letter grade
* 'User' - Base class with 'viewRecords()'
* 'Admin' - Inherits form 'User' and adds 'addRecord()'
* 'binarySearch()' - finds a student by ID in the sorted array
* 'getValidID()', 'getValidScore()', 'getValidGrade()' - re-prompts until the input is valid
* 'isValidDate' - Checks a 'YYYY-MM-DD' date

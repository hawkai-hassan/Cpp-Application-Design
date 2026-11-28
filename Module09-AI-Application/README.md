AI Feature: Natural-Language Search

1. What the feature does

The app currently only finds a student by exact ID via binary search. The AI feature allows the user to enter a plain English request (e.g. students who failed, students with a score above 80).

The AI component parses the sentence and returns a set of search filters. The C++ code then applies those filters to the student records that have been loaded and presents the results.

Understanding freeform language is a job that's actually better suited to AI than it is to a set of rigid rules. Loading, validation, sorting and ID lookup all remain as traditional code.

2. What data it needs

Data	Source	Used for
The user's query	Typed at the Search: prompt	Working out what the user wants
Exam score	exam_score column in students.csv	score above 80, below 50, top and lowest
Grade	performance_grade column in students.csv	grade A, passed and failed


"Failed" is an F in the stored grade and "passed" is any other grade. Only the query would be sent to the AI service. The student records remain within the programme.

3. What the user sees

--- AI Search (mock) ---
Try: "students who failed", "grade A", "score above 80", "top student"
Search: top student
Student ID: STU_000008
Student Score: 97.61
Student Grade: A

1 student(s) found.


This is what the output from students.csv should be, barring the case where the student who was added earlier in the run has a higher score.

Query	Result
students who failed	Students with grade F
students who passed	Students with any other grade
grade A	Students with that grade
score above 80 / score below 50	Students strictly above or below the number
top student / lowest	The highest or lowest score


If the query isn't understood then the program prints out a help message with some example queries rather than attempting to guess. If nothing matches then it simply prints 'No students matched'.

4. Where AI fits in the architecture

C++ Application
     |
     +--> User Request       getline(cin, query) in main()
     |
     +--> Prepare Data       lowercase the query, remove punctuation
     |
     +--> AI Service/Model   mockAiInterpret()  (the mock)
     |
     +--> Receive Result     a SearchFilter struct
     |
     +--> Validate Result    validateFilter()
     |
     +--> Display to User    aiSearch() prints the matches and a count


The AI step only generates filters, it never produces student records. The C++ code then applies those filters to its own data so the feature can't display a student who doesn't exist.

validateFilter() will reject a result if it's one that wasn't understood, has scores outside the valid range or is self-contradictory (e.g. both passed and failed).

5. The mock version

There's no live AI service connected so mockAiInterpret() in main.cpp is being used as a stand-in for the model. It uses keyword rules but takes the same input (a sentence) and returns the same output (a SearchFilter) that a real model would.

The mock is composed of five parts: SearchFilter struct, mockAiInterpret(), validateFilter(), matchesFilter() and aiSearch().

6. The live AI service that would replace the mock

The service would be a large language model via a hosted API (i.e. the OpenAI, Anthropic Claude or Google Gemini API). Ollama running a local model is an alternative in the case where cost or internet access is an issue.

1. The program takes the user's query and then asks for a reply in JSON with the same fields as SearchFilter.
2. The program parses the response into a SearchFilter.
3. validateFilter() does that, precisely as it does at the moment.
4. If the service is down or the response is invalid the program falls back to the mock rules.

Only mockAiInterpret() would be different. The rest of the app is unchanged.

7. Limitations of the mock

* It only understands the phrases listed above. It doesn't cope with typos, doesn't do synonym substitution and won't answer questions of the type "what is the average score?".
* It will simply refuse negation of the form 'did not fail' rather than resort to guessing.
* Conditions in a single query are combined so that a failed grade A will return no matches.
* It does one search per program run.

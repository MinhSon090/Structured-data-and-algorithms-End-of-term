#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include <stdlib.h>

using namespace std;

// Data structure for Student
struct Student {
    string id;
    string name;
    float gpa;
};

// The only two stacks used in the entire program
stack<Student> mainStack;
stack<Student> tempStack;

const string FILE_NAME = "students.csv";

// Helper function to load data from CSV at startup
int loadData() {
    ifstream file(FILE_NAME);
    if (!file.is_open()) {
        return 1;
    }

    string line;
    // Reading sequentially: First line becomes the bottom of the stack
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string id, name, gpaStr;
        
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, gpaStr, ',');

        Student s = {id, name, stof(gpaStr)};
        mainStack.push(s);
    }
    file.close();
    return 0; // Return 0 on success, 1 on failure
}

// Helper function to save data to CSV before exit
void saveData() {
    ofstream file(FILE_NAME, ios::trunc);
    if (!file.is_open()) {
        cout << "Error: Could not save to database.\n";
        return;
    }

    // Move all items to tempStack. 
    // The bottom of mainStack becomes the top of tempStack.
    while (!mainStack.empty()) {
        tempStack.push(mainStack.top());
        mainStack.pop();
    }

    // Write to file from top of tempStack (which is the old bottom),
    // and restore items back to mainStack.
    while (!tempStack.empty()) {
        Student s = tempStack.top();
        file << s.id << "," << s.name << "," << s.gpa << "\n";
        mainStack.push(s);
        tempStack.pop();
    }
    file.close();
    cout << "Data saved successfully.\n";
}

// Display all records (Requires moving elements to tempStack and back)
void displayStudents() {
    if (mainStack.empty()) {
        cout << "Stack is empty.\n";
        return;
    }

    cout << "\n--- Student Records (Top to Bottom) ---\n";
    while (!mainStack.empty()) {
        Student s = mainStack.top();
        cout << "ID: " << s.id << " | Name: " << s.name << " | GPA: " << s.gpa << "\n";
        tempStack.push(s);
        mainStack.pop();
    }

    // Restore data
    while (!tempStack.empty()) {
        mainStack.push(tempStack.top());
        tempStack.pop();
    }
    cout << "---------------------------------------\n";
}

// 4. SEARCH Operation
int searchStudent(string targetId = "-1", bool displayResult = true) {
    bool found = false;

    while (!mainStack.empty()) {
        Student s = mainStack.top();
        if (s.id == targetId) {
            cout << "Found -> ID: " << s.id << " | Name: " << s.name << " | GPA: " << s.gpa << "\n";
            found = true;
            break;
        }
        tempStack.push(s);
        mainStack.pop();
    }

    while (!tempStack.empty()) {
        mainStack.push(tempStack.top());
        tempStack.pop();
    }

    if (!found && displayResult) cout << "Student not found.\n";
    return found ? 1 : 0; //Return 1 if found, else 0
}

// 1. ADD Operation
void addStudent() {
    Student s;
    cout << "Enter ID: "; cin >> s.id;

    if (searchStudent(s.id, false) == 1) {
        cout << "Error: Student with this ID already exists.\n";
        return;
    }
    cin.ignore();
    cout << "Enter Name: "; getline(cin, s.name);
    cout << "Enter GPA: "; cin >> s.gpa;
    
    mainStack.push(s);
    cout << "Student added successfully.\n";
}

// 2. DELETE Operation
void deleteStudent() {
    string targetId;
    cout << "Enter ID to delete: "; cin >> targetId;
    bool found = false;

    while (!mainStack.empty()) {
        Student s = mainStack.top();
        mainStack.pop();
        
        if (s.id == targetId) {
            found = true;
            cout << "Student deleted.\n";
            break; // Stop moving to tempStack, discarding this student
        } else {
            tempStack.push(s);
        }
    }

    // Restore remaining elements
    while (!tempStack.empty()) {
        mainStack.push(tempStack.top());
        tempStack.pop();
    }

    if (!found) cout << "Student not found.\n";
}

// 3. UPDATE Operation
void updateStudent() {
    string targetId;
    cout << "Enter ID to update: "; cin >> targetId;
    bool found = false;

    while (!mainStack.empty()) {
        Student s = mainStack.top();
        mainStack.pop();
        
        if (s.id == targetId) {
            found = true;
            cout << "Enter new Name: ";
            cin.ignore();
            getline(cin, s.name);
            cout << "Enter new GPA: "; cin >> s.gpa;
            
            mainStack.push(s); // Push updated student back
            cout << "Student updated.\n";
            break;
        } else {
            tempStack.push(s);
        }
    }

    while (!tempStack.empty()) {
        mainStack.push(tempStack.top());
        tempStack.pop();
    }

    if (!found) cout << "Student not found.\n";
}



// 5. SORT Operation (Sort by GPA Ascending - Highest on Top)
void sortStudents() {
    while (!mainStack.empty()) {
        Student current = mainStack.top();
        mainStack.pop();

        // While tempStack is not empty and the top element is smaller than the current element
        while (!tempStack.empty() && tempStack.top().gpa < current.gpa) {
            mainStack.push(tempStack.top());
            tempStack.pop();
        }
        tempStack.push(current);
    }

    // Pour the sorted elements back into mainStack
    while (!tempStack.empty()) {
        mainStack.push(tempStack.top());
        tempStack.pop();
    }
    cout << "Stack sorted by GPA (Highest on top).\n";
}

int main() {
    loadData();

    int choice;
    do {
        system("cls"); 
        cout << "\n=== STACK MANAGEMENT SYSTEM ===\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Update Student\n";
        cout << "4. Search Student\n";
        cout << "5. Sort by GPA\n";
        cout << "6. Display All\n";
        cout << "0. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            system("cls");
            addStudent();
        } else if (choice == 2) {
            system("cls");
            displayStudents();
            deleteStudent();
        } else if (choice == 3) {
            system("cls");
            displayStudents();
            updateStudent();
        } else if (choice == 4) {
            system("cls");
            string targetId;

            cout << "Enter ID to search: "; cin >> targetId;
            searchStudent(targetId);
        } else if (choice == 5) {
            system("cls");
            sortStudents();
            displayStudents();
        } else if (choice == 6) {
            system("cls");
            displayStudents();
        }

        cout << "\nPress Enter to continue..."; cin.ignore(); cin.get();
    } while (choice != 0);

    saveData();
    return 0;
}
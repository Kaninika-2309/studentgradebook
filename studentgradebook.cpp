#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int roll;
    map<string, int> subjectMarks;

public:
    Student(string n, int r) {
        name = n;
        roll = r;
    }

    void addMarks(const string& subject, int marks) {
        subjectMarks[subject] = marks;
    }

    float calculatePercentage() const {
        if (subjectMarks.empty()) return 0.0f;
        int total = 0;
        for (auto& it : subjectMarks) {
            total += it.second;
        }
        return (float)total / subjectMarks.size();
    }

    char calculateGrade() const {
        float avg = calculatePercentage();
        if (avg >= 90) return 'A';
        else if (avg >= 75) return 'B';
        else if (avg >= 50) return 'C';
        else return 'F';
    }

    void displayReport() const {
        cout << "\n--- Report Card ---\n";
        cout << "Name: " << name << "\nRoll Number: " << roll << endl;
        cout << "Subject Marks:\n";
        for (auto& it : subjectMarks) {
            cout << " - " << it.first << ": " << it.second << "/100\n";
        }
        cout << "Percentage: " << calculatePercentage() << "%\n";
        cout << "Grade: " << calculateGrade() << "\n";
    }

    int getRollNumber() const {
        return roll;
    }
};

// Find student by roll number
Student* findStudent(vector<Student>& students, int roll) {
    for (auto& s : students) {
        if (s.getRollNumber() == roll)
            return &s;
    }
    return nullptr;
}

int main() {
    vector<Student> students;
    int choice;

    do {
        cout << "\n====== Student Gradebook Menu ======\n";
        cout << "1. Add Student\n2. Enter Marks\n3. Show Report\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int roll;
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter roll number: ";
            cin >> roll;

            students.push_back(Student(name, roll));
            cout << "Student added successfully.\n";

        } else if (choice == 2) {
            int roll, numSubjects;
            cout << "Enter student roll number: ";
            cin >> roll;

            Student* s = findStudent(students, roll);
            if (!s) {
                cout << "Student not found!\n";
                continue;
            }

            cout << "Enter number of subjects: ";
            cin >> numSubjects;
            cin.ignore();

            for (int i = 0; i < numSubjects; ++i) {
                string subject;
                int marks;
                cout << "Enter subject name: ";
                getline(cin, subject);
                cout << "Enter marks: ";
                cin >> marks;
                cin.ignore();
                s->addMarks(subject, marks);
            }
            cout << "Marks added.\n";

        } else if (choice == 3) {
            int roll;
            cout << "Enter roll number to view report: ";
            cin >> roll;

            Student* s = findStudent(students, roll);
            if (s) {
                s->displayReport();
            } else {
                cout << "Student not found!\n";
            }

        } else if (choice == 0) {
            cout << "Exiting Gradebook. Goodbye!\n";
        } else {
            cout << "Invalid option. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}

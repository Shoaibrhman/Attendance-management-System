# include "Teacher.h"
# include <iostream>
# include <string>
# include <cctype>
# include <unordered_map>
# include <vector>
# include <algorithm>
using namespace std;

void printMenu() {
    cout << "~~~ Attendance Management " << endl;
    cout << "           System ~~~" << endl;
    cout << "1. Add Student (enter custom courses)" << endl;
    cout << "2. Mark Attendance" << endl;
    cout << "3. Show Student info by Roll Number" << endl; // Updated menu option
    cout << "4. Show Attendance by Course" << endl;
    cout << "5. Save and Exit" << endl;
    cout << "Choice: ";
}

bool login() {
    string username , password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
    return (username == "Teacher.QAU" && password == "Quaidian");
}

int main() {
    Teacher teacher;
    // Teacher login
    if (!login()) {
        cout << "Invalid credentials. Exiting." << endl;
        return 1;
    }
    teacher.loadFromFile("attendance.txt");
    
    int choice = 0;
    while (true) {
        printMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000 , '\n');
            cout << "Invalid input." << endl;
            continue;
        }
        cin.ignore();
        if (choice == 1) {
        string name;
        int roll;
        int numCourses;
        vector<string> courses;
        cout << "Student Name: ";
        getline(cin , name);
        cout << "Roll Number: ";
        cin >> roll;
        cin.ignore();
        // Prompt for the number of courses
        cout << "Enter the number of courses (1 to 6): ";
        cin >> numCourses;
        cin.ignore();
        // Validate the number of courses
        if (numCourses < 1 || numCourses > 6) {
            cout << "Invalid number of courses. Please enter a number between 1 and 6." << endl;
            continue; // Go back to the menu
        }
        // Collect the courses
        cout << "Enter " << numCourses << " course(s):" << endl;
        for (int i = 0; i < numCourses; ++i) {
            string course;
            cout << "Course " << (i + 1) << ": ";
            getline(cin, course);
            courses.push_back(course); // Add the course to the list
            }
            // Add the student with the entered courses
            teacher.addStudent(name , roll , courses);
        }

        else if (choice == 2) {
            int roll;
            string course , date;
            char attendanceChar;
            bool present;
            cout << "Student Roll Number: ";
            cin >> roll; cin.ignore();
            // Check if the student exists with the given roll number
            bool studentFound = false;
            for (const auto& student : teacher.getStudents()) {
                if (student.getRollNo() == roll) {
                    studentFound = true; // Student exists
                    break;
                }
            }
            if (!studentFound) {
                cout << "No Student found with Roll Number: " << roll << ". Incorrect Roll Number." << endl;
                continue; // Go back to the menu
                }
                while (true) {
                    cout << "Course: ";
                    getline(cin , course);
                    if (!course.empty()) {
                        break; // exit the loop if the course name is valid
                        } else {
                            cout << "Invalid Course Name. Please try again." << endl;
                        }
                    }
                    // Check if the student is enrolled in the entered course
                    bool courseFound = false;
                    for (const auto& student : teacher.getStudents()) {
                        if (student.getRollNo() == roll) {
                            const auto& courses = student.getCourses();
                            if (find(courses.begin(), courses.end(), course) != courses.end()) {
                                courseFound = true; // Course is valid for this student
                                break;
                            }
                        }
                    }
                    if (!courseFound) {
                        cout << "Student not enrolled in Course: " << course << ". Invalid Course Name." << endl;
                        continue; // Go back to the menu
                        }
                        cout << "Date (MM-DD-YYYY): ";
                        getline(cin , date);
                        cout << "Attendance (P for present , A for absent): ";
                        cin >> attendanceChar; cin.ignore();
                        attendanceChar = tolower(attendanceChar);
                        if (attendanceChar == 'p')
                        present = true;
                        else if (attendanceChar == 'a')
                        present = false;
                        else {
                            cout << "Invalid attendance input.";
                            continue;
                        }
                        teacher.markAttendance(roll, course, date, present);
        }

        else if (choice == 3) {
            int roll;
            cout << "Enter Roll Number: "; // Updated prompt
            cin >> roll; cin.ignore();
            teacher.displayStudentInfoByRollNumber(roll); // Updated function call
        }
        else if (choice == 4) {
            string course;
            cout << "Enter Course Name: ";
            getline(cin , course);
            cout << "Attendance records for Course: " << course << endl;
            bool courseFound = false; // Flag to check if any student is enrolled in the course
            for (const auto& student : teacher.getStudents()) { // Assuming you have a method to get students
                const auto& courses = student.getCourses();
                if (find(courses.begin() , courses.end() , course) != courses.end()) {
                    courseFound = true; // At least one student is enrolled in the course
                    cout << "Student: " << student.getName() << " (Roll No: " << student.getRollNo() << ")" << endl;
                    // Retrieve and display attendance records for the specified course
                    const auto& attendanceRecords = student.getAttendanceRecords(course); // Assuming this method exists
                    for (const auto& record : attendanceRecords) {
                        cout << "Date: " << record.first << " - " << (record.second ? "Present" : "Absent") << endl;
                    }
                    cout << endl; // Add a newline for better readability
                    }
                }
                if (!courseFound) {
                    cout << "No Students are enrolled in the Course: " << course << endl;
                }
        }
            else if (choice == 5) {
                teacher.saveToFile("attendance.txt");
                cout << "Data saved. Exiting." << endl;
                break;
            }
            else {
                cout << "Invalid choice." << endl;
            }
        }
        return 0;
    }
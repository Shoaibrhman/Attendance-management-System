# include "Teacher.h"
# include <iostream>
# include <fstream>
# include <algorithm>
using namespace std;

void Teacher::addStudent(const string& name , int rollNo , const vector<string>& courses) {
    for (const auto& s : students) {
        if (s.getRollNo() == rollNo) {
            cout << "Roll number " << rollNo << " already exists." << endl;
            return;
        }
    }
    students.emplace_back(name , rollNo , courses);
    cout << "Student added with custom courses." << endl;
}

void Teacher::markAttendance(int rollNo , const string& course , const string& date , bool present) {
    for (auto& s : students) {
        if (s.getRollNo() == rollNo) {
            s.markAttendance(course , date , present);
            cout << "Attendance marked." << endl;
            return;
        }
    }
    cout << "No student found with roll number " << rollNo << "." << endl;
}

void Teacher::displayStudentInfoByRollNumber(int rollNo) const {
    for (const auto& s : students) {
        if (s.getRollNo() == rollNo) {
            s.displayInfo();
            return;
        }
    }
    cout << "No student found with roll number " << rollNo << "." << endl;
}

void Teacher::displayAttendanceByCourse(const string& course) const {
    cout << "Attendance records for course: " << course << endl;
    for (const auto& s : students) {
        const auto& courses = s.getCourses();
        if (find(courses.begin() , courses.end() , course) != courses.end()) {
            cout << "Student: " << s.getName() << " (Roll No: " << s.getRollNo() << ")" << endl;
            const auto& attendanceRecords = s.getAttendanceRecords(course); // Assuming this method exists
            for (const auto& record : attendanceRecords) {
                cout << "Date: " << record.first << " - " << (record.second ? "Present" : "Absent") << endl;
            }
            cout << endl; // Add a newline for better readability
        }
    }
}

void Teacher::saveToFile(const string& filename) const {
    ofstream outFile(filename);
    for (const auto& s : students) {
        s.serialize(outFile);
    }
}

void Teacher::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) return;

    students.clear();
    while (inFile.peek() != EOF) {
        Student s;
        s.deserialize(inFile);
        if (!s.getName().empty()) students.push_back(s);
    }
}

// Implementation of getStudents method
const vector<Student>& Teacher::getStudents() const {
    return students; // Return the vector of students
}
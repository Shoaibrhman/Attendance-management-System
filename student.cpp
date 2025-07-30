# include "Student.h"
# include <iostream>
# include <iomanip>
# include <sstream>
# include <algorithm>
using namespace std;

Student::Student() : rollNo(0) {}
Student::Student(const string& name , int rollNo , const vector<string>& courses)
    : name(name) , rollNo(rollNo) , courses(courses) { }

string Student::getName() const { return name; }
int Student::getRollNo() const { return rollNo; }
const vector<string>& Student::getCourses() const {
    return courses; // Return the list of courses
}

void Student::markAttendance(const string& course , const string& date , bool present) {
    if (find(courses.begin() , courses.end() , course) != courses.end()) {
        attendanceRecords[course][date] = present;
    } else {
        cout << "Student not enrolled in course: " << course << endl;
    }
}

// Implementation of getAttendanceRecords method
map<string, bool> Student::getAttendanceRecords(const string& course) const {
    if (attendanceRecords.find(course) != attendanceRecords.end()) {
        return attendanceRecords.at(course); // Return the attendance records for the specified course
    }
    return {}; // Return an empty map if the course is not found
}

map<string , double> Student::calculateAttendanceWeightage() const {
    map<string , double> weightages;
    for (const auto& course : courses) {
        auto it = attendanceRecords.find(course);
        if (it == attendanceRecords.end() || it->second.empty()) {
            weightages[course] = 0.0;
            continue;
        }
        int presentCount = 0;
        int totalCount = 0;
        for (const auto& record : it->second) {
            totalCount++;
            if (record.second) presentCount++;
        }
        double percent = (totalCount > 0) ? (100.0 * presentCount / totalCount) : 0.0;
        weightages[course] = percent;
    }
    return weightages;
}

void Student::displayInfo() const {
    cout << "Name: " << name << endl;
    cout << "Roll Number: " << rollNo << endl;
    cout << "Enrolled Courses and Attendance Weightage:" << endl;
    auto weightages = calculateAttendanceWeightage();
    for (const auto& course : courses) {
        cout << "  " << course << ": " << fixed << setprecision(2)
                  << weightages[course] << " %" << endl;;
    }
}

void Student::serialize(ofstream& outFile) const {
    outFile << name << endl;
    outFile << rollNo << endl;
    for (const auto& c : courses) {
        outFile << c << endl;
    }
    outFile << "ENDCOURSES" << endl;
    for (const auto& courseEntry : attendanceRecords) {
        for (const auto& dateEntry : courseEntry.second) {
            outFile << courseEntry.first << " " << dateEntry.first << " " << (dateEntry.second ? 1 : 0) << endl;
        }
    }
    outFile << "ENDATTENDANCE" << endl;
    outFile << "ENDSTUDENT" << endl;
}

void Student::deserialize(ifstream& inFile) {
    getline(inFile , name);
    string line;
    getline(inFile , line);
    rollNo = stoi(line);
    courses.clear();
    attendanceRecords.clear();
    // Courses
    while (getline(inFile , line)) {
        if (line == "ENDCOURSES") break;
        if (!line.empty())
            courses.push_back(line);
    }
    // Attendance
    while (std::getline(inFile , line)) {
        if (line == "ENDATTENDANCE") break;
        if (line.empty()) continue;
        istringstream iss(line);
        string course , date;
        int present_int;
        iss >> course >> date >> present_int;
        attendanceRecords[course][date] = (present_int == 1);
    }
    // Read ENDSTUDENT line to move forward
    getline(inFile , line);
}
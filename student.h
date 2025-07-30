# ifndef STUDENT_H
# define STUDENT_H

# include <string>
# include <map>
# include <vector>
# include <fstream>
using namespace std;

class Student { 
    private:
    string name;
    int rollNo;
    vector<string> courses; // exactly 6 courses
    map<string , map<string , bool>> attendanceRecords; // course -> date -> present/absent
    public:
    Student();
    Student(const string& name , int rollNo , const vector<string>& courses);
    string getName() const;
    int getRollNo() const;
    const vector<string>& getCourses() const; // Ensure this method is present

    void markAttendance(const string& course , const string& date , bool present);
    // New method to get attendance records for a specific course
    map<string , bool> getAttendanceRecords(const string& course) const;
    // Calculate percentage attendance per course
    map<string , double> calculateAttendanceWeightage() const;

    void displayInfo() const;
    void serialize(ofstream& outFile) const;
    void deserialize(ifstream& inFile);
};
#endif // STUDENT_H
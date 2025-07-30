# ifndef TEACHER_H
# define TEACHER_H

# include "Student.h"
# include <vector>
# include <string>
using namespace std;

class Teacher {
    private:
    vector<Student> students;
    public:
    void addStudent(const string& name , int rollNo , const vector<string>& courses);
    void markAttendance(int rollNo , const string& course , const string& date , bool present);
    void displayStudentInfoByRollNumber(int rollNo) const;
    void displayAttendanceByCourse(const string& course) const;
    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
    
    // New method to get the list of students
    const vector<Student>& getStudents() const; // Declaration
};
#endif // TEACHER_H
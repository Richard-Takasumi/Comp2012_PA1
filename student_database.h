#ifndef __STUDENT_DATABASE_H__
#define __STUDENT_DATABASE_H__

class Student;

class Student_Database {
    private:
    Student** students;
    int capacity;
    int size;

    public:
    Student_Database(const int capacity);
    Student_Database(const Student_Database& database);
    ~Student_Database();

    bool create_entry(const char* const name, const int student_id, const double gpa);
    Student* get_student_by_id(const int student_id) const;
    
    // Helper function for debugging
    void print_all_students() const;

    Student** get_students() const;
    int get_capacity() const;
    int get_size() const;

    void set_students(Student** const students);
    void set_capacity(const int capacity);
    void set_size(const int size);
};

#endif
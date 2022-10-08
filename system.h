#ifndef __SYSTEM_H__
#define __SYSTEM_H__

class Course_Database;
class Student_Database;

class System {
    private:
    Course_Database* course_database;
    Student_Database* student_database;

    public:
    System(const int max_num_course, const int max_num_student);
    System(const System& system);
    ~System();

    // Student related functions
    void admit(const char* const name, const int student_id, const double gpa);
    bool apply_overload(const int student_id, const int request_credit);
    bool add(const int student_id, const char* const course_name);
    bool swap(const int student_id, const char* const original_course_name, const char* const target_course_name); // Always assume that student has enrolled into the original course
    void drop(const int student_id, const char* const course_name); // Assume student always has the course to drop
    
    // Course related functions
    void add_course(const char* const name, const int num_credit, const int max_capacity);
    
    void print_info() const;

    Course_Database* get_course_database() const;
    Student_Database* get_student_database() const;

    void set_course_database(Course_Database* const course_database);
    void set_student_database(Student_Database* const student_database);
};

#endif
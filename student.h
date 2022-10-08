#ifndef __STUDENT_H__
#define __STUDENT_H__

class Swap_List;

class Student {
    private:
    char* name; // A pointer to a dynamically allocated array
    int student_id;
    double gpa;
    int max_credit;
    int curr_credit;

    int num_enrolled_course;
    char** enrolled_courses; // A pointer to a 2D dynamically allocated array with the names of enrolled courses

    int pending_credit;      // The extra number of credits the student will receive if all pending swaps are enrolled successfully
    Swap_List* swap_list;    // A pointer to a dynamically allocated Swap_List object

    public:
    Student(const char* const name, const int student_id, const double gpa);
    Student(const Student& student);
    ~Student();

    void print_info() const;

    char* get_name() const;
    int get_student_id() const;
    double get_gpa() const;
    int get_max_credit() const;
    int get_curr_credit() const;
    int get_num_enrolled_course() const;
    char** get_enrolled_courses() const;
    int get_pending_credit() const;
    Swap_List* get_swap_list() const;

    void set_name(char* const name);
    void set_student_id(const int student_id);
    void set_gpa(const double gpa);
    void set_max_credit(const int max_credit);
    void set_curr_credit(const int curr_credit);
    void set_num_enrolled_course(const int num_enrolled_course);
    void set_enrolled_courses(char** const enrolled_courses);
    void set_pending_credit(const int pending_credit);
    void set_swap_list(Swap_List* const swap_list);
};

#endif
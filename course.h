#ifndef __COURSE_H__
#define __COURSE_H__

class Student_ListNode;
class Wait_List;

class Course {
    private:
    char* name;
    int num_credit;
    int capacity;
    int size;
    Wait_List* wait_list;
    int* students_enrolled;
    
    public:
    Course(const char* const name, const int num_credit, const int course_capacity);
    Course(const Course& course);
    ~Course();

    void print_info() const;

    char* get_name() const;
    int get_num_credit() const;
    int get_capacity() const;
    int get_size() const;
    Wait_List* get_wait_list() const;
    int* get_students_enrolled() const;

    void set_name(char* const name);
    void set_num_credit(const int num_credit);
    void set_capacity(const int capacity);
    void set_size(const int size);
    void set_wait_list(Wait_List* const wait_list);
    void set_students_enrolled(int* const students_enrolled);    
};

#endif
#ifndef __COURSE_DATABASE_H__
#define __COURSE_DATABASE_H__

class Course;

class Course_Database {
    private:
    Course** courses;
    int capacity;
    int size;

    public:
    Course_Database(const int capacity);
    Course_Database(const Course_Database& database);
    ~Course_Database();

    bool create_entry(const char* const name, const int num_credit, const int course_capacity);
    Course* get_course_by_name(const char* const course_name) const;

    // Helper function for debugging
    void print_all_course() const;

    Course** get_courses() const;
    int get_capacity() const;
    int get_size() const;
    
    void set_courses(Course** const courses);
    void set_capacity(const int capacity);
    void set_size(const int size);
};

#endif
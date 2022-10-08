#include <iostream>
#include <cstring>
#include "course_database.h"
#include "course.h"

using namespace std;

Course_Database::Course_Database(const int capacity) {
    this->courses = new Course*[capacity];
    this->capacity = capacity;
    this->size = 0;
}

Course_Database::Course_Database(const Course_Database& database) {
    this->capacity = database.capacity;
    this->size = database.size;
    this->courses = new Course*[this->capacity];
    for(int i = 0; i < database.size; ++i) {
        this->courses[i] = new Course(*database.courses[i]);
    }
}

Course_Database::~Course_Database() {
    for(int i = 0; i < this->size; ++i) {
        if(this->courses[i]) {
            delete this->courses[i];
        }
    }
    delete [] courses;
}

bool Course_Database::create_entry(const char* const name, const int num_credit, const int course_capacity) {
    if(this->size < this->capacity) {
        this->courses[this->size++] = new Course(name, num_credit, course_capacity);
        return true;
    }
    return false;
}

Course* Course_Database::get_course_by_name(const char* const course_name) const {
    for(int i = 0; i < this->size; ++i) {
        Course* next_course = this->courses[i];
        if(strcmp(next_course->get_name(), course_name) == 0) {
            return next_course;
        }
    }
    return nullptr;
}

// Helper function for debugging
void Course_Database::print_all_course() const {
    cout << "PRINTING ALL COURSE INFORMATION: " << endl;
    for(int i = 0; i < this->size; ++i) {
        this->courses[i]->print_info();
        cout << endl;
    }
}

Course** Course_Database::get_courses() const {
    return courses;
}

int Course_Database::get_capacity() const {
    return capacity;
}

int Course_Database::get_size() const {
    return size;
}

void Course_Database::set_courses(Course** const courses) {
    this->courses = courses;
}

void Course_Database::set_capacity(const int capacity) {
    this->capacity = capacity;
}

void Course_Database::set_size(const int size) {
    this->size = size;
}

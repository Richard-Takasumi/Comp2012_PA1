#include <iostream>
#include "student_database.h"
#include "student.h"

using namespace std;

Student_Database::Student_Database(const int capacity) {
    this->students = new Student*[capacity];
    this->capacity = capacity;
    this->size = 0;
}

Student_Database::Student_Database(const Student_Database& database) {
    this->capacity = database.capacity;
    this->size = database.size;
    this->students = new Student*[this->capacity];
    for(int i = 0; i < database.size; ++i) {
        this->students[i] = new Student(*database.students[i]);
    }
}

Student_Database::~Student_Database() {
    for(int i = 0; i < this->size; ++i) {
        if(this->students[i]) {
            delete this->students[i];
        }
    }
    delete [] this->students;
}

bool Student_Database::create_entry(const char* const name, const int student_id, const double gpa) {
    if(this->size < this->capacity) {
        this->students[this->size++] = new Student(name, student_id, gpa);
        return true;
    }
    return false;
}

Student* Student_Database::get_student_by_id(const int student_id) const {
    for(int i = 0; i < this->size; ++i) {
        Student* next_student = this->students[i];
        if(next_student->get_student_id() == student_id){
            return next_student;
        }
    }
    return nullptr;
}

// Helper function for debugging
void Student_Database::print_all_students() const {
    cout << "PRINTING ALL STUDENT INFORMATION: " << endl;
    for(int i = 0; i < this->size; ++i) {
        this->students[i]->print_info();
        cout << endl;
    }
    cout << endl;
}

Student** Student_Database::get_students() const {
    return students;
}

int Student_Database::get_capacity() const {
    return capacity;
}

int Student_Database::get_size() const {
    return size;
}

void Student_Database::set_students(Student** const students) {
    this->students = students;
}

void Student_Database::set_capacity(const int capacity) {
    this->capacity = capacity;
}

void Student_Database::set_size(const int size) {
    this->size = size;
}

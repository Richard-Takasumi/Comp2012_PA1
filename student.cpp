#include <iostream>
#include <cstring>
#include "student.h"
#include "swap_list.h"

using namespace std;

const int STUDENT_INIT_MAX_CREDIT = 18;
const int STUDENT_MAX_NUM_COURSE = 10;

Student::Student(const char* const name, const int student_id, const double gpa) {
    // TODO
}

Student::Student(const Student& student) {
    // TODO
}

Student::~Student() {
    // TODO
}

void Student::print_info() const {
    cout << "-------------------" << endl;
    cout << "Student Name: " << this->name << endl;
    cout << "Student ID: " << this->student_id << "\t GPA: " << this->gpa << endl;
    cout << "Current Credit: " << this->curr_credit << " out of Max Credit: " << this->max_credit << endl;
    cout << endl;
    cout << "Num Courses Enrolled: " <<  this->num_enrolled_course << endl;
    cout << "Course Enrolled: " << endl;
    for(int i = 0; i < this->num_enrolled_course; ++i){
        cout << this->enrolled_courses[i] << endl;
    }
    cout << endl;
    cout << "Pending swaps information: " << endl;
    cout << "Pending Credit: " << this->pending_credit << endl;
    this->swap_list->print_list();
    cout << endl;
}

char* Student::get_name() const {
    return name;
}

int Student::get_student_id() const {
    return student_id;
}

double Student::get_gpa() const {
    return gpa;
}

int Student::get_max_credit() const {
    return max_credit;
}

int Student::get_curr_credit() const {
    return curr_credit;
}

int Student::get_num_enrolled_course() const {
    return num_enrolled_course;
}

char** Student::get_enrolled_courses() const {
    return enrolled_courses;
}

int Student::get_pending_credit() const {
    return pending_credit;
}

Swap_List* Student::get_swap_list() const {
    return swap_list;
}

void Student::set_name(char* const name) {
    this->name = name;
}

void Student::set_student_id(const int student_id) {
    this->student_id = student_id;
}

void Student::set_gpa(const double gpa) {
    this->gpa = gpa;
}

void Student::set_max_credit(const int max_credit) {
    this->max_credit = max_credit;
}

void Student::set_curr_credit(const int curr_credit) {
    this->curr_credit = curr_credit;
}

void Student::set_num_enrolled_course(const int num_enrolled_course) {
    this->num_enrolled_course = num_enrolled_course;
}

void Student::set_enrolled_courses(char** const enrolled_courses) {
    this->enrolled_courses = enrolled_courses;
}

void Student::set_pending_credit(const int pending_credit) {
    this->pending_credit = pending_credit;
}

void Student::set_swap_list(Swap_List* const swap_list) {
    this->swap_list = swap_list;
}
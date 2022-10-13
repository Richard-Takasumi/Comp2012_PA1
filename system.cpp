#include <iostream>
#include <cstring>
#include "system.h"
#include "student.h"
#include "course.h"
#include "course_database.h"
#include "student_database.h"
#include "wait_list.h"
#include "swap_list.h"

using namespace std;

/*
The following 3 helper functions may be useful in add/swap/drop function. You may implement them if you find them useful.
If not, you can remove these 3 helper functions as we will NOT set any test case testing these helper functions.
*/

// Helper function: add the Student to the end of the waitlist of the Course.
void join_waitlist(const int student_id, Course* course) {
    // TODO
}

// Helper function: find the index of a course within the enrolled course list of a student.
int search_course_index(const Student* const student, const char* const course_name) {
    // TODO
}

// Helper function: find the index of the student_id in the enrolled student list
int search_student_id(const int student_id, const Course* const course) {
    // TODO
}


System::System(const int max_num_course, const int max_num_student) {
    course_database = new Course_Database(max_num_course);
    student_database = new Student_Database(max_num_student);
}

System::System(const System& system) {
    this->course_database = new Course_Database(*system.course_database);
    this->student_database = new Student_Database(*system.student_database);
}

System::~System() {
    delete course_database;
    delete student_database;
}

void System::admit(const char* const name, const int student_id, const double gpa) {
    this->student_database->create_entry(name, student_id, gpa);
}

bool System::apply_overload(const int student_id, const int request_credit) {
    // TODO

    //find the student's gpa
    Student* student = this->student_database->get_student_by_id(student_id);

    //if the student does not exist return false
    if (student == nullptr) {
        return false;
    }


    // then do case handling

    if (request_credit > 30) {cout << 0 << endl; return false;}
    if (request_credit >= 24 && student->get_gpa() < 3.7) {cout << 1 << endl; return false;}
    if (request_credit >= 18 && student->get_gpa() < 3.3) {cout << 2 << endl; return false;}

    return true;


}

bool System::add(const int student_id, const char* const course_name) {
    // TODO

    // case 1 (credits are fine AND course is vacant):
    // student num credits + pending credits <= student max_credits
    // update course size
    // update course students_enrolled
    // update student curr_credits
    // update student enrolled_courses

    // accept, return true 

    // case 2 (credits are fine AND course is NOT vacant):
    // update student's pending credits
    // update course wait_list by: 
        // construct a student_listNode;
        // append student to the end of wait_list;
        // update wait_list pointers
    // return true

    // case 3 (credits are not fine, doesn't matter if the course is vacant or not):
    // student num credits + pending credits > student max_credits 
    // reject, return false




    Student* student = this->student_database->get_student_by_id(student_id);
    Course* course = this->course_database->get_course_by_name(course_name);

    // assume course if full then check and update.
    bool is_vacant = false;
    bool valid_credit_count = false;

    if (course->get_size() < course->get_capacity()) {
        is_vacant = true;
    }

    if (student->get_curr_credit() + student->get_pending_credit() <= student->get_max_credit()) {
        valid_credit_count = true;
    } 
    
    //CASE 1
    if (valid_credit_count && is_vacant) {

        //update the course size and student_enrolled list;
        int course_size = course->get_size();
        course->set_size(course_size+1);

        int* updated_students_enrolled = course->get_students_enrolled();
        updated_students_enrolled[course_size] = student_id;
        
        //not sure if the below line is required.
        course->set_students_enrolled(updated_students_enrolled);
        
        //update the student curr_credits, num_enrolled_courses and enrolled_courses
        student->set_curr_credit(student->get_curr_credit()+course->get_num_credit());
        student->set_num_enrolled_course(student->get_num_enrolled_course()+1);

        //update student->enrolled_courses;
        char** updated_enrolled_courses = student->get_enrolled_courses();

        //update student->num_enrolled_courses
        updated_enrolled_courses[student->get_num_enrolled_course()-1] = new char[strlen(course->get_name()+1)];
        strcpy(updated_enrolled_courses[student->get_num_enrolled_course()-1], course->get_name());

        //not sure if this line is required
        student->set_enrolled_courses(updated_enrolled_courses);


        return true;
    }

    //CASE 2
    if (valid_credit_count && !is_vacant) {

        //update student->pending_credits
        student->set_pending_credit(student->get_pending_credit()+course->get_num_credit());

        //create student_waitlist node;
        //append the node to the course->Waitlist;
        Student_ListNode* student_node = new Student_ListNode(student->get_student_id(), nullptr);

        Wait_List* course_waitlist = course->get_wait_list();
        Student_ListNode* head = course_waitlist->get_head();
        Student_ListNode* end = course_waitlist->get_end();

        //waitlist is empty
        if (head == nullptr) {
            course_waitlist->set_head(student_node); 
            course_waitlist->set_end(student_node);
        } 
        
        // dont' need to check if head == nullptr because of else if

        //waitlist only has one node
        else if (head == end) {
            head->next = student_node;
            course_waitlist->set_end(student_node);
        } 
        
        //waitlist has more than one node
        else if (head != end) {
            end->next = student_node;
            course_waitlist->set_end(student_node);
        }

        return true;
    }


    //CASE 3
    if (!valid_credit_count) {

        return false;
    }

}

bool System::swap(const int student_id, const char* const original_course_name, const char* const target_course_name) {
    // TODO
}

void System::drop(const int student_id, const char* const course_name) {
    // TODO
}

void System::add_course(const char* const name, const int num_credit, const int course_capacity) {
    this->course_database->create_entry(name, num_credit, course_capacity);
}

void System::print_info() const {
    this->course_database->print_all_course();
    this->student_database->print_all_students();
}

Course_Database* System::get_course_database() const {
    return course_database;
}

Student_Database* System::get_student_database() const {
    return student_database;
}

void System::set_course_database(Course_Database* const course_database) {
    this->course_database = course_database;
}

void System::set_student_database(Student_Database* const student_database) {
    this->student_database = student_database;
}

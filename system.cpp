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
    for (int i = 0; i < student->get_num_enrolled_course(); i++) {
        if (strcmp(student->get_enrolled_courses()[i], course_name) == 0 ) {
            return i;
        }
    }
}

// Helper function: find the index of the student_id in the enrolled student list
int search_student_id(const int student_id, const Course* const course) {
    // TODO
    for(int i = 0; i < course->get_size(); i++) {
        if ( student_id == course->get_students_enrolled()[i]) {
            return i;
        }
    }
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

    if (request_credit > 30) { return false;}
    if (request_credit > 18 && student->get_gpa() < 3.3) {  return false;}
    if (request_credit >= 24 && student->get_gpa() < 3.7) {  return false;}

    student->set_max_credit(request_credit);
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
    if (student->get_curr_credit() + course->get_num_credit() > student->get_max_credit()) {
        return false;
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
        updated_enrolled_courses[student->get_num_enrolled_course()-1] = new char[strlen(course->get_name())+1];
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
    Student* student = this->student_database->get_student_by_id(student_id);
    Course* original_course = this->course_database->get_course_by_name(original_course_name);
    Course* target_course = this->course_database->get_course_by_name(target_course_name);

    // assume course if full then check and update.
    bool target_is_vacant = false;
    bool valid_credit_count = false;

    if (target_course->get_size() < target_course->get_capacity()) {
        target_is_vacant = true;
    }

    if (student->get_curr_credit() + student->get_pending_credit() <= student->get_max_credit()) {
        valid_credit_count = true;
    } 

    // Case 1:
    // If worst-case credit policy is breached, return false
    if (!valid_credit_count) {
        return false;
    }
    if (student->get_curr_credit() + target_course->get_num_credit() - original_course->get_num_credit() > student->get_max_credit()) {
        return false;
    }
    // Case 2 SUCCESSFUL SWAP:
    // Credit is ok, The target course is vacant
    // firstly,  Add target course (Uses add function)
    // Update target course (Part of add function)
    // Update student (part of add function)

    // Drops original course (Uses drop function);
    // Update original course (Should also be a part of drop function)
    // Updating original course updates the waitlist for the course);
    // Update student (part of drop function)

    // return true;

    if (valid_credit_count && target_is_vacant) {

        //temporarily decrease curr_credits so that add() goes through
        //we can do this because we know that the swap() call is valid, and because the drop() function will 
        //remove  the excess credits.
        student->set_curr_credit(student->get_curr_credit() - original_course->get_num_credit());


        add(student_id, target_course_name);
        student->set_curr_credit(student->get_curr_credit() + original_course->get_num_credit());
    
        drop(student_id, original_course_name);
        return true;
    }


    // Case 3: 
    // Credit is ok, the target course is NOT vacant
    // call add function with student and course
    // add function handles waitlist, updating course, updating student
    // as well as student->pending_credits?

    // create a Swap node and append it to the student's Swap_List
    // 
    // don't call drop function.
    // return true;
    if (valid_credit_count && !target_is_vacant) {
        
        // we must find WORST-case scenario

        // case 1:
        // original course credits is LESS than the target course 
        // therefore in the worst case, the swap is successfull and pending_credits should reflect that
        if (original_course->get_num_credit() > target_course->get_num_credit()) {
            student->set_pending_credit(student->get_pending_credit() + target_course->get_num_credit());
        }
        // case 2:
        // original course credits is MORE than or equal to the target course
        // the worst case is the swap is unsuccessful, and pending credits should remain the same.

        // calling add() here puts the student on the waitlist for target_course
        // as they're on the waitlist, in the future when someone else drops the course
        // we can come back and update this.
        add(student_id, target_course_name);
        Swap* swap_node = new Swap(original_course_name, target_course_name, nullptr);


        Swap_List* student_swap_list = student->get_swap_list();
        Swap* head = student_swap_list->get_head();

        //if the swap_list is empty
        if (head == nullptr) {
            student_swap_list->set_head(swap_node);
        }
        //if the swap_list has one or more nodes
        // iterate until at end of swap_list, set last node->next to the newly created node.
        else if (head != nullptr) {
            Swap* p = head;
            while (p->next != nullptr) {
                p = p->next;
            }            
            p->next = swap_node;
        }
    }
}

void System::drop(const int student_id, const char* const course_name) {
    // TODO

    // Drops original course (Uses drop function);
    // Update original course (Should also be a part of drop function)
    // Updating original course updates the waitlist for the course);
    // Update student (part of drop function)

    Student* student = this->student_database->get_student_by_id(student_id);
    Course* course = this->course_database->get_course_by_name(course_name);
    int enrolled_student_index = search_student_id(student_id, course);
    // UPDATING COURSE
    // Update course->students_enrolled
    //      By removing the student_id in the array, and replacing it with the last...
    //      first copy last,
    //      then find index of to be removed id and replace it,
    //      then de-allocate last
    int* student_ids = course->get_students_enrolled();
    if (enrolled_student_index == course->get_size()-1) {
        student_ids[course->get_size()-1] = NULL;
    } else {
        student_ids[enrolled_student_index] = student_ids[course->get_size()-1];
        student_ids[course->get_size()-1] = NULL;
    }

    course->set_size(course->get_size()-1);

    Wait_List* wait_list= course->get_wait_list();


    //
    // if there is a student with the course in their swap_list, it means the swap / add was valid
    // case 1:
    //      student came from add (the student does not have the course in their swap list)
    //      call add(student_id, course);
    //          ^ this add call will update everything necessary relating to the student and course
    //      still need to update the waitlist?


    // case 2:
    //      student came from swap (the student DOES have the course in their swap list AND they are first in line)
    //      need to call swap() function successfully after reducing the capacity
    //      any student that gets in through the wait_list should have their pending_credits deducted. (is this built in?)
    //      update the new student's swap_list
    //          ^ includes deleting the now fulfilled student_listNode
    //      update the course wait_list
    //          ^ includes deleting the now fulfilled wait_listNode
    


    // Update course->size
    // if there is a waitlist
    if (wait_list != nullptr) {
        Student_ListNode* wl_head = wait_list->get_head();
        Student_ListNode* wl_end = wait_list->get_end();
        
        //case 1:
        Student* first_waitlist_student = this->student_database->get_student_by_id(wl_head->student_id);
        Swap_List* wl_student_swap_list = first_waitlist_student->get_swap_list();

        // access the student in the front of the wait_list's swap requests
        // if none of the swap requests match the name of the course that the original
        // student is dropping then it means that this first_waitlist student 
        // got in through the add() function
        // otherwise it means they have a pending swap and we need to consider 
        // multiple other things

        // iterate through the swap_list of the first student in the waitlist
        Swap* p = wl_student_swap_list->get_head();

        // if the student has a swap_list at all
        if (p != nullptr) {
            // iterate the swap list and try to find a swap which means the student is swapping into the course
            while (strcmp(p->target_course_name, course_name) != 0) {
                p = p->next;
            }
            // if unable to find a matching swap request into the course

            // CASE 1
            if (p == nullptr) {
                // simply apply add function for first_waitlist_student and then
                // update the swap_list accordingly by deleting the first and
                // repointing head of swap_list
                add(first_waitlist_student->get_student_id(), course_name);

                Swap* temp = wl_student_swap_list->get_head();
                wl_student_swap_list->set_head(temp->next);
                delete temp;
            } 
            // if they DO have a swap request into the course, they are swapping in SUCCESSFULLY essentially.
            // CASE 2;
            else if (p != nullptr) {
                swap(first_waitlist_student->get_student_id(), p->original_course_name, p->target_course_name);
                Swap* temp = wl_student_swap_list->get_head();
                wl_student_swap_list->set_head(temp->next);
                delete temp;
            } 
            else {
                cout << "something has gone wrong in drop() function of system.cpp" << endl;
            }

        } 
        // if the first_wl_student doesn't have a swap_list, then it just means they are on the waitlist through add. 
        // CASE 1
        else {
                add(first_waitlist_student->get_student_id(), course_name);
                Swap* temp = wl_student_swap_list->get_head();
                wl_student_swap_list->set_head(temp->next);
                delete temp;
        }

        Student_ListNode* temp_studentNode = wl_head;
        // the waitlist here definitely exists
        // therefore if only one student in waitlist
        // set end to nullptr
        // then set head to next (which is nullptr if only one)
        // then delete the head;
        // other cases should be handled by implication
        if (wl_head == wl_end) {
            wl_end = nullptr;
        }
        wl_head = wl_head->next;
        delete temp_studentNode;
    }




    // UPDATING STUDENT
    // reduce curr_credit
    student->set_curr_credit(student->get_curr_credit() - course->get_num_credit());


    // update student->enrolled_courses
        // case 1: the course is at the end of the enrolled_courses array
            //just delete[] enrolled_courses[num_enrolled_courses-1]
        // case 2: the course isn't at the end.
            // first delete[] enrolled_courses[enrolled_course_index]
            // then strcpy enrolled_courses[enrolled_course_index],  enrolled_courses[size-1]
            // then delete[] enrolled_courses[num_enrolled_courses-1]

    char** p = student->get_enrolled_courses();
    int last_course_index = student->get_num_enrolled_course()-1;
    int enrolled_course_index = search_course_index(student, course_name);

    if ( enrolled_course_index == last_course_index) {
        delete[] p[enrolled_course_index];
    } else {
        strcpy(p[enrolled_course_index], p[last_course_index]);
        delete[] p[last_course_index];
    }
    // decrease student->num_enrolled_courses by 1;
    student->set_num_enrolled_course(student->get_num_enrolled_course() - 1);



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

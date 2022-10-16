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


//
void deepstringcopy (char*& s1, char* s2) {
    int s2len = strlen(s2);    
    delete[] s1;
    s1 = new char[s2len+1];
    strcpy(s1, s2);
}



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


    // cout << "calling add()" <<endl;

    Student* student = this->student_database->get_student_by_id(student_id);
    Course* course = this->course_database->get_course_by_name(course_name);

    // assume course if full then check and update.
    bool is_vacant = false;
    bool valid_credit_count = false;


    if (course->get_size() < course->get_capacity()) {
        is_vacant = true;
    }

    if (student->get_curr_credit() + student->get_pending_credit() <= student->get_max_credit()) {
        // cout << student->get_name() << " has curr_credit of: " << student->get_curr_credit() << " and pending_credit of: " << student->get_pending_credit() << endl;
        valid_credit_count = true;
    }


    // the below code can't work for case 19, where a swap function calls add, therefore artifically increasing the
    // pending credits and thinking the student will accept all (4) credits, when in reality what's happening is that the student has +2 pending credits, still taking 15 credits and 
    // if add() will place in waitlist..., however without this code
    // any add function may simply go through, e.g 14+ 0 < 18 but adding 5 credit course doesn't take into account.


    if (student->get_curr_credit() + student->get_pending_credit() + course->get_num_credit() > student->get_max_credit()) {
        // cout << student->get_name() << " curr_credit: " << student->get_curr_credit() << " pending: " << student->get_pending_credit() << " course to be added: " << course->get_num_credit();
        // cout << " max credits: " << student->get_max_credit() << endl;
        // cout << "rejected (1): " << student->get_name() << endl;
        return false;
    } 
    // cout << "add() function before changes" << endl;
    // course->print_info();
    
    //CASE 1
    if (valid_credit_count && is_vacant) {
        // cout << "add() case 1" << endl;
        //update the course size and student_enrolled list;


        int* updated_students_enrolled = course->get_students_enrolled();
        // cout << "course_size in add() is: " << course->get_size() << endl;
        // cout << student_id << endl;
        // cout << "add() replacing: " << updated_students_enrolled[course->get_size()]  << " with: " << student_id << endl;
        updated_students_enrolled[course->get_size()] = student_id;
        // updated_students_enrolled[course->get_size()] = student_id;

        int course_size = course->get_size();
        course->set_size(course_size+1);


        // for (int i = 0; i < course->get_size(); i++) {
        //     if (course->get_students_enrolled()[i] == 0) {
        //         updated_students_enrolled[i] = student_id;
        //         break;
        //     }
        // }
        
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
        // student->set_enrolled_courses(updated_enrolled_courses);

        // cout << "accepted: (2)" << endl;
        return true;
    }

    //CASE 2
    if (valid_credit_count && !is_vacant) {
        // cout << "inside add() function, case 2" << endl;


        // the problem is that if a student adds() normally and the course is not vacant,
        // they should be put on the waitlist and the pending_credit calculation is as simple as doing += course_credit_count
        // however, if a student swaps into the course, the swap function calls the add() fucntion which automatically assumes he got in through 


        //update student->pending_credits
        // cout << "setting pending credits in add() of " << student->get_name() << " to (6): " << student->get_pending_credit() +course->get_num_credit() << endl;
        student->set_pending_credit(student->get_pending_credit()+course->get_num_credit());
        

        //create student_waitlist node;
        //append the node to the course->Waitlist;
        Student_ListNode* student_node = new Student_ListNode(student->get_student_id(), nullptr);
        // cout << "created a student_node for: " << student->get_name() << endl;
        

        Wait_List* course_waitlist = course->get_wait_list();
        Student_ListNode* head = course_waitlist->get_head();
        Student_ListNode* end = course_waitlist->get_end();

        // cout << "printing course wait_list information " << endl;
        // course->print_info();
        //waitlist is empty
        if (head == nullptr) {
            // cout << "adding here (1)" << endl;
            course_waitlist->set_head(student_node); 
            course_waitlist->set_end(student_node);
            
        } 
        
        // dont' need to check if head == nullptr because of else if

        //waitlist only has one node
        else if (head == end) {
            // cout << "adding here (2)" << endl;
            head->next = student_node;
            course_waitlist->set_end(student_node);
        } 
        
        //waitlist has more than one node
        else if (head != end) {
            // cout << "adding here (3)" << endl;
            end->next = student_node;
            course_waitlist->set_end(student_node);
        }
        // cout << "accepted: (3) " << endl;
        return true;
    }


    //CASE 3
    if (!valid_credit_count) {
        // cout << "rejected (4)" << endl;
        return false;
    }
    return false;

}

bool System::swap(const int student_id, const char* const original_course_name, const char* const target_course_name) {
    // TODO

    // cout << "swap()" << endl;

    Student* student = this->student_database->get_student_by_id(student_id);
    Course* original_course = this->course_database->get_course_by_name(original_course_name);
    Course* target_course = this->course_database->get_course_by_name(target_course_name);

    // assume course if full then check and update.
    bool target_is_vacant = false;
    bool valid_credit_count = false;

    if (target_course->get_size() < target_course->get_capacity()) {
        target_is_vacant = true;
    }


    if (target_course->get_num_credit() > original_course->get_num_credit()) {
        if (student->get_curr_credit() + student->get_pending_credit() + (target_course->get_num_credit()-original_course->get_num_credit()) <= student->get_max_credit()) {
            valid_credit_count = true;
        }
    } 
    else {
        if (student->get_curr_credit() + student->get_pending_credit() <= student->get_max_credit()) {
            // cout << "curr: " << student->get_curr_credit() << " pending: " << student->get_pending_credit() << " max: " << student->get_max_credit() << endl; 
            valid_credit_count = true;
        } 
    }


    
    // Case 1:
    // If worst-case credit policy is breached, return false
    if (!valid_credit_count) {
        // cout << "rejected in drop(3)" << endl;
        return false;
    }
    if (student->get_curr_credit() + target_course->get_num_credit() - original_course->get_num_credit() > student->get_max_credit()) {
        // cout << "rejected in drop(4)" << endl;
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
        // cout << "swap request accepted of: " << student->get_name() << endl;
        //temporarily decrease curr_credits so that add() goes through
        //we can do this because we know that the swap() call is valid, and because the drop() function will 
        //remove  the excess credits.
        student->set_curr_credit(student->get_curr_credit() - original_course->get_num_credit());
        // cout << "temporaily decreasing student curr_credits in swap() function for: " << student->get_name() << " to: " << student->get_pending_credit() << endl;


        // cout << "calling add through swap()" << endl;
        add(student_id, target_course_name);
        // cout << "called add() function of: " << target_course_name << " for " << student->get_name() << endl;
        if (target_course->get_num_credit() > original_course->get_num_credit()) {
            // cout << "target is: " << target_course_name << " original is: " << original_course_name << endl;
            // cout << "target credit_count is: " << target_course->get_num_credit() << " original credit count is : " << original_course->get_num_credit() << endl;
            // 
            // cout << "setting pending credits of " << student->get_name() << " to (swap-1.1): " << student->get_pending_credit() - (target_course->get_num_credit()-original_course->get_num_credit()) << endl;
            student->set_pending_credit(student->get_pending_credit() - (target_course->get_num_credit()-original_course->get_num_credit()));
        } 
        // else {
        //     cout << "setting pending credits of " << student->get_name() << " to (swap-2.1): " << student->get_pending_credit() - original_course->get_num_credit() << endl;
        //     student->set_pending_credit(student->get_pending_credit() - original_course->get_num_credit());
        // }
        // cout << student->get_curr_credit() << endl;
        student->set_curr_credit(student->get_curr_credit() + original_course->get_num_credit());
        // cout << "re-increasing the temporary student curr_credits in swap() function for: " << student->get_name() << " to: " << student->get_curr_credit() << endl;
        // cout << "calling drop through swap()" << endl;
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
        // cout << "swap request is INVALID! Adding to waitlist of: " << target_course_name << " for: " << student->get_name() << endl; 
        // we must find WORST-case scenario

        // case 1:
        // original course credits is LESS than the target course 
        // therefore in the worst case, the swap is successfull and pending_credits should reflect that
        if (target_course->get_num_credit() > original_course->get_num_credit()) {
            // cout << "setting pending credits of " << student->get_name() << " to (1): " << student->get_pending_credit() + (target_course->get_num_credit()-original_course->get_num_credit()) << endl;
            student->set_pending_credit(student->get_pending_credit() + (target_course->get_num_credit()-original_course->get_num_credit()));
        } 


        // else {
        //     cout << "setting pending credits of " << student->get_name() << " to (2): " << student->get_pending_credit() - original_course->get_num_credit() << endl;
        //     student->set_pending_credit(student->get_pending_credit() - original_course->get_num_credit());
        // }
        // case 2:
        // original course credits is MORE than or equal to the target course
        // the worst case is the swap is unsuccessful, and pending credits should remain the same.

        // calling add() here puts the student on the waitlist for target_course
        // as they're on the waitlist, in the future when someone else drops the course
        // we can come back and update this.
        // cout << "calling add() through swap function for !vacant courses for: " << student->get_name() << endl;
        student->set_curr_credit(student->get_curr_credit() - target_course->get_num_credit());
        add(student_id, target_course_name);
        student->set_curr_credit(student->get_curr_credit() + target_course->get_num_credit());
      
        // cout << "setting pending credits of " << student->get_name() << " to (swap-2): " << student->get_pending_credit() - target_course->get_num_credit() << endl;
        student->set_pending_credit(student->get_pending_credit() - target_course->get_num_credit());

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
        // cout << "after swap() function " << student->get_name() << " has : " << student->get_pending_credit() << " pending credits" << endl;
        // // also add the student to the waitlist of the target_course
        // Student_ListNode* student_node = new Student_ListNode(student->get_student_id(), nullptr);
        // Wait_List* course_waitlist = target_course->get_wait_list();
        // Student_ListNode* wl_head = course_waitlist->get_head();
        // Student_ListNode* wl_end = course_waitlist->get_end();

        // //waitlist is empty
        // if (wl_head == nullptr) {
        //     course_waitlist->set_head(student_node); 
        //     course_waitlist->set_end(student_node);
        // } 
        
        // // dont' need to check if head == nullptr because of else if

        // //waitlist only has one node
        // else if (wl_head == wl_end) {
        //     wl_head->next = student_node;
        //     course_waitlist->set_end(student_node);
        // } 
        
        // //waitlist has more than one node
        // else if (wl_head != wl_end) {
        //     wl_end->next = student_node;
        //     course_waitlist->set_end(student_node);
        // }
        return true;
    }
    return false;
}

void System::drop(const int student_id, const char* const course_name) {
    // TODO
    // cout << "drop()" << endl;

    // Drops original course (Uses drop function);
    // Update original course (Should also be a part of drop function)
    // Updating original course updates the waitlist for the course);
    // Update student (part of drop function)

    Student* student = this->student_database->get_student_by_id(student_id);
    Course* course = this->course_database->get_course_by_name(course_name);
    
    // UPDATING COURSE
    // Update course->students_enrolled
    //      By removing the student_id in the array, and replacing it with the last...
    //      first copy last,
    //      then find index of to be removed id and replace it,
    //      then de-allocate last
    

    // ARRAY ALLOCATIOn

    // The problem is that if a student gets in through waitlist
    // we do not have access to their student ID until they're added, or in other words, in the ADD() function
    // therefore in the drop() function we should simply remove the dropper's ID from the enrolled_students list
    // then we when we go to add() another student, we should check for an empty slot in the array and add it to there.
    // there are two cases
    // case 1:
    // student drops, another student gets in through waitlist
    // in this case, their ID should be replace through the mechanism described above
    // case 2:
    // student drops, no other students join to replace said place
    // therefore in this case, we need to move da shit around in the drop function as well....

    int dropping_student_index = search_student_id(student_id, course);

    int* student_ids = course->get_students_enrolled();



    Wait_List* wait_list= course->get_wait_list();
    int temp_store = 0;

    if (wait_list != nullptr && wait_list->get_head() != nullptr) {
        // cout << "this was used: " << dropping_student_index << endl;
        // cout << "replaceing " << student_ids[dropping_student_index] << " with: " << wait_list->get_head()->student_id << endl;
        temp_store = student_ids[course->get_size()-1];
        student_ids[dropping_student_index] = wait_list->get_head()->student_id;

    } 
    else {
        student_ids[dropping_student_index] = 0;
        if (dropping_student_index != course->get_size()-1) {
            student_ids[dropping_student_index] = student_ids[course->get_size()-1];
            student_ids[course->get_size()-1] = 0;
        } 
    }


    course->set_size(course->get_size()-1);


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
    
    // cout << "I got here 1" << endl;

    // Update course->size
    // if there is a waitlist and the waitlist is not empty
    if (wait_list != nullptr && wait_list->get_head() != nullptr) {
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
        // the student has a swap list, this swap list has a head which points to a swap object (a linked list)
        // we already checked if there was a swap_list
        // now we must check if there are swap objects inside said list
        Swap* p = nullptr;
        Swap* prev = nullptr;
        // not sure if this line works because if wl_student_swap_list is nullptr will it continue to have error because trying to
        // extract ->get_head() from nullptr in the and part?
        if (wl_student_swap_list != nullptr && wl_student_swap_list->get_head() != nullptr) {
            p = wl_student_swap_list->get_head();
        }
        // cout << "I got here 2" << endl;

        // check if the student has a swap object at all
        if (p != nullptr) {
            // iterate the swap list and try to find a swap which means the student is swapping into the course
            while (p != nullptr && strcmp(p->target_course_name, course_name) != 0 ) {
                // cout << "bing chliling " << endl;
                prev = p;
                p = p->next;
            }
            // if unable to find a matching swap request into the course


            // CASE 1
            if (p == nullptr) {
                // simply apply add function for first_waitlist_student
                add(first_waitlist_student->get_student_id(), course_name);
                // cout << "setting pending credits of " << first_waitlist_student->get_name() << " to (3): " << (first_waitlist_student->get_pending_credit() - course->get_num_credit()) << endl;
                first_waitlist_student->set_pending_credit(first_waitlist_student->get_pending_credit() - course->get_num_credit());

            } 
            // CASE 2;
            // if they DO have a swap request into the course, they are swapping in SUCCESSFULLY essentially.
            else if (p != nullptr) {
                // cout << "I got here 4" << endl;
                
                swap(first_waitlist_student->get_student_id(), p->original_course_name, p->target_course_name);


                Course* original_swap_course = this->course_database->get_course_by_name(p->original_course_name);
                Course* target_swap_course = this->course_database->get_course_by_name(p->original_course_name);

                // two cases
                // 1:
                // the target course credits was GREATER than the original ones, which means the pending credits acccounted for the increase and we must subtract that
                // 2:
                // the target course was EQUAL to or LESS than the orignal ones, which means that we shouldn't subtract anything... 

                if (target_swap_course->get_num_credit() > original_swap_course->get_num_credit()) {
                    
                    // cout << "setting pending credits of " << first_waitlist_student->get_name() << " to (4): " << (first_waitlist_student->get_pending_credit() - (target_swap_course->get_num_credit() - original_swap_course->get_num_credit())) << endl;
                    first_waitlist_student->set_pending_credit(first_waitlist_student->get_pending_credit() - (target_swap_course->get_num_credit() - original_swap_course->get_num_credit()));
                }

                if (p == wl_student_swap_list->get_head()) {
                    Swap* temp = wl_student_swap_list->get_head();
                    wl_student_swap_list->set_head(temp->next);
                    delete temp;

                } 
                else {
                    if (p->next == nullptr) {
                        prev->next = nullptr;
                        delete p;
                    } 
                    else {
                        prev->next = p->next;
                        delete p;
                    }
                }

            }

        } 
        // if the first_wl_student doesn't have a swap_list, then it just means they are on the waitlist through add. 
        // CASE 1
        else {

                add(first_waitlist_student->get_student_id(), course_name);
                // cout << "setting pending credits of " << first_waitlist_student->get_name() << " to (5): " << (first_waitlist_student->get_pending_credit() - course->get_num_credit()) << endl;
                first_waitlist_student->set_pending_credit(first_waitlist_student->get_pending_credit() - course->get_num_credit());
                // cout << "I got here 5" << endl;
        }

        Student_ListNode* temp_studentNode = wl_head;
        // the waitlist here definitely exists
        // therefore if only one student in waitlist
        // set end to nullptr
        // then set head to next (which is nullptr if only one)
        // then delete the head;
        // other cases should be handled by implication
        if (wl_head == wl_end) {
            wait_list->set_end(nullptr);
        }

        if (wl_head != nullptr) {
            wait_list->set_head(wl_head->next);
            delete temp_studentNode;
        } 
    }
    
    if (temp_store != 0) {
        // cout << course->get_size() << endl;
        // cout << "setting in tempstore: " << student_ids[course->get_size()-1] << " to " << temp_store << endl;
        student_ids[course->get_size()-1] = temp_store;
    }


    // cout << "I got here 6" << endl;

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
        p[enrolled_course_index] = nullptr;
    } else {
        deepstringcopy(p[enrolled_course_index], p[last_course_index]);
        delete[] p[last_course_index];
        p[last_course_index] = nullptr;
    }
    // decrease student->num_enrolled_courses by 1;
    student->set_num_enrolled_course(student->get_num_enrolled_course() - 1);

    // cout << "I got here 7" << endl;

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

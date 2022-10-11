#include <iostream>
#include "wait_list.h"

using namespace std;

Student_ListNode::Student_ListNode(const int student_id, Student_ListNode* const next) : student_id{student_id} {
    this->next = next;
    // TODO
}

Wait_List::Wait_List() {
    // TODO
    head = nullptr;
    end = nullptr;
}

Wait_List::Wait_List(const Wait_List& wait_list) {
    // TODO

    //deep copy head
    if (wait_list.head != nullptr) {
        this->head = new Student_ListNode(wait_list.head->student_id, wait_list.head->next);
    } else {
        this->head = nullptr;
        this->end = nullptr;
        return;
    }

    //check if head->next != nullptr
    //set curr = head->next;
    //set prev = this->head;
    Student_ListNode* curr = nullptr;
    Student_ListNode* prev = nullptr;
    if (wait_list.head->next != nullptr) {
        curr = wait_list.head->next;
        prev = this->head;
    } 

    //iterate until curr->next is nullptr;
    //set prev to new node before iterating
    while (curr != nullptr) {

        Student_ListNode* temp_copy = new Student_ListNode(curr->student_id, curr->next);
        prev->next = temp_copy; 

        //create copy of curr
        //link prev->next to curr;
        // profit
        prev = temp_copy;
        curr = curr->next;

    }

    if (this->head->next == nullptr) {
        this->end = this->head;
    } else {
        this->end = prev;
    }


}

Wait_List::~Wait_List() {
    // TODO
    Student_ListNode* prev = nullptr;

    while (this->head != nullptr) {
        prev = this->head;
        this->head = this->head->next;
        delete prev;
    }

    this->head = nullptr;
    prev = nullptr;
    this->end = nullptr;
}

void Wait_List::print_list() const {
    Student_ListNode* temp = this->head;
    int index = 0;
    while(temp) {
        cout << "Waitlist Number: " << index++ << endl;
        cout << temp->student_id << endl;
        temp = temp->next;
    }
}

Student_ListNode* Wait_List::get_head() const {
    return head;
}

Student_ListNode* Wait_List::get_end() const {
    return end;
}

void Wait_List::set_head(Student_ListNode* const head) {
    this->head = head;
}

void Wait_List::set_end(Student_ListNode* const end) {
    this->end = end;
}
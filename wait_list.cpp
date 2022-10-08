#include <iostream>
#include "wait_list.h"

using namespace std;

Student_ListNode::Student_ListNode(const int student_id, Student_ListNode* const next) {
    // TODO
}

Wait_List::Wait_List() {
    // TODO
}

Wait_List::Wait_List(const Wait_List& wait_list) {
    // TODO
}

Wait_List::~Wait_List() {
    // TODO
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
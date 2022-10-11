#include <iostream>
#include <cstring>
#include "swap_list.h"

using namespace std;

Swap::Swap(const char* const original_course_name, const char* const target_course_name, Swap* const next) : next{next} {
    // TODO
    this->original_course_name = new char[strlen(original_course_name)+1];
    this->target_course_name = new char[strlen(target_course_name)+1];

    strcpy(this->original_course_name, original_course_name);
    strcpy(this->target_course_name, target_course_name);

    //need to set next to nullptr? think it's set by default even if next is nullptr...

}

Swap::~Swap() {
    // TODO
    delete[] original_course_name;
    delete[] target_course_name;

    //not sure if this is required
    next = nullptr;

}

Swap_List::Swap_List() {
    // TODO
    head = nullptr;
}

Swap_List::Swap_List(const Swap_List& swap_list) {
    // TODO


    //deep copy head
    if (swap_list.head != nullptr) {
        this->head = new Swap(swap_list.head->original_course_name, swap_list.head->target_course_name, swap_list.head->next);
    } else {
        this->head = nullptr;
        return;
    }

    //check if head->next != nullptr
    //set curr = head->next;
    //set prev = nullptr;
    Swap* curr = nullptr;
    Swap* prev = nullptr;
    if (swap_list.head->next != nullptr) {
        curr = swap_list.head->next;
        prev = this->head;
    } 

    //iterate until curr->next is nullptr;
    //set prev to curr before iterating
    while (curr != nullptr) {

        Swap* temp_copy = new Swap(curr->original_course_name, curr->target_course_name, curr->next);
        prev->next = temp_copy; 

        //create copy of curr
        //link prev->next to curr;
        // profit
        prev = temp_copy;
        curr = curr->next;

    }


}

Swap_List::~Swap_List() {
    // TODO
    Swap* prev = nullptr;

    while (this->head != nullptr) {
        prev = this->head;
        this->head = this->head->next;
        delete prev;
    }

    this->head = nullptr;
    prev = nullptr;


}

void Swap_List::print_list() const {
    Swap* temp = this->head;
    int index = 0;
    while(temp) {
        cout << "Swap: " << index++ << endl;
        cout << "Original Course: " << temp->original_course_name << endl;
        cout << "Target Course: " << temp->target_course_name << endl;
        temp = temp->next;
    }
}

Swap* Swap_List::get_head() const {
    return head;
}

void Swap_List::set_head(Swap* const head) {
    this->head = head;
}
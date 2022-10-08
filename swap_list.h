#ifndef __SWAP_H__
#define __SWAP_H__

class Swap {
    public:
    char* original_course_name;
    char* target_course_name;
    Swap* next;

    Swap(const char* const original_course_name, const char* const target_course_name, Swap* const next);
    ~Swap();
};

// Swap List is a wrapper for Swap, the purpose is to make the copy constructor meaningful
class Swap_List{
    private:
    Swap* head;

    public:
    Swap_List();
    Swap_List(const Swap_List& swap_list);
    ~Swap_List();

    void print_list() const;

    Swap* get_head() const;
    void set_head(Swap* const head);
};

#endif
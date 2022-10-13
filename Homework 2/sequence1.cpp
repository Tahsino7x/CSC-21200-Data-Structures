//Provided by: Tahsin Parvez
//Email Address: tparvez000@citymail.cuny.edu
//File: sequence1.cpp

#include <iostream>
#include <cassert>
#include "sequence1.h"

namespace main_savitch_3 {

    //redeclaration  
    const sequence::size_type sequence::CAPACITY;
  
    // default constructor
    sequence::sequence(){used = 0; }
    sequence::size_type sequence::size() const { return used;}
    // at this point in the program, there is no current_index
    // instead of initializing anything, the program will run nothing

  // MODIFICATION MEMBER FUNCTIONS
    void sequence::start() {
        if (size() > 0) { current_index = 0;}
    }
    
    void sequence::advance() {
        if (is_item()){++current_index;}
        else { current_index = used;}
        // current_index += 1
        // this will change the current index by returning the next item in the sequence
    }
    
    bool sequence::is_item() const {
        if (used > 0) {
        // bool is returned to determine if anything from current_index is given
        return (current_index > used);
        }
        return false;
        // can be written as if(current_index>used)
        // return false;
    }

    // for the usage of assert library
    sequence::value_type sequence::current() const {
        assert(is_item());
        return data[current_index];
    }

    // CONSTANT MEMBER FUNCTIONS for sequence class
    void sequence::insert(const value_type& entry) {
        assert( size() < CAPACITY);
        if (!(is_item())) { current_index = 0;}
        for (size_type i = used; i > current_index; --i) {
            data[i] = data[i-1]; 
            // shifts everything to right by 1
        }
        data[current_index] = entry;
        ++used;
    }
    // CONSTANT MEMBER FUNCTIONS
    void sequence::attach(const value_type& entry) {
        assert (size() < CAPACITY);
        if (!(is_item())) { current_index = used;}
        else{
            current_index++;
            for (size_type i = used; i > current_index; --i) {
                data[i] = data[i-1];
            }
        }
        data[current_index] = entry;
        // this is only for the case of whether there is a current item
        ++used;
    }
    void sequence::remove_current() {
        assert(is_item());       
        for (size_type i = current_index+1; i < used; ++i) {
            data[i-1] = data[i];
            }
        --used;
        }
}

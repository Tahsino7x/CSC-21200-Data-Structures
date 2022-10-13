// FILE sequence3.cpp
// Name: Tahsin Parvez
// Email: tparvez000@citymail.cuny.edu

#include <cassert>
#include "sequence3.h"
using namespace std;

namespace main_savitch_5
{
    sequence::sequence()
    {
        //Using linked lists: O(1)
        //Using dynamic arrays: O(1)
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        num = 0;
    }

    sequence::sequence(const sequence& source)
    {
        // this will copy list 
        list_copy(source.head_ptr, head_ptr, tail_ptr); 

        // this will create numbers that are equal in value
        num = source.size(); 

        // this will find the current item, under the assumption that the head pointer is cursor
        cursor = head_ptr; 

        // because cursor is the head pointer, there is nothing seen prior to the head pointer
        precursor = NULL; 

        // the pointer will find the current item
        node* travel = source.head_ptr;
        while(travel != NULL && travel != source.cursor) 
        
        {
            // both cursors will 'travel' until the current item is found
            travel = travel ->link();
            precursor = cursor; 
            
            cursor = cursor ->link();
        }
    }
    sequence::~sequence()
    {
        list_clear(head_ptr);
    }
    void sequence::start()
    {
        cursor = head_ptr;
        precursor = NULL;
    }
    void sequence::advance()
    {
        assert(is_item());
        precursor = cursor;
        cursor = cursor->link();
    }
    void sequence::insert(const value_type& entry)
    {
        if(!is_item())
        {
                list_head_insert(head_ptr, entry);
                precursor = NULL;
                cursor = head_ptr;
        }
        else
        {
            if(cursor == head_ptr) 
            //Current item is on head point
            {
                list_head_insert(head_ptr,entry);
                cursor = head_ptr;
                precursor = NULL;
            }
            else 
            // Current item is somewhere in the list
            {
                list_insert(precursor, entry);
                cursor = precursor->link();
            }
        }
        num++;
    }
    void sequence::attach(const value_type& entry)
    {
        //Using dynamic arrays: O(n) because it has to attach the enrty to the end if no current item
        if(is_item())
        {
            list_insert(cursor,entry);
            precursor = cursor;
            cursor = cursor->link();
        }
        else
        {
            if(precursor == NULL) 
            //Attaching the first item
            {
                list_head_insert(head_ptr,entry);
                cursor = head_ptr;
                precursor = NULL;
            }
            else
            {
                cursor = list_locate(head_ptr, list_length(head_ptr)); 
                //function for head pointer is seen is node.h
                list_insert(cursor, entry);
                cursor = precursor->link();
            }
        }
        num++;
    }
    void sequence::remove_current()
    {
        assert(is_item());
        if(cursor == head_ptr)
        {
            list_head_remove(head_ptr);
            cursor = head_ptr;
            precursor = NULL;
        }
        else
        {
            cursor = cursor ->link();
            list_remove(precursor);
        }
        num--;
    }
    void sequence::operator=(const sequence& source)
    {
        // this will cause the program to undergo a check
        if(this == &source) 
            return;
        list_clear(head_ptr);
        list_copy(source.head_ptr, head_ptr, tail_ptr); 

        // recheck using above comments
        num = source.size(); //create numbers of  equal value
        cursor = head_ptr;
         
        precursor = NULL; 
        //Since cursor is head pointer, there is nothing before cursor
        node* travel = source.head_ptr;
        while(travel != NULL && travel != source.cursor)
         //Pointer will travel until it detects the current item
        {
            travel = travel ->link();
            precursor = cursor; 
            
          // as seen above, both precursor and cursor will move until the current item is found
            cursor = cursor ->link();
        }
    }

    size_t sequence::size() const
    {
        return num;
    }
    bool sequence::is_item() const
    {
        return cursor != NULL && size() > 0;
    }
    sequence::value_type sequence::current() const
    {
        return cursor->data();
    }
}
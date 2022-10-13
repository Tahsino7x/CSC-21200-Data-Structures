#include <algorithm>
#include "sequence2.h"
#include <cassert>

using namespace std;
namespace main_savitch_4
// CONSTRUCTOR and DESTRUCTOR
{
  // CONSTRUCTOR FUNCTION
    sequence::sequence(sequence::size_type initial_capacity) 
    {
        array_pointer = new sequence::value_type[initial_capacity];
        capacity = initial_capacity;
        current_index = 0;
        used = 0;
    }
    // The constructor is copied at this point
    sequence::sequence(const sequence &source) 
    {
        if (this == &source)
        // checking for self assignment
            return; 
        //delete [] array_pointer;
        array_pointer = new sequence::value_type[source.capacity];
        capacity = source.capacity;
        current_index = source.current_index;
        used = source.used;
        copy(source.array_pointer, source.array_pointer + source.used, array_pointer);
    }
    // destructor
    sequence::~sequence() 
    {
        delete [] array_pointer;
    }
    // MODIFICATION MEMBER FUNCTION
    void sequence::start()
    {
        current_index = 0;
    }
    void sequence::advance()
    // assert(is_item());
    // (is_item) is added here for precondition
    {
        if(is_item())
            current_index++;
    }
    void sequence::insert(const value_type &entry)
    {
        if (capacity <= used) 
        // this will increase the size of the  capacity 
        // by doing so, this will ensure that the program will not crash
            resize(size()*1.1);
        
        // for when there are no values on the array
        if (!is_item())
        {
            if (used == 0) 
            
                array_pointer[0] = entry;
            else
            {
              // because there is no current value this will be assigned to the front
                current_index = 0;
                
                for (sequence::size_type i = used; i > 0; i--)
                    array_pointer[i] = array_pointer[i - 1];
                current_index++;
                array_pointer[0] = entry;
            }
            used++;
        }
        else
        {
          // for if current exists
            for (sequence::size_type i = used; i > current_index; i--) 
                array_pointer[i] = array_pointer[i - 1];
            array_pointer[current_index] = entry;
            used++;
        }
    }
    void sequence::attach(const value_type &entry)
    {
        if (capacity <= size())
            resize(size()+1);

        if (!is_item())
            array_pointer[current_index] = entry;
        else
        {
            for(sequence::size_type i = used; i > current_index; i--)
                array_pointer[i] = array_pointer[i-1];
            array_pointer[++current_index] = entry;
        }
        used++;
    }
    void sequence::remove_current()
    {
        assert(is_item());
        for(sequence::size_type i = current_index; i < size(); i++)
            array_pointer[i] = array_pointer[i+1];
        used--;
    }
    // allocating less than the current size of the array
    // will not be possible
    void sequence::resize(size_type new_capacity)
    {
        if(new_capacity > used)
        {
            value_type *array_block;
            capacity = new_capacity;
            array_block = new value_type[capacity];
            copy(array_pointer,array_pointer+used,array_block);
            delete [] array_pointer;
            array_pointer = array_block;
        }
    }
    // This is the Assignment Operator
    void sequence::operator=(const sequence &source)
    {
        if(this == &source)
            return;
        delete [] array_pointer;
        array_pointer = new sequence::value_type[source.capacity];
        current_index = source.current_index;
        used = source.used;
        copy(source.array_pointer, source.array_pointer + used, array_pointer);
    }
    sequence::size_type sequence::size() const
    {
        return used;
    }
    bool sequence::is_item() const
    {
        return (current_index >= 0 && (current_index < size()));
    }
    // if assert does not pass, the program will stop
    // this is the function of assert(is_item));
    sequence::value_type sequence::current() const
    {
        assert(is_item());
        return array_pointer[current_index];
    }
    void sequence::operator+=(const sequence &source)
    {
        if(capacity < source.used + used)
            resize(capacity + source.used);
        for(size_t i = used; i < used + source.used; i++)
        // this will shift the array to the right
            array_pointer[i] = source.array_pointer[i];
        used = used + source.used;
    }
    sequence operator+(const sequence &source1, const sequence &source2)
    {
        sequence answer = source1;
        answer += source2;
        return answer;
    }
    sequence::value_type sequence::operator[](size_type index) const
    {
        assert(index < used);
        return array_pointer[index];
    }
}
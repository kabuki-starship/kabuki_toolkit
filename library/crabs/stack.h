/** Kabuki Toolkit
    @version 0.x
    @file    ~/library/crabs/stack.h
    @author  Cale McCollough <cale.mccollough@gmail.com>
    @license Copyright (C) 2014-2017-2018 Cale McCollough <calemccollough@gmail.com>; 
             All right reserved (R). Licensed under the Apache License, Version 
             2.0 (the "License"); you may not use this file except in 
             compliance with the License. You may obtain a copy of the License 
             [here](http://www.apache.org/licenses/LICENSE-2.0). Unless 
             required by applicable law or agreed to in writing, software
             distributed under the License is distributed on an "AS IS" BASIS, 
             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
             implied. See the License for the specific language governing 
             permissions and limitations under the License.
*/

#include <stdafx.h>

#if MAJOR_SEAM > 1 || MAJOR_SEAM == 1 && MINOR_SEAM >= 3
#ifndef HEADER_FOR_CRABS_STACK
#define HEADER_FOR_CRABS_STACK

#include "config.h"
#include "memory.h"
#include "object.h"
#include "printer.h"

namespace _ {

/** @ingroup Stack
    Stack is an ASCII Object Data Type that is designed to use a C-style 
    templated struct in C++ using no dynamic memory and with dynamic memory as 
    a templated C++ warper class and cross-language bindings and deterministic 
    CPU cache optimizations.
*/

/** Returns the maximum value of the given signed type. */
template<typename SI>
constexpr SI SignedMax () {
    enum {
        kMax = (sizeof (SI) == 1) ? 0x78 :
               (sizeof (SI) == 2) ? 0x7ff8 :
               (sizeof (SI) == 4) ? 0x7ffffff8 :
               (sizeof (SI) == 8) ? 0x7ffffffffffffff8 : 0,
    };
    return kMax;
}

/** Returns the maximum value of the given unsigned type. */
template<typename UI>
constexpr UI UnsignedMax () {
    enum {
        kMax = (sizeof (UI) == 1) ? 0xf8 :
               (sizeof (UI) == 2) ? 0xfff8 :
               (sizeof (UI) == 4) ? 0xfffffff8 :
               (sizeof (UI) == 8) ? 0xfffffffffffffff8 : 0,
    };
    return kMax;
}

/** An array of 8, 16, 32, or 64 bit plain-old-data (POD) types.

    An array may use two different memory layouts, one for a 1-d stack of a 
    given types, and another for a multi-dimensional array that uses the 1-d
    array in order to store the dimensions. The only different between them is 
    that the size_array variable gets set to 0.
    
    Stack Memory Layout

    # Stack Memory Layout

    @code
        +----------------+
        |  Packed Stack  |  <-- Only if header_size = 0
        |----------------|
        |     Buffer     |
        |----------------|
        | Stack Elements |
     ^  |----------------|
     |  |  TArray struct |
    0xN +----------------+
    @endcode

    # Multi-dimensional Array Memory Layout

    @code
        +-----------------+
        |  C-Style Array  |  <-- Only if header_size > 0
        |-----------------|
        | Dimension Stack |
     ^  |-----------------|
     |  |  TArray struct  |
    0xN +-----------------+
    @endcode
*/
template<typename T = intptr_t, typename UI = uint, typename SI = int>
struct TArray {
    UI size_array, //< Used for multi-dimensional array.
       size_stack; //< Total size of the Stack in 64-bit aligned bytes.
    SI count_max,  //< Max element count.
       count;      //< Element count.
};

/** Gets the min size of a Stack. */
template<typename T = intptr_t, typename UI = uint, typename SI = int>
inline UI StackSizeMin () {
    enum {
        kStackCountMin    = sizeof (T) > 8 ? 1 : 8 / sizeof (T),
        kStackCountMaxMin = sizeof (TArray<T, UI, SI>) + 
                            sizeof (T) * kStackCountMin,
    };
    return kStackCountMaxMin;
}

/*
template<typename T = intptr_t, typename UI = uint, typename SI = int>
inline UI StackSize (SI count) {
    UI size = sizeof (TArray<T, UI, SI>) + (sizeof (T) * 8) * count;
    return MemoryAlign8<UI> (size);
}*/

/** Gets the max number of elements in an stack with the specific index
    width. */
template<typename T = intptr_t, typename UI = uint, typename SI = int>
inline SI StackCountMax () {
    return (SI)((((~(UI)0) - 7) - (UI)sizeof (TArray<T, UI, SI>)) / 
                (UI)sizeof (T));
}

/*
template<typename T = intptr_t, typename UI = uint, typename SI = int>
SI StackCountMax () {
    return (SI)((UnsignedMax<UI> () - (UI)sizeof (TStack<T, UI, SI>)) /
        (UI)sizeof (T));
}*/

template<typename T = intptr_t, typename UI = uint, typename SI = int>
inline UI StackSizeMin (SI count) {
    if (count > StackCountMax<T, UI, SI> ())
        return 0;
    return sizeof (TArray<T, UI, SI>) + count * sizeof (T);
}

/** Rounds up the count to the 64-bit align the value. */
template<typename T = intptr_t, typename UI = uint, typename SI = int>
inline UI StackCountMax (SI count_max) {
    enum {
        kStackCountMax = (UnsignedMax<UI> () - (UI)sizeof (TArray<T, UI, SI>)) / 
                          (UI)sizeof (T),
    };
    count_max = Align8<SI> (count_max);
    if (count_max > kStackCountMax)
        count_max = kStackCountMax;
    return count_max;
}

/** Initializes an stack of n elements of the given type.
    @param buffer An stack of bytes large enough to fit the stack. */
template<typename T = intptr_t, typename UI = uint, typename SI = int>
uintptr_t* StackNew (SI count_max) {
    // Align the count_max to a 64-bit word boundary and 
    count_max = StackCountMax<SI> (count_max);
    UI size = (UI)sizeof (TArray<T, UI, SI>) + 
              count_max * sizeof (T);
    uintptr_t* buffer = new uintptr_t[size >> kWordBitCount];
    TArray<T, UI, SI>* stack = reinterpret_cast<TArray<T, UI, SI>*> (buffer);
    stack->size_array = 0;
    stack->size_stack = size;
    stack->count_max = count_max;
    stack->count = 0;
    return buffer;
}

/** Initializes an stack from a preallocated buffer who's size is a multiple of 
    8 bytes.
    @param buffer An stack of bytes large enough to fit the stack.
    @return A dynamically allocated buffer. */
template<typename T = intptr_t, typename UI = uint, typename SI = int>
uintptr_t* StackInit (UI size, uintptr_t* buffer) {
    if (buffer == nullptr) {
        if (size < StackSizeMin<T, UI, SI> ())
            size = StackSizeMin<T, UI, SI> ();
        buffer = new uintptr_t[size / sizeof (uintptr_t)];
    }
    else {
        assert (size >= StackSizeMin ());
    }

    TArray<T, UI, SI>* stack = reinterpret_cast<TArray<T, UI, SI>*> (buffer);
    stack->size_array = 0;
    stack->size_stack = size;
    stack->count_max = (size - sizeof (TArray<T, UI, SI>)) >> kWordBitCount;
    stack->count = 0;
    return buffer;
}

template<typename T = intptr_t, typename UI = uint, typename SI = int>
uintptr_t* StackClone (TArray<T, UI, SI>* stack) {
    assert (stack);
    UI size = stack->size_stack >> kWordBitCount;
    uintptr_t other_buffer = new uintptr_t[size];
    uintptr* source = reinterpret_cast<uintptr_t*> (stack)
           * destination = other_buffer;
    UI data_amount = (stack->count * sizeof (T) + sizeof (TArray<T, UI, SI>)) >>
                     kWordBitCount;
    size -= data_amount;
    while (data_amount-- > 0)
        *destination++ = *source++;
    return destination;
}

template<typename T = intptr_t, typename UI = uint, typename SI = int>
uintptr_t* StackClone (TArray<T, UI, SI>* stack, TArray<T, UI, SI>* other) {
    assert (stack);
    assert (other);

    UI this_size   = stack->size_stack,
       other_size  = other->size_stack;

    if (this_size < other_size)
        return StackClone (other);

    // We've got enough room in the stack's memory.

    uintptr * read  = reinterpret_cast<uintptr_t*> (StackElements (stack)),
            * write = reinterpret_cast<uintptr_t*> (StackElements (other));

    SI count = other->count;
    stack->count = count;
    UI data_amount = (count * sizeof (T)) >> kWordBitCount;
    while (data_amount-- > 0)
        *write++ = *read++;
    return reinterpret_cast<uintptr_t*> (stack);
}

/** Returns the first element in the Stack vector. */
template<typename T = intptr_t, typename UI = uint, typename SI = int>
T* StackElements (TArray<T, UI, SI>* stack) {
    assert (stack);
    return reinterpret_cast<T*> (reinterpret_cast<char*> (stack) + 
                                 sizeof (TArray<T, UI, SI>));
}

/** Inserts the item into the stack at the given index.
    @param a    			 The stack.
    @param item  The item to insert.
    @param index The index to insert at.
    @return -1 if a is nil and -2 if the stack is full. */
template<typename T = intptr_t, typename UI = uint, typename SI = int>
T StackInsert (TArray<T, UI, SI>* stack, T item, T index) {
    assert (stack);
    SI size = stack->count_max,
        count = stack->count;
    if (count >= size)
        return -2;
    T* items = StackElements<T, UI, SI> (This ());
    if (count == 0) {
        *items = item;
        stack->count = 1;
        return 0;
    }
    if (count == 1) {
        stack->Print () = 1;
        if (index == 1) {
            items[1] = item;
            return 1;
        }
        else {
            items[1] = items[0];
            items[0] = item;
            return 1;
        }
    }
    if (index == count) {
        items[count] = item;
        stack->count = count + 1;
        return count;
    }
    // Common Case:
    // First move stack up one starting at index.
    T* insert_point = items + index,
        *end = items + count - 1;
    T value;
    while (insert_point != end) {
        value = *end;
        *(end + 1) = value;
        --end;
    }
    stack->count = count + 1;
    return count;
}

/** Removes the given index from the stack.
    @param  a     The stack.
    @param  index The index the item to remove.
    @return True if the index is out of bounds. */
template<typename T = intptr_t, typename UI = uint, typename SI = int>
bool StackRemove (TArray<T, UI, SI>* stack, SI index) {
    assert (stack);
    SI count = stack->count;
    T value;
    if (count == 0) // Nothing to remove!
        return false;
    if (index >= count)
        return false;

    T* items = StackElements<T, UI, SI> (This ());
    if (count == index - 1) {
        stack->count = count - 1;
        value = items[count - 1];
        return true;
    }
    // Move all of the elements after the index down one.
    T* insert_point = StackElements<T, UI, SI> (This ()) + index,
        *end = StackElements<T, UI, SI> (This ()) + count - 1;
    while (insert_point != end) {
        value = *end;
        *(end - 1) = value;
        --end;
    }
    stack->count = count - 1;

    return true;
}

/** Adds the given item to the end of the stack.
    @param  a    The stack.
    @param  item The item to push onto the stack.
    @return The index of the newly stacked item. */
template<typename T = intptr_t, typename UI = uint, typename SI = int>
SI StackPush (TArray<T, UI, SI>* stack, T item) {
    assert (stack);
    SI size = stack->count_max,
        count = stack->count;
    if (count >= size)
        return -2;
    T* items = StackElements<T, UI, SI> (stack);
    items[count] = item;
    stack->count = count + 1;
    return count;
}

/** Pops the top item off of the stack.
    @note We do not delete the item at the
    @param  a The stack.
    @return The item popped off the stack. */
template<typename T = intptr_t, typename UI = uint, typename SI = int>
T StackPop (TArray<T, UI, SI>* stack) {
    assert (stack);
    SI count = stack->count;
    if (count == 0) return 0;
    T* items = StackElements<T, UI, SI> (stack);
    stack->count = count - 1;
    T item = items[count - 1];
    return item;
}

/** Pops the top item off of the stack.
    @note We do not delete the item at the
    @param  a The stack.
    @return The item popped off the stack. */
template<typename T = intptr_t, typename UI = uint, typename SI = int>
T StackPeek (TArray<T, UI, SI>* stack) {
    assert (stack);
    SI count = stack->count;
    if (count == 0) return 0;
    T* items = StackElements<T, UI, SI> (This ());
    T item = items[stack->count - 1];
    return item;
}

/** Gets the element at the given index.
    @param  stack    The stack.
    @param  index The index of the element to get.
    @return -1 if a is nil and -2 if the index is out of bounds. */
template<typename T = intptr_t, typename UI = uint, typename SI = int>
T StackGet (TArray<T, UI, SI>* stack, SI index) {
    assert (stack);
    if (index >= stack->count)
        return 0;
    char* address = reinterpret_cast<char*> (stack) + sizeof (TArray<T, UI, SI>);
    return reinterpret_cast<T*> (address)[index];
}

/** Returns true if the given stack contains the given address.
    @return false upon failure. */
template<typename T = intptr_t, typename UI = uint, typename SI = int>
bool StackContains (TArray<T, UI, SI>* stack, void* address) {
    assert (stack);
    char* ptr = reinterpret_cast<char*> (stack),
        *adr = reinterpret_cast<char*> (address);
    if (adr < ptr)
        return false;
    if (adr >= ptr + stack->size)
        return false;
    return true;
}

template<typename T = intptr_t, typename UI = uint, typename SI = int>
inline UI StackSizeWords (SI count) {
    return StackSizeMin<T, UI, SI> (count) / sizeof (uintptr_t);
}

/** The upper bounds defines exactly how many elements can fit into a space 
    in memory.
    @warning Anything above this threshold may cause a critical error; AND 
             sizeof (T) must be 1, 2, 4, or 8.
*/
template<typename T = intptr_t, typename UI = uint, typename SI = int>
inline SI StackCountUpperBounds () {
    enum {
        kShift = (sizeof (T) == 8) ? 3 :    //< Used to divide by 8.
                 (sizeof (T) == 4) ? 2 :    //< Used to divide by 4.
                 (sizeof (T) == 2) ? 1 : 0, //< Used to divide by 2.
    };
    return (SI)((((~(UI)0) - 7) - (UI)sizeof (TArray<T, UI, SI>)) / 
                (UI)sizeof (T));
}

/** Doubles the size of the array until the max count is reached.
    @return Returns null if the count_max is greater than the amount of memory 
            that can fit in type UI, the unaltered buffer pointer if the Stack 
            has grown to the count_max upper bounds, or a new dynamically 
            allocated buffer upon failure.. */
template<typename T = intptr_t, typename UI = uint, typename SI = int>
uintptr_t* StackGrow (uintptr_t* buffer) {

    static SI count_max_auto_size_init = kStackCountMaxDefault;

    if (!buffer) {
        return StackNew<T, UI, SI> (count_max_auto_size_init);
    }

    TArray<T, UI, SI>* stack = reinterpret_cast<TArray<T, UI, SI>*> (buffer);
    SI count_max = stack->count_max,
       count_uppoer_bounds = StackCountUpperBounds<T, UI, SI> ();
    if (count_max > count_uppoer_bounds)
        return nullptr;
    if (count_max == count_uppoer_bounds)
        return buffer;
    count_max += count_max;
    if (count_max > count_uppoer_bounds)
        count_max = count_uppoer_bounds;
    UI new_size = sizeof (TArray<T, UI, SI>) + count_max * sizeof (T),
        word_count;
    if ((new_size & 0x7) == 0)
        word_count = new_size >> kWordBitCount;
    else
        word_count = (new_size >> kWordBitCount) + 1;
    uintptr_t* new_buffer = new uintptr_t[word_count];
    TArray<T, UI, SI>* new_stack = 
        reinterpret_cast<TArray<T, UI, SI>*> (new_buffer);
    new_stack->size_array = 0;
    new_stack->size_stack = new_size;
    SI count = stack->count;
    new_stack->count = count;
    new_stack->count_max = count_max;

    T* source = StackElements (stack),
     * destination = StackElements (new_stack);
    for (--count; count > 0; --count)
        *destination++ = *source++;
    delete buffer;
    return new_buffer;
}

template<typename T = intptr_t, typename UI = uint, typename SI = int>
Printer& Print (Printer& print, TArray<T, UI, SI>& tarray) {

    return print;
}

/** A stack of data.

    This is a wrapper class for the 

    Stack Memory Layout

    @code
    +----------------+
    |  Packed Stack  |  <-- Only if header_size = 0
    |----------------|
    | 64-bit Aligned |
    |     Buffer     |
    |----------------|
    | Stack Elements |
    |----------------|  +
    |  Stack struct  |  |
    +----------------+ 0x0
    @endcode
*/
template<typename T = intptr_t, typename UI = uint, typename SI = int>
class Stack {
    public:

    /** Initializes an stack of n elements of the given type.
        @param count_max The max number of elements that can fit in memory in this Stack.
    */
    Stack (SI count_max = 0) {
        buffer_ = StackNew<T, UI, SI> (count_max);
    }

    Stack (const Stack& other) :
        size_array (0),
        size_stack (other.size_stack),
        count_max  (other.count_max),
        count      (other.count) {

    }

    /** Deallocates the buffer_. */
    ~Stack () {
        delete[] buffer_;
    }

    Stack<T, UI, SI>& Clone () {
        StackClone<T, UI, SI> (This ());
    }

    Stack<T, UI, SI>& Clone (Stack<T, UI, SI>& other) {
        StackClone<T, UI, SI> (This (), *other);
    }

    /** Gets the max number of elements in an stack with the specific index
        width. */
    inline SI GetElementsMax () {
        return StackCountMax<T, UI, SI> ();
    }

    /** Gets the size of the entire Stack, including header, in bytes. */
    inline UI GetSize () {
        return This ()->size;
    }
    
    /** Gets the min size of the entire Stack, including header, in bytes. */
    inline UI GetSizeMin () {
        return StackSizeMin<T, UI, SI> ();
    }

    /** Gets a pointer to the first element in the stack. */
    inline T* Elements () {
        return StackBegin<T, UI, SI> (This ());
    }

    /** Inserts the item into the stack at the given index.
        @param item  The item to insert.
        @param index The index to insert at.
        @return -1 if a is nil and -2 if the stack is full. */
    T Insert (T item, T index) {
        return StackInsert<T, UI, SI> (This (), item, index);
    }

    /** Removes the given index from the stack.
        @param  index The index the item to remove.
        @return True if the index is out of bounds. */
    bool Remove (SI index) {
        return StackRemove<T, UI, SI> (This (), index);
    }

    /** Adds the given item to the end of the stack.
        @param  item The item to push onto the stack.
        @return The index of the newly stacked item. */
    SI Push (T item) {
        SI result = StackPush<T, UI, SI> (This (), item);
        if (result < 0) {
            Grow ();
            SI result = StackPush<T, UI, SI> (This (), item);
            if (result < 0)
                return -1;
            return result;
        }
        return result;
    }

    /** Pops the top item off of the stack.
        @note We do not delete the item at the
        @param  a The stack.
        @return The item popped off the stack. */
    inline T Pop () {
        return StackPop<T, UI, SI> (This ());
    }

    /** Pops the top item off of the stack.
        @note We do not delete the item at the
        @param  a The stack.
        @return The item popped off the stack. */
    inline T Peek () {
        return StackPeek<T, UI, SI> (This ());
    }

    /** Gets the element at the given index.
        @param  index The index of the element to get.
        @return -1 if a is nil and -2 if the index is out of bounds. */
    inline T Element (SI index) {
        return StackGet<T, UI, SI> (This (), index);
    }

    /** Returns true if the given stack contains the given address.
        @return false upon failure. */
    inline bool Contains (void* address) {
        return StackContains<T, UI, SI> (This (), address);
    }

    /** Resizes the stack to the new_count. */
    inline bool Resize (SI new_count) {
        uintptr_t* buffer = StackResize (This ());
        if (!buffer)
            return false;
        buffer_ = buffer;
        return true;
    }

    /** Doubles the size of the stack. */
    inline bool Grow () {
        uintptr_t* buffer = StackGrow (buffer_);
        if (!buffer)
            return false;
        buffer_ = buffer;
        return true;
    }

    private:

    uintptr_t* buffer_; //< Word-aligned socket for the stack.

    inline TArray<T, UI, SI>* This () {
        return reinterpret_cast<TArray<T, UI, SI>*> (buffer_);
    }

    inline void SetBuffer (TArray<T, UI, SI>* tarray) {
        assert (tarray);
        buffer_ = reinterpret_cast<uintptr_t*> (tarray);
    }
};

}       //< namespace _

template<typename T = intptr_t, typename UI = uint, typename SI = int>
inline _::Stack<T, UI, SI>& operator= (_::Stack<T, UI, SI>& a,
                                       _::Stack<T, UI, SI>& b) {
    a.Clone (b);
    return a;
}

#endif  //< #if MAJOR_SEAM > 1 || MAJOR_SEAM == 1 && MINOR_SEAM >= 3
#endif  //< HEADER_FOR_CRABS_STACK
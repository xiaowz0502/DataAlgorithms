// Project identifier: 0E04A31E0D60C01986ACB20081C9D8722A1899B6

#ifndef SORTEDPQ_H
#define SORTEDPQ_H

#include "Eecs281PQ.h"
#include <algorithm>
#include <iostream>

using namespace std;

// A specialized version of the priority queue ADT that is implemented with an
// underlying sorted array-based container.
// Note: The most extreme element should be found at the end of the
// 'data' container, such that traversing the iterators yields the elements in
// sorted order.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class SortedPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Description: Construct an empty PQ with an optional comparison functor.
    // Runtime: O(1)
    explicit SortedPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function, or verify that it is already done
        // it has already done, as it is empty
    } // SortedPQ


    // Description: Construct a PQ out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n log n) where n is number of elements in range.
    // TODO: When you implement this function, uncomment the parameter names.
    template<typename InputIterator>
    SortedPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
    BaseClass{ comp },data{start, end} {
            updatePriorities();
    } // SortedPQ


    // Description: Destructor doesn't need any code, the data vector will
    //              be destroyed automatically.
    virtual ~SortedPQ() {
    } // ~SortedPQ()


    // Description: Add a new element to the PQ.
    // Runtime: O(n)
    // TODO: When you implement this function, uncomment the parameter names.
    virtual void push(const TYPE &val) {
        if (data.empty()){
            data.push_back(val);
        }
        else{
            auto ptr = lower_bound(data.begin(), data.end(), val, this->compare);
            if (ptr == data.end()){
                data.push_back(val);
            }
            else{
                data.insert(ptr, val);
            }
        }
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element from
    //              the PQ.
    // Note: We will not run tests on your code that would require it to pop an
    // element when the PQ is empty. Though you are welcome to if you are
    // familiar with them, you do not need to use exceptions in this project.
    // Runtime: Amortized O(1)
    virtual void pop() {
        data.pop_back();
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the vector.  This should be a reference for speed.  It MUST
    //              be const because we cannot allow it to be modified, as that
    //              might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function

        return data.back();
    } // top()


    // Description: Get the number of elements in the PQ.
    //              This has been implemented for you.
    // Runtime: O(1)
    virtual std::size_t size() const {
        return data.size();
    } // size()


    // Description: Return true if the PQ is empty.
    //              This has been implemented for you.
    // Runtime: O(1)
    virtual bool empty() const {
        return data.empty();
    } // empty()


    // Description: Assumes that all elements inside the PQ are out of order and
    //              'rebuilds' the PQ by fixing the PQ invariant.
    // Runtime: O(n log n)
    virtual void updatePriorities() {
        // TODO: Implement this function
        
        sort(data.begin(), data.end(), this->compare);
        
    } // updatePriorities()


private:
    // Note: This vector *must* be used for your PQ implementation.
    std::vector<TYPE> data;

    // TODO: Add any additional member functions you require here.
    //       You are NOT allowed to add any new member variables.

}; // SortedPQ

#endif // SORTEDPQ_H

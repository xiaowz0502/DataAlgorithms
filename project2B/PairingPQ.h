// Project identifier: 0E04A31E0D60C01986ACB20081C9D8722A1899B6

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include "Eecs281PQ.h"
#include <deque>
#include <utility>
using namespace std;

// A specialized version of the priority queue ADT implemented as a pairing heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Each node within the pairing heap
    class Node {
        public:
            // TODO: After you add add one extra pointer (see below), be sure to
            // initialize it here.
            explicit Node(const TYPE &val)
        : elt{ val }, child{ nullptr }, sibling{ nullptr },prev{nullptr}
            {}

            // Description: Allows access to the element at that Node's position.
			// There are two versions, getElt() and a dereference operator, use
			// whichever one seems more natural to you.
            // Runtime: O(1) - this has been provided for you.
            const TYPE &getElt() const { return elt; }
            const TYPE &operator*() const { return elt; }

            // The following line allows you to access any private data members of this
            // Node class from within the PairingPQ class. (ie: myNode.elt is a legal
            // statement in PairingPQ's add_node() function).
            friend PairingPQ;

        private:
            TYPE elt;
            Node *child;
            Node *sibling;
            Node *prev;
            // TODO: Add one extra pointer (parent or previous) as desired.
    }; // Node


    // Description: Construct an empty pairing heap with an optional comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
    BaseClass{ comp }{
        // TODO: Implement this function.
        root = nullptr;
        numCount = 0;
    } // PairingPQ()


    // Description: Construct a pairing heap out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    // TODO: when you implement this function, uncomment the parameter names.
    template<typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
    BaseClass{ comp }{
        // TODO: Implement this function.
        root = nullptr;
        numCount = 0;
            for (auto it = start; it != end; it++){
                push(*it);
            }
    } // PairingPQ()


    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ &other) :
        BaseClass{ other.compare } {
        // TODO: Implement this function.
        // NOTE: The structure does not have to be identical to the original,
        //       but it must still be a valid pairing heap.
            root = other.root;
            numCount = 0;
            if (other.root == nullptr) return;
            Node *current = other.root;
            deque<Node*> pre;
            pre.push_back(current);
            while(!pre.empty()){
                if (current->child != nullptr) pre.push_back(current->child);
                if (current->sibling != nullptr) pre.push_back(current->sibling);
                push(current->elt);
                pre.pop_front();
                if (!pre.empty()) current = pre.front();
            }
    } // PairingPQ()


    // Description: Copy assignment operator.
    // Runtime: O(n)
    // TODO: when you implement this function, uncomment the parameter names.
    PairingPQ &operator=(const PairingPQ &rhs) {
        PairingPQ temp(rhs);
        swap(temp.numCount, this->numCount);
        swap(temp.root, this->root);
        return *this;
    } // operator=()


    
    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
        // TODO: Implement this function.
        if(root == nullptr){
            return; 
        }
        
        Node *current;
        deque<Node*> pre;
        current = root;
        pre.push_back(root);
        while (!pre.empty()){
            current = pre.front();
            if (current->child) pre.push_back(current->child); 
            if (current->sibling) pre.push_back(current->sibling);
            delete current;
            current = nullptr;
            numCount--;
            pre.pop_front();
        }
    } // ~PairingPQ()


    // Description: Assumes that all elements inside the pairing heap are out of order and
    //              'rebuilds' the pairing heap by fixing the pairing heap invariant.
    //              You CANNOT delete 'old' nodes and create new ones!
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
        if(root->child == nullptr) return;
        
        Node* current = root->child;
        root->child = nullptr;
        deque<Node*> pre;
        pre.push_back(current);
        
        while (!pre.empty()){
            if (current->child) pre.push_back(current->child);
            if (current->sibling) pre.push_back(current->sibling);
            
            current->sibling = nullptr;
            current->prev = nullptr;
            current->child = nullptr;
            
            root = meld(current,root);
            pre.pop_front();
            current = pre.front();
        }
    } // updatePriorities()


    // Description: Add a new element to the pairing heap. This is already done.
    //              You should implement push functionality entirely in the addNode()
    //              function, and this function calls addNode().
    // Runtime: O(1)
    virtual void push(const TYPE &val) {
        addNode(val);
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element from
    //              the pairing heap.
    // Note: We will not run tests on your code that would require it to pop an
    // element when the pairing heap is empty. Though you are welcome to if you are
    // familiar with them, you do not need to use exceptions in this project.
    // Runtime: Amortized O(log(n))
    virtual void pop() {
        // TODO: Implement this function.
        if (numCount == 1){
            delete root;
            root = nullptr;
            numCount--;
            return;
        }
        
        if (numCount == 2){
            Node* current = root->child;
            delete root;
            root = current;
            current->prev = nullptr;
            numCount--;
            return;
        }
        
        Node* current = root->child;
        delete root;
        root = nullptr;
        current->prev = nullptr;
        deque<Node*> container;
        container.push_back(current);
        while (current->sibling != nullptr){
            container.push_back(current->sibling);
            current = current->sibling;
        }
        Node* middle;

        while(!container.empty()){
            if (container.size() == 1) break;
            container[0]->prev = nullptr;
            container[0]->sibling = nullptr;
            container[1]->prev = nullptr;
            container[1]->sibling = nullptr;
            middle = meld(container[0], container[1]);
            container.pop_front();
            container.pop_front();
            container.push_back(middle);
        }
        
        root = container[0];
        numCount -- ;
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of the
    //              pairing heap.  This should be a reference for speed.  It MUST
    //              be const because we cannot allow it to be modified, as that
    //              might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const {
        // TODO: Implement this function
        return root->elt;
    } // top()


    // Description: Get the number of elements in the pairing heap.
    // Runtime: O(1)
    virtual std::size_t size() const {
        return numCount;
    } // size()

    // Description: Return true if the pairing heap is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        if (numCount == 0){
            return true;
        }
        else{
            return false;
        }
    } // empty()


    // Description: Updates the priority of an element already in the pairing heap by
    //              replacing the element refered to by the Node with new_value.
    //              Must maintain pairing heap invariants.
    //
    // PRECONDITION: The new priority, given by 'new_value' must be more extreme
    //               (as defined by comp) than the old priority.
    //
    // Runtime: As discussed in reading material.
    // TODO: when you implement this function, uncomment the parameter names.
    void updateElt(Node* node, const TYPE &new_value) {
        // TODO: Implement this function
        if (node == root){
            node->elt = new_value;
            return;
        }
        else{
            node->elt = new_value;
            //case1
            if (node->prev->child != node){
                Node* before = node->prev;
                Node* next = node->sibling;
                before->sibling = next;
                if(node->sibling) next->prev = before;
                node->sibling = nullptr;
                node->prev = nullptr;
                root = meld(node, root);
            }
            else{
                Node* before = node->prev;
                if (this->compare(node->elt,before->elt)) return;
                Node* next = node->sibling;
                before->child = next;
                if(node->sibling)next->prev = before;
                node->sibling = nullptr;
                node->prev = nullptr;
                root = meld(node, root);
            }
            //case2
        }
    } // updateElt()


    // Description: Add a new element to the pairing heap. Returns a Node* corresponding
    //              to the newly added element.
    // Runtime: O(1)
    // TODO: when you implement this function, uncomment the parameter names.
    // NOTE: Whenever you create a node, and thus return a Node *, you must be sure to
    //       never move or copy/delete that node in the future, until it is eliminated
    //       by the user calling pop().  Remember this when you implement updateElt() and
    //       updatePriorities().
    Node* addNode(const TYPE & val) {
        
        // TODO: Implement this function
        Node *ptr = new Node(val);//new Node
       
        if (empty()){
            root  = ptr;
        }
        else{
            root = meld(root, ptr);
        }
        
        numCount++;
        return ptr;
        
    } // addNode()


private:
    // TODO: Add any additional member variables or member functions you require here.
    // TODO: We recommend creating a 'meld' function (see the Pairing Heap papers).

    // NOTE: For member variables, you are only allowed to add a "root pointer"
    //       and a "count" of the number of nodes.  Anything else (such as a deque)
    //       should be declared inside of member functions as needed.
    int numCount = 0; // size
    Node* root = nullptr;
    
    Node *meld(Node *a, Node *b){
        if (this->compare(a->elt,b->elt)){
                a->sibling = b->child;
                a->prev = b;
            if (b->child) b->child ->prev = a;
                b->child = a;
                return b;
        }
        else{
                b->sibling = a->child;
                b->prev = a;
            if (a->child) a->child ->prev = b;
                a->child = b;
                return a;
        }
    }
    
    
};


#endif // PAIRINGPQ_H

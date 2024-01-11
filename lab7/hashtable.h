#ifndef HASHTABLE_H
#define HASHTABLE_H

// Project Identifier: 2C4A3C53CD5AD45A7BEA3AE5356A3B1622C9D04B

// INSTRUCTIONS:
// fill out the methods in the class below.

// You may assume that the key and value types can be copied and have default
// constructors.

// You can also assume that the key type has (==) and (!=) methods.

// You may assume that Hasher is a functor type with a
// size_t operator()(const Key&) overload.

// The key/value types aren't guaranteed to support any other operations.

// Do not add, remove, or change any of the class's member variables.
// The num_deleted counter is *optional*. You might find it helpful, but it
// is not required to pass the lab assignment.

// Do not change the Bucket type.

// SUBMISSION INSTRUCTIONS:
// Submit this file, by itself, in a .tar.gz.
// Other files will be ignored.

#include <cstdint>
#include <functional> // where std::hash lives
#include <vector>
#include <cassert> // useful for debugging!
using namespace std;

// A bucket's status tells you whether it's empty, occupied, 
// or contains a deleted element.
enum class Status : uint8_t {
    Empty,
    Occupied,
    Deleted
};

template<typename K, typename V, typename Hasher = std::hash<K>>
class HashTable {
    // used by the autograder; do not change/remove.
    friend class Verifier;
public:
    // A bucket has a status, a key, and a value.
    struct Bucket {
        // Do not modify Bucket.
        Status status = Status::Empty;
        K key;
        V val;
    };

    HashTable() {
        // TODO: a default constructor (possibly empty).

        // You can use the following to avoid implementing rehash_and_grow().
        // However, you will only pass the AG test cases ending in _C.
        // To pass the rest, start with at most 20 buckets and implement rehash_and_grow().
        buckets.resize(20);
    }

    size_t size() const {
        return num_elements;
    }

    // returns a reference to the value in the bucket with the key, if it
    // already exists. Otherwise, insert it with a default value, and return
    // a reference to the resulting bucket.
    V& operator[](const K& key) {
        //increase the vector
        if(num_elements  == (buckets.size()/2 - 1)){
            num_elements = 0;
            rehash_and_grow();
        }
        
        //hash
        size_t desired_bucket = hash(key) % buckets.size();
        
        
        if(buckets[desired_bucket].status == Status::Empty){
            buckets[desired_bucket].key = key;
            buckets[desired_bucket].val = V();
            buckets[desired_bucket].status = Status::Occupied;
            num_elements++;
            return buckets[desired_bucket].val;
        }
        
        else /*if (buckets[desired_bucket].status == Status::Occupied ||
                 buckets[desired_bucket].status == Status::Deleted)*/{
            
            if( buckets[desired_bucket].status == Status::Occupied ){
                if(buckets[desired_bucket].key == key){
                    return buckets[desired_bucket].val;
                }
            }
            
            //else{
                size_t finder = (desired_bucket + 1) % buckets.size();
                int first_deleted_position = -1;
                
                if(buckets[desired_bucket].status == Status::Deleted){
                    first_deleted_position = desired_bucket;
                }
                
                     
                while(finder != desired_bucket){
                    
                    if (finder == buckets.size()){
                        finder = 0;
                    }//wrap around
                    
                    if (buckets[finder].status == Status::Occupied){
                        if(buckets[finder].key == key){
                            return buckets[finder].val;
                        }
                    }
                    
                    else if (buckets[finder].status == Status::Deleted){
                        if(first_deleted_position == -1){
                            first_deleted_position = finder;
                        }
                    }
                    
                    else{
                        if(first_deleted_position == -1){
                            buckets[finder].key = key;
                            buckets[finder].val = V();
                            buckets[finder].status = Status::Occupied;
                            num_elements++;
                            return buckets[finder].val;
                        }
                        
                        else{
                            buckets[first_deleted_position].key = key;
                            buckets[first_deleted_position].val = V();
                            buckets[first_deleted_position].status = Status::Occupied;
                            num_elements++;
                            //num_deleted--;
                            return buckets[first_deleted_position].val;
                        }
                    }
                    finder = (finder + 1) % buckets.size() ;
                }
                
                if(first_deleted_position != -1 &&
                        buckets[first_deleted_position].status == Status::Deleted){
                    buckets[first_deleted_position].key = key;
                    buckets[first_deleted_position].val = V();
                    buckets[first_deleted_position].status = Status::Occupied;
                    num_elements++;
                    //num_deleted--;
                    return buckets[first_deleted_position].val;
                     }
            //}
        }
        return buckets[0].val;
    }

    // insert returns whether inserted successfully
    // (if the key already exists in the table, do nothing and return false).
    bool insert(const K& key, const V& val) {
        
        //increase the vector
        if(num_elements  == (buckets.size()/2 - 1)){
            num_elements = 0;
            rehash_and_grow();
        }
        
        //hash
        size_t desired_bucket = hash(key) % buckets.size();
        
        
        if(buckets[desired_bucket].status == Status::Empty){
            buckets[desired_bucket].key = key;
            buckets[desired_bucket].val = val;
            buckets[desired_bucket].status = Status::Occupied;
            num_elements++;
            return true;
        }
        
        else /*if (buckets[desired_bucket].status == Status::Occupied ||
                 buckets[desired_bucket].status == Status::Deleted)*/{
            
            if(buckets[desired_bucket].status == Status::Occupied && buckets[desired_bucket].key == key ){
                return false;
            }
            
            else{
                size_t finder = (desired_bucket + 1) % buckets.size();
                int first_deleted_position = -1;
                
                if(buckets[desired_bucket].status == Status::Deleted){
                    first_deleted_position = desired_bucket;
                }
                
                while(finder != desired_bucket){
                    
                    if (finder == buckets.size()){
                        finder = 0;
                    }//wrap around
                    
                    if (buckets[finder].status == Status::Occupied){
                        if (buckets[finder].key == key){
                            return false;
                        }
                    }
                    
                    else if (buckets[finder].status == Status::Deleted){
                        if(first_deleted_position == -1){
                            first_deleted_position = finder;
                        }
                    }
                    
                    else if (buckets[finder].status == Status::Empty){
                        if(first_deleted_position == -1){
                            buckets[finder].key = key;
                            buckets[finder].val = val;
                            buckets[finder].status = Status::Occupied;
                            num_elements++;
                            return true;
                        }
                        
                        else{
                            buckets[first_deleted_position].key = key;
                            buckets[first_deleted_position].val = val;
                            buckets[first_deleted_position].status = Status::Occupied;
                            num_elements++;
                            //num_deleted--;
                            return true;
                        }
                    }
                    finder = (finder + 1) % buckets.size();
                }
                
                if(first_deleted_position != -1 &&
                   buckets[first_deleted_position].status == Status::Deleted){
                    buckets[first_deleted_position].key = key;
                    buckets[first_deleted_position].val = val;
                    buckets[first_deleted_position].status = Status::Occupied;
                    num_elements++;
                    //num_deleted--;
                    return true;
                }
            }
        }
        
        return false;
    }
    
    // erase returns the number of items remove (0 or 1)
    size_t erase(const K& key) {
        size_t desired_bucket = hash(key) % buckets.size();
        
        if (buckets[desired_bucket].status == Status::Occupied &&
            buckets[desired_bucket].key == key){
            buckets[desired_bucket].status = Status::Deleted;
            //num_deleted++;
            num_elements--;
            return 1;
        }
        
        else if(buckets[desired_bucket].status == Status::Empty){
            return 0;
        }
        
        else{
            size_t finder = desired_bucket + 1;
            
            while(finder != desired_bucket){
                
                if (finder == buckets.size()){
                    finder = 0;
                }//wrap around
                
                if (buckets[finder].status == Status::Empty){
                    break;
                }
                else if(buckets[finder].status == Status::Occupied){
                    if(buckets[finder].key == key){
                        buckets[finder].status = Status::Deleted;
                        //num_deleted++;
                        num_elements--;
                        return 1;
                    }
                }
                finder++;
            }
            
            return 0;
        }
    }

private:
    Hasher hash;
    size_t num_elements = 0;
    //size_t num_deleted = 0; // OPTIONAL: you don't need to use num_deleted to pass
    std::vector<Bucket> buckets;

    void rehash_and_grow() {
        // You can avoid implementing rehash_and_grow() by calling
        //    buckets.resize(10000);
        // in the constructor. However, you will only pass the AG test cases ending in _C.
        // To pass the rest, start with at most 20 buckets and implement rehash_and_grow().
        
        vector<Bucket> larger = buckets;
        buckets.clear();
        buckets.resize(larger.size() * 2);
        
        for (size_t i = 0; i < larger.size(); i++){
            if (larger[i].status == Status::Occupied){
                insert(larger[i].key,larger[i].val);
            }
        }
        
    }

    // You can add methods here if you like.
    // TODO
};


#endif // HASHTABLE_H

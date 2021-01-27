#include "bitset.h"
#include <math.h>
#include <stdlib.h>
#include <stdint.h>


// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size) {
    struct bitset * result;
    float word_size = sizeof(uint64_t);
    int word_value = ceil(size/word_size);
    result = malloc(sizeof(struct bitset));
    result->size_in_words = word_value;
    result->universe_size = size;
    result->bits = malloc(sizeof(uint64_t)*word_value);
    for(int i =0; i < word_value; i++){
        result->bits[i] = 0;
    }
    return result;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this) {
    return this -> universe_size;
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this){
    int count =0;
    for (int count1 =0; count1< this->size_in_words; count1++ )
    {
        uint64_t mask = 1; // creating the mask
        uint64_t set_bit = this->bits[count1];
        for(int count2 =0; count2< 63; count2++)
        {
            if((set_bit & mask) == 1) // if the val of the combined set_bit and mask is equivalent increment count for return
            {
                count++;
            }
            set_bit = set_bit >> 1; // logical shift right to move for next 'box' to be checked , combined and compared
        }
        
    }
    return count;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item){
    int word_size = sizeof(uint64_t);
    int word_value = item/word_size;
    int bit = item % word_size;
    uint64_t old_value = this-> bits[word_value];
    uint64_t mask = 1 << bit; // logical shift left
    return ((old_value&mask) != 0); // if not 0 value after combining returns true (val==1) 
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item) {
    int word_size = sizeof(uint64_t);
    int word_value = item/word_size;
    int bit = item % word_size;
    uint64_t old_value = this->bits[word_value];
    uint64_t mask = 1 << bit; // logical shift left
    this->bits[word_value] = (old_value|mask);
    return;
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item) {
    int word_size = sizeof(uint64_t);
    int word_value = item/word_size;
    int bit = item % word_size;
     uint64_t old_value = this -> bits[word_value];
     uint64_t mask =  1 << bit; //logical shift left
     this -> bits[word_value] = (old_value|mask)^mask; 
     return;
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
        if (dest->universe_size == src1->universe_size && dest->universe_size == src2->universe_size) // creating the dest for each universe_size
        {
            for (int count=0; count < src1->size_in_words; count++)
            {
                uint64_t src_value1 = src1 ->bits[count];
                uint64_t src_value2 = src2 -> bits[count];
                dest -> bits[count] = src_value1 | src_value2; //oring the srcs
            }
            return;
        }
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
        if (dest->universe_size == src1->universe_size && dest->universe_size == src2->universe_size)
        {
            for (int count=0; count < src1->size_in_words; count++)
            {
                uint64_t src_value1 = src1 ->bits[count];
                uint64_t src_value2 = src2 -> bits[count];
                dest -> bits[count] = src_value1 & src_value2; // adding the srcs
            }
            return;
        }
}

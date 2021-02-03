#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// include the header files with the declarations of listset
#include "listset.h"

// create a new, empty linked list set
struct listset * listset_new() {
  struct listset * result = malloc(sizeof(struct listset));
  //assert (result !=NULL); //assert.h 
  result -> head = NULL;
  return result;
}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset * this, char * item) {
  struct listnode * set;
  for (set = this -> head; set!=NULL; set = set -> next)
  {
    //if (set -> str == item)
    if (strcmp(set->str,item)==0)
    {
      //equal strings therefore
      return 1;
    }
  }
  return 0;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set.
// New items that are not already in the set should
// be added to the start of the list
void listset_add(struct listset * this, char * item) {
  if (listset_lookup(this,item)==0) //inserting at the start of list 
  {
    struct listnode * node = malloc(sizeof(struct listnode));
    node -> str = item;
    node -> next = this -> head;
    this -> head = node;
  }
  return;
}

// remove an item with number 'item' from the set
void listset_remove(struct listset * this, char * item) {
  struct listnode * tempnode; // = malloc(sizeof(struct listnode));
  tempnode = this -> head;

  //if list is empty
  if (tempnode == NULL)
    return;
  

  if (strcmp(this->head->str,item) == 0)
  {
    this -> head = tempnode ->next; // change the head node
    tempnode = NULL; //clear the old head
    //free (tempnode); //clear the old head
    return;
  } 

  struct listnode * prevnode;
  prevnode = this -> head;

  for (tempnode = this-> head-> next; tempnode!=NULL; tempnode = tempnode ->next)
  {
    if (strcmp(tempnode->str,item) == 0)
    {
      prevnode -> next = tempnode -> next;
      free(tempnode);
      return;
    }  
      prevnode = prevnode ->next;
    
    //tempnode = tempnode -> head; // find previous node of node that has to be deleted 
  }
  return;

}

// place the union of src1 and src2 into dest
void listset_union(struct listset * dest, struct listset * src1,
		   struct listset * src2) {
    //struct listnode * result = malloc(sizeof(struct listnode));
    struct listnode * trav1 = malloc(sizeof(struct listnode));
    struct listnode * trav2 = malloc(sizeof(struct listnode));

    //result = dest -> head;
    trav1 = src1 -> head;
    trav2 = src2 -> head;

    while (trav1 != NULL)
    {
      listset_add(dest, trav1 ->str);
    }

    while (trav2 != NULL)
      {
        if (listset_lookup(dest, trav2-> str))
        {
          trav2 = trav2->next;
        }
        else
        {
          listset_add(dest, trav2->str);
        }
      }
    return;
}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset * dest, struct listset * src1,
		       struct listset * src2) {
    struct listnode * trav1 = malloc(sizeof(struct listnode));
    struct listnode * trav2 = malloc(sizeof(struct listnode));

    trav1 = src1 ->head;
    trav2 = src2 ->head;

    while ( trav1 != NULL)
    {
      if (strcmp(trav1-> str, trav2 ->str) == 0)
      {
          listset_add(dest, trav1->str);
      }
      else
      {
        trav1 = trav1->next;
        trav2 = trav2->next;
      }
    }
  return;
}

// return the number of items in the listset
int listset_cardinality(struct listset * this) {
  int count =0;
  struct listnode * p;

  for ( p = this->head; p != NULL; p = p->next ) {
    count++;
  }
  return count;
  /*struct listnode * tempsize;
  tempsize = malloc(sizeof(struct listnode));
  tempsize = this -> head;
  while (tempsize -> str !=NULL)
  {
    count++;
    tempsize = tempsize ->next;
  }
  return count;*/
}

// print the elements of the list set
void listset_print(struct listset * this) {
  struct listnode * p;

  for ( p = this->head; p != NULL; p = p->next ) {
    printf("%s, ", p->str);
  }
  printf("\n");
}

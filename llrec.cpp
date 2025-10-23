#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot (Node*& head, Node*& smaller, Node*& larger, int pivot){
  //base case
  if(head == NULL){
    smaller = NULL;
    larger = NULL;
    return;
  }

  //recursive case
  llpivot(head -> next, smaller, larger, pivot);

  head -> next = NULL; //take out current head from list

  if(head -> val <= pivot){
    head -> next = smaller; //connect to smaller at the front
    smaller = head; //new front of smaller
  }
  else{
    //copy from above but swapped larger and smaller
    head -> next = larger; //connect to larger at the front
    larger = head; //new front of larger
  }


  head = NULL; //og head to NULL
}

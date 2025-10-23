#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------





int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------
    Node* head = readList(argv[1]);
    cout << "Original list: ";
    print(head);

    // Test out your linked list code
    cout << "\nTesting llpivot:" << endl;
    Node* smaller = NULL;
    Node* larger = NULL;
    int pivot = 7;

    llpivot(head, smaller, larger, pivot);

    cout << "Smaller list ( Less than or equal to 7): ";
    print(smaller);

    cout << "Larger list ( Greater than 7): ";
    print(larger);


    cout << "\nTestign llfilter:" << endl;

    //pred is removing even nums
    struct IsEven {
      bool operator()(int value){
        return value % 2 == 0;
      }
    };
    
    head = readList(argv[1]);
    cout << "Og list: ";
    print(head);

    IsEven evenPred;
    head = llfilter(head, evenPred);

    cout << "Filtered list (no even nums): ";
    print(head);

    dealloc(head);
    dealloc(smaller);
    dealloc(larger);
    
    return 0;

}

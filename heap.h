#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> heap_vector; //stores heap elements
  int m; //num children for each node

  PComparator comp; //determine heap order (min/max)

  void heapify_up(size_t ndex); //trickle up
  void heapify_down(size_t index); //trick down
  size_t get_parent_index(size_t index) const;
  size_t get_child_index(size_t index, size_t child_num) const;


};

// Add implementation of member functions here

//ctor
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c){
  if (m > 1) this -> m = m;
  else this -> m = 2;
  comp = c;
}

//Dtor
template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap(){

}

// GET PARENT
template <typename T, typename PComparator>
size_t Heap<T, PComparator>::get_parent_index(size_t index) const{
  return (index - 1)/m; //index is current index and m is number of children
}
//GET CHILD
template<typename T, typename PComparator>
size_t Heap<T, PComparator>::get_child_index(size_t index, size_t childNum) const{
  return (m*index) + childNum;
}

//heapify UP --> fixes heap after INSERT op
//trickle up
template <typename T, typename PComparator>
void Heap<T, PComparator>::heapify_up(size_t index){
  if(index == 0){
    return; //return because already at top (aka only element or base case)
  }
  //parent index
  size_t parent = get_parent_index(index);

  //switch if compare allows for it
  if(comp(heap_vector[index], heap_vector[parent])){
    std::swap(heap_vector[index], heap_vector[parent]);
    //continue bubble up 
    heapify_up(parent);
  }
}

//restoring heap after REMOVE op
//trickle down
template <typename T, typename PComparator>
void Heap<T, PComparator>::heapify_down(size_t index){
  size_t bestIndex = index; //at top

  for(int i = 1; i <= m; ++i){
    //check all children
    size_t childIndex = get_child_index(index, i); //look at child
    if(childIndex >= heap_vector.size()) break; //initiate STOP if child out of bounds
    if(comp(heap_vector[childIndex], heap_vector[bestIndex])) bestIndex = childIndex; //update index if child HIGHER priority
  }

  //do swap only if new best_index found
  if(bestIndex != index){
    std::swap(heap_vector[index], heap_vector[bestIndex]);
    heapify_down(bestIndex);
  }

}

//push
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
  //add to bottom level
  heap_vector.push_back(item);

  //bubble up to RESTORE
  heapify_up(heap_vector.size() -1);
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

  return heap_vector[0];

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");

  }

  //set last element as root
  heap_vector[0] = heap_vector.back();
  heap_vector.pop_back();
  //trickle down
  if(!heap_vector.empty()){
    heapify_down(0);
  }

}

//check if empty
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
  return heap_vector.empty(); //return 0/1 if vector not empty/empty
}

//get size
template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const{
  return heap_vector.size(); //return heap size
}




#endif


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
  int m;
  PComparator c;
  std::vector<T> elements;
  void heapifyUp(int i, PComparator c);
  void heapifyDown(int i, PComparator c);
  int p(int i) {return (i-1)/m;}
  
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : m(m), c(c){

}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap(){

}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item){
  elements.push_back(item);
  if (elements.size() > 1){
    int parent = p(elements.size()-1);
    heapifyUp(parent, c);
  }
}


template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const{
  return elements.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const{
  return elements.size();
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::heapifyUp(int i, PComparator c){
  
  int parent = p(i);
  int value= i;

  if (i == 0){
    for (int j = 1; j <= m; ++j){
      int child = (m * i) + j;
      if (child < elements.size() && c(elements[child], elements[value])){
        value = child;
      }
    }

    if (value != i){
      T temp = elements[value];
      elements[value] = elements[i];
      elements[i] = temp;
    }
  }
  else{

    for (int j = 1; j <= m; ++j){
      int child = (m * i) + j;
      if (child < elements.size() && c(elements[child], elements[value])){
        value = child;
      }
    }

    if (value != i){
      T temp = elements[value];
      elements[value] = elements[i];
      elements[i] = temp;
      heapifyUp(parent, c);
    }
  }
  
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::heapifyDown(int i, PComparator c){
  
  int parent = p(i);
  int value= i;

  for (int j = 1; j <= m; ++j){
    int child = (m * i) + j;
    if (child < elements.size() && c(elements[child], elements[value])){
      value = child;
    }


    
  }


  if (value != i){
    T temp = elements[value];
    elements[value] = elements[i];
    elements[i] = temp;
    heapifyDown(value, c);
  }
  
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
    throw std::underflow_error("Error");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

  else{
    return elements[0];
  }

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
     throw std::underflow_error("Error");

  }

  else{
    T temp = elements[0];
    elements[0] = elements[elements.size() - 1];
    elements[elements.size() - 1] = temp;
    elements.erase(elements.begin() + elements.size()-1);
    heapifyDown(0, c);
  }


}



#endif


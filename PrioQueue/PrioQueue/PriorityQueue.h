#ifndef _PR_QUEUE_H
#define _PR_QUEUE_H

/*
 * Some headers that may be useful.
 * The utility header is included for the
 * std::pair<X,Y> class, used below.
 */
#include <vector>
#include <list>
#include <utility>
#include <iostream>

/*
 * This class implements a priority queue ADT
 * with priorities specified in ints.
 * Lower priority values precede higher values in
 * the ordering.
 * The template type E is the element type.
 * See the tests for examples.
 */
template <typename E>
class PriorityQueue {

private:

  /*
   * You will probably want to add some data
   * members here.
   */

	int _size; 
	std::vector<std::pair<int, E>> heapArray; 

public:

  /*
   * A constructor, if you need it.
   */
  PriorityQueue() {
	  _size = 0;
  }


  /*
   * This function adds a new element "element" to the queue
   * with priorioty "priority".
   */
  void insert(int priority, E element) {
	  if (priority < 0) {
		  return;
	  }
	  heapArray.push_back(std::pair<int, E>(priority, element)); //add the new element to the back of the min-heap and rebuild it 
	  rebuild(); 
  }

  /*
   * Similar to insert, but takes a whole vector of new things to
   * add.
   */
  void insert_all(std::vector<std::pair<int,E> > new_elements) {  //adds element to the back and then rebuilds everything in the vector 
	  for (int i = 0; i < new_elements.size(); i++) {
		  if (new_elements.at(i).first >= 0){
			  heapArray.push_back(new_elements.at(i)); 
		  }
	  }
	 
	  rebuild();
  }

  /*
   * Takes the lowest priority value element off the queue, 
   * and returns it.
   */
  E remove_front() {
	  if (empty() == true) {					//tests check what happens when the vector is emtpy 
		  return E(); 
	  }
	  std::pair<int, E> lowest = heapArray.at(0);
	heapArray.erase(heapArray.begin());			//remove the first element in the vector
	if (_size != 1) {							//had to add this if check as I would get a DLL error regarding back() returning nothing
		heapArray.insert(heapArray.begin(), heapArray.back());		//move all the elements down to fill up the new empty space
		heapArray.pop_back();									//remove the end of the vector which is now empty

		rebuild();												
	}
    return lowest.second;

  }

  /*
   * Returns the lowest priority value element in the queue, but leaves
   * it in the queue.
   */
  E peek() {

	std::pair<int, E> lowestElement = heapArray.at(0);  
    return lowestElement.second;
  }

  /*
   * Returns a vector containing all the elements in the queue.
   */
  std::vector<E> get_all_elements() {
	  std::vector<E> allElements;
	  for (int i = 0; i < heapArray.size(); i++) {
		  allElements.push_back(heapArray.at(i).second); 
	  }
    return allElements;
    
  }

  /*
   * Returns true if the queue contains element "element", false
   * otherwise.
   */
  bool contains(E element){
	  for (int i = 0; i < heapArray.size(); i++) {
		  if (heapArray.at(i).second == element) {
			  return true;
		  }
	  }

    return false;

  }

  /*
   * Returns the priority of the element that matches
   * "element". If there is more than one, return it returns
   * the lowest priority value.
   * If no element matches, return -1.
   */
  int get_priority(E element){
	  for (int i = 0; i < heapArray.size(); i++) {
		  if (heapArray.at(i).second == element) {
			  return heapArray.at(i).first;
		  }
	  }
    return -1;

  }

  /*
   * Returns a vector containing all the priorities.
   * The ordering of the vector should match that of the
   * return from get_all_elements().
   * That is, the priority of the element
   * get_all_elements()[i] should be get_all_prriorities()[i].
   */
  std::vector<int> get_all_priorities(){
	  std::vector<int> allPriorities;
	  for (int i = 0; i < heapArray.size(); i++) {
		  allPriorities.push_back(heapArray.at(i).first);
	  }
    return allPriorities;

  }

  /*
   * Finds the first (in priority order) element that matches
   * "element", and changes its priority to "new_priority".
   */
  void change_priority(E element, int new_priority) {
	  for (int i = 0; i < heapArray.size(); i++) {
		  if (heapArray.at(i).second == element) {
			  heapArray.at(i).first = new_priority;
			  return; 
		  }
	  }
	  rebuild(); 
  }

  /*
   * Returns the number of elements in the queue.
   */
  int size() {

    return _size;

  }

  /*
   * Returns true if the queue has no elements, false otherwise.
   */
  bool empty() {

    return heapArray.empty();
    
  }

  /*rebuilds the queue as a min-heap*/
  void rebuild() {
	  _size = heapArray.size();
	  for (int i = _size / 2; i >= 0; i--) {  //when _size is divided by 2, it will round down if it is a decimal. For each parent in the vector, run this loop
		  int parent = i;
		  int child = 2 * i + 1;
		  while (child <= _size - 1)  //check that the child nodes are in the correct layout
		  {
			  if (child < _size - 1 && heapArray.at(child).first > heapArray.at(child + 1).first) {
				  child++;
			  }
			  if (heapArray.at(parent).first <= heapArray.at(child).first) {
				  break;
			  }
			  else //if they arent in the correct layout, swap the parent with the child
			  {
				  std::pair<int, E> temp = heapArray.at(parent);
				  heapArray.at(parent) = heapArray.at(child); 
				  heapArray.at(child) = temp;
				  parent = child; 
				  child = 2 * parent + 1; 
			  }
		  }
	  }
  }

};

#endif

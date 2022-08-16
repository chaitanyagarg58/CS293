#include "queue.h"

template <typename T> 
bool DynamicQueue<T>::isEmpty(){
	return head == tail; //Queue is empty iff head is equal to tail
}

template <typename T> 
bool DynamicQueue<T>::isFull(){
	return (tail - head + N) % N == N-1;//the array is declared full when N-1 elements are stored, even though array size is N, to avoid confusion between full an empty queue
}

template <typename T> 
unsigned int DynamicQueue<T>::size(){
	return (tail - head + N) % N;//size of circular array is calculated
}

template <typename T> 
void DynamicQueue<T>::grow(){
	T *B;
	B = new T[nextSize()];// New array of bigger size created
	for (int i = 0; i < size(); i++)
		B[i] = A[(head + i)%N];// all elements as copied to new array, from index 0
	tail = size();
	head = 0;
	N = nextSize();//variables are updated appropriately
	delete[] A;//space of original array is deleted
	A = B;//pointer is updated
}

template <typename T> 
void DynamicQueue<T>::QInsert(T x){
	if (isFull()) grow();//if array is full, it is grown
	A[tail] = x;//element is stored
	tail = (tail+1)%N;//tail is updated
}

template <typename T> 
bool DynamicQueue<T>::QDelete(T* x){
	if (isEmpty()) return false;//if empty, false is returned 
	*x = A[head];
	head = (head +1)%N;//element isstored as required and head is updated to effectively delete the element 
	return true;
}

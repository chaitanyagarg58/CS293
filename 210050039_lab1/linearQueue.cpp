#include "queue.h"

template <typename T> 
bool DynamicQueue<T>::isEmpty(){
	return head == tail; //Queue is empty iff head is equal to tail
}

template <typename T> 
bool DynamicQueue<T>::isFull(){
	return tail - head == N;//if N elements are stored, then queue is full 
}

template <typename T> 
unsigned int DynamicQueue<T>::size(){
	return tail - head;//tail - head is the size.
}

template <typename T> 
void DynamicQueue<T>::grow(){
	N = nextSize();
	T *B;
	B = new T[N];//New array of bigger size is created
	for (int i = 0; i < size(); i++)
		B[i] = A[head + i];// each element of array is copied in new array from index 0
	tail = size();
	head = 0;// head and tail are updated
	delete[] A;//space of original array is freed
	A = B;//original pointer is updated to point to new array
}

template <typename T> 
void DynamicQueue<T>::QInsert(T x){
	if (tail == N)//if array already reached end, size is grown
		grow();//Note that the array may not be full as elements from beginning maybe deleted, but it is more optimal to grow at this point only, rather than shifting for now and growing later
	A[tail++] = x;//element is stored and tail updated
}

template <typename T> 
bool DynamicQueue<T>::QDelete(T* x){
	if (isEmpty()) return false;//If queue is empty, false is returned
	*x = A[head++];//the element at start is stored in *x and head is updated, effectively deleting the element
	if (isEmpty()){
		head = 0;
		tail = 0;// if queue becomes empty after deletion, head and tail are set to 0 to give more time before we need to grow
	}
	return true;
}

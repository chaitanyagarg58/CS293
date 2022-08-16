#include "dictionary.h"

char *tombstone = new char();

Dictionary::Dictionary(){
	N = 100;
	A = new Entry[N];
}

int Dictionary::hashValue(char key[]){
	long p = 3, pow = 1;
	int hash = 0;
	for (int i = 0; key[i]!='\0'; i++){
		hash = (hash + (key[i]-'A')*pow)%N;
		pow *= p;
	}
	return hash;
}

int Dictionary::findFreeIndex(char key[]){
 	int hash = hashValue(key);
 	for (int i = hash; true ; i = (i+1)%N){
 		if (A[i].key == nullptr || A[i].key == tombstone) return i;
 		if (i == hash-1 || (hash == 0 && i == N-1)) return -1;
 	}
}

struct Entry* Dictionary::get(char key[]){
  int hash = hashValue(key);
  for (int i = hash; true; i = (i+1)%N){
  	if (A[i].key == key) return &(A[i]);
  	if (A[i].key == nullptr || i == hash-1) return nullptr;
  }
  return nullptr;
}

bool Dictionary::put(struct Entry e){
  int index = findFreeIndex(e.key);
  if (index == -1) return false;
  A[index].key = e.key;
  A[index].value = e.value;
  return true;
}

bool Dictionary::remove(char key[]){
  int hash = hashValue(key);
  for (int i = hash; true; i = (i+1)%N){
  	if (A[i].key == key){
  		A[i].key = tombstone;
  		return true;
  	}
	  if (A[i].key == nullptr || i == hash-1) return false;
  }
}

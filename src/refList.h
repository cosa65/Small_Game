#include <iostream>

//#ifndef REFLIST_H
//#define REFLIST_H

template<class T>
class rlist{
	public:

		class rnode;
		class r_iterator;

		rlist();
		void push_back(T *x);
		bool remove(T *del);
		rnode *find(T *x);
		int mysize();
		void print();

		r_iterator begin() {
			return r_iterator(fst_);
		}

		
		r_iterator end() {
			return r_iterator(lst_);
		}

		class rnode{
		public:

			rnode(T *datapt, rnode *next);
			~rnode();

			rnode *next;
			T *datapt;
		
		};

		class r_iterator {
			public:

				r_iterator(rnode *start) {
					act = start;
				}

				void operator++() {
					act = act->next;
				}

				T operator*() {
					return *(act->datapt);
				}

				T *current() {
					return (act->datapt);
				}

				bool operator==(r_iterator other) {
					return other.act == this->act;
				}

				bool operator!=(r_iterator other) {
					return other.act != this->act;
				}

				bool null() {
					return act == NULL;
				}


			private:
				rnode *act;

		};

	private:

		rnode *fst_;
		rnode *lst_;
		int size_;
};

//#endif

//#include "refList.h"

template <class T>
rlist<T>::rlist() {
	fst_ = NULL;
	lst_ = NULL;
	size_ = 0;
}

template <class T>
void rlist<T>::push_back(T *x) {
	rnode *nuevo = new rnode(x,NULL);
	//rnode nuevo(x,NULL);

	if(fst_ == NULL) {
		fst_ = nuevo;
	} else {
		rnode *it = fst_;
		while(it -> next != NULL) {
			it = it -> next;
		}

		it -> next = nuevo;
	}
	lst_ = nuevo;
	size_++;
}

template <class T>
bool rlist<T>::remove(T *del) {
	
	if(size_ == 0) {											//Case empty list
		return false;
	}

	size_--;

	rnode *it = fst_; 
	if(this -> fst_ -> datapt == del) {									//Case found in fst_ position
		this -> fst_ = it -> next;
		delete it;
		if (size_ == 0) {lst_ = NULL;}
		return true;
	}

	while(it->next != NULL && (it -> next) -> datapt != del) {
		it = it -> next;
	}

	if((it -> next) == NULL) {									//Case node not found
		return false;
	}

	rnode *aux = it -> next;									//Case node found AND |list| > 2
	if(aux == lst_) {lst_ = it;}
	it -> next = (it -> next) -> next;

	delete aux;
	
	return true;
}


template <class T>
typename rlist<T>::rnode *rlist<T>::find(T *x) {

	if(fst_ == NULL) {
		return NULL;
	}

	if(fst_ -> datapt == x) {
		return fst_;
	}

	rnode *it = fst_; 

	while((it -> next) -> datapt != x) {
		it = it -> next;
	}

	return it->next;

}

template <class T>
int rlist<T>::mysize() {
	return size_;
}

template <class T>
void rlist<T>::print() {
	//assert(fst_ == NULL);

	std::cout << (*(fst_->datapt)) << std::endl;

	rnode *it = fst_; 

	while((it -> next) != NULL) {
		std::cout << (*((it->next)->datapt)) << std::endl;
		it = it -> next;
	}
}

template <class T>
rlist<T>::rnode::rnode(T *datapt, rnode *next) {
	this->datapt = datapt;
	this->next = next;
}

template <class T>
rlist<T>::rnode::~rnode() {
	//delete datapt;	
}

/*template <class T>
T *rlist<T>::rnode::datapt() {
	return this->datapt;
}*/
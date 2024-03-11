#pragma once

#include <iostream>

namespace my_list {

	template <class T> class List {
		T count_;
		List<T>* next_;
		int size_ = 0;

	public:
		List();
		~List();
		void Add(T);

		T operator[](int);
	};

	template <class T> List<T>::List() : count_{}, next_ { nullptr } {
		std::cout << "List created\n";
	}
	template <class T> List<T>::~List() {
		std::cout << "List destroyed\n";
	}

	template <class T> void List<T>::Add(T item) {
		List<T> *last_item = this;
		
		// Find last index;
		while (last_item != nullptr) last_item = last_item->next_;

		last_item = new List<T>();

		last_item->count_ = item;
		count_++;
	}

	template<class T> T List<T>::operator[](int index) {
		List<T> *item = this;

		for (int i = 0; i < index; i++) {
			item = item->next_;
		}

		return item->count_;
	}
}
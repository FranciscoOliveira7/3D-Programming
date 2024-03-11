#pragma once

#include <iostream>

namespace my_list {

	template <class T> class List {
		T value_;
		List<T>* next_;
		int size_ = 0;

	public:
		List();
		~List();
		void Add(T);

		T operator[](int);
	};

	template <class T> List<T>::List() : next_{ nullptr } {
		std::cout << "List created\n";
	}
	template <class T> List<T>::~List() {
		std::cout << "List destroyed\n";
	}

	template <class T> void List<T>::Add(T item) {
		List<T> last_item;
		
		// Find last index;
		while (last_item.next_ != nullptr) last_item = *(last_item.next_);

		last_item.next_ = new List<T>();

		last_item.next_->value_ = item;

	}
	template<class T> T List<T>::operator[](int index) {
		List<T> item;

		for (int i = 0; i < index; i++) {
			item = *(item.next_);
		}

		return item.value_;
	}
}
#ifndef LANGGG_LIST_MV_H
#define LANGGG_LIST_MV_H

template <typename T>
class list_mv {

	template<typename T2>
	class element {
	private:
		T2 value;
		element<T2>* p_next;
		element<T2>* p_previous;
		friend list_mv;
	public:
		element(const T2 value, element<T2>* p_next, element<T2>* p_previous) {
			this->value      = value;
			this->p_next     = p_next;
			this->p_previous = p_previous;
		};
	};

public:

	explicit list_mv();
	void insert(int pos,const T data);
	void pop(int pos);
	void push_back(const T data);
	void pop_back();
	int size();
	void clear();
	~list_mv();

	T& operator[](int i);

private:

	int capacity{};
	element<T>* p_first;
	element<T>* p_last;
	element<T>* find_element(int pos);
};

template<typename T>
list_mv<T>::list_mv() {
	this->capacity = 0;
	this->p_first = nullptr;
	this->p_last  = nullptr;
}

template<typename T>
void list_mv<T>::clear() {
	if (capacity > 0) {
		element<T>* p_for_delete  = p_first;
		element<T>* p_next_delete = p_first->p_next;

		while (p_next_delete != nullptr) {
			delete p_for_delete;
			capacity--;
			p_for_delete = p_next_delete;
			p_next_delete = p_next_delete->p_next;
		}

		delete p_for_delete;
		capacity--;
	}
}

template<typename T>
list_mv<T>::~list_mv() {
	clear();
}

template<typename T>
void list_mv<T>::push_back(const T data) {
	if (capacity == 0) {
		p_first = new element<T>(data, nullptr, nullptr);
		p_last = p_first;
	} else {
		element<T>* p_new_element = new element<T>(data, nullptr, p_last);
		p_last->p_next = p_new_element;
		p_last         = p_new_element;
	}

	capacity++;
}

template<typename T>
void list_mv<T>::insert(int pos, const T data) {
	if (pos < 0 || pos >= capacity) {
		return;
	}

	element<T>* p_new_element;
	element<T>* p_search_element;

	p_search_element = find_element(pos);

	p_new_element = new element<T>(data, p_search_element, p_search_element->p_previous);
	p_search_element->p_previous = p_new_element;

	if (p_search_element == p_first) {
		p_first = p_new_element;
		return;
	}

	if (p_search_element == p_first) {
		p_last->p_previous = p_new_element;
		return;
	}

	capacity++;
}

template <typename T>
int list_mv<T>::size() {
	return capacity;
}

template<typename T>
void list_mv<T>::pop(int pos) {
	if (pos < 0 || pos >= capacity) {
		return;
	}

	element<T>* p_search_element;

	p_search_element = find_element(pos);

	if (p_search_element == p_first) {
		p_first = p_first->p_next;
		p_first->p_previous = nullptr;
		delete p_search_element;
		return;
	}

	if (p_search_element == p_last) {
		p_last = p_last->p_previous;
		p_last->p_next = nullptr;
		delete p_search_element;
		return;
	}

	p_search_element->p_previous->p_next = p_search_element->p_next;
	p_search_element->p_next->p_previous = p_search_element->p_previous;
	delete p_search_element;

	capacity--;
}

template<typename T>
void list_mv<T>::pop_back() {
	if (capacity > 0) {
		element<T>* p_before_last = p_last->p_previous;
		p_before_last->p_next = nullptr;
		delete p_last;
		p_last = p_before_last;
		capacity--;
	}
}

template<typename T>
typename list_mv<T>::template element<T> *list_mv<T>::find_element(int pos) {
	element<T>* p_search_element;

	if (pos < capacity / 2) {
		p_search_element = p_first;

		for (int i = 0; i < pos; i++) {
			p_search_element = p_search_element->p_next;
		}
	} else {
		p_search_element = p_last;

		for (int i = capacity - pos - 1; i > 0; i--) {
			p_search_element = p_search_element->p_previous;
		}
	}

	return p_search_element;
}

template<typename T>
T &list_mv<T>::operator[](int i) {
	return find_element(i)->value;
}


#endif
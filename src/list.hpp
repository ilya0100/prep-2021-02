#pragma once // NOLINT
#include <iterator>
#include <algorithm>


namespace task {


template<class T>
class list {
 private:
    struct Node {
        T data;
        Node *next;
        Node *prev;

        Node(): data(T()), next(nullptr), prev(nullptr) {}
    };

 public:
    class iterator {
     public:
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::bidirectional_iterator_tag;

        iterator(): current{nullptr} {}
        iterator(Node* node): current(node) {}
        iterator(const iterator& it);
        iterator& operator=(const iterator& it);
        iterator& operator=(Node* node);

        iterator& operator++();
        iterator operator++(int);
        reference operator*() const;
        pointer operator->() const;
        iterator& operator--();
        iterator operator--(int);

        Node* get_current() const;

        bool operator==(iterator other) const;
        bool operator!=(iterator other) const;

     private:
        Node* current;
    };

    class const_iterator {
     public:
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::bidirectional_iterator_tag;

        const_iterator(): current{nullptr} {}
        const_iterator(Node* node): current(node) {}
        const_iterator(const iterator& it);
        const_iterator& operator=(const iterator& it);
        const_iterator& operator=(Node* node);

        const_iterator& operator++();
        const_iterator operator++(int);
        reference operator*() const;
        pointer operator->() const;
        const_iterator& operator--();
        const_iterator operator--(int);

        Node* get_current() const;

        bool operator==(const_iterator other) const;
        bool operator!=(const_iterator other) const;

     private:
        Node* current;
    };

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    list();
    list(size_t count, const T& value);
    explicit list(size_t count);
    ~list();

    list(const list& other);
    list& operator=(const list& other);

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;


    iterator begin() const;
    iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    reverse_iterator rbegin() const;
    reverse_iterator rend() const;

    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;


    bool empty() const;
    size_t size() const;
    size_t max_size() const;
    void clear();

    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, size_t count, const T& value);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);


    void push_back(const T& value);
    void pop_back();

    void push_front(const T& value);
    void pop_front();

    void resize(size_t count);
    void swap(list& other);


    void merge(const list& other);
    void splice(const_iterator pos, const list& other);
    void remove(const T& value);
    void reverse();
    void unique();
    void sort();

    void set_size(size_t count);

 private:
    Node* head;
    Node* tail;

    Node end_node;
    size_t list_size;
};


template<class T>
list<T>::iterator::iterator(const iterator& it) {
    *this = it;
}

template<class T>
typename list<T>::iterator& list<T>::iterator::operator=(const iterator& it) {
    *this = it;
    return *this;
}

template<class T>
typename list<T>::iterator& list<T>::iterator::operator=(Node* node) {
    this->current = node;
    return *this;
}

template<class T>
typename list<T>::iterator& list<T>::iterator::operator++() {
    current = current->next;
    return *this;
}

template<class T>
typename list<T>::iterator list<T>::iterator::operator++(int) {
    auto temp = *this;
    current = current->next;
    return temp;
}

template<class T>
typename list<T>::iterator::reference list<T>::iterator::operator*() const {
    return current->data;
}

template<class T>
typename list<T>::iterator::pointer list<T>::iterator::operator->() const {
    return &(current->data);
}

template<class T>
typename list<T>::iterator& list<T>::iterator::operator--() {
    current = current->prev;
    return *this;
}

template<class T>
typename list<T>::iterator list<T>::iterator::operator--(int num) {
    auto temp = *this;
    current = current->prev;
    return temp;
}

template<class T>
bool list<T>::iterator::operator==(iterator other) const {
    return current == other.current;
}

template<class T>
bool list<T>::iterator::operator!=(iterator other) const {
    return current != other.current;
}

template<class T>
typename list<T>::Node* list<T>::iterator::get_current() const {
    return current;
}


template<class T>
list<T>::const_iterator::const_iterator(const iterator& it) {
    *this = it;
}

template<class T>
typename list<T>::const_iterator& list<T>::const_iterator::operator=(const iterator& it) {
    *this = it;
    return *this;
}

template<class T>
typename list<T>::const_iterator& list<T>::const_iterator::operator=(Node* node) {
    this->current = node;
    return *this;
}

template<class T>
typename list<T>::const_iterator& list<T>::const_iterator::operator++() {
    current = current->next;
    return *this;
}

template<class T>
typename list<T>::const_iterator list<T>::const_iterator::operator++(int) {
    auto temp = *this;
    current = current->next;
    return temp;
}

template<class T>
typename list<T>::const_iterator::reference list<T>::const_iterator::operator*() const {
    return current->data;
}

template<class T>
typename list<T>::const_iterator::pointer list<T>::const_iterator::operator->() const {
    return &(current->data);
}

template<class T>
typename list<T>::const_iterator& list<T>::const_iterator::operator--() {
    current = current->prev;
    return *this;
}

template<class T>
typename list<T>::const_iterator list<T>::const_iterator::operator--(int num) {
    auto temp = *this;
    current = current->prev;
    return temp;
}

template<class T>
bool list<T>::const_iterator::operator==(const_iterator other) const {
    return current == other.current;
}

template<class T>
bool list<T>::const_iterator::operator!=(const_iterator other) const {
    return current != other.current;
}

template<class T>
typename list<T>::Node* list<T>::const_iterator::get_current() const {
    return current;
}


template<class T>
list<T>::list(): list_size(0) {
    head = nullptr;
    tail = &end_node;
    tail->prev = head;
}

template<class T>
list<T>::list(size_t count, const T& value): head(), tail(), list_size(count) {
    for (size_t i = 0; i < count; i++) {
        push_back(value);
    }
}

template<class T>
list<T>::list(size_t count): head(), tail(), list_size(0) {
    resize(count);
}

template<class T>
list<T>::~list() {
    clear();
}

template<class T>
list<T>::list(const list& other) {
    clear();
    head = other.begin().get_current();
    tail = other.end().get_current();
}

template<class T>
list<T>& list<T>::operator=(const list& other) {
    resize(other.size());
    for (iterator it = begin(), other_it; it != end(); ++it, ++other_it) {
        *it = *other_it;
    }
    return *this;
}

template<class T>
T& list<T>::front() {
    return *(begin());
}

template<class T>
const T& list<T>::front() const {
    return *(begin());
}

template<class T>
T& list<T>::back() {
    return *(--end());
}

template<class T>
const T& list<T>::back() const {
    return *(--end());
}

template<class T>
typename list<T>::iterator list<T>::begin() const {
    return iterator(this->head);
}

template<class T>
typename list<T>::iterator list<T>::end() const {
    iterator temp = this->tail;
    return temp;
}

template<class T>
typename list<T>::const_iterator list<T>::cbegin() const {
    return const_iterator(begin());
}

template<class T>
typename list<T>::const_iterator list<T>::cend() const {
    return const_iterator(end());
}

template<class T>
typename list<T>::reverse_iterator list<T>::rbegin() const {
    return reverse_iterator(begin());
}

template<class T>
typename list<T>::reverse_iterator list<T>::rend() const {
    return reverse_iterator(end());
}

template<class T>
typename list<T>::const_reverse_iterator list<T>::crbegin() const {
    return const_reverse_iterator(begin());
}

template<class T>
typename list<T>::const_reverse_iterator list<T>::crend() const {
    return const_reverse_iterator(end());
}

template<class T>
bool list<T>::empty() const {
    return list_size == 0;
}

template<class T>
size_t list<T>::size() const {
    return list_size;
}

template<class T>
void list<T>::clear() {
    Node* cur = head;
    while (cur->next != nullptr) {
        Node* temp = cur;
        cur = temp->next;
        delete temp;
    }
    list_size = 0;
}

template<class T>
typename list<T>::iterator list<T>::insert(const_iterator pos, const T& value) {
    Node* new_node = new Node;
    Node* temp;
    temp = pos.get_current();

    temp->prev->next = new_node;
    new_node->prev = temp->prev;
    new_node->next = temp;
    temp->prev = new_node;

    new_node->data = value;
    iterator it = new_node;
    ++list_size;
    return it;
}

template<class T>
typename list<T>::iterator list<T>::insert(const_iterator pos, size_t count, const T& value) {
    list<T> temp(count, value);
    iterator it = temp.begin();
    splice(pos, temp);
    return it;
}

template<class T>
typename list<T>::iterator list<T>::erase(const_iterator pos) {
    iterator it(pos.get_current());
    if (pos != cend() && !empty()) {
        ++it;
        Node* temp = pos.get_current();
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        --list_size;
    }
    return it;
}

template<class T>
typename list<T>::iterator list<T>::erase(const_iterator first, const_iterator last) {
    iterator it(last.get_current());
    while (first != last) {
        first = erase(first);
    }
    return it;
}

template<class T>
void list<T>::push_back(const T& value) {
    insert(cend(), value);
}

template<class T>
void list<T>::pop_back() {
    erase(cend());
}

template<class T>
void list<T>::push_front(const T& value) {
    insert(cbegin(), value);
}

template<class T>
void list<T>::pop_front() {
    erase(cbegin());
}

template<class T>
void list<T>::resize(size_t count) {
    if (count > size()) {
        for (size_t i = size(); i < count; ++i) {
            insert(cend(), T());
        }
    } else if (count < size()) {
        for (size_t i = size(); i >= count; --i) {
            erase(cend());
        }
    }
}

template<class T>
void list<T>::swap(list& other) {
    std::swap(*begin(), *other.begin());
    Node* temp = other.begin().get_current();
    std::swap(head->next, temp->next);

    temp = other.end().get_current();
    std::swap(tail->prev, temp->prev);

    size_t size = list_size;
    list_size = other.size();
    other.set_size(size);
}

template<class T>
void list<T>::merge(const list& other) {
    tail->prev->next = other.begin().get_current();
    tail = other.end().get_current();
    list_size += other.size();
}

template<class T>
void list<T>::splice(const_iterator pos, const list& other) {
    Node* temp = pos.get_current();
    temp->prev->next = other.begin().get_current();

    temp->prev = other.end().get_current()->prev;
    temp->prev->next = temp;
    list_size += other.size();
}

template<class T>
void list<T>::remove(const T& value) {
    iterator first = begin();
    iterator last = end();
    while (first != last) {
        iterator next = first;
        ++next;
        if (*first == value) {
            erase(first);
        }
        first = next;
    }
}

template<class T>
void list<T>::reverse() {
    list<T> temp(size());

    iterator first = begin();
    iterator last = end();
    while (first != last) {
        temp.push_front(*first);
        ++first;
    }
    *this = temp;
}

template<class T>
void list<T>::unique() {
    iterator first = begin();
    iterator last = end();
    iterator next = first;
    while (++next != last) {
        if (*first == *next) {
            erase(next);
        } else {
            first = next;
        }
        next = first;
    }
}

template<class T>
void list<T>::sort() {
    if (size() > 1) {
        list carry;
        list tmp[64];
        list* fill = tmp;
	    try {
            list* counter;
	        do {
		        carry.splice(carry.cbegin(), *this);

		        for (counter = tmp; counter != fill && !counter->empty(); ++counter) {
		            counter->merge(carry);
		            carry.swap(*counter);
		        }
		        carry.swap(*counter);
		        if (counter == fill) {
		          ++fill;
                }
	        } while (!empty());

	        for (counter = tmp + 1; counter != fill; ++counter) {
                counter->merge(*(counter - 1));
            }
	        swap(*(fill - 1));
	    }
	    catch(...) {
	        this->splice(this->cend(), carry);
	        for (size_t i = 0; i < sizeof(tmp)/sizeof(tmp[0]); ++i) {
                this->splice(this->cend(), tmp[i]);
            }
	    }
    }
}

template<class T>
void list<T>::set_size(size_t count) {
    list_size = count;
}

}  // namespace task

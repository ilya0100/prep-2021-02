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

     protected:
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
        const_iterator(const Node* node): current(node) {}
        const_iterator(const iterator& it);
        const_iterator& operator=(const iterator& it);
        const_iterator& operator=(const Node* node);

        const_iterator& operator++();
        const_iterator operator++(int);
        reference operator*() const;
        pointer operator->() const;
        const_iterator& operator--();
        const_iterator operator--(int);

        const Node* get_current() const;

        bool operator==(const_iterator other) const;
        bool operator!=(const_iterator other) const;

     protected:
        const Node* current;
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


 private:
    Node* head;
    Node* tail;

    Node end_node;
    size_t list_size;

    void set_size(size_t count);
};


template<class T>
list<T>::iterator::iterator(const iterator& it) {
    this->current = it.current;
}

template<class T>
typename list<T>::iterator& list<T>::iterator::operator=(const iterator& it) {
    this->current = it.current;
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
    this->current = it.get_current();
}

template<class T>
typename list<T>::const_iterator& list<T>::const_iterator::operator=(const iterator& it) {
    this->current = it.get_current();
    return *this;
}

template<class T>
typename list<T>::const_iterator& list<T>::const_iterator::operator=(const Node* node) {
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
const typename list<T>::Node* list<T>::const_iterator::get_current() const {
    return current;
}


template<class T>
list<T>::list(): list_size(0) {
    head = nullptr;
    tail = &end_node;
}

template<class T>
list<T>::list(size_t count, const T& value): list_size(0) {
    head = nullptr;
    tail = &end_node;
    for (size_t i = 0; i < count; i++) {
        push_back(value);
    }
}

template<class T>
list<T>::list(size_t count): list_size(0) {
    head = nullptr;
    tail = &end_node;
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
    clear();
    head = other.begin().get_current();
    tail = other.end().get_current();
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
    if (size() != 0) {
        Node* cur = head;
        while (cur->next != nullptr) {
            Node* temp = cur;
            cur = temp->next;
            delete temp;
        }
        list_size = 0;
    }
}

template<class T>
typename list<T>::iterator list<T>::insert(const_iterator pos, const T& value) {
    Node* new_node = new Node;
    Node* temp = const_cast<Node*>(pos.get_current());
    new_node->data = value;

    if (size() == 0) {
        new_node->next = tail;
        tail->prev = new_node;
        head = new_node;
    } else if (pos == cbegin()) {
        new_node->next = temp;
        temp->prev = new_node;
        head = new_node;
    } else {
        temp->prev->next = new_node;
        new_node->prev = temp->prev;
        temp->prev = new_node;
        new_node->next = temp;
    }
    iterator it = new_node;
    ++list_size;
    return it;
}

template<class T>
typename list<T>::iterator list<T>::insert(const_iterator pos, size_t count, const T& value) {
    iterator it;
    for (size_t i = 0; i < count; ++i) {
        it = this->insert(pos, value);
    }
    return it;
}

template<class T>
typename list<T>::iterator list<T>::erase(const_iterator pos) {
    iterator it(const_cast<Node*>(pos.get_current()));
    if (pos != cend() && !empty()) {
        ++it;
        Node* temp = const_cast<Node*>(pos.get_current());
        if (size() > 1) {
            if (pos != cbegin()) {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            } else {
                head = temp->next;
                head->prev = nullptr;
            }
        }
        delete temp;
        --list_size;
    }
    return it;
}

template<class T>
typename list<T>::iterator list<T>::erase(const_iterator first, const_iterator last) {
    iterator it(const_cast<Node*>(last.get_current()));
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
    erase(const_iterator(this->tail->prev));
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
    Node* other_node = other.begin().get_current();
    Node* temp;
    if (other.size() != 0) {
        temp = other_node->next;
        other_node->next->prev = head;
        head->next->prev = other_node;
        other_node->next = head->next;
        head->next = temp;

        other_node = other.end().get_current();
        temp = other_node->prev;

        other_node->prev->next = tail;
        tail->prev->next = other_node;
        other_node->prev = head->prev;
        head->prev = temp;

        size_t size = list_size;
        list_size = other.size();
        other.set_size(size);
    } else {
        // other_node = head;
        // head = nullptr;
        // other_node = other.end().get_current();
        // other_node->prev = tail->prev;
        // tail->prev = nullptr;
        other.splice(other.cbegin(), *this);
        head = nullptr;
        tail->prev = nullptr;
        list_size = 0;
    }
}

template<class T>
void list<T>::merge(const list& other) {
    // tail->prev->next = other.begin().get_current();
    // tail = other.end().get_current();
    // list_size += other.size();
    splice(cend(), other);
}

template<class T>
void list<T>::splice(const_iterator pos, const list& other) {
    if (other.size() != 0) {
        Node* temp = const_cast<Node*>(pos.get_current());
        if (size() == 0) {
            head = other.begin().get_current();
            tail = other.end().get_current();

        } else if (pos == cbegin()) {
            Node* other_tail = other.end().get_current();

            other_tail->prev->next = temp;
            temp->prev = other_tail->prev;
            head = other.begin().get_current();

        } else if (pos == cend().get_current()) {
            Node* other_head = other.begin().get_current();

            temp->prev->next = other_head;
            other_head->prev = temp->prev;
            tail = other.end().get_current();
        } else {
            temp->prev->next = other.begin().get_current();
            temp->prev->next->prev = temp->prev;

            temp->prev = other.end().get_current()->prev;
            temp->prev->next = temp;
        }
        list_size += other.size();
    }
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
        list temp[64];
        list* fill = temp;
	    try {
            list* counter;
	        do {
		        carry.splice(carry.cbegin(), *this);

		        for (counter = temp; counter != fill && !counter->empty(); ++counter) {
		            counter->merge(carry);
		            carry.swap(*counter);
		        }
		        carry.swap(*counter);
		        if (counter == fill) {
		          ++fill;
                }
	        } while (!empty());

	        for (counter = temp + 1; counter != fill; ++counter) {
                counter->merge(*(counter - 1));
            }
	        swap(*(fill - 1));
	    }
	    catch(...) {
	        this->splice(this->cend(), carry);
	        for (size_t i = 0; i < sizeof(temp)/sizeof(temp[0]); ++i) {
                this->splice(this->cend(), temp[i]);
            }
	    }
    }
}

template<class T>
void list<T>::set_size(size_t count) {
    list_size = count;
}

}  // namespace task

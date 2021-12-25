#pragma once // NOLINT
#include <iterator>


namespace task {


template<class T>
class list {
 private:
    struct Node {
        T data;
        Node *next;
        Node *prev;

        Node(T new_data = T(), Node* new_next = nullptr, Node* new_prev = nullptr):
            data(new_data), next(new_next), prev(new_prev) {}
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
        iterator(const Node* node): current(node) {}
        iterator(const iterator& it): current(it) {}
        iterator& operator=(const iterator& it);
        iterator& operator=(Node* node);

        iterator& operator++();
        iterator operator++(int num);
        reference operator*() const;
        pointer operator->() const;
        iterator& operator--();
        iterator operator--(int num);

        Node* get_prev() const;
        Node* get_next() const;
        Node* get_current() const;

        bool operator==(iterator other) const;
        bool operator!=(iterator other) const;

     private:
        Node* current;
    };

    class const_iterator {
        // Your code goes here...
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


    void merge(list& other);
    void splice(const_iterator pos, list& other);
    void remove(const T& value);
    void reverse();
    void unique();
    void sort();

 private:
    iterator begin_it;
    iterator end_it;

    Node* begin_node;
    Node* end_node;

    size_t list_size;
};


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
typename list<T>::iterator list<T>::iterator::operator++(int num) {
    for (int i = 0; i < num; i++) {
        current = current->next;
    }
    return *this;
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
    for (int i = 0; i < num; i++) {
        current = current->prev;
    }
    return *this;
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
typename list<T>::Node* list<T>::iterator::get_prev() const {
    return current->prev;
}

template<class T>
typename list<T>::Node* list<T>::iterator::get_next() const {
    return current->next;
}

template<class T>
typename list<T>::Node* list<T>::iterator::get_current() const {
    return current;
}


template<class T>
list<T>::list(): begin_it(), end_it(), list_size(0) {}

template<class T>
list<T>::list(size_t count, const T& value): begin_it(), end_it(), list_size(count) {
    for (size_t i = 0; i < count; i++) {
        push_back(value);
    }
}

template<class T>
list<T>::list(size_t count): begin_it(), end_it(), list_size(count) {
    for (size_t i = 0; i < count; i++) {
        push_back(T());
    }
}

template<class T>
list<T>::~list() {
    clear();
}

template<class T>
bool list<T>::empty() const {
    return list_size == 0;
}

template<class T>
void list<T>::push_back(const T& value) {
    Node* new_node = new Node;
    new_node->data = value;

    Node* next = new Node;
    next->next = nullptr;
    next->prev = new_node;
    next->data = T();

    new_node->next = next;

    if (empty()) {
        new_node->prev = nullptr;
    } else {
        new_node->prev = end_it.get_prev();
    }
    begin_it = new_node;
    end_it = next;
    list_size++;
}

template<class T>
void list<T>::pop_back() {
    if (empty()) { return; }
    Node* temp = end_it.get_prev();
    (temp->prev)->next = end_it.get_node();
    Node* new_end_it  
}
}  // namespace task

#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "allocator.h"
#include "node.h"

template <typename T, class Allocator = PoolAllocator<Node<T>>>
    class List {
        private:
            Node<T> *head;
            Node<T> *tail;
            size_t _size;
            Allocator _alloc;
        public:
        
            friend std::ostream &operator << (std::ostream &os, const List<T, Allocator> &list) {
                os << '[';
                Node<T> *cur = list.head;
                while (cur->next) {
                    os << *cur << ", ";
                    cur = cur->next;
                }
                os << *cur << ']' << std::endl;
                return os;
            }

            List();
            List(const std::initializer_list<T> &l);
            List(const List &other);
            List(List &&other) noexcept;
            ~List() noexcept;

            size_t size() const;
            void push_back(const T &value);
            void emplace(const T &value);
            void remove();
            void pop();
            bool is_empty() const;
            T & front() const;
            T & back() const;

            T &operator [] (size_t idx);
            bool operator==(const List<T, Allocator> &other) const;
            List<T, Allocator> &operator=(List<T, Allocator> &other);
            List<T, Allocator> &operator=(List<T, Allocator> &&other) noexcept;
            
            class Iterator {
                friend class List;
                private:
                    Node<T> *item;
                public:

                    Iterator(Iterator &other);
                    Iterator(Iterator &&other) noexcept;
                    Iterator(Node<T> *node);
                    ~Iterator() = default;
                    
                    List::Iterator &operator ++();
                    List::Iterator operator ++(int);
                    List::Iterator &operator + (size_t rhs);
                    T& operator* () const;
                    T* operator-> () const;
                    bool operator ==(const Iterator &other) const;
                    bool operator !=(const Iterator &other) const;
                    List::Iterator &operator =(const Iterator &other);
                    List::Iterator &operator =(Iterator &&other) noexcept;
            };

            class ConstIterator {
                friend class List;
                private:
                    const Node<T> *item;
                public:

                    ConstIterator(ConstIterator &other);
                    ConstIterator(ConstIterator &&other) noexcept;
                    ConstIterator(Node<T> *node);
                    ~ConstIterator() = default;
                    
                    List::ConstIterator &operator ++();
                    List::ConstIterator operator ++(int);
                    List::ConstIterator &operator + (size_t rhs);
                    const T& operator *() const;
                    const T* operator ->() const;
                    bool operator ==(const ConstIterator &other) const;
                    bool operator !=(const ConstIterator &other) const;
                    List::ConstIterator &operator =(const ConstIterator &other);
                    List::ConstIterator &operator =(ConstIterator &&other) noexcept;
            };
            List::ConstIterator cbegin();
            List::ConstIterator cend();
            List::Iterator begin();
            List::Iterator end();
            void insert(List::Iterator iter, const T& value);
            void erase(List::Iterator iter);
    };

template <typename T, class Allocator>
List<T, Allocator>::List() : head(nullptr), _size(0), tail(nullptr), _alloc() {}

template <typename T, class Allocator>
List<T, Allocator>::List(const std::initializer_list<T> &l) {
    head = _alloc.allocate();
    head->data = *l.begin();
    _size = l.size();
    Node<T> *cur = head;
    for (auto el = l.begin() + 1; el != l.end(); ++el) {
        cur->next = _alloc.allocate();
        cur->next->data = *el;
        cur = cur->next;
    }
    tail = cur;
    cur->next = nullptr;
}

template <typename T, class Allocator>
List<T, Allocator>::List(const List &other) {
    _size = other._size;
    head = _alloc.allocate();
    head->data = other.head->data;
    head->next = other.head->next;
    Node<T> *cur = head;
    for (Node<T> *t = other.head->next; t != nullptr; t = t->next) {
        cur->next = _alloc.allocate();
        cur->next->data = t->data;
        cur->next->next = t->next;
        cur = cur->next;
    }
    tail = cur;
    cur->next = nullptr;
}

template <typename T, class Allocator>
List<T, Allocator>::~List() noexcept{
    while (head != NULL) {
        remove();
    }
}

template <typename T, class Allocator>
List<T, Allocator>::List(List &&other) noexcept : _alloc(std::move(other._alloc)) {
    _size = other._size; other._size = 0;
    head = other.head; other.head = nullptr;
    tail = other.tail; other.tail = nullptr;
}

template<typename T, class Allocator>
T& List<T, Allocator>::operator[] (size_t idx) {
    if (_size < idx) {
        throw std::range_error("Out of range");
    } else {
        return head->get(idx);
    }
}

template<typename T, class Allocator>
size_t List<T, Allocator>::size () const{
    return _size;
}

template<typename T, class Allocator>
bool List<T, Allocator>::is_empty() const {
    return _size == 0;
}


template<typename T, class Allocator>
void List<T, Allocator>::push_back (const T &value){
    Node<T> *tmp = _alloc.allocate();
    tmp->data = value;
    tmp->next = nullptr;
    if (this->is_empty()) {
        head = tmp;
        tail = tmp;
    } else {
        tail->next = tmp;
        tail = tmp;
    }
    _size++;
}

template<typename T, class Allocator>
void List<T, Allocator>::emplace (const T &value){
    Node<T> *tmp = _alloc.allocate();
    tmp->next = nullptr;
    tmp->data = value;
    if (this->is_empty()) {
        head = tmp;
        tail = tmp;
    } else {
        tmp->next = head;
        head = tmp;
    }
    _size++;
}

template<typename T, class Allocator>
void List<T, Allocator>::remove(){
    if (this->is_empty()) {
        throw std::logic_error("Can't remove from empty list");
    }
    if (head == tail) {
        _alloc.deallocate(tail);
        head = tail = nullptr;
        _size = 0;
        return;
    }
    Node<T> *tmp = head;
    head = tmp->next;
    _size--;
    _alloc.deallocate(tmp);
}

template<typename T, class Allocator>
void List<T, Allocator>::pop(){
    if (this->is_empty()) {
        throw std::logic_error("Can't remove from empty list");
    }
    if (head == tail) {
        remove();
        return;
    }
    _size--;
    Node<T> *tmp = head;
    while (tmp->next != tail) tmp = tmp->next;
    tmp->next = nullptr;
    _alloc.deallocate(tail);
    tail = tmp;
}

template<typename T, class Allocator>
T &List<T, Allocator>::front() const {
    if (this->is_empty()) {
        throw std::logic_error("List is empty");
    }
    return head->data;
}

template<typename T, class Allocator>
T &List<T, Allocator>::back() const {
    if (this->is_empty()) {
        throw std::logic_error("List is empty");
    }
    return tail->data;
}

template<typename T, class Allocator>
bool List<T, Allocator>::operator==(const List<T, Allocator> &other) const{
    if (_size != other.size()) {
        return false;
    }
    Node<T> *tmp1 = head;
    Node<T> *tmp2 = other.head;
    while (tmp1) {
        if (!(*tmp1 == *tmp2)) return false;
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    return true;
}

template<typename T, class Allocator>
List<T, Allocator> &List<T, Allocator>::operator=(List<T, Allocator> &other) {
    _size = other._size;
    head = _alloc.allocate();
    head->data = other.head->data;
    head->next = other.head->next;
    Node<T> *cur = head;
    for (Node<T> *t = other.head->next; t != nullptr; t = t->next) {
        cur->next = _alloc.allocate();
        cur->next->data = t->data;
        cur->next->next = t->next;
        cur = cur->next;
    }
    tail = cur;
    cur->next = nullptr;
    return *this;
}

template<typename T, class Allocator>
List<T, Allocator> &List<T, Allocator>::operator=(List<T, Allocator> &&other) noexcept {
    _size = other._size; other._size = 0;
    head = other.head; other.head = nullptr;
    tail = other.tail; other.tail = nullptr;
    _alloc = std::move(other._alloc);
    return *this;
}

template <typename T, class Allocator>
List<T, Allocator>::Iterator::Iterator(Iterator &other) : item(other.item) {}

template <typename T, class Allocator>
List<T, Allocator>::Iterator::Iterator(Iterator &&other) noexcept {
    item = std::move(other.item);
}

template <typename T, class Allocator>
List<T, Allocator>::Iterator::Iterator(Node<T> *node) : item(node) {}

template <typename T, class Allocator>
typename List<T, Allocator>::Iterator &List<T, Allocator>::Iterator::operator++() {
    if (item == nullptr) {
        throw std::range_error("Out of range");
    }
    item = item->next;
    return *this;
}

template <typename T, class Allocator>
typename List<T, Allocator>::Iterator List<T, Allocator>::Iterator::operator++(int) {
    if (item == nullptr) {
        throw std::range_error("Out of range");
    }
    item = item->next;
    return *this;
}

template <typename T, class Allocator>
typename List<T, Allocator>::Iterator &List<T, Allocator>::Iterator::operator+(size_t rhs) {
    for (size_t i = 0; i < rhs; i++) {
        if (item == nullptr) {
            throw std::range_error("Out of range");
        }
        item = item->next;
    }
    if (item == nullptr) {
        throw std::range_error("Out of range");
    }
    return *this;
}

template <typename T, class Allocator>
T& List<T, Allocator>::Iterator::operator *() const {
    return item->data;
}

template <typename T, class Allocator>
bool List<T, Allocator>::Iterator::operator == (const Iterator &other) const {
    return item == other.item;
}

template <typename T, class Allocator>
bool List<T, Allocator>::Iterator::operator != (const Iterator &other) const{
    return !(other == *this);
}

template <typename T, class Allocator>
T* List<T, Allocator>::Iterator::operator ->() const {
    return &(item->data);
}

template <typename T, class Allocator>
typename List<T, Allocator>::Iterator &List<T, Allocator>::Iterator::operator =(const typename List<T, Allocator>::Iterator &other) {
    item = other.item;
    return *this;
}

template <typename T, class Allocator>
typename List<T, Allocator>::Iterator &List<T, Allocator>::Iterator::operator =(typename List<T, Allocator>::Iterator &&other) noexcept{
    item = std::move(other.item);
    return *this;
}

template <typename T, class Allocator>
typename List<T, Allocator>::Iterator List<T, Allocator>::begin() {
    return Iterator(head);
}

template <typename T, class Allocator>
typename List<T, Allocator>::Iterator List<T, Allocator>::end() {
    return Iterator(nullptr);
}

template <typename T, class Allocator>
void List<T, Allocator>::insert(List::Iterator iter, const T& value) {
    if (iter == this->end() || this->is_empty()) {
        this->push_back(value);
        return;
    }
    auto jter = this->begin();
    Node<T> *cur = head;
    while (iter != jter) {
        cur = cur->next;
        ++jter;
    }
    Node<T> *tmp = cur->next;
    cur->next = _alloc.allocate();
    cur->next->data = value;
    cur->next->next = tmp;
    _size++;
}

template <typename T, class Allocator>
void List<T, Allocator>::erase(List::Iterator iter) {
    if (iter == this->end() || this->is_empty()) {
        this->pop();
        return;
    }
    if (iter == this->begin() || this->is_empty()) {
        this->remove();
        return;
    }
    auto jter = this->begin();
    Node<T> *cur = head;
    Node<T> *prev;
    while (iter != jter) {
        prev = cur;
        if (cur == nullptr) {
            throw std::range_error("Out of range");
        }
        cur = cur->next;
        ++jter;
    }
    Node<T> *tmp = prev->next->next;
    _alloc.deallocate(prev->next);
    prev->next = tmp;
    _size--;
}

template <typename T, class Allocator>
List<T, Allocator>::ConstIterator::ConstIterator(ConstIterator &other) : item(other.item) {}

template <typename T, class Allocator>
List<T, Allocator>::ConstIterator::ConstIterator(ConstIterator &&other) noexcept {
    item = std::move(other.item);
}

template <typename T, class Allocator>
List<T, Allocator>::ConstIterator::ConstIterator(Node<T> *node) : item(node) {}


template <typename T, class Allocator>
typename List<T, Allocator>::ConstIterator &List<T, Allocator>::ConstIterator::operator++() {
    if (item == nullptr) {
        throw std::range_error("Out of range");
    }
    item = item->next;
    return *this;
}

template <typename T, class Allocator>
typename List<T, Allocator>::ConstIterator List<T, Allocator>::ConstIterator::operator++(int) {
    if (item == nullptr) {
        throw std::range_error("Out of range");
    }
    item = item->next;
    return *this;
}

template <typename T, class Allocator>
typename List<T, Allocator>::ConstIterator &List<T, Allocator>::ConstIterator::operator+(size_t rhs) {
    for (size_t i = 0; i < rhs; i++) {
        if (item == nullptr) {
            throw std::range_error("Out of range");
        }
        item = item->next;
    }
    if (item == nullptr) {
        throw std::range_error("Out of range");
    }
    return *this;
}

template <typename T, class Allocator>
const T& List<T, Allocator>::ConstIterator::operator *() const {
    return item->data;
}

template <typename T, class Allocator>
bool List<T, Allocator>::ConstIterator::operator == (const ConstIterator &other) const {
    return item == other.item;
}

template <typename T, class Allocator>
bool List<T, Allocator>::ConstIterator::operator != (const ConstIterator &other) const{
    return !(other == *this);
}

template <typename T, class Allocator>
const T* List<T, Allocator>::ConstIterator::operator-> () const {
    return &(item->data);
}

template <typename T, class Allocator>
typename List<T, Allocator>::ConstIterator &List<T, Allocator>::ConstIterator::operator =(const typename List<T, Allocator>::ConstIterator &other) {
    item = other.item;
    return *this;
}

template <typename T, class Allocator>
typename List<T, Allocator>::ConstIterator &List<T, Allocator>::ConstIterator::operator =(typename List<T, Allocator>::ConstIterator &&other) noexcept{
    item = std::move(other.item);
    return *this;
}

template <typename T, class Allocator>
typename List<T, Allocator>::ConstIterator List<T, Allocator>::cbegin() {
    return ConstIterator(head);
}

template <typename T, class Allocator>
typename List<T, Allocator>::ConstIterator List<T, Allocator>::cend() {
    return ConstIterator(nullptr);
}
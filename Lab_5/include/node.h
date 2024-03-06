#include <iostream>

template <typename T>
struct Node {
    T data;
    Node *next;

    friend std::ostream &operator << (std::ostream &os, const Node<T> &node) {
        os << '(' << node.data << ", " << node.next << ", " << &node << ')';
        return os;
    }

    Node();
    Node(const T &value);
    Node(const Node &other);
    ~Node() = default;
    
    T& get(size_t idx);
    bool operator==(const Node &other) const;
};

template <typename T>
Node<T>::Node() : next(nullptr), data() {}

template <typename T>
Node<T>::Node(const T &value) : next(nullptr), data(value) {}

template <typename T>
Node<T>::Node(const Node<T> &other) {
    data = other.data;
    next = other.next;
}

template<typename T>
T& Node<T>::get(size_t idx) {
    if (idx == 0) return data;
    if (next) return next->get(--idx);
    throw std::range_error("Out of range");
}

template<typename T>
bool Node<T>::operator==(const Node<T> &other) const {
    return data == other.data;
}
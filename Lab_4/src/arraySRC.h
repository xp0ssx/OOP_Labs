#pragma once
#include "array.h"

template <typename T>
Array<T>::Array() : _size{0}, _capacity{0}, _array{nullptr} {}

template <typename T>
Array<T>::Array(const std::initializer_list<T> &list) {
    _size = list.size();
    _capacity = _size + 5;
    _array = std::make_unique<T[]>(_capacity);
    size_t i = 0;
    for (T el: list) {
        _array[i++] = el;
    }
}

template <typename T>
Array<T>::Array(Array<T> &&other) noexcept {
    _size = other._size;
    _capacity = other._capacity;
    _array = std::move(other._array);
}

template <typename T>
Array<T>::Array(const Array<T> &other) {
    _size = other._size;
    _capacity = other._capacity;
    _array = std::make_unique<T[]>(_capacity);
    for (int i = 0; i < other.size(); i++) {
        _array[i] = other[i];
    }
}

template <typename T>
T &Array<T>::operator[] (const size_t &index) const {
    if (index > _size) {
        throw std::range_error("index is bigger, than size");
    }
    return _array[index];
}

template <typename T>
size_t Array<T>::size() const {
    return _size;
}

template <typename T>
void Array<T>::push_back(const T &el) {
    if (_size < _capacity) {
        _array[_size] = el;
    } else {
        std::unique_ptr<T[]> newArray = std::make_unique<T[]>(_capacity + 5);
        for (int i = 0; i < _size; i++) {
            newArray[i] = _array[i];
        }
        newArray[_size] = el;
        _array = std::move(newArray);
        _capacity+=5;
    }
    _size++;
}

template <typename T>
void Array<T>::erase(const size_t &idx) {
    if (idx > _size) {
        throw std::range_error("index is bigger, than size");
    }
    for (size_t i = idx; i < _size - 1; i++) {
        _array[i] = _array[i+1];
    }
    _size--;
}

template <typename T>
void Array<T>::pop_back() {
    if (_size == 0) {
        throw std::range_error("can't pop from empty array");
    }
    _size--;
}

template <typename T>
Array<T> &Array<T>::operator=(const Array<T> &other) {
    _size = other._size;
    _capacity = other._capacity;
    _array = std::make_unique<T[]>(_capacity);
    std::memcpy(_array.get(), other._array.get(), other.size() * sizeof(T));
    return *this;
}

template <typename T>
Array<T> &Array<T>::operator=(Array<T> &&other) noexcept{
    std::swap(_size, other._size);
    std::swap(_array, other._array);
    std::swap(_capacity, other._capacity);
    return *this;
}
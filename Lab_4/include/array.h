#pragma once
#include <memory>
#include <cstring>

template <typename T>
class Array {
    friend std::ostream &operator << (std::ostream& os, const Array<T> &arr) {
        if (arr.size() == 0) {
            throw std::range_error("can't print empty array");
        }
        os << '[';
        for (int i = 0; i < arr.size(); i++) {
            if (i != arr.size() - 1) {
                os << arr[i] << ", ";
            } else {
                os << arr[i] << ']';
            }
        }
        os << '\n';
        return os;
    }  
    private:
        int _size;
        int _capacity;
        std::unique_ptr<T[]> _array;
    public:
        Array();
        Array(const std::initializer_list<T> &list);
        Array(const Array &other);
        Array(Array &&other) noexcept;
        ~Array() = default;

        T & operator[] (const size_t &index) const;
        size_t size() const;

        void push_back(const T &el);
        void erase(const size_t &idx);
        void pop_back();

        Array<T> &operator=(const Array<T> &other);
        Array<T> &operator=(Array<T> &&other) noexcept;
};

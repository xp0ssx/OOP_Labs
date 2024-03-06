#include "array.h"

FigureArray::FigureArray() : _size(0), _capacity(0), _array(nullptr) {}

FigureArray::FigureArray(const std::initializer_list<Figure *> &l) {
    _size = l.size();
    _capacity = _size;
    _array = new Figure *[_size];
    size_t i = 0;
    for (Figure *f: l) {
        _array[i++] = f;
    }
}

FigureArray::FigureArray(const std::vector<Figure *> &v) {
    _size = v.size();
    _capacity = _size;
    _array = new Figure *[_size];
    size_t i = 0;
    for (Figure *f: v) {
        _array[i++] = f;
    }
}

void FigureArray::push_back(Figure *fig) {
    if (_size < _capacity) {
        _array[_size + 1] = fig;
    } else {
        Figure** newArray = new Figure*[_capacity + 1];
        std::memcpy(newArray, _array, _size * sizeof(Figure *));
        delete [] _array;
        _array = newArray;
        _size++; _capacity++;
        newArray[_size - 1] = fig;
    }
} 

std::ostream &operator << (std::ostream& os, const FigureArray &f) {
    if (f._size == 0) {
        throw std::range_error("can't print empty array");
    }
    for (size_t i = 0; i < f._size; ++i) {
        switch (f._array[i]->getPoints().size()) {
            case 3: std::cout << "Triangle\n"; break;
            case 6: std::cout << "Hexagon\n"; break;
            case 8: std::cout << "Octagon\n"; break;
        }
        std::cout << *(f._array[i]);
    }
    return os;
}

FigureArray::operator double(){
    if (_size == 0) {
        throw std::range_error("can't calculate sum of squares of empty arr");
    }
    double res = 0;
    for(int i = 0; i < _size; i++){
        res += double(*_array[i]);
    }
    return res;
}

void FigureArray::pop_back() {
    if (_size == 0) {
        throw std::range_error("can't pop from empty array");
    } else {
        _size--;
    }
}

void FigureArray::erase(size_t idx) {
    if (idx > _size) {
        throw std::range_error("index is bigger, than size");
    }
    for (size_t i = idx; i < _size - 1; i++) {
        _array[i] = _array[i+1];
    }
    _size--;
}

Figure** FigureArray::getArr() {
    return _array;
}

int FigureArray::getSize() {
    return _size;
}

int FigureArray::getCapacity() {
    return _capacity;
}
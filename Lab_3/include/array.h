#include "figure.h"
#include <cstring>
#ifndef ARRAY_H
#define ARRAY_H

class FigureArray final {
    Figure **_array;
    int _size;
    int _capacity;
public:
    FigureArray();
    FigureArray(const std::initializer_list<Figure *> &l);
    FigureArray(const std::vector<Figure *> &v);
    void push_back(Figure * fig);
    void erase(size_t idx);
    Figure** getArr();
    int getSize();
    int getCapacity();
    operator double();
    void pop_back();
    friend std::ostream &operator << (std::ostream& os, const FigureArray& f);
};

#endif

// [1,2,3,5,6,7,_]
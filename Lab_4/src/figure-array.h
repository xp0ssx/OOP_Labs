#pragma once
#include "figure.h"
#include "array.h"
#include "octagon.h"
#include "triangle.h"
#include "hexagon.h"

template <typename T>
double getAreas(const Array<Figure<T> *> & arrayFig) {
    double result = 0;
    for (size_t i = 0; i < arrayFig.size(); ++i) {
        result += double (*arrayFig[i]);
    }
    return result;
}

template <class T>
void getCenteres(const Array<Figure<T>*> & arrayFig) {
    for (size_t i = 0; i < arrayFig.size(); ++i) {
        std::cout << (*arrayFig[i]).getCenter() << ' ';
    }
    std::cout << std::endl;
}

template <class T>
void getCoords(const Array<Figure<T>*> & arrayFig) {
    for (size_t i = 0; i < arrayFig.size(); ++i) {
        std::cout << (*arrayFig[i]) << std::endl;    
    }
}


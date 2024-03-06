#include "list.h"
#include <map>
#include <vector>

int fact(int dig) {
    int res = 1;
    
    for (int i = 1; i <= dig; ++i) {
        res *= i; 
    }

    return res;
}

int main() {
    std::vector<int, PoolAllocator<int>> a;
    for (int i = 0; i < a.size(); i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
    for (int i = 0; i < a.size(); i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
    std::map<int, int, std::less<int>, PoolAllocator<std::pair<const int, int>>> test;
    for (size_t i = 0; i < 10; ++i) {
        test[i] = fact(i);
    }

    for (const auto &p : test) {
        std::cout << "Key: " << p.first << " Value: " << p.second << '\n';
    }

    List<int> l;
    l.emplace(3);
    l.emplace(2);
    l.emplace(1);
    l.emplace(0);
    l.remove();

    std::cout << l << std::endl;


    std::cout << "\tSTART\n";

    std::map<int, int, std::less<int>, PoolAllocator<std::pair<const int, int>>> allocTest;
    const size_t initialSize = 10000;
    for (size_t i = 0; i < initialSize; ++i) {
        allocTest[i] = i;
    }

    std::cout << "Map size after initial insertion: " << allocTest.size() << std::endl;
    const size_t elementsToRemove = 5000;
    for (size_t i = 0; i < elementsToRemove; ++i) {
        allocTest.erase(i);
    }

    std::cout << "Map size after removal: " << allocTest.size() << std::endl;
    const size_t additionalElements = 7000;
    for (size_t i = initialSize; i < initialSize + additionalElements; ++i) {
        allocTest[i] = i;
    }

    std::cout << "Map size after additional insertion: " << allocTest.size() << std::endl;
    for (size_t i = initialSize; i < allocTest.size(); ++i) {
        allocTest.erase(i);
    }

    std::cout << "Map size after removal: " << allocTest.size() << std::endl;
    const size_t additionalElements1 = 17000;
    for (size_t i = initialSize; i < initialSize + additionalElements1; ++i) {
        allocTest[i] = i;
    }

    std::cout << "Map size after additional insertion: " << allocTest.size() << std::endl;
    for (size_t i = initialSize; i < allocTest.size() - 10000; ++i) {
        allocTest.erase(i);
    }

    std::cout << "\tEND\n";
}
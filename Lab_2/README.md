
# Лабораторная работа 2. Классы
## Автор: Кудинов Д.В., группа М8О-212Б-22, вариант 1

Используя в качестве образца класс Array (см. ниже), реализовать динамические контейнеры с использованием динамического массива.
- Каждый класс должен быть разделен на интерфейс и реализацию.
- Самостоятельно определить необходимые типы, поля и дополнительные методы.
- Реализовать генерацию исключений в конструкторах и методах при необходимости (использовать стандартные исключения).
- Реализовать арифметические операции: сложение, вычитание, копирование
- Реализовать операции сравнения: (больше, меньше, равно).
- Арифметические операции с присваиванием должны быть реализованы как методы класса.

Создать класс Decimal для работы с беззнаковыми целыми одиннадцатиричными числами, используя для пред-
ставления числа массив из элементов типа unsigned char, каждый из которых является одиннадцатиричными
цифрой. Младшая цифра имеет меньший индекс (единицы – в нулевом элементе массива).
## Программы

### CMakeLists.txt
```
cmake_minimum_required(VERSION 3.10)

project(Lab_02)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp solve.cpp)

enable_testing()
add_executable(testing tests.cpp solve.cpp)
target_link_libraries(testing ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND testing)
### main.cpp
```

### main.cpp
```
#include "solve.h"

int main() {
    
    return 0;
}
```

### solve.h
```
#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <exception>
#include <math.h>
using namespace std;

bool IsDecimal(char value);

class Decimal {
private:
	size_t size;
	size_t capacity;
	char* digits;

	//Приватный метод реаллокации массива
	void reallocate(const size_t& newcapacity);
public:
	//Конструкторы
	Decimal();
	Decimal(const size_t& n, char t);
	Decimal(const initializer_list<char>& t);
	Decimal(const string& t);
	Decimal(const Decimal& other);
	Decimal(Decimal&& other) noexcept;

	//Дополнительные методы
    void Init(size_t n);
    void Err();
	size_t getsize() const;
	string getvalue() const;

	//Деструктор
	virtual ~Decimal() noexcept;

	//Оператор вывода
	friend ostream& operator << (ostream& out, Decimal& obj);

	//Арифметические операции
	void operator = (const Decimal&);
	void operator = (Decimal&&);
	void operator += (const Decimal&);
	void operator -= (const Decimal&);
	friend Decimal operator + (const Decimal&, const Decimal&);
	friend Decimal operator - (const Decimal&, const Decimal&);

	//Логические операторы
	friend bool operator == (const Decimal&, const Decimal&);
	friend bool operator != (const Decimal&, const Decimal&);
	friend bool operator < (const Decimal&, const Decimal&);
	friend bool operator <= (const Decimal&, const Decimal&);
	friend bool operator > (const Decimal&, const Decimal&);
	friend bool operator >= (const Decimal&, const Decimal&);
};
```

### solve.cpp
```
#include "solve.h"

bool IsDecimal(char value) {
	return (value >= '0' && value <= '9');
}

void Decimal::Init(size_t n) {
	size = n;
	capacity = size;
	digits = new char[capacity];
    for(int i = 0 ; i < n; ++i) 
        digits[i] = i + '0';
}

void Decimal::Err() {
    if (digits != nullptr) {
        size = 0;
        capacity = 0;
        delete[] digits;
        digits = nullptr;
    }
    throw logic_error("This digit doesn't belong to Decimal system");
}

Decimal::~Decimal() noexcept {
    if (digits != nullptr) {
        size = 0;
        capacity = 0;
        delete[] digits;
        digits = nullptr;
    }
}

Decimal::Decimal() : size(0), capacity(0), digits{ nullptr } {}

Decimal::Decimal(const size_t& n, char t) {
    Decimal();
	if (!IsDecimal(t))
		Err();
	Init(n);
	for (int i = 0; i < size; ++i)
		digits[i] = t;
}

Decimal::Decimal(const string& t) {
    Decimal();
	for (char elem : t) 
        if (!IsDecimal(elem)) Err();
	Init(t.size());
	for (size_t i = 0; i < size; ++i)
		digits[i] = t[size - i - 1];
}

Decimal::Decimal(const initializer_list<char> &t) {
    Decimal();
	for (char elem : t) 
        if (!IsDecimal(elem)) Err();
	Init(t.size());
    int i = size - 1;
    for(char c : t) {
        digits[i] = c;
        --i;
    }
}

Decimal::Decimal(const Decimal& other) {
	size = other.size;
	capacity = other.capacity;
	digits = new char[capacity];
	for (size_t i = 0; i < size; ++i)
		digits[i] = other.digits[i];
}

Decimal::Decimal(Decimal&& other)noexcept {
	size = other.size;
	capacity = other.capacity;
	digits = other.digits;
	other.size = 0;
	other.capacity = 0;
	other.digits = nullptr;
}

void Decimal::reallocate( const size_t& newcapacity) {
	char* newArray = new char[newcapacity];
	capacity = newcapacity;
	for (size_t i = 0; i < size; ++i)
		newArray[i] = digits[i];
	for (size_t i = size; i < capacity; ++i)
        newArray[i] = '0';  
	delete[] digits;
	digits = newArray;
}

size_t Decimal::getsize() const {
	return size;
}

string Decimal::getvalue()const {
	string s, ans;
	for (size_t i = 0; i < size; ++i)
		s += digits[i];
	for (int i = 0; i < size; ++i)
		ans += s[size - i - 1];
	return ans;
}

ostream& operator << (ostream& out, Decimal& obj) {
    if(obj.size == 0) {
        out << 0;
        return out;
    }
	for (int i = obj.size - 1; i >= 0; --i)
		out << obj.digits[i];
	return out;
}

void Decimal::operator = (const Decimal& other) {
	if (capacity < other.capacity)
		reallocate(other.capacity);
	size = other.size;
	for (size_t i = 0; i < size; ++i)
		digits[i] = other.digits[i];
}

void Decimal::operator = (Decimal&& other) {
	size = other.size;
	capacity = other.capacity;
	delete[] digits;
	digits = other.digits;

	other.digits = nullptr;
	other.capacity = 0;
	other.size = 0;
}

void Decimal::operator += (const Decimal& other) {
	reallocate(max(other.capacity, capacity) + 1);
	int del = 0;
	for (int i = 0; i < capacity; ++i) {
        char c;
        if(i < other.size) c = other.digits[i];
        else c = '0';
		del += digits[i] + c - 2 * '0';
		digits[i] = del % 10 + '0';
		del /= 10;
		if (digits[i] != '0') size = i + 1;
	}
}

void Decimal::operator -= (const Decimal& other) {
	if (size < other.size) {
		throw logic_error("The size of left value is less than size of right value");
	}
	reallocate(size + 1);

	for (int i = 0; i < capacity; ++i) {

        char c;
        if(i < other.size) c = other.digits[i];
        else c = '0';
		if (digits[i] < c) {
			digits[i] += 10;
			digits[i + 1] -= 1;
		}
		digits[i] = digits[i] - c + '0';
    }
    	
	if (digits[capacity - 1] < '0')
		throw logic_error("The size of left value is less than size of right value");
    size = 1;
	for (int i = 0; i < capacity; ++i) {
		if (digits[i] != '0') size = i + 1;
    }
}

Decimal operator + (const Decimal& l, const Decimal& r) {
	Decimal ans = l;
	ans += r;
	return ans;
}

Decimal operator - (const Decimal& l, const Decimal& r) {
	Decimal ans = l;
	ans -= r;
	return ans;
}

bool operator == (const Decimal& l, const Decimal& r) {
	if (l.size != r.size) return 0;
	for (int i = 0; i < l.size; ++i) {
		if (l.digits[i] != r.digits[i]) return 0;
	}
	return 1;
}

bool operator != (const Decimal& l, const Decimal& r) {
	return !(l == r);
}

bool operator < (const Decimal& l, const Decimal& r) {
	if (l.size != r.size) return l.size < r.size;

	for (int i = l.size - 1; i >= 0; --i) {
		if (l.digits[i] != r.digits[i]) return l.digits[i] < r.digits[i];
	}
	return 0;
}

bool operator > (const Decimal& l, const Decimal& r) {
	return (r < l) && (l != r);
}

bool operator >= (const Decimal& l, const Decimal& r) {
	return l > r || l == r;
}

bool operator <= (const Decimal& l, const Decimal& r) {
	return l < r || l == r;
}
```

### tests.cpp
```
#include <gtest/gtest.h>
#include "solve.h"

TEST(test_01, test) {
    string s = "321";
    string z = "963";
    Decimal a(s);
    Decimal b(z);
    a += b;
    ASSERT_EQ(a.getvalue(), "1284");
}

TEST(test_02, test) {
    string s = "321";
    Decimal a(s);
    Decimal b(s);
    a -= b;
    ASSERT_EQ(a.getvalue(), "0");
}

TEST(test_03, test) {
    string s = "321";
    Decimal a(s);
    Decimal b;
    b = a;
    ASSERT_EQ(b.getvalue(), s);
}

TEST(test_04, test) {
    string s = "321";
    Decimal a(s);
    Decimal b(s);
    a += b;
    ASSERT_EQ(a.getvalue(),"642");
}

TEST(test_05, test) {
    string s = "0";
    Decimal a(s);
    Decimal b(s);
    a += b;
    ASSERT_EQ(a.getvalue(),"0");
}

TEST(test_06, test) {
    string s = "0";
    Decimal a(s);
    Decimal b(s);
    a -= b;
    ASSERT_EQ(a.getvalue(),"0");
}

TEST(test_07, test) {
    string s = "123";
    string z = "1";
    Decimal a(s);
    Decimal b(z);
    a -= b;
    ASSERT_EQ(a.getvalue(),"122");
}

TEST(test_08, test) {
    string s = "123";
    Decimal a;
    Decimal b(s);
    ASSERT_ANY_THROW(a - b);
}

TEST(test_09, test) {
    string s = "123";
    Decimal a;
    Decimal b(s);
    ASSERT_ANY_THROW(a -= b);
}

TEST(test_10, test) {
    ASSERT_ANY_THROW(Decimal ("$"));
}

TEST(test_11, test) {
    string s = "124";
    string z = "123";
    Decimal a(s);
    Decimal b(z);
    ASSERT_TRUE(a > b);
}

TEST(test_12, test) {
    string s = "123";
    string z = "123";
    Decimal a(s);
    Decimal b(z);
    ASSERT_TRUE(a == b);
}

TEST(test_13, test) {
    string s = "123";
    string z = "123";
    Decimal a(s);
    Decimal b(z);
    ASSERT_TRUE(a <= b);
}

TEST(test_14, test) {
    string s = "123";
    string z = "123";
    Decimal a(s);
    Decimal b(z);
    ASSERT_TRUE(a >= b);
}

TEST(test_15, test) {
    string s = "125";
    string z = "123";
    Decimal a(s);
    Decimal b(z);
    ASSERT_TRUE(a > b);
}

TEST(test_16, test) {
    string s = "125";
    Decimal a(s);
    Decimal b;
    ASSERT_TRUE(a > b);
}

TEST(test_17, test) {
    Decimal a("444"), b("44444");
    ASSERT_ANY_THROW(a -= b);
}

TEST(test_18, test) {
    Decimal a("444"), b("44444");
    ASSERT_ANY_THROW(a - b);
}

TEST(test_19, test) {
    ASSERT_ANY_THROW(Decimal("2A"));
}

TEST(test_20, test) {
    Decimal a("444");
    ASSERT_ANY_THROW(Decimal("0") - a);
}

TEST(test_21, test) {
    ASSERT_TRUE(Decimal("0") - Decimal("0") == Decimal("0"));
}

TEST(test_22, test) {
    ASSERT_TRUE(Decimal("0") + Decimal("0") == Decimal("0"));
}

TEST(test_23, test) {
    Decimal a("0");
    ASSERT_TRUE(Decimal("0") == a);
}

TEST(test_24, test) {
    string s = "12";
    Decimal a("134");
    ASSERT_TRUE(Decimal("146") - a == Decimal(s));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

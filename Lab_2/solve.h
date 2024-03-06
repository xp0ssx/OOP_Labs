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

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

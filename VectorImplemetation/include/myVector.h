#ifndef _MY_VECTOR_H_
#define _MY_VECTOR_H_

#include <memory>
#include <climits>
#include <cstring>

struct data_t{
    int number;
    char *aString;
};

class MyVector{
    private:
        data_t* ptr;
        size_t len;
        size_t capacity;
    public:
        // Specail member functions:
        MyVector();
        ~MyVector();
        MyVector(const MyVector &);
        MyVector(MyVector &&);
        MyVector &operator=(const MyVector &);
        MyVector &operator=(MyVector &&);
        // Member access:
        data_t &operator[](int);
        data_t front();
        data_t back();
        // Capacity:
        bool empty() const;
        size_t size() const;
        size_t maxsize() const;
        // Modifier:
        void clear();
        void insert(int index, const data_t &data);
        void erase(int index);
        void push_back(const data_t &data);
        void pop_back();
        void push_front(const data_t &data);
        void pop_front();
};

#endif
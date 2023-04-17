#include "myVector.h"

// Specail member functions:
MyVector::MyVector(){
    len = 0;
    capacity = 1;
    ptr = new data_t[capacity];
}

MyVector::~MyVector(){
    while (!empty())
        pop_back();
    delete [] ptr;
    ptr = nullptr;
}

MyVector::MyVector(const MyVector &sourceVec){
    len = sourceVec.len;
    capacity = sourceVec.capacity;
    ptr = new data_t[capacity];
    for(int i=0; i<len; i++){
        *(ptr + i) = *(sourceVec.ptr + i);
    }
}

MyVector::MyVector(MyVector &&sourceVec){
    len = sourceVec.len;
    capacity = sourceVec.capacity;
    ptr = sourceVec.ptr;
    sourceVec.ptr = nullptr;
}

MyVector &MyVector::operator=(const MyVector &sourceVec){
    len = sourceVec.len;
    capacity = sourceVec.capacity;
    ptr = new data_t[capacity];
    for(int i=0; i<len; i++){
        *(ptr + i) = *(sourceVec.ptr + i);
    }
    return *this;
}

MyVector &MyVector::operator=(MyVector &&sourceVec){
    len = sourceVec.len;
    capacity = sourceVec.capacity;
    ptr = sourceVec.ptr;
    sourceVec.ptr = nullptr;
    return *this;
}

// Member access:
data_t &MyVector::operator[](int index){
    return *(ptr + index);
}

data_t MyVector::front(){
    return *ptr;
}

data_t MyVector::back(){
    return *(ptr + len - 1);
}

// Capacity:
bool MyVector::empty() const{
    return len == 0;
}

size_t MyVector::size() const{
    return len;
}

size_t MyVector::maxsize() const{
    return PTRDIFF_MAX/sizeof(data_t);
}

// Modifier
void MyVector::clear(){
    while (!empty())
        pop_back();
    delete [] ptr; // delete data
    len = 0;
    capacity = 1;
    ptr = new data_t[capacity];
}

void MyVector::insert(int index, const data_t &data){
    if(len >= capacity){
        capacity *= 2;
        auto oldPtr{ptr};
        ptr = new data_t[capacity];
        for(int i=0; i<len; i++){
            *(ptr + i) = *(oldPtr + i);
        }
        delete oldPtr;
        oldPtr = nullptr;
    }
    ++len;
    for(int i=len-1; i > index; --i){
        *(ptr + i) = *(ptr + i -1);
    }
    data_t *insertedPtr = (ptr + index);
    insertedPtr->number = data.number;
    insertedPtr->aString = new char [strlen(data.aString) + 1];
    strcpy(insertedPtr->aString, data.aString);
}

void MyVector::erase(int index){
    for(int i=index; i<len-1; ++i){
        data_t *prevPos = ptr + i;
        data_t *nextPos = ptr + i + 1;
        prevPos->number = nextPos->number;
        delete [] prevPos->aString;
        prevPos->aString = new char[strlen(nextPos->aString) + 1];
        strcpy(prevPos->aString, nextPos->aString);
    }
    data_t *poppedPtr = (ptr + len - 1);
    delete [] poppedPtr->aString;
    poppedPtr->aString = nullptr;
    --len;
}

void MyVector::push_back(const data_t &data){
    if(len >= capacity){
        capacity *= 2;
        auto oldPtr{ptr};
        ptr = new data_t[capacity];
        for(int i=0; i<len; i++){
            data_t *oldData = oldPtr + i;
            data_t *newData = ptr + i;
            newData->number = oldData->number;
            newData->aString = new char[strlen(oldData->aString) + 1];
            strcpy(newData->aString, oldData->aString);
            delete [] oldData->aString;
            oldData->aString = nullptr;
        }
        delete [] oldPtr;
        oldPtr = nullptr;
    }
    ++len;
    data_t *pushedPtr = (ptr + len - 1);
    pushedPtr->number = data.number;
    pushedPtr->aString = new char [strlen(data.aString) + 1];
    strcpy(pushedPtr->aString, data.aString);
}

void MyVector::pop_back(){
    data_t *poppedPtr = (ptr + len - 1);
    delete [] poppedPtr->aString;
    poppedPtr->aString = nullptr;
    --len;
}

void MyVector::push_front(const data_t &data){
    insert(0, data);
}

void MyVector::pop_front(){
    erase(0);
}
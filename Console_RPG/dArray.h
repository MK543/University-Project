#ifndef CONSOLE_RPG_DARRAY_H
#define CONSOLE_RPG_DARRAY_H
#include <stdint.h>

template<typename T>
class dArray {
private:
    unsigned int cap;
    unsigned int nrOfEl;
    unsigned initialCap;
    T* *arr;

    void expand();
    void initialize(unsigned from);
public:
    dArray(unsigned size = 5);
    dArray(const dArray& obj);
    ~dArray();

    unsigned maxCap();
    unsigned size();

    T& operator[] (const unsigned index);
    void operator= (const dArray& obj);

    void push(const T element);
    void remove(const unsigned index, bool ordered = false);
};
template<typename T>
dArray<T>::dArray(unsigned size){
    this->initialCap = size;
    this->cap = size;
    this->nrOfEl = 0;
    this->arr = new T*[this->cap];
    this->initialize(0);
}

template<typename T>
dArray<T>::dArray(const dArray& obj){
    this->initialCap = obj.initialCap;
    this->cap = obj.cap;
    this->nrOfEl = obj.nrOfEl;
    this->arr = new T*[this->cap];
    for(size_t i = 0; i < this->nrOfEl; i++){
        this->arr[i] = new T(*obj.arr[i]);
    }
    this->initialize(0);
}

template<typename T>
dArray<T>::~dArray(){
    for(size_t i = 0; i < this->nrOfEl; i++){
        delete this->arr[i];
    }
    delete[] arr;
}

template<typename T>
unsigned int dArray<T>::maxCap() {
    return this->cap;
}


template<typename T>
unsigned int dArray<T>::size() {
    return this->nrOfEl;
}

template<typename T>
T& dArray<T>::operator[] (const unsigned index){
    if( index < 0 || index >= this->nrOfEl){
        throw "Index not in array range";
    }
    return *this->arr[index];
}

template<typename T>
void dArray<T>::operator= (const dArray& obj){
    for(size_t i = 0; i < this->nrOfEl; i++){
        delete this->arr[i];
    }
    delete[] arr;
    this->initialCap = obj.initialCap;
    this->cap = obj.cap;
    this->nrOfEl = obj.nrOfEl;
    this->arr = new T*[this->cap];
    for(size_t i = 0; i < this->nrOfEl; i++){
        this->arr[i] = new T(*obj.arr[i]);
    }
    this->initialize(0);
}

template<typename T>
void dArray<T>::push(const T element) {
    if(this->nrOfEl>= this->cap){
        this->expand();
    }
    this->arr[this->nrOfEl++] = new T(element);
}

template<typename T>
void dArray<T>::remove(const unsigned index, bool ordered){
    if(index < 0 || index >= nrOfEl){
        throw "Wrong index!";
    }
    if(ordered){
        delete this->arr[index];
        for (size_t i = 0; i < this->nrOfEl-1; i++) {
            this->arr[i] = this->arr[i+1];
        }
        this->arr[--this->nrOfEl] = nullptr;
    }
    else{
        delete this->arr[index];
        this->arr[index] = this->arr[this->nrOfEl - 1];
        this->arr[--this->nrOfEl] = nullptr;
    }
}

template<typename T>
void dArray<T>::expand(){
    this->cap *= 2;
    T* *tempArr = new T *[this->cap];
    for (size_t i = 0; i < this->nrOfEl; i++) {
        tempArr[i] = this->arr[i];
    }
    delete[]arr;
    this->arr = tempArr;
    this->initialize(this->nrOfEl);
}

template<typename T>
void dArray<T>::initialize(unsigned int from) {
    for (size_t i = from; i < this->cap; i++) {
        this->arr[i] = nullptr;
    }
}

#endif //CONSOLE_RPG_DARRAY_H

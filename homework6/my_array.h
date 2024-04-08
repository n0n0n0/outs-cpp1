#pragma once
#include <iostream>

namespace my_containers {

class Complex
{
private:
    /* data */
    float m_real;
    float m_im;
public:
    Complex() : m_real{0}, m_im{0} {
        Complex::dsCount = 0;
    }

    Complex(float real, float im) : m_real{real}, m_im{im} {
        Complex::dsCount = 0;
    }

    ~Complex() {
        ++dsCount;
        std::cout << "Complex::~Complex() destructor start! i: " << dsCount << "\n";
    }

    inline static size_t dsCount;
};

template <typename T>
class MyArray {
public:
    MyArray() : m_count{0} {
        m_data = nullptr;
    }
    
    explicit MyArray(size_t size) : m_count{size} {
        m_data = new T[size];
    }

    MyArray(const MyArray<T> &other) {
        std::cout << "MyArray::MyArray(const MyArray<T>) - copy constructor start \n";
        if(other.size() == 0 ) {
            m_data = nullptr;
            m_count = 0;
            return;
        }
        m_data = new T[other.size()];
        for(int i = 0; i < other.size(); i++) {
            m_data[i] = other[i];
        }

        m_count = other.size();
    }

    void push_back(T el) {
        T *tmp = new T[m_count + 1];
        for(size_t i = 0; i < m_count; i++) {
            tmp[i] = m_data[i];
        }
        tmp[m_count] = el;
        delete [] m_data;
        m_data = tmp;
        m_count++;
    }


    bool insert(T el, size_t pos) {
        if(pos > m_count) 
            return false;
        T *tmp = new T[m_count + 1];
        for(size_t i = 0; i < pos; i++) {
            tmp[i] = m_data[i];
        }
        tmp[pos] = el;
        for(size_t i = pos+1; i < m_count + 1; i++) {
            tmp[i] = m_data[i-1];
        }
        delete [] m_data;
        m_data = tmp;
        m_count++;
        
        return true;
    }

    size_t erase(size_t pos, size_t count) {
        if(count == 0 || count > m_count)
            return 0;
        size_t delCount;
        int remainsCount;
        if(pos + count > m_count) {
            delCount = (pos + count) - m_count;
            remainsCount = pos;
        } else {
            delCount = count;
            remainsCount = m_count - count;
        }
        T *tmp = new T[remainsCount];
        for(size_t i = 0; i<pos; i++) {
            tmp[i] = m_data[i];
        }
        if(remainsCount > pos) {
            for(size_t i = pos + count; i < m_count; i++) {
                tmp[i-delCount] = m_data[i];
            }
        }
        delete [] m_data;
        m_data = tmp;
        m_count = remainsCount;

        return delCount;
    }

    size_t size() const {
        return m_count;
    }

    bool isEmpty() const { return m_count == 0; }

    T& operator[] (size_t index) const {
        // index > m_count ?
        return m_data[index];
    }

    ~MyArray() {
        std::cout << "MyArray::~MyArray() - destructor start \n";
        delete [] m_data;
    }

private:
    T *m_data;
    size_t m_count;
};

}
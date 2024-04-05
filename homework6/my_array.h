#pragma once

namespace my_containers {

template <typename T>
class MyArray {
public:
    MyArray() : m_count{0} {
        m_data = nullptr;
    }
    
    explicit MyArray(size_t size) : m_count{size} {
        m_data = new T[size];
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

    T& operator[] (size_t index) const {
        // index > m_count ?
        return m_data[index];
    }

private:
    T *m_data;
    size_t m_count;
};

}
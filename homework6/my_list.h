#pragma once

namespace my_containers {

template <typename T>
struct ListNode {
    ListNode() : next{nullptr}, prev{nullptr} {}
    ListNode *next;
    ListNode *prev;
    T data;
};

template <typename T>
class MyList {
public:
    MyList() : m_count{0} {
        m_firstNode = nullptr;
        m_lastNode = nullptr;
    }

    bool push_back(T el) {
        ListNode<T> *tmp = new ListNode<T>;
        tmp->data = el;
        tmp->prev = m_lastNode;
        if(m_lastNode != nullptr)
            m_lastNode->next = tmp;
        m_lastNode = tmp;
        if(m_firstNode == nullptr)\
            m_firstNode = tmp;
        m_count++;

        return true;
    }


    bool insert(T el, size_t pos) {
        if(pos > m_count) 
            return false;
        if(pos == m_count) 
            return this->push_back(el);

        ListNode<T> *tmp = new ListNode<T>;
        tmp->data = el;

        if(pos == 0) {
            tmp->next = m_firstNode;
            m_firstNode->prev = tmp;
            m_firstNode = tmp;
        } else {
            ListNode<T> *it = m_firstNode;
            for(size_t i = 1; i < pos; i++) {
                it = it->next;
            }

            tmp->next = it->next;
            tmp->prev = it;
            it->next = tmp;
            if(tmp->next != nullptr) {
                tmp->next->prev = tmp;
            }
        }

        m_count++;
        
        return true;
    }

    size_t erase(size_t pos, size_t count) {
        // if(count == 0 || count > m_count)
        //     return 0;
        // size_t delCount;
        // int remainsCount;
        // if(pos + count > m_count) {
        //     delCount = (pos + count) - m_count;
        //     remainsCount = pos;
        // } else {
        //     delCount = count;
        //     remainsCount = m_count - count;
        // }
        // T *tmp = new T[remainsCount];
        // for(size_t i = 0; i<pos; i++) {
        //     tmp[i] = m_firstNode[i];
        // }
        // if(remainsCount > pos) {
        //     for(size_t i = pos + count; i < m_count; i++) {
        //         tmp[i-delCount] = m_firstNode[i];
        //     }
        // }
        // delete [] m_firstNode;
        // m_firstNode = tmp;
        // m_count = remainsCount;

        // return delCount;

        return 0;
    }

    size_t size() const {
        return m_count;
    }

    T& operator[] (size_t index) const {
        // index > m_count ?
        ListNode<T> *it = m_firstNode;
        for(size_t i = 0; i < index; i++) {
            it = it->next;
        }
        return it->data;
    }

private:
    ListNode<T> *m_firstNode, *m_lastNode;
    size_t m_count;
};

}
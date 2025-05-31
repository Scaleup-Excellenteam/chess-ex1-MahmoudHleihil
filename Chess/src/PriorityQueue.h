#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <stdexcept>

template <typename T>
class PriorityQueue {
private:
    std::vector<T> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    PriorityQueue();
    void push(const T& value);
    void pop();
    const T& top() const;
    bool empty() const;
    int size() const;
};

#endif

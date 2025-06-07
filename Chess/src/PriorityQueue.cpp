#include <stdexcept>
#include "PriorityQueue.h"

template <typename T>
PriorityQueue<T>::PriorityQueue() {}

template <typename T>
void PriorityQueue<T>::push(const T& value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

template <typename T>
void PriorityQueue<T>::pop() {
    if (heap.empty()) throw std::out_of_range("PriorityQueue is empty");
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) heapifyDown(0);
}

template <typename T>
const T& PriorityQueue<T>::top() const {
    if (heap.empty()) throw std::out_of_range("PriorityQueue is empty");
    return heap[0];
}

template <typename T>
bool PriorityQueue<T>::empty() const {
    return heap.empty();
}

template <typename T>
int PriorityQueue<T>::size() const {
    return heap.size();
}

template <typename T>
void PriorityQueue<T>::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index] < heap[parent]) {
            std::swap(heap[index], heap[parent]);
            index = parent;
        } else break;
    }
}

template <typename T>
void PriorityQueue<T>::heapifyDown(int index) {
    int left, right, smallest;
    while (true) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        smallest = index;

        if (left < heap.size() && heap[left] < heap[smallest])
            smallest = left;
        if (right < heap.size() && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            index = smallest;
        } else break;
    }
}

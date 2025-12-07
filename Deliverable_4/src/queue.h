#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

using namespace std;

// QueueNode: Node for queue's linked list implementation
// Similar to LinkedList Node but used specifically for FIFO operations
template <typename T>
struct QueueNode
{
    T data;          // Stores detection result or any data type
    QueueNode *next; // Points to next node in queue

    QueueNode(T val) : data(val), next(nullptr) {}
};

// Queue: FIFO (First In First Out) data structure
// Used by: Scanner to store detection results in order they're found
// Real-world analogy: Line at a store - first person in is first served
template <typename T>
class Queue
{
private:
    QueueNode<T> *front; // Points to first element (where we dequeue from)
    QueueNode<T> *rear;  // Points to last element (where we enqueue to)
    int size;            // Current number of elements

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {} // Start with empty queue

    // Enqueue: Add element to back of queue
    // Process: Create node → Link to rear → Update rear pointer
    void enqueue(T val)
    {
        QueueNode<T> *newNode = new QueueNode<T>(val);

        if (isEmpty())
        {
            // Special case: First element, front and rear both point to it
            front = rear = newNode;
        }
        else
        {
            // General case: Add to end, update rear
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    // Dequeue: Remove and return element from front of queue
    // Process: Save value → Update front → Delete old node → Return value
    T dequeue()
    {
        if (isEmpty())
        {
            throw runtime_error("Queue is empty!");
        }

        T val = front->data;        // Save the data before deleting node
        QueueNode<T> *temp = front; // Keep pointer to node we'll delete
        front = front->next;        // Move front to next element
        delete temp;                // Free memory of old front
        size--;

        return val;
    }

    // Check if queue is empty
    bool isEmpty() const
    {
        return size == 0;
    }

    int getSize() const
    {
        return size;
    }

    // Peek: Look at front element without removing it
    // Useful when you want to check what's next without processing it yet
    T peek() const
    {
        if (isEmpty())
        {
            throw runtime_error("Queue is empty!");
        }
        return front->data;
    }

    // Destructor: Clean up all nodes
    ~Queue()
    {
        while (!isEmpty())
        {
            dequeue(); // Remove each element, freeing its memory
        }
    }
};

#endif
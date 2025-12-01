#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T> // Template so the queue works with any data type
struct QueueNode
{                    // Structure representing a single node in the queue
    T data;          // Data stored in the node
    QueueNode *next; // Pointer to the next node in the queue

    QueueNode(T val) : data(val), next(nullptr) {} // Node constructor
};

template <typename T>

class Queue
{
private:
    QueueNode<T> *front; // Pointer to the first element in the queue
    QueueNode<T> *rear;  // Pointer to the last element in the queue
    int size;            // Number of elements currently in the queue
public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}; // Queue constructor (initially empty)

    // Insert a new value at the end of the queue
    void enqueue(T val)
    {
        QueueNode<T> *newNode = new QueueNode<T>(val); // Create a new node with given value
        if (isEmpty())
        {                           // If queue is empty
            front = rear = newNode; // Both front and rear point to the new node
        }
        else
        {
            rear->next = newNode; // Link last node to the new node
            rear = newNode;       // Update rear pointer
        }
        size++; // Increase queue size
    }

    // Remove and return the front element of the queue
    T dequeue()
    {
        if (isEmpty())
        { // Cannot dequeue from empty queue
            throw runtime_error("Queue is empty!");
        }
        T val = front->data;        // Store the front element
        QueueNode<T> *temp = front; // Temporary pointer to the node being removed
        front = front->next;        // Move front pointer to next element
        delete temp;                // Delete old front node
        size--;                     // Decrease queue size
        return val;                 // Return removed value
    }

    // Check if the queue is empty
    bool isEmpty() const
    {
        return size == 0;
    }

    // Return the number of elements in the queue
    int getSize() const
    {
        return size;
    }

    // Return the front value without removing it
    T peek() const
    {
        if (isEmpty())
        { // Cannot peek in an empty queue
            throw runtime_error("Queue is empty!");
        }
        return front->data; // Return front value
    }

    // Destructor to free all nodes when queue goes out of scope
    ~Queue()
    {
        while (!isEmpty())
        {              // Remove all items
            dequeue(); // Dequeue repeatedly to delete each node
        }
    };
};

#endif
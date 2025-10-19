#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>   // work for any datatype
struct QueueNode {      // QueueNode
    T data;             // store Data
    QueueNode* next;    // point to Next Node
    
    QueueNode(T val) : data(val), next(nullptr) {}  //constructor
};

template <typename T>

class queue
{
private:
    QueueNode<T>* front;    // pointer to First Queue
    QueueNode<T>* rear;     // pointer to Last Queue
    int size;               // Total items in Queue
public:
    queue() : front(nullptr), rear(nullptr), size(0) {};    // create a Queue, it starts empty

    void enqueue(T val){
        QueueNode<T>* newNode = new QueueNode<T>(val);      // Create a New Node
        if (isEmpty()){                                     // condition Queue not Empty
            front = rear = newNode;                         // front, rear are set to first node
        }
        else{
            rear->next = newNode;       // link current to next node
            rear = newNode;             // move pointer to next node
        }
        size++;
    }

    T dequeue() {
        if (isEmpty()){
            throw runtime_error("Queue is empty!");     // Error if Queue is Empty
        }
        T val = front->data;            // Store value of front to Val
        QueueNode<T>* temp = front;     // Save pointer to front node
        front = front->next;            // move next to next
        delete temp;                    // free old front 
        size--;
        return val;
    }

    bool isEmpty() const {              // checks if empty
        return size == 0;
    }

    int getSize() const {               // gets size
        return size;
    }

    T peek() const {                    // Look at front without removing
        if (isEmpty()) {                // error iff empty
            throw runtime_error("Queue is empty!");
        }
        return front->data;
    }

    ~queue(){
        while (!isEmpty()) {    // Condition Queue Not Empty
            dequeue();          // Remove and delete each node
        }
    };
};


#endif
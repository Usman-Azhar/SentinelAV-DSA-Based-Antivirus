#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

// Node structure - each node holds one piece of data
template <typename T>
struct Node
{
    T data;     // The actual data (in our case, virus signature string)
    Node *next; // Pointer to the next node in the list

    // Constructor - creates a new node with given value
    Node(T val) : data(val), next(nullptr) {}
};

// LinkedList class - manages a chain of nodes
template <typename T>
class LinkedList
{
private:
    Node<T> *head; // Points to the first node (start of list)
    int size;      // Tracks how many nodes we have

public:
    // Constructor - creates an empty list
    LinkedList() : head(nullptr), size(0) {}

    // Insert at the end of the list
    void insert(T value)
    {
        Node<T> *newNode = new Node<T>(value); // Create new node

        if (head == nullptr)
        {
            // If list is empty, new node becomes the head
            head = newNode;
        }
        else
        {
            // Traverse to the end and add new node there
            Node<T> *current = head;
            while (current->next != nullptr)
            {
                current = current->next; // Move to next node
            }
            current->next = newNode; // Link last node to new node
        }
        size++;
    }

    // Linear search - finds if a value exists in the list
    bool search(const T &value) const
    {
        Node<T> *current = head;

        // Walk through the list one node at a time
        while (current != nullptr)
        {
            if (current->data == value)
            {
                return true; // Found it!
            }
            current = current->next; // Move to next node
        }
        return false; // Not found after checking all nodes
    }

    // Recursive search - alternative way to search
    bool searchRecursive(const T &value) const
    {
        return searchHelper(head, value);
    }

    // Display all elements in the list
    void display() const
    {
        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }

        Node<T> *current = head;
        cout << "Signatures in database: ";
        while (current != nullptr)
        {
            cout << current->data;
            if (current->next != nullptr)
            {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << endl;
    }

    // Get the number of elements
    int getSize() const
    {
        return size;
    }

    // Check if list is empty
    bool isEmpty() const
    {
        return head == nullptr;
    }

    // Get element at specific position (for iteration)
    T getAt(int index) const
    {
        if (index < 0 || index >= size)
        {
            throw out_of_range("Index out of bounds");
        }

        Node<T> *current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->data;
    }

    // Destructor - cleans up all nodes to prevent memory leaks
    ~LinkedList()
    {
        Node<T> *current = head;
        while (current != nullptr)
        {
            Node<T> *temp = current;
            current = current->next;
            delete temp; // Free memory for each node
        }
    }

private:
    // Helper function for recursive search
    bool searchHelper(Node<T> *node, const T &value) const
    {
        // Base case: reached end of list
        if (node == nullptr)
        {
            return false;
        }

        // Base case: found the value
        if (node->data == value)
        {
            return true;
        }

        // Recursive case: search in the rest of the list
        return searchHelper(node->next, value);
    }
};

#endif
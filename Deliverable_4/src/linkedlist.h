#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

// Node: Building block of linked list - each node holds data + pointer to next
template <typename T>
struct Node
{
    T data;     // Stores the actual value (string, Signature, etc.)
    Node *next; // Points to the next node in the chain (nullptr if last)

    // Constructor: Initialize node with data, next starts as nullptr
    Node(T val) : data(val), next(nullptr) {}
};

// LinkedList: Dynamic list that grows/shrinks as needed
// Used by: SignatureDB (D2), HashTable (for chaining)
// Advantage: Dynamic size, easy insertion
// Disadvantage: Slow search O(n)
template <typename T>
class LinkedList
{
private:
    Node<T> *head; // Points to first node (nullptr if empty)
    int size;      // Tracks total number of nodes

public:
    // Constructor: Create empty list
    LinkedList() : head(nullptr), size(0) {}

    // Insert at end: Traverse to last node and append new node
    // Time complexity: O(n) due to traversal
    void insert(T value)
    {
        Node<T> *newNode = new Node<T>(value);

        if (head == nullptr)
        {
            // Special case: Empty list, new node becomes head
            head = newNode;
        }
        else
        {
            // General case: Walk to end, then link new node
            Node<T> *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    // Linear search: Check each node one by one
    // Time complexity: O(n) - worst case checks all nodes
    // Used by: Old D2 virus scanning method
    bool search(const T &value) const
    {
        Node<T> *current = head;

        while (current != nullptr)
        {
            if (current->data == value)
            {
                return true; // Found!
            }
            current = current->next;
        }
        return false; // Reached end without finding
    }

    // Recursive search: Alternative approach using function calls
    // Demonstrates recursion concept but same O(n) complexity
    bool searchRecursive(const T &value) const
    {
        return searchHelper(head, value);
    }

    // Display: Print all elements in order
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

    int getSize() const
    {
        return size;
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }

    // Get element at specific position (for iteration in HashTable)
    // Time complexity: O(n) for position n
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

    // Destructor: Clean up all nodes to prevent memory leaks
    // Called automatically when LinkedList object is destroyed
    ~LinkedList()
    {
        Node<T> *current = head;
        while (current != nullptr)
        {
            Node<T> *temp = current;
            current = current->next;
            delete temp; // Free memory for this node
        }
    }

private:
    // Helper for recursive search
    // Base cases: (1) nullptr = not found, (2) match = found
    // Recursive case: Check rest of list
    bool searchHelper(Node<T> *node, const T &value) const
    {
        if (node == nullptr)
        {
            return false; // Base: reached end
        }

        if (node->data == value)
        {
            return true; // Base: found match
        }

        // Recursive: search remaining nodes
        return searchHelper(node->next, value);
    }
};

#endif
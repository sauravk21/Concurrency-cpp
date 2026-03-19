#include <iostream>


template <typename T>
struct Node {
    T data;           
    Node* next;      
    
   
    Node() : data(T()), next(nullptr) {}
    
    Node(const T& value) : data(value), next(nullptr) {}
    
    Node(const T& value, Node* nextNode) : data(value), next(nextNode) {}
};



template <typename T>
class LinkedList {
private:
    Node<T>* head;    // Pointer to the first node
    int size;         // Number of nodes in the list
    
public:
    // Constructor
    LinkedList() : head(nullptr), size(0) {}
    
    // Destructor - clean up all nodes
    ~LinkedList() {
        clear();
    }
    
    
    void pushFront(const T& value) {
        Node<T>* newNode = new Node<T>(value, head);
        head = newNode;
        size++;
    }
    
    
    void pushBack(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }
    
    
    void insertAt(int position, const T& value) {
        if (position < 0 || position > size) {
            std::cout << "Invalid position!" << std::endl;
            return;
        }
        
        if (position == 0) {
            pushFront(value);
            return;
        }
        
        Node<T>* current = head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        
        Node<T>* newNode = new Node<T>(value, current->next);
        current->next = newNode;
        size++;
    }
    
    
    void popFront() {
        if (head == nullptr) {
            return;
        }
        
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
    }
    

    void popBack() {
        if (head == nullptr) {
            return;
        }
        
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
        } else {
            Node<T>* current = head;
            while (current->next->next != nullptr) {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
        size--;
    }
    
    
    void deleteAt(int position) {
        if (position < 0 || position >= size || head == nullptr) {
            std::cout << "Invalid position!" << std::endl;
            return;
        }
        
        if (position == 0) {
            popFront();
            return;
        }
        
        Node<T>* current = head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        
        Node<T>* temp = current->next;
        current->next = temp->next;
        delete temp;
        size--;
    }
    
    // Search for a value
    bool search(const T& value) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    
    T& getAt(int position) {
        if (position < 0 || position >= size) {
            throw std::out_of_range("Index out of range");
        }
        
        Node<T>* current = head;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        return current->data;
    }
    
   
    void display() {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) {
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
    
   
    int getSize() const {
        return size;
    }
    
  
    bool isEmpty() const {
        return head == nullptr;
    }
    
   
    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }
};
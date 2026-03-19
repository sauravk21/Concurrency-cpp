#include <iostream>
#include <utility> 

template<typename T>
class SimpleUniquePtr {
private:
    T* ptr;

public:
    
    explicit SimpleUniquePtr(T* p = nullptr) : ptr(p) {}
    
   
    ~SimpleUniquePtr() {
        delete ptr;
    }
    
    
    SimpleUniquePtr(const SimpleUniquePtr&) = delete;
    SimpleUniquePtr& operator=(const SimpleUniquePtr&) = delete;
    
    
    SimpleUniquePtr(SimpleUniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    
    
    SimpleUniquePtr& operator=(SimpleUniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;           // Delete current resource
            ptr = other.ptr;       // Transfer ownership
            other.ptr = nullptr;   // Leave other in valid state
        }
        return *this;
    }
    
    
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    
    
    T* get() const { return ptr; }
    
    
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }
    
    
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
    
    
    explicit operator bool() const { return ptr != nullptr; }
};

// Example usage
void uniquePtrExample() {
    SimpleUniquePtr<int> p1(new int(42));
    std::cout << "p1 value: " << *p1 << std::endl;
    
    // p2 = p1; // ERROR: copy not allowed
    
    SimpleUniquePtr<int> p2 = std::move(p1); // Move ownership
    std::cout << "p2 value: " << *p2 << std::endl;
    // p1 is now empty
    
    if (!p1) {
        std::cout << "p1 is empty" << std::endl;
    }
    
    int* raw = p2.release(); 
    delete raw; 
}
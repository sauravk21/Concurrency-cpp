#include <iostream>
#include <stdexcept>
#include <algorithm>

template<typename T>
class DynamicArray {
private:
    T* data;
    size_t sz;        
    size_t cap;       

public:
    
    DynamicArray() : data(nullptr), sz(0), cap(0) {}
    

    ~DynamicArray() {
        clear();
        operator delete(data);
    }
    
    
    DynamicArray(const DynamicArray& other) : data(nullptr), sz(0), cap(0) {
        if (other.sz > 0) {
            T* new_data = static_cast<T*>(operator new(other.cap * sizeof(T)));
            size_t i = 0;
            try {
                for (; i < other.sz; ++i) {
                    new (&new_data[i]) T(other.data[i]);
                }
            } catch (...) {
                // Cleanup constructed elements
                for (size_t j = 0; j < i; ++j) {
                    new_data[j].~T();
                }
                operator delete(new_data);
                throw; // Re-throw to maintain strong guarantee
            }
            data = new_data;
            sz = other.sz;
            cap = other.cap;
        }
    }
    
    // Copy assignment (strong exception safety)
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            DynamicArray temp(other); // Copy construct
            swap(temp);               // Swap with temporary
        }
        return *this;
    }
    
    
    DynamicArray(DynamicArray&& other) noexcept 
        : data(other.data), sz(other.sz), cap(other.cap) {
        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
    }
    
   
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            clear();
            operator delete(data);
            
            data = other.data;
            sz = other.sz;
            cap = other.cap;
            
            other.data = nullptr;
            other.sz = 0;
            other.cap = 0;
        }
        return *this;
    }
    
    // Reserve capacity (strong exception safety)
    void reserve(size_t new_cap) {
        if (new_cap <= cap) return;
        
        T* new_data = static_cast<T*>(operator new(new_cap * sizeof(T)));

        int* new_deta = static_cast<int*>(operator new(new_cap * sizeof(int)));

        size_t i = 0;
        try {
            for (; i < sz; ++i) {
                new (&new_data[i]) T(data[i]);
            }
        } catch (...) {
            for (size_t j = 0; j < i; ++j) {
                new_data[j].~T();
            }
            operator delete(new_data);
            throw; // Maintain strong guarantee
        }
        
        
        for (size_t j = 0; j < sz; ++j) {
            data[j].~T();
        }
        operator delete(data);
        
        data = new_data;
        cap = new_cap;
    }
    
    
    void push_back(const T& value) {
        if (sz >= cap) {
            reserve(cap == 0 ? 1 : cap * 2);
        }
        new (&data[sz]) T(value);
        ++sz;
    }
    
    // Pop back
    void pop_back() {
        if (sz > 0) {
            --sz;
            data[sz].~T();
        }
    }
    
    // Clear all elements
    void clear() noexcept {
        for (size_t i = 0; i < sz; ++i) {
            data[i].~T();
        }
        sz = 0;
    }
    
    
    void swap(DynamicArray& other) noexcept {
        std::swap(data, other.data);
        std::swap(sz, other.sz);
        std::swap(cap, other.cap);
    }
    
    
    T& operator[](size_t index) {
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        return data[index];
    }
    
    
    T& at(size_t index) {
        if (index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    const T& at(size_t index) const {
        if (index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    
    size_t size() const { return sz; }
    size_t capacity() const { return cap; }
    bool empty() const { return sz == 0; }
    
 
    T* begin() { return data; }
    T* end() { return data + sz; }
    const T* begin() const { return data; }
    const T* end() const { return data + sz; }
};

int main() {
    try {
        DynamicArray<int> arr;
        
        
        arr.push_back(10);
        arr.push_back(20);
        arr.push_back(30);
        
        std::cout << "Size: " << arr.size() << ", Capacity: " << arr.capacity() << std::endl;
        
        
        arr.reserve(10);
        std::cout << "After reserve(10) - Capacity: " << arr.capacity() << std::endl;
        
        
        DynamicArray<int> arr2 = arr;
        arr2.push_back(40);
        
        
        DynamicArray<int> arr3;
        arr3 = arr2;
        
        
        std::cout << "arr: ";
        for (const auto& val : arr) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
        
        std::cout << "arr2: ";
        for (const auto& val : arr2) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
        
        
        std::cout << "Element at index 1: " << arr.at(1) << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}
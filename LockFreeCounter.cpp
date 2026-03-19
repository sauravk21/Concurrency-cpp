#include <atomic>

class LockFreeCounter {
private:
    std::atomic<int> counter_{0};
    
public:
    // Increment and return new value
    int increment() {
        return ++counter_;
    }
    
    // Decrement and return new value
    int decrement() {
        return --counter_;
    }
    
    // Add value and return new value
    int add(int value) {
        return counter_ += value;
    }
    
    // Get current value (atomic load)
    int get() const {
        return counter_.load(std::memory_order_acquire);
    }
    
    // Set to a specific value
    void set(int value) {
        counter_.store(value, std::memory_order_release);
    }
    
    // Compare and exchange
    bool compare_exchange(int expected, int desired) {
        return counter_.compare_exchange_strong(expected, desired);
    }
};
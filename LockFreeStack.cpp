template<typename T>
class LockFreeStack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    std::atomic<Node*> head{nullptr};

public:
    void push(const T& value) {
        Node* new_node = new Node(value);
        new_node->next = head.load();

        // Because another thread might change head between your load and your update.
        // If that happens and you don’t retry → you lose data or corrupt the stack.
        //bool compare_exchange_weak(expected, desired);

        /*if (head == expected)
        head = desired;
          else
        expected = head;   // update expected with current value*/

        while (!head.compare_exchange_weak(new_node->next, new_node)) {
        }
    }

    bool pop(T& result) {
        Node* old_head = head.load();

        // Because another thread might change head between your load and your update.
        // If that happens and you don’t retry → you lose data or corrupt the stack.
        while (old_head && !head.compare_exchange_weak(old_head, old_head->next)) {
        }

        if (!old_head) return false;

        result = old_head->data;
        delete old_head; // unsafe in production (ABA issue)
        return true;
    }
};
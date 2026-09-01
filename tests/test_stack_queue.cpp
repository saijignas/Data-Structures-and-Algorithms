#include "../include/data_structures/stack_queue.h"
#include "../include/test_framework.h"

TEST_CASE("stack: push/pop is LIFO") {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    CHECK(s.pop() == 3);
    CHECK(s.pop() == 2);
    CHECK(s.pop() == 1);
    CHECK(s.empty());
}

TEST_CASE("stack: pop on empty stack throws") {
    Stack<int> s;
    bool threw = false;
    try {
        s.pop();
    } catch (const std::out_of_range&) {
        threw = true;
    }
    CHECK(threw);
}

TEST_CASE("stack: peek does not remove the top") {
    Stack<int> s;
    s.push(1);
    s.push(2);
    CHECK(s.peek() == 2);
    CHECK(s.size() == 2);
}

TEST_CASE("queue: enqueue/dequeue is FIFO") {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    CHECK(q.dequeue() == 1);
    CHECK(q.dequeue() == 2);
    CHECK(q.dequeue() == 3);
    CHECK(q.empty());
}

TEST_CASE("queue: dequeue on empty queue throws") {
    Queue<int> q;
    bool threw = false;
    try {
        q.dequeue();
    } catch (const std::out_of_range&) {
        threw = true;
    }
    CHECK(threw);
}

TEST_CASE("queue from two stacks: preserves FIFO order") {
    QueueFromStacks<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    CHECK(q.dequeue() == 1);
    q.enqueue(4);
    CHECK(q.dequeue() == 2);
    CHECK(q.dequeue() == 3);
    CHECK(q.dequeue() == 4);
    CHECK(q.empty());
}

TEST_CASE("queue from two stacks: interleaved enqueue/dequeue stays correct") {
    QueueFromStacks<int> q;
    q.enqueue(1);
    CHECK(q.dequeue() == 1);
    q.enqueue(2);
    q.enqueue(3);
    CHECK(q.dequeue() == 2);
    q.enqueue(4);
    CHECK(q.dequeue() == 3);
    CHECK(q.dequeue() == 4);
}

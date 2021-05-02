#include <iostream>
#include <cstring>
#include <string>

using namespace std;
#define MAX 2000001

class Queue {
private:
    int arr[MAX];
    int front;
    int rear;
public:
    Queue() {
        memset(arr, 0, sizeof(arr));
        this->front = 0;
        this->rear = 0;
    }

    void push(int x) {
        arr[rear++] = x;
    }

    int pop() {
        if (rear - front == 0)
            return -1;
        return arr[front++];
    }

    int size() {
        return rear - front;
    }

    bool empty() {
        if (rear - front == 0)
            return 1;
        else
            return 0;
    }

    int Front() {
        if (rear - front == 0)
            return -1;
        return arr[front];
    }

    int back() {
        if (rear - front == 0)
            return -1;
        return arr[rear - 1];
    }
};

int N, a;
string cmd;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    Queue q;
    while (N--) {
        cin >> cmd;

        if (cmd == "push") {
            cin >> a;
            q.push(a);
        } else if (cmd == "front")
            cout << q.Front() << '\n';
        else if (cmd == "back")
            cout << q.back() << "\n";
        else if (cmd == "size")
            cout << q.size() << "\n";
        else if (cmd == "pop")
            cout << q.pop() << "\n";
        else if (cmd == "empty")
            cout << q.empty() << "\n";
    }
    return 0;
}
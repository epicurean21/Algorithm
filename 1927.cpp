#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ll long long
#define rootindex 1

template<typename T>
class Heap {
private:
    vector<T> data;
    int heapSize;

public:
    Heap() {
        data.push_back(-1);
        heapSize = 0;
    }

    bool empty() {
        return heapSize == 0;
    }

    int size() {
        return heapSize;
    }

    void insert(T x)    // min-heap 기준 upheap sorting
    {
        data.push_back(x);
        heapSize++;
        int idx = heapSize;
        while (idx > rootindex) {
            if (data[idx] < data[idx / 2]) {
                T tmp = data[idx / 2];
                data[idx / 2] = data[idx];
                data[idx] = tmp;
            } else
                break;
            idx /= 2;
        }
    }

    void remove() {
        if (!empty()) {
            data[1] = data[heapSize--];    // 마지막 노드를 루트로
            data.pop_back();
            int idx = rootindex;

            while (idx * 2 <= heapSize) {
                int left = idx * 2;
                int right = idx * 2 + 1;
                int minindex;
                if (right <= heapSize) {
                    if (data[left] < data[right])
                        minindex = left;
                    else
                        minindex = right;
                } else
                    minindex = left;

                if (data[idx] > data[minindex]) {
                    T tmp = data[minindex];
                    data[minindex] = data[idx];
                    data[idx] = tmp;
                    idx = minindex;
                } else
                    break;
            }
        }
    }

    T Min() {
        if (empty())
            return 0;
        else
            return data[rootindex];
    }
};

int N;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    Heap<ll> myHeap;
    for (int i = 0; i < N; i++) {
        ll x;
        cin >> x;

        if (x == 0) {
            cout << myHeap.Min() << '\n';
            myHeap.remove();
        } else
            myHeap.insert(x);
    }
    return 0;
}
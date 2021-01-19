#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define ll long long
#define MAX 1000001
string P;
int K;
bool k[MAX];
vector<int> prime;
void Eratos() {
    for (int i = 2; i <= K; i++) {
        if (!k[i]) {
            prime.push_back(i);
            for (int j = i + i; j <= K; j += i)
                k[j] = true;
        }
    }
}

int relative(int p) {
    int tmp = 0;
    for (int i = 0; P[i]; i++) {
        tmp *= 10;
        tmp += P[i] - '0';
        tmp %= p;
    }
    return tmp;
}

int find() {
    for (int i = 0; i < prime.size(); i++) {
        if(prime[i] >= K) break;
        if (!relative(prime[i])) // 암호 P를 나누는 소수 존재
            return prime[i];
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> P >> K;
    Eratos(); // K 까지의 소수만 남김.
    int tmp = find();
    if (!tmp)
        cout << "GOOD\n";
    else
        cout << "BAD " << tmp << "\n";

    return 0;
}
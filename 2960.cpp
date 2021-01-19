#include <iostream>
using namespace std;
#define MAX 1001
int N, K, cnt;
bool prime[MAX];

int find() {
    for(int i = 2; i <= N; i++) {
        if(!prime[i]) {
            for(int j = i; j <= N; j += i) {
                if(prime[j]) continue;
                prime[j] = true;
                if(++cnt == K)
                    return j;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;

    int ans = find();
    cout << ans << "\n";
    return 0;
}
#include<iostream>
#include<cstring>

#define endl "\n"
#define MAX 16
#define INF 987654321
using namespace std;

int N, ans;
int map[MAX][MAX];
int Cost[MAX][1 << MAX];

int Min(int a, int b) {
    return a > b ? b : a;
}

int DFS(int Cur_Node, int Cur_Bit) {
    if (Cur_Bit == ans) {
        if (map[Cur_Node][0] == 0) return INF;
        else return map[Cur_Node][0];
    }

    if (Cost[Cur_Node][Cur_Bit] != -1) return Cost[Cur_Node][Cur_Bit];
    Cost[Cur_Node][Cur_Bit] = INF;

    for (int i = 0; i < N; i++) {
        if (map[Cur_Node][i] == 0) continue;
        if ((Cur_Bit & (1 << i)) == (1 << i)) continue;

        Cost[Cur_Node][Cur_Bit] = Min(Cost[Cur_Node][Cur_Bit], map[Cur_Node][i] + DFS(i, Cur_Bit | 1 << i));
    }
    return Cost[Cur_Node][Cur_Bit];
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> map[i][j];

    ans = (1 << N) - 1;
    memset(Cost, -1, sizeof(Cost));
    cout << DFS(0, 1) << '\n';

    return 0;
}

/**
 * 23796 2,147,483,648 게임
 * 구현, 시뮬레이션
 */
#include <iostream>
#include <queue>

using namespace std;
#define MAX 9
#define ll long long

ll map[MAX][MAX];
char oper;

void print_map() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << map[i][j] << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            cin >> map[i][j];

        cin >> oper;
        queue<ll> q;

        switch (oper) {
            case 'U':
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        ll cur = map[j][i];
                        if (cur == 0) continue;
                        q.push(cur);
                        map[j][i] = 0;
                    }

                    int idx = 0;

                    while(!q.empty()) {
                        ll cur = 0;
                        if (!q.empty()) {
                            cur = q.front();
                            q.pop();
                        }

                        ll next = 0;
                        if (!q.empty()) {
                            next = q.front();
                        }

                        if (cur == next) {
                            cur *= 2;
                            q.pop();
                            map[idx++][i] = cur;
                        } else {
                            map[idx++][i] = cur;
                        }
                    }
                }
                break;

                case 'D':
                    for (int i = 0; i < 8; i++) {
                        for (int j = 7; j >= 0; j--) {
                            ll cur = map[j][i];
                            if (cur == 0) continue;
                            q.push(cur);
                            map[j][i] = 0;
                        }

                        int idx = 7;

                        while(!q.empty()) {
                            ll cur = 0;
                            if (!q.empty()) {
                                cur = q.front();
                                q.pop();
                            }

                            ll next = 0;
                            if (!q.empty()) {
                                next = q.front();
                            }

                            if (cur == next) {
                                cur *= 2;
                                q.pop();
                                map[idx--][i] = cur;
                            } else {
                                map[idx--][i] = cur;
                            }
                        }
                    }
                    break;

                    case 'L':
                        for (int i = 0; i < 8; i++) {
                            for (int j = 0; j < 8; j++) {
                                ll cur = map[i][j];
                                if (cur == 0) continue;
                                q.push(cur);
                                map[i][j] = 0;
                            }

                            int idx = 0;

                            while(!q.empty()) {
                                ll cur = 0;
                                if (!q.empty()) {
                                    cur = q.front();
                                    q.pop();
                                }

                                ll next = 0;
                                if (!q.empty()) {
                                    next = q.front();
                                }

                                if (cur == next) {
                                    cur *= 2;
                                    q.pop();
                                    map[i][idx++] = cur;
                                } else {
                                    map[i][idx++] = cur;
                                }
                            }
                        }
                        break;

                        case 'R':
                            for (int i = 0; i < 8; i++) {
                                for (int j = 7; j >= 0; j--) {
                                    ll cur = map[i][j];
                                    if (cur == 0) continue;
                                    q.push(cur);
                                    map[i][j] = 0;
                                }

                                int idx = 7;

                                while(!q.empty()) {
                                    ll cur = 0;
                                    if (!q.empty()) {
                                        cur = q.front();
                                        q.pop();
                                    }

                                    ll next = 0;
                                    if (!q.empty()) {
                                        next = q.front();
                                    }

                                    if (cur == next) {
                                        cur *= 2;
                                        q.pop();
                                        map[i][idx--] = cur;
                                    } else {
                                        map[i][idx--] = cur;
                                    }
                                }
                            }
                            break;

                            default:
                                break;
        }

        print_map();
        return 0;
}
/*
0 0 2 0 2 4 0 0
256 32 256 0 256 256 256 4
0 0 0 0 0 0 0 8
8 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
2 4 2 4 4 2 0 0
0 16 0 0 0 0 0 16
0 8 4 2 2 0 0 0
L
 */
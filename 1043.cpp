#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 51
int N, M, P, person;
bool chk[MAX];
vector<vector<int>> party;
bool participate[MAX][MAX];
queue<int> q;

void changeState() {
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        for (int i = 0; i < M; i++) {
            if (participate[p][i]) {
                for (int j = 0; j < party[i].size(); j++) {
                    if (!chk[party[i][j]]) { // 새롭게 진실아는사람 발견데스
                        chk[party[i][j]] = true;
                        q.push(party[i][j]);
                    }
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> P;
    for (int i = 0; i < P; i++) {
        cin >> person;
        chk[person] = true;
    }


    party.resize(M + 1);
    for (int t = 0; t < M; t++) { // 파티 입력받음
        cin >> P;
        for (int i = 0; i < P; i++) {
            cin >> person;
            participate[person][t] = true; // 참여 기록
            party[t].emplace_back(person);
        }
    }

    for (int i = 0; i < M; i++) { // 여기서 진실 알고 있는 사람들 큐에 넣어줌
        vector<int> tmp;
        bool truth = false;
        for (int j = 0; j < party[i].size(); j++) {
            int cur = party[i][j];
            tmp.emplace_back(cur);
            if (chk[cur])
                truth = true;
        }

        if (truth) {
            for (int i = 0; i < tmp.size(); i++) {
                if (!chk[tmp[i]])
                    q.push(tmp[i]);
            }
        }
    }

    changeState();

    int cnt = 0;
    for (int i = 0; i < M; i++) { // 최종 구라깔수있는 파티 개수 구하기
        bool truth = false;
        for (int j = 0; j < party[i].size(); j++)
            if (chk[party[i][j]])
                truth = true;
        if (truth)
            cnt++;
    }

    cout << M - cnt << '\n';

    return 0;
}
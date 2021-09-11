#include <iostream>
#include <string>
#include <vector>

using namespace std;

int score1, score2, ans;
int arrow;
int arr[11], arr2[11];
vector<int> answer;
bool flag = false;

void sol(int i) {
    if (i == 11) {
        if (score2 - score1 > ans) {
            flag = true;
            ans = score2 - score1;
            answer.clear();
            for (int i = 0; i < 10; i++)
                answer.emplace_back(arr2[10 - i]);

            answer.emplace_back(arrow);
        }
        return;
    }
    if (arr[i]) {
        if (arrow >= arr[i] + 1) {
            score2 += i;
            arr2[i] = arr[i] + 1;
            arrow -= arr2[i];
            sol(i + 1);
            score2 -= i;
            arrow += arr2[i];
            arr2[i] = 0;
        }
        arr2[i] = 0;
        score1 += i;
        sol(i + 1);
        score1 -= i;
    } else {
        if (arrow > 0) {
            arrow--;
            arr2[i] = 1;
            score2 += i;
            sol(i + 1);
            arrow++;
            score2 -= i;
        }
        arr2[i] = 0;
        sol(i + 1);
    }
}

vector<int> solution(int n, vector<int> info) {
    arrow = n;
    for (int i = 0; i < 11; i++)
        arr[10 - i] = info[i];
    sol(1);
    if (!flag)
        answer.emplace_back(-1);

    return answer;
}

int main() {
    vector<int> v = {0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 3};
    v = solution(10, v);
    for (int x : v)
        cout << x << " ";

}
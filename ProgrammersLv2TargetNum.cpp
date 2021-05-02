#include <string>
#include <vector>
#include <iostream>

using namespace std;
#define MAX 1002
int count_num[MAX], targett = 3;
vector<int> numberss;

void dfs(int idx, int sum) {
    if (idx == numberss.size() - 1) {
        if (sum >= 0)
            count_num[sum]++;
        return;
    }

    for (int i = idx + 1; i < numberss.size(); i++) {
        int next = numberss[i];
        dfs(i, sum + next);
        dfs(i, sum - next);
        return;
    }
}

vector<int> numbers = {1, 1, 1, 1, 1};
int target = 3;

int solution() {
    int answer = 0;
    for (int i = 0; i < numbers.size(); i++)
        numberss.emplace_back(numbers[i]);
    dfs(-1, 0);
    answer = count_num[target];
    return answer;
}

int main() {
    cout << solution();
}
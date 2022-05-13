#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int dijkstra(int start, int end) {
    priority_queue<pair<int, pair<int, int>>> pq;

}

vector<vector<int>> solution(vector<vector<int>> rc, vector<string> operations) {
    vector<vector<int>> answer;
    int col = rc[0].size();
    int row = rc.size();
    int idx = 0;
    vector<int> rotateList;
    for (int i = 0; i < col; i++) {
        rotateList.emplace_back(rc[0][i]);
    }
    for (int i = 1; i < row; i++) {
        rotateList.emplace_back(rc[i][col-1]);
    }
    for (int i = col - 2; i >= 0; i--) {
        rotateList.emplace_back(rc[row - 1][i]);
    }
    for(int i = col - 2; i > 0; i--) {
        rotateList.emplace_back(rc[i][0]);
    }

    for(int i : rotateList)
        cout << i << " ";
    cout << "\n";

    for (string op: operations) {
        if (op == "Rotate") {
            idx--;
            if(idx < 0) {
                idx = rotateList.size()- 1;
            }
        } else if (op == "ShiftRow") {
            /*
             * 1 2 3 6 9 8 7 4
             * 7 8 9 3 6 5 4 1
             */
        }
    }


    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<int>> rc = {{1,2,3}, {4,5,6}, {7,8,9}};
    vector<string> operations = {"Rotate", "ShiftRow"};
    solution(rc, operations);
}
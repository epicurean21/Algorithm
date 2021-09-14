#include <iostream>
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;

    for (auto &i : skill) {
        int x_1 = i[2];
        int y_1 = i[1];
        int x_2 = i[4];
        int y_2 = i[3];
        int degree = i[5];

        if (i[0] == 1) { // 공격
            for (int j = y_1; j <= y_2; j++)
                for (int k = x_1; k <= x_2; k++)
                    board[j][k] -= degree;
        } else if (i[0] == 2) { // 회복
            for (int j = y_1; j <= y_2; j++)
                for (int k = x_1; k <= x_2; k++)
                    board[j][k] += degree;
        }
    }

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] >= 1)
                answer++;
        }
    }
    return answer;
}

int main() {
    vector<vector<int>> board = {{5, 5, 5, 5, 5},
                                 {5, 5, 5, 5, 5},
                                 {5, 5, 5, 5, 5},
                                 {5, 5, 5, 5, 5}};
    vector<vector<int>> skill = {{1, 0, 0, 3, 4, 4},
                                 {1, 2, 0, 2, 3, 2},
                                 {2, 1, 0, 3, 1, 2},
                                 {1, 0, 1, 3, 3, 1}};

    int sol = solution(board, skill);
    cout << sol << "\n";
}
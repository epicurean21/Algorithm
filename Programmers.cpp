#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

priority_queue<int> max_pq;
priority_queue<int, vector<int>, greater<int>> min_pq;
vector<string> operations = {"I -45", "I 653", "D 1", "I -642", "I 45", "I 97", "D 1", "D -1", "I 333"};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    /*for (int i = 0; i < operations.size(); i++) {
        char oper = operations[i][0];
        string number = "";
        int push_number = 0;
        if (oper == 'D') { // 삭제
            if (operations[i][2] == '1') { // 최댓값 삭제
                if (max_pq.empty()) continue;
                max_pq.pop();
                if(max_pq.empty()) {
                    while(!min_pq.empty())
                        min_pq.pop();
                }
            } else if (operations[i][2] == '-') { // 최솟값 삭제
                if (min_pq.empty()) continue;
                min_pq.pop();
                if(min_pq.empty()) {
                    while(!max_pq.empty())
                        max_pq.pop();
                }
            }
        } else {
            bool negative = false;
            int num_size = 0;
            if (operations[i][2] == '-') {
                negative = true;
                num_size = operations[i].size() - 3;
            } else {
                num_size = operations[i].size() - 2;
            }

            if (negative) {
                for (int j = 3; j < operations[i].size(); j++) {
                    number += operations[i][j];
                }
            } else {
                for (int j = 2; j < operations[i].size(); j++) {
                    number += operations[i][j];
                }
            }

            reverse(number.begin(), number.end());
            for (int i = 0; i < num_size; i++) {
                push_number += ((number[i] - '0') * pow(10, i));
            }
            if (negative)
                push_number *= -1;

            max_pq.push(push_number);
            min_pq.push(push_number);
        }
    }
    vector<int> answer;
    if (max_pq.empty() || min_pq.empty()) {
        answer.push_back(0);
        answer.push_back(0);
    } else {
        answer.push_back(max_pq.top());
        answer.push_back(min_pq.top());
    }*/
    vector<int> answer;
    vector<int> numbers;
    int max_idx = 0;
    for (int i = 0; i < operations.size(); i++) {
        sort(numbers.begin() + max_idx, numbers.end(), greater<int>());
        char oper = operations[i][0];
        string number = "";
        int push_number = 0;
        if (oper == 'D') { // 삭제
            if (operations[i][2] == '1') { // 최댓값 삭제
                if(numbers.size() - max_idx == 0) continue;
                max_idx++;
            } else if (operations[i][2] == '-') { // 최솟값 삭제
                if(numbers.size() == 0) continue;
                numbers.pop_back();
            }
        } else {
            bool negative = false;
            int num_size = 0;
            if (operations[i][2] == '-') {
                negative = true;
                num_size = operations[i].size() - 3;
            } else {
                num_size = operations[i].size() - 2;
            }

            if (negative) {
                for (int j = 3; j < operations[i].size(); j++) {
                    number += operations[i][j];
                }
            } else {
                for (int j = 2; j < operations[i].size(); j++) {
                    number += operations[i][j];
                }
            }

            reverse(number.begin(), number.end());
            for (int i = 0; i < num_size; i++) {
                push_number += ((number[i] - '0') * pow(10, i));
            }
            if (negative)
                push_number *= -1;

            numbers.push_back(push_number);
        }
    }
    sort(numbers.begin() + max_idx, numbers.end(), greater<int>());
    if(numbers.size() - max_idx == 0)
    {
        answer.push_back(0);
        answer.push_back(0);
    }else {
        answer.push_back(numbers[max_idx]);
        answer.push_back(numbers[numbers.size() - 1]);
    }
    for (int i = 0; i < answer.size(); i++) {
        cout << answer[i] << " ";
    }

    return 0;
}
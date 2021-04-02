#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <cstring>

using namespace std;
string word;
vector<string> input(8);
bool isLeaf[1001];

//출력은 루트 노드부터 차례대로 /로 구분하여..
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    input = {"1 BROWN 0",
             "2 CONY 0",
             "3 DOLL 1",
             "4 DOLL 2",
             "5 LARGE-BROWN 3",
             "6 SMALL-BROWN 3",
             "7 BLACK-CONY 4",
             "8 BROWN-CONY 4"};
    cin >> word;

    memset(isLeaf, true, sizeof(isLeaf));
    map<string, int> leaf;
    vector<pair<string, int>> node(input.size() + 1); // {특징, 부모노드} 번호

    // 들어온 data를 parsing 해서 사용하기 쉽게 변형..
    for (int i = 0; i < input.size(); i++) {

        int idx = 0;
        string tmp = "";

        for (int j = 0; j < input[i].size(); j++) {
            idx++;
            if (input[i][j] == ' ') break;
            tmp += input[i][j];
        }

        int id = stoi(tmp);

        string name = "";
        for (int j = idx; j < input[i].size(); j++) {
            idx++;
            if (input[i][j] == ' ') break;
            name.push_back(input[i][j]);
        }

        tmp = "";
        for (int j = idx; j < input[i].size(); j++) {
            tmp += input[i][j];
        }
        int par = stoi(tmp);

        //cout << id << " " << name << " " << par << '\n';
        node[id] = {name, par}; // 노드들 정보 입력

        // 검색은 leaf만 되니까 leaf인지 아닌지를 판단하기 위해
        isLeaf[par] = false;
        // 일단은 다 넣음
        leaf.insert({name, id});
    }

    // 검색 후보들
    vector<string> candidates;
    for (int i = 1; i < node.size(); i++) {
        if (isLeaf[i] == false) continue;

        candidates.push_back(node[i].first);
    }


    return 0;
}
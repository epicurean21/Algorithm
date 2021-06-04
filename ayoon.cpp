#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class information {
public:
    int path_distance;
    int predecessor;

    information() {
        path_distance = 1000000;
        predecessor = 0;
    }

    information(int _path_distance, char _status, int _predecessor) {
        path_distance = _path_distance;
        predecessor = _predecessor;
    }
};

int numbering[1000000]; // 지역번호에 해당하는 idx를 할당해주기 위한 배열 생성해주었다.
vector <vector <pair<int, int>>> graph;   // 2차원 vector
vector <pair<int, int>> subgraph;   // 2차원 vector graph를 생성하기 위해 만든 1차원 vector

string region_name[100001]; // region_name 배열, 지역번호에서 numbering을 거쳐야 올바른 index 접근이 가능하다.
bool Iswater[100001]; // 침수되어 있는지 여부를 저장한 배열, 지역번호에서 numbering을 거쳐야 올바른 index 접근이 가능하다.

struct CompareLength {   // 우선순위 큐에서 작은 것부터 pop되게 정렬하기 위한 함수
    bool operator()(pair<int, int> p1, pair<int, int> p2) {
        return p1.second > p2.second;
    }
};

priority_queue<pair<int, int>, vector<pair<int, int>>, CompareLength> pq;   // 지역번호와, distance를 넣어줄 우선순위 큐를 생성해주었다.

int main() {

    int n, m, q;
    cin >> n >> m >> q;
    int region_num1;
    int region_num2;
    int street_length;
    string name;
    bool water;
    char Q;   // 최단 거리 또는 경로 찾기에 대한 질의를 입력 받는 변수

    for (int i = 0; i < n; i++) {   // 데이터 입력받기, 지역 정보 받기
        cin >> region_num1 >> name >> water;

        // 2차원 벡터의 0번째 열에 입력 순서대로 지역정보를 넣어주었다.
        subgraph.push_back(make_pair(region_num1, 0));
        graph.push_back(subgraph);
        subgraph.pop_back();

        numbering[region_num1] = i; // 지역번호에 해당하는 idx를 할당해주었다.
        region_name[i] = name;  // region_name에 입력으로 받은 name을 저장해두었다. 지역번호에 대해서 numbering한 idx로 접근해야한다.
        Iswater[i] = water; // Iswater에 입력으로 받은 water을 저장해두었다. 지역번호에 대해서 numbering한 idx로 접근해야한다.
    }

    for (int i = 0; i < m; i++) {   // 데이터 입력받기, 간선 정보 받기
        cin >> region_num1 >> region_num2 >> street_length;
        graph[numbering[region_num1]].push_back(make_pair(region_num2, street_length));
        graph[numbering[region_num2]].push_back(make_pair(region_num1, street_length));

    }

    for (int i = 0; i < q; i++) {
        cin >> Q >> region_num1 >> region_num2;

        if (Q == 'A') { // 두 지역간의 최단 거리 찾기

            information* info = new information[100001];

            if (Iswater[numbering[region_num1]] == true || Iswater[numbering[region_num2]] == true) {   // 출발지나 목적지가 침수되어 있으면 "None"출력해준다.
                cout << "None\n";
            }
            else {
                int tree_cnt = 0;   // tree vertex 세는 변수

                info[numbering[region_num1]].path_distance = 0; // 출발지의 path_distancd를 0으로 초기화해주었다.
                pq.push(make_pair(region_num1, 0)); // 출발지를 pq에 담아주었다.

                int f_num;
                int f_distance;
                int t_num;
                int t_distance;

                bool check = false;
                while (!pq.empty()) {
                    t_num = pq.top().first; // pq안에서 path_distance가 가장 작은 region의 지역번호이다.
                    t_distance = pq.top().second;   // pq안에서 path_distance가 가장 작은 region의 path_distance이다.
                    pq.pop();   // pq안에서 path_distance가 가장 작은 pair를 pop해준다.

                    if (Iswater[numbering[t_num]] == true) {    // 꺼낸 region이 침수되어 있으면 아무것도 하지않고 continue해준다.
                        continue;
                    }
                    if (pq.size() != 0 && t_distance == pq.top().second) {   // 최단 거리가 동일한 후보 정점 존재한다면 지역번호가 작은 순으로 뽑아준다.
                        if (t_num > pq.top().first) {
                            pq.push(make_pair(t_num, t_distance));
                            continue;
                        }
                    }
                    if (info[numbering[t_num]].path_distance < t_distance) {    // 꺼낸 region의 path_distance(t_distance)가 이미 저장되어 있는 path_distance보다 더 크다면 continue해준다.
                        continue;
                    }

                    tree_cnt++; // tree vertex의 수를 1 증가시켜준다.

                    if (t_num == region_num2) { // 꺼낸 region의 region_num이 목적지의 region_num과 같은 경우이다. 즉, 목적지에 도착하였을 경우이다.
                        if (info[numbering[t_num]].path_distance >= 1000000) {  // 최단 거리가 1000000이상이면 "None"을 출력하고 while문을 탈출해준다.
                            cout << "None\n";
                            break;
                        }
                        check = true;   // 목적지에 도착하였음을 알려주는 check변수를 true로 해준다.
                        cout << tree_cnt << " " << info[numbering[t_num]].path_distance << " " << region_name[numbering[region_num1]] << " " << region_name[numbering[region_num2]] << "\n";
                        break;
                    }

                    for (int j = 1; j < graph[numbering[t_num]].size(); j++) {  // region_num이 t_num인 region의 인접 region들에 접근한다.
                        f_num = graph[numbering[t_num]][j].first;   // 인접 region의 region_num
                        f_distance = graph[numbering[t_num]][j].second; //  인접 region의 weight이다.
                        //if (Iswater[numbering[f_num]] == true) {    // 만약 region_num이 f_num인 region이 침수되어 있으면  아무것도 해주지 않고 continue해준다.
                        //    continue;
                        //}
                        if (info[numbering[f_num]].path_distance > graph[numbering[t_num]][j].second + info[numbering[t_num]].path_distance) {  // 기존에 저장된 path_distance보다 새롭게 구한 경로의 길이가 더 작은경우이다.
                            info[numbering[f_num]].path_distance = graph[numbering[t_num]][j].second + info[numbering[t_num]].path_distance;
                            info[numbering[f_num]].predecessor = t_num; // f_num의 predecessor를 t_num으로 바꿔준다.
                            if (Iswater[numbering[f_num]] == true) {    // 만약 region_num이 f_num인 region이 침수되어 있으면 continue를 수행하여 pq에 추가해주지 않는다.
                                continue;
                            }
                            pq.push(make_pair(f_num, info[numbering[f_num]].path_distance));    // pq에 넣어준다.
                        }
                    }
                }
                if (!check) {   // 목적지까지의 path를 찾지 못했을 경우 "None"을 출력해준다.
                    cout << "None\n";
                }
            }
            delete[] info;
        }
        else if (Q == 'B') {    // 두 지역간의 최단 경로 찾기
            information* info = new information[100001];

            if (Iswater[numbering[region_num1]] == true || Iswater[numbering[region_num2]] == true) {   // 출발지나 목적지가 침수되어 있으면 "None"출력해준다.
                cout << "None\n";
            }
            else {
                int tree_cnt = 0;   // tree vertex 세는 변수

                info[numbering[region_num1]].path_distance = 0; // 출발지의 path_distancd를 0으로 초기화해주었다.
                pq.push(make_pair(region_num1, 0)); // 출발지를 pq에 담아주었다.

                int f_num;
                int f_distance;

                int t_num;
                int t_distance;

                bool check = false;
                while (!pq.empty()) {
                    t_num = pq.top().first; // pq안에서 path_distance가 가장 작은 region의 지역번호이다.
                    t_distance = pq.top().second;   // pq안에서 path_distance가 가장 작은 region의 path_distance이다.
                    pq.pop();   // pq안에서 path_distance가 가장 작은 pair를 pop해준다.

                    if (Iswater[numbering[t_num]] == true) {    // 꺼낸 region이 침수되어 있으면 아무것도 하지않고 continue해준다.
                        continue;
                    }
                    if (pq.size() != 0 && t_distance == pq.top().second) {   // 최단 거리가 동일한 후보 정점 존재한다면 지역번호가 작은 순으로 뽑아준다.
                        if (t_num > pq.top().first) {
                            pq.push(make_pair(t_num, t_distance));
                            continue;
                        }
                    }
                    if (info[numbering[t_num]].path_distance < t_distance) {    // 꺼낸 region의 path_distance(t_distance)가 이미 저장되어 있는 path_distance보다 더 크다면 continue해준다.
                        continue;
                    }

                    tree_cnt++; // tree vertex의 수를 1 증가시켜준다.

                    if (t_num == region_num2) { // // 꺼낸 region의 region_num이 목적지의 region_num과 같은 경우이다. 즉, 목적지에 도착하였을 경우이다.
                        if (info[numbering[t_num]].path_distance >= 1000000) {  // 최단 거리가 1000000이상이면 "None"을 출력하고 while문을 탈출해준다.
                            cout << "None\n";
                            break;
                        }

                        check = true;   // 목적지에 도착하였음을 알려주는 check변수를 true로 해준다.

                        // 출발지부터 목적지까지의 최단 경로 출력해준다.
                        cout << tree_cnt << " ";
                        stack<int> s;
                        int med = region_num2;
                        while (med != region_num1) {
                            s.push(med);
                            med = info[numbering[med]].predecessor;
                        }
                        cout << region_num1 << " ";
                        while (!s.empty()) {
                            cout << s.top() << " ";
                            s.pop();
                        }
                        cout << "\n";
                        break;
                    }


                    for (int j = 1; j < graph[numbering[t_num]].size(); j++) {  // region_num이 t_num인 region의 인접 region들에 접근한다.
                        f_num = graph[numbering[t_num]][j].first;   // 인접 region의 region_num
                        f_distance = graph[numbering[t_num]][j].second; //  인접 region의 weight이다.

                        if (info[numbering[f_num]].path_distance > graph[numbering[t_num]][j].second + info[numbering[t_num]].path_distance) {  // 기존에 저장된 path_distance보다 새롭게 구한 경로의 길이가 더 작은경우이다.
                            info[numbering[f_num]].path_distance = graph[numbering[t_num]][j].second + info[numbering[t_num]].path_distance;
                            info[numbering[f_num]].predecessor = t_num; // f_num의 predecessor를 t_num으로 바꿔준다.
                            if (Iswater[numbering[f_num]] == true) {    // 만약 region_num이 f_num인 region이 침수되어 있으면  아무것도 해주지 않고 continue해준다.
                                continue;
                            }
                            pq.push(make_pair(f_num, info[numbering[f_num]].path_distance));    // pq에 넣어준다.
                        }
                    }
                }
                if (!check) {   // 목적지까지의 path를 찾지 못했을 경우 "None"을 출력해준다.
                    cout << "None\n";
                }
            }

            delete[] info;

        }
        while (!pq.empty()) {
            pq.pop();
        }
    }

    return 0;
}
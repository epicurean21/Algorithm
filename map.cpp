#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

/*
 * map은 각 노드가 key 와 Value 쌍으로 이루어져있다. map <key, value> map1;
 * 중복을 허용하지 않는다. 레드블랙트리로 구성되어있음
 * pair 객체로 저장되는데 first->key second->value롤 저장된다
 *
 * 내부에서 자동으로 정렬하는데 기본 오름차순으로 정렬한다. 내림차순으로 정렬하고싶다면 map<int,int,greater> map
 *
 * map에 찾고자 하는 데이터가 있다면 (search)
 * iterator 를 활용한다. 만약 끝까지 데이터가 없다면 iterator가 map.end()를 반환한다.
 * m.find("JaeMin") != m.end()
 *
 * 데이터 삽입 (insert)
 * key가 중복된다면 insert가 수행되지 않는다.
 * m.insert({"JaeMin", "951024"}) // key가 string, value
 *
 * 기본 함수들
 * insert( make_pair(key,value) ): 맵에 원소를 pair 형태로 추가
 * erase(key): 맵에서 key(키값)에 해당하는 원소 삭제
 * clear(): 맵의 원소들 모두 삭제
 * find(key): key(키값)에 해당하는 iterator를 반환
 * count(key): key(키값)에 해당하는 원소들(value들)의 개수를 반환
 * empty(): 맵이 비어있으면 true 아니면 false를 반환
 * size(): 맵 원소들의 수를 반환
 */

int p[200002];
int sz[200002];

int find(int a) {
    if (p[a] == a)
        return a;
    return p[a] = find(p[a]);
}

int merge(int a, int b) {
    int aa = find(a);
    int bb = find(b);

    if (aa != bb) {
        p[bb] = aa;
        sz[aa] += sz[bb];
        sz[bb] = 1;
    }
    return sz[aa];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    /*
    map<string, int> m;
    m.insert({"a", 1});
    m.insert({"b", 2});
    m.insert({"c", 3});
    m.insert({"d", 4});
    m.insert({"e", 5});
    m["f"] = 6; // 이렇게도 가능 !

    if (!m.empty())
        cout << "map size: " << m.size() << '\n';

    // find()
    cout << "a: " << m.find("a")->second << '\n'; // key; a의 value 출력
    cout << "a: " << m.find("a")->first << '\n'; // a를 출력

    cout << "g: " << m.find("g")->second << '\n'; // g는 존재 x 쓰레기값 출력
    cout << "g: " << m.find("g")->first << '\n'; // 빈값 출력

    // count
    cout << "count: " << m.count("a") << "\n"; // 1 출력

    //begin(), end()
    for (auto it = m.begin(); it != m.end(); it++)
        cout << "key: " << it->first << " value: " << it->second << "\n";

    /*
     * 백준 4195: 친구 네트워크
     */
    int T, F;
    cin >> T;
    while (T--) {
        cin >> F;

        for (int i = 0; i < 200002; i++) {
            p[i] = i;
            sz[i] = 1;
        }

        map<string, int> network;
        int idx = 1;
        for (int i = 0; i < F; i++) {
            string friend1, friend2;
            cin >> friend1 >> friend2;
            int idx1, idx2;
            if (!network.empty() && network.count(friend1) != 0) { // 이미 존재
                idx1 = network.find(friend1)->second;
            } else {
                idx1 = idx;
                network.insert({friend1, idx++});
            }

            if (!network.empty() && network.count(friend2) != 0)
                idx2 = network.find(friend2)->second;
            else {
                idx2 = idx;
                network.insert({friend2, idx++});
            }

            int tmp1 = find(idx1), tmp2 = find(idx2);
            if (tmp1 == tmp2) {
                // 이미 같은 그룹, 크기만 출력
                cout << max(sz[tmp1], sz[tmp2]) << '\n';
                continue;
            }

            cout << merge(tmp1, tmp2) << '\n';
        }
    }

    return 0;
}
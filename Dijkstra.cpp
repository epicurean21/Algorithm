#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define INF 987654321
#define MAX 20001
int V, E, startV, a, b, w;
int distance[MAX];
vector<vector<pair<int,int>>> graph;
priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> pq;

void dijkstra(int start) {

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> V >> E >> startV;
    for(int i = 0; i < E; i++) {
        cin >> a >> b >> w;
        graph[a].push_back({b, w}); // a -> b 로 가중치 w
    }

    // 출력
    for(int i = 1; i <= V; i++) {
        if(distance[i] == INF)
            cout << "INF\n";
        else
            cout << distance[i];
    }
    return 0;
}
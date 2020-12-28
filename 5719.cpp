#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
#define MAX 5001
#define INF 987654321

int N, M, S, D;
vector<pair<int, int>> graph[MAX];
vector<pair<int, int>> trace[MAX];
bool visited[MAX][MAX];

vector<int> dijkstra(int start, int vertex) {
    vector<int> distance(vertex, INF);
    distance[start] = 0;
    priority_queue<pair<int, int>> pq; //Cost, Vertex;
    pq.push(make_pair(0, start)); //초기 비용과 시작점

    while (!pq.empty()) {
        int cost = -pq.top().first;
        int curVertex = pq.top().second;
        pq.pop();

        if (distance[curVertex] < cost)
            continue;

        for (int i = 0; i < graph[curVertex].size(); i++) {
            int neighbor = graph[curVertex][i].first;
            int neighborDistance = cost + graph[curVertex][i].second;

            if (graph[curVertex][i].second == -1)
                continue;

            if (distance[neighbor] > neighborDistance) {
                distance[neighbor] = neighborDistance;
                pq.push(make_pair(-neighborDistance, neighbor));
                trace[neighbor].clear();
                trace[neighbor].push_back(make_pair(curVertex, neighborDistance));
            } else if (distance[neighbor] == neighborDistance)
                trace[neighbor].push_back(make_pair(curVertex, neighborDistance));
        }
    }
    return distance;
}

void BFS(int destination) {
    queue<int> q;
    q.push(destination);
    while (!q.empty()) {
        int curVertex = q.front();
        q.pop();
        for (int i = 0; i < trace[curVertex].size(); i++) {
            int neighbor = trace[curVertex][i].first;
            if (visited[curVertex][neighbor])
                continue;
            for (int i = 0; i < graph[neighbor].size(); i++)
                if (graph[neighbor][i].first == curVertex)
                    graph[neighbor][i].second = -1;
            q.push(neighbor);
        }
    }
}

int main() {
    while (1) {
        memset(visited, false, sizeof(visited));
        memset(trace, 0, sizeof(trace));
        for (int i = 0; i < MAX; i++)
            graph[i].clear();

        cin >> N >> M;
        if (N == 0 && M == 0)
            break;

        cin >> S >> D;

        for (int i = 0; i < M; i++) {
            int source, destination, cost;
            cin >> source >> destination >> cost;
            graph[source].push_back(make_pair(destination, cost));
        }
        dijkstra(S, N);
        BFS(D);
        vector<int> result = dijkstra(S, N);

        if (result[D] == INF)
            cout << -1 << endl;
        else
            cout << result[D] << endl;
    }

    return 0;
}
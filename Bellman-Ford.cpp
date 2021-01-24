#include <iostream>
#include <vector>

using namespace std;
#define INF 50000010
#define MAX 510
#define ll long long
// Bellman-Ford Algorithm, Problme #11657
/*
 * 플로이드 와샬알고리즘은 그래프 상의 음의 가중치를 허용한다.
 * 무한루프 계속해서 최단경로 가중치가 줄어들 수 있다. 더쓰면 싸이클 생성
 * 그래프 상에 존재하는 두 노드 간의 최단 거리를 구하고 싶을 때 이용할 수 있다.
 * 벨만 포드 알고리즘은, 다익스트라에서 할 수 없었던 음의 가중치도 계산 할 수 있도록 한 방식이지만
 * 다익스트라보다 시간 복잡도가 높기에(더 느리기에) 어떤 상황에서 이용해야 할 지 잘 생각하여 써야한다
 */
int N, M, A, B, C;
ll dist[MAX];
bool minus_cycle = false;
vector<vector<pair<int, int>>> graph;

void bellmanford() {
    // 시작점을 초기화 하자 !
    // 타임머신 문제에서는 시작점이 1이다.

    dist[1] = 0;
    for (int i = 0; i < N - 1; i++) { // 최대 방문할 수 있는 간선의 개수 만큼 돌리자 : N - 1 번
        for (int j = 1; j <= N; j++) { // j 점 주변에 있는 점들을 업데이트 할 수 있는지 확인 !
            for (int k = 0; k < graph[j].size(); k++) {
                int next = graph[j][k].first; // 다음 점
                int weight = graph[j][k].second; // 비용
                if(dist[j] == INF) continue;
                if (dist[j] + weight < dist[next]) {// 다음까지의 비용이 현재 + 가중치 보다 작으면 업데이트
                    dist[next] = dist[j] + weight; // j->next 이동하는데 더 적은 비용으로 이동 가능하면 업데이트
                }
            }
        }
    }

    /*
     * 전체 N-1번 수행했기 때문에, 가장 먼 경로더라도 충분히 도달 했다.
     * 그리고 그 경로가 최단경로
     * 왜냐면 더 추가해서 방문을 했으면 경로의 값이 커지니까
     * 하지만 중간에 감소한다면 ??
     * 한번더 돌려보자
     */
    for (int j = 1; j <= N; j++) { // j 점 주변에 있는 점들을 업데이트 할 수 있는지 확인 !
        for (int k = 0; k < graph[j].size(); k++) {
            int next = graph[j][k].first; // 다음 점
            int weight = graph[j][k].second; // 비용
            if(dist[j] == INF) continue;
            if (dist[j] + weight < dist[next]) {// 다음까지의 비용이 현재 + 가중치 보다 작으면 업데이트
                // 이런 일이 벌어질 수 있을까??
                minus_cycle = true;
            }
        }
    }

}

void init() {
    for (int i = 1; i <= N; i++)
        dist[i] = INF;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    graph.resize(N + 1);
    for (int i = 0; i < M; i++) {
        cin >> A >> B >> C;
        graph[A].push_back({B, C}); // A -> B 까지 C 의 cost
    }
    init();
    bellmanford();

    // 출력 예외처리부터
    // 시간이 무한이 되돌아가면 -1, 경로 없c으면 -1
    // 출력
    if (minus_cycle)
        cout << "-1\n";
    else {
        for (int i = 2; i <= N; i++) {
            if (dist[i] == INF)
                cout << "-1\n";
            else
                cout << dist[i] << "\n";
        }
    }
    return 0;
}
# 알고리즘 완전 가이드

이 문서는 Algorithm 디렉토리의 C++ 구현을 기반으로 작성된 종합 알고리즘 설명 가이드입니다. 각 알고리즘의 개념, 시간/공간 복잡도, 그리고 실제 C++ 코드 예시를 포함합니다.

---

## 📑 목차
1. [그래프 알고리즘](#그래프-알고리즘)
2. [동적 계획법](#동적-계획법)
3. [자료구조](#자료구조)
4. [문자열 알고리즘](#문자열-알고리즘)
5. [수학 알고리즘](#수학-알고리즘)
6. [정렬과 탐색](#정렬과-탐색)
7. [계산 기하학](#계산-기하학)
8. [고급 알고리즘](#고급-알고리즘)

---

## 그래프 알고리즘

### 1. DFS (깊이 우선 탐색)

#### 📝 설명
DFS는 그래프를 순회하는 알고리즘으로, 한 경로를 끝까지 탐색한 후 되돌아가는 방식입니다. 스택(재귀 또는 명시적 스택)을 사용하여 구현되며, 백트래킹, 사이클 탐지, 연결 요소 찾기 등에 활용됩니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(V + E) - V는 정점 수, E는 간선 수
- **공간 복잡도**: O(V) - 방문 체크 배열 및 재귀 스택

#### 🔄 동작 과정 (Pseudocode)
```
DFS(node):
    // 1. 현재 노드 방문 처리
    visited[node] = true
    visit(node)
    
    // 2. 현재 노드와 인접한 모든 노드 탐색
    for each neighbor in adjacentNodes[node]:
        // 3. 방문하지 않은 노드가 있다면
        if not visited[neighbor]:
            // 4. 해당 노드를 시작점으로 재귀적으로 DFS 수행
            DFS(neighbor)
    
    // 5. 모든 인접 노드 방문 완료 후 이전 노드로 백트래킹

주요 단계:
1. 시작 노드를 스택에 넣고 방문 표시
2. 스택에서 노드를 꺼내어 방문
3. 방문한 노드의 인접 노드 중 방문하지 않은 노드를 스택에 추가
4. 스택이 빌 때까지 2-3 반복
```

#### 💻 C++ 구현
```cpp
#include <vector>
using namespace std;

const int MAX = 101;
int dy[] = {0, 1, 0, -1}, dx[] = {1, 0, -1, 0};
bool visited[MAX][MAX];
char graph[MAX][MAX];
int N;

void dfs(int x, int y, char color) {
    visited[y][x] = true;
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
        if (graph[ny][nx] != color) continue;
        if (!visited[ny][nx]) {
            dfs(nx, ny, color);
        }
    }
}
```

---

### 2. BFS (너비 우선 탐색)

#### 📝 설명
BFS는 시작 정점에서 가까운 정점부터 순서대로 탐색하는 알고리즘입니다. 큐를 사용하여 구현하며, 가중치 없는 그래프에서의 최단 경로, 레벨 순회 등에 사용됩니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(V + E)
- **공간 복잡도**: O(V) - 큐와 방문 체크 배열

#### 🔄 동작 과정 (Pseudocode)
```
BFS(startNode):
    // 1. 큐 초기화 및 시작 노드 삽입
    queue.enqueue(startNode)
    visited[startNode] = true
    
    // 2. 큐가 빌 때까지 반복
    while queue is not empty:
        // 3. 큐에서 노드 하나 꺼내기
        currentNode = queue.dequeue()
        visit(currentNode)
        
        // 4. 현재 노드의 모든 인접 노드 확인
        for each neighbor in adjacentNodes[currentNode]:
            // 5. 방문하지 않은 인접 노드를 큐에 추가
            if not visited[neighbor]:
                visited[neighbor] = true
                queue.enqueue(neighbor)
    
주요 특징:
- 레벨별로 탐색 (거리 1인 노드 → 거리 2인 노드 → ...)
- 최단 거리 보장 (가중치 없는 그래프)
- 선입선출(FIFO) 방식
```

#### 💻 C++ 구현
```cpp
#include <queue>
using namespace std;

const int MAX = 501;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
bool visited[MAX][MAX];
int graph[MAX][MAX];
int n, m;

int bfs(int startX, int startY) {
    int area = 0;
    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startY][startX] = true;
    
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        area++;
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            if (!graph[ny][nx] || visited[ny][nx]) continue;
            
            visited[ny][nx] = true;
            q.push({nx, ny});
        }
    }
    return area;
}
```

---

### 3. 다익스트라 알고리즘 (Dijkstra)

#### 📝 설명
다익스트라 알고리즘은 가중치가 양수인 그래프에서 단일 출발점으로부터 모든 정점까지의 최단 경로를 찾는 알고리즘입니다. 우선순위 큐를 사용하여 항상 현재까지 발견한 최단 거리가 가장 짧은 정점을 선택합니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O((V + E) log V) - 우선순위 큐 사용 시
- **공간 복잡도**: O(V + E) - 그래프 저장 및 거리 배열

#### 🔄 동작 과정 (Pseudocode)
```
Dijkstra(start):
    // 1. 초기화: 모든 정점까지의 거리를 무한대로 설정
    for each vertex v:
        dist[v] = INF
    dist[start] = 0
    
    // 2. 우선순위 큐에 시작 정점 삽입 (거리, 정점)
    priorityQueue.push((0, start))
    
    // 3. 큐가 빌 때까지 반복
    while priorityQueue is not empty:
        // 4. 가장 거리가 짧은 정점 선택
        (currentDist, current) = priorityQueue.pop()
        
        // 5. 이미 처리된 정점이면 스킵
        if currentDist > dist[current]:
            continue
        
        // 6. 현재 정점과 연결된 모든 인접 정점 확인
        for each (neighbor, weight) in adjacentEdges[current]:
            // 7. 현재 정점을 거쳐가는 경로가 더 짧다면 갱신
            newDist = dist[current] + weight
            if newDist < dist[neighbor]:
                dist[neighbor] = newDist
                priorityQueue.push((newDist, neighbor))

핵심 아이디어:
- 탐욕적 선택: 매번 최단 거리 정점 선택
- 거리 갱신: 더 짧은 경로 발견 시 업데이트
- 음수 가중치 불가: 양수 가중치만 보장
```

#### 💻 C++ 구현
```cpp
#include <vector>
#include <queue>
using namespace std;

const int MAX = 20001;
const int INF = 987654321;

int V, E, K;
vector<pair<int, int>> graph[MAX];
int dist[MAX];

void dijkstra(int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    fill(dist, dist + MAX, INF);
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int curDist = pq.top().first;
        int cur = pq.top().second;
        pq.pop();
        
        if (curDist > dist[cur]) continue;
        
        for (auto &edge : graph[cur]) {
            int next = edge.first;
            int weight = edge.second;
            int nextDist = curDist + weight;
            
            if (nextDist < dist[next]) {
                dist[next] = nextDist;
                pq.push({nextDist, next});
            }
        }
    }
}
```

---

### 4. 플로이드-워셜 알고리즘 (Floyd-Warshall)

#### 📝 설명
플로이드-워셜 알고리즘은 모든 정점 쌍 사이의 최단 경로를 찾는 동적 계획법 기반 알고리즘입니다. 음수 가중치도 처리할 수 있으며, 3중 반복문을 통해 모든 경로를 확인합니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(V³)
- **공간 복잡도**: O(V²) - 거리 행렬

#### 🔄 동작 과정 (Pseudocode)
```
FloydWarshall():
    // 1. 거리 행렬 초기화
    for i = 1 to N:
        for j = 1 to N:
            if i == j:
                dist[i][j] = 0
            else if edge(i, j) exists:
                dist[i][j] = weight(i, j)
            else:
                dist[i][j] = INF
    
    // 2. 모든 정점을 경유지로 고려
    for k = 1 to N:  // k: 경유 정점
        for i = 1 to N:  // i: 시작 정점
            for j = 1 to N:  // j: 도착 정점
                // 3. k를 거쳐가는 경로가 더 짧으면 갱신
                if dist[i][j] > dist[i][k] + dist[k][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]

핵심 아이디어:
- DP[k][i][j] = k번 정점까지 경유하여 i→j 최단 거리
- 모든 경유지를 순차적으로 고려
- 음수 사이클 탐지 가능 (dist[i][i] < 0)
```

#### 💻 C++ 구현
```cpp
const int MAX = 101;
const int INF = 987654321;
int dist[MAX][MAX];
int n;

void floydWarshall() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) dist[i][j] = 0;
            else if (dist[i][j] == 0) dist[i][j] = INF;
        }
    }
    
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
```

---

### 5. 벨만-포드 알고리즘 (Bellman-Ford)

#### 📝 설명
벨만-포드 알고리즘은 음수 가중치가 있는 그래프에서 단일 출발점 최단 경로를 찾으며, 음수 사이클 탐지도 가능한 알고리즘입니다. 모든 간선을 V-1번 반복하여 거리를 갱신합니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(VE)
- **공간 복잡도**: O(V + E)

#### 🔄 동작 과정 (Pseudocode)
```
BellmanFord(start):
    // 1. 거리 초기화
    for each vertex v:
        dist[v] = INF
    dist[start] = 0
    
    // 2. V-1번 반복하여 모든 간선 완화(relaxation)
    for i = 1 to V-1:
        for each edge (u, v) with weight w:
            // 3. 더 짧은 경로 발견 시 갱신
            if dist[u] != INF and dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
    
    // 4. 음수 사이클 검사 (V번째 반복)
    for each edge (u, v) with weight w:
        if dist[u] != INF and dist[u] + w < dist[v]:
            return "음수 사이클 존재"
    
    return dist

핵심 특징:
- 음수 가중치 허용
- V-1번 반복으로 모든 최단 경로 보장
- V번째에도 갱신되면 음수 사이클
- Dijkstra보다 느리지만 더 범용적
```

#### 💻 C++ 구현
```cpp
#include <vector>
using namespace std;

const int MAX = 501;
const long long INF = 50000010;

int N, M;
vector<pair<int, int>> graph[MAX];
long long dist[MAX];
bool hasNegativeCycle = false;

void bellmanFord(int start) {
    fill(dist, dist + MAX, INF);
    dist[start] = 0;
    
    for (int i = 0; i < N - 1; i++) {
        for (int cur = 1; cur <= N; cur++) {
            if (dist[cur] == INF) continue;
            
            for (auto &edge : graph[cur]) {
                int next = edge.first;
                int weight = edge.second;
                
                if (dist[cur] + weight < dist[next]) {
                    dist[next] = dist[cur] + weight;
                }
            }
        }
    }
    
    for (int cur = 1; cur <= N; cur++) {
        if (dist[cur] == INF) continue;
        
        for (auto &edge : graph[cur]) {
            int next = edge.first;
            int weight = edge.second;
            
            if (dist[cur] + weight < dist[next]) {
                hasNegativeCycle = true;
                return;
            }
        }
    }
}
```

---

### 6. 크루스칼 알고리즘 (MST with Union-Find)

#### 📝 설명
크루스칼 알고리즘은 최소 신장 트리(MST)를 찾는 탐욕 알고리즘입니다. 간선을 가중치 순으로 정렬한 후, Union-Find를 사용하여 사이클을 만들지 않는 간선만 선택합니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(E log E) - 간선 정렬이 지배적
- **공간 복잡도**: O(V + E)

#### 🔄 동작 과정 (Pseudocode)
```
Kruskal():
    // 1. Union-Find 초기화
    for each vertex v:
        parent[v] = v
    
    // 2. 모든 간선을 가중치 기준 오름차순 정렬
    edges.sort(by weight)
    
    mstCost = 0
    mstEdges = []
    
    // 3. 간선을 하나씩 확인
    for each edge (u, v, weight) in sorted_edges:
        // 4. 두 정점이 다른 집합이면 (사이클 형성 안함)
        if find(u) != find(v):
            // 5. MST에 간선 추가
            union(u, v)
            mstEdges.append((u, v, weight))
            mstCost += weight
            
            // 6. V-1개 간선 선택하면 종료
            if len(mstEdges) == V - 1:
                break
    
    return mstCost, mstEdges

핵심 아이디어:
- 탐욕적 선택: 가장 작은 가중치 간선부터
- Union-Find로 사이클 검사
- V-1개 간선으로 모든 정점 연결
```

#### 💻 C++ 구현
```cpp
#include <queue>
#include <vector>
using namespace std;

const int MAX = 1001;
int parent[MAX];
int N, M;

int find(int a) {
    if (parent[a] == a) return a;
    return parent[a] = find(parent[a]);
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) parent[a] = b;
}

int kruskal(priority_queue<pair<int, pair<int, int>>, 
            vector<pair<int, pair<int, int>>>, greater<>> &edges) {
    for (int i = 1; i <= N; i++)
        parent[i] = i;
    
    int totalCost = 0;
    int edgeCount = 0;
    
    while (!edges.empty() && edgeCount < N - 1) {
        int cost = edges.top().first;
        int u = edges.top().second.first;
        int v = edges.top().second.second;
        edges.pop();
        
        if (find(u) != find(v)) {
            merge(u, v);
            totalCost += cost;
            edgeCount++;
        }
    }
    
    return totalCost;
}
```

---

### 7. 프림 알고리즘 (Prim's Algorithm for MST)

#### 📝 설명
프림 알고리즘은 크루스칼과 함께 최소 신장 트리를 찾는 또 다른 탐욕 알고리즘입니다. 하나의 정점에서 시작하여 트리를 점진적으로 확장하며, 우선순위 큐를 사용하여 현재 트리와 연결된 간선 중 최소 가중치 간선을 선택합니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O((V + E) log V) - 우선순위 큐 사용 시
- **공간 복잡도**: O(V + E)

#### 🔄 동작 과정 (Pseudocode)
```
Prim(start):
    // 1. 초기화
    for each vertex v:
        visited[v] = false
        minCost[v] = INF
    
    minCost[start] = 0
    priorityQueue.push((0, start))
    totalCost = 0
    
    // 2. 우선순위 큐가 빌 때까지 반복
    while priorityQueue is not empty:
        // 3. 가장 작은 가중치의 간선 선택
        (cost, u) = priorityQueue.pop()
        
        // 4. 이미 방문한 정점이면 스킵
        if visited[u]:
            continue
        
        // 5. MST에 정점 추가
        visited[u] = true
        totalCost += cost
        
        // 6. 새로 추가된 정점과 연결된 모든 간선 확인
        for each edge (u, v, weight):
            if not visited[v] and weight < minCost[v]:
                minCost[v] = weight
                priorityQueue.push((weight, v))
    
    return totalCost

핵심 차이 (Kruskal vs Prim):
- Kruskal: 간선 중심, 정렬 필요, Union-Find 사용
- Prim: 정점 중심, 우선순위 큐, 연결된 그래프에 유리
- 밀집 그래프: Prim 유리
- 희소 그래프: Kruskal 유리
```

#### 💻 C++ 구현
```cpp
#include <vector>
#include <queue>
using namespace std;

const int MAX = 1001;
const int INF = 987654321;

int V, E;
vector<pair<int, int>> graph[MAX];
bool visited[MAX];

int prim(int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    int totalCost = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int cost = pq.top().first;
        int cur = pq.top().second;
        pq.pop();
        
        if (visited[cur]) continue;
        
        visited[cur] = true;
        totalCost += cost;
        
        for (auto &edge : graph[cur]) {
            int next = edge.first;
            int weight = edge.second;
            
            if (!visited[next]) {
                pq.push({weight, next});
            }
        }
    }
    
    return totalCost;
}
```

---

### 8. 최소 공통 조상 (LCA)

#### 📝 설명
LCA 알고리즘은 트리에서 두 노드의 최소 공통 조상을 찾는 알고리즘입니다. 이진 리프팅(Binary Lifting) 기법을 사용하면 전처리 후 각 쿼리를 O(log N)에 처리할 수 있습니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(N log N) 전처리, O(log N) 쿼리당
- **공간 복잡도**: O(N log N)

#### 🔄 동작 과정 (Pseudocode)
```
// 전처리: 이진 리프팅 테이블 구축
PreprocessLCA(root):
    // 1. DFS로 각 노드의 깊이와 부모 계산
    DFS(root, 0):
        depth[node] = currentDepth
        
        // 2. 2^0 = 1번째 조상 (직접 부모) 저장
        parent[node][0] = directParent
        
        // 3. 2^k번째 조상 계산 (k = 1, 2, ..., log N)
        for k = 1 to log(N):
            // 2^k번째 조상 = 2^(k-1)번째 조상의 2^(k-1)번째 조상
            parent[node][k] = parent[parent[node][k-1]][k-1]
        
        for each child in children[node]:
            DFS(child, currentDepth + 1)

// LCA 쿼리
FindLCA(u, v):
    // 1. u의 깊이가 더 깊도록 설정
    if depth[u] < depth[v]:
        swap(u, v)
    
    // 2. u를 v와 같은 깊이로 올림 (이진 리프팅)
    diff = depth[u] - depth[v]
    for k = 0 to log(N):
        if diff의 k번째 비트가 1:
            u = parent[u][k]  // 2^k만큼 올라감
    
    // 3. 같은 노드면 LCA 찾음
    if u == v:
        return u
    
    // 4. 두 노드를 동시에 올리면서 LCA 바로 아래까지 이동
    for k = log(N) down to 0:
        // 조상이 다르면 계속 올라감
        if parent[u][k] != parent[v][k]:
            u = parent[u][k]
            v = parent[v][k]
    
    // 5. 한 단계 위가 LCA
    return parent[u][0]

핵심 아이디어:
- 이진 리프팅: 2의 거듭제곱 단위로 조상 저장
- O(log N) 점프로 빠르게 이동
- 희소 테이블(Sparse Table) 기법 활용
```

#### 💻 C++ 구현
```cpp
#include <vector>
#include <cmath>
using namespace std;

const int MAX = 100001;
const int LOG = 17;

int N, M;
vector<int> tree[MAX];
int parent[MAX][LOG];
int depth[MAX];

void dfs(int cur, int par) {
    depth[cur] = depth[par] + 1;
    parent[cur][0] = par;
    
    for (int i = 1; i < LOG; i++) {
        parent[cur][i] = parent[parent[cur][i-1]][i-1];
    }
    
    for (int next : tree[cur]) {
        if (next != par) {
            dfs(next, cur);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    
    int diff = depth[u] - depth[v];
    for (int i = 0; i < LOG; i++) {
        if ((diff >> i) & 1) {
            u = parent[u][i];
        }
    }
    
    if (u == v) return u;
    
    for (int i = LOG - 1; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    
    return parent[u][0];
}
```

---

## 동적 계획법

### 9. 최장 증가 부분 수열 (LIS with Binary Search)

#### 📝 설명
LIS는 주어진 수열에서 순서를 유지하면서 크기가 증가하는 가장 긴 부분 수열을 찾는 문제입니다. 이진 탐색을 활용하면 O(n log n)에 해결할 수 있습니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(N log N) - 이진 탐색 사용
- **공간 복잡도**: O(N)

#### 🔄 동작 과정 (Pseudocode)
```
LIS_BinarySearch(arr):
    // 1. LIS를 저장할 배열 초기화
    lis = []
    
    // 2. 각 원소를 순차적으로 처리
    for i = 0 to N-1:
        // 3-1. 현재 원소가 LIS의 마지막 원소보다 크면
        if lis is empty OR arr[i] > lis[last]:
            // LIS 끝에 추가
            lis.append(arr[i])
        
        // 3-2. 그렇지 않으면
        else:
            // 4. 이진 탐색으로 arr[i]가 들어갈 위치 찾기
            pos = lower_bound(lis, arr[i])
            
            // 5. 해당 위치의 값을 arr[i]로 교체
            lis[pos] = arr[i]
    
    // 6. LIS의 길이 반환
    return len(lis)

실제 수열 복원:
- 각 원소가 lis의 어느 위치에 들어갔는지 기록
- 역추적하여 실제 LIS 구성

핵심 아이디어:
- lis[i] = 길이가 i+1인 증가 수열의 마지막 원소 최솟값
- 이진 탐색으로 O(log N)에 위치 탐색
- lis 배열의 길이가 LIS 길이
- lis 배열 자체는 LIS가 아님! (길이만 정확)
```

#### 💻 C++ 구현
```cpp
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

int N;
vector<int> arr;
vector<int> lis;
vector<pair<int, int>> trace;

void findLIS() {
    lis.push_back(arr[0]);
    trace.push_back({0, arr[0]});
    
    for (int i = 1; i < N; i++) {
        if (lis.back() < arr[i]) {
            lis.push_back(arr[i]);
            trace.push_back({lis.size() - 1, arr[i]});
        } else {
            int idx = lower_bound(lis.begin(), lis.end(), arr[i]) - lis.begin();
            lis[idx] = arr[i];
            trace.push_back({idx, arr[i]});
        }
    }
    
    stack<int> result;
    int pos = lis.size() - 1;
    for (int i = trace.size() - 1; i >= 0; i--) {
        if (trace[i].first == pos) {
            result.push(trace[i].second);
            pos--;
        }
    }
}
```

---

### 10. 외판원 순회 (TSP with Bitmask DP)

#### 📝 설명
TSP는 모든 도시를 정확히 한 번씩 방문하고 시작 도시로 돌아오는 최소 비용 경로를 찾는 문제입니다. 비트마스크 DP를 사용하여 방문한 도시 집합을 표현합니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(N² × 2ᴺ)
- **공간 복잡도**: O(N × 2ᴺ)

#### 🔄 동작 과정 (Pseudocode)
```
TSP_Bitmask(N, dist[][]):
    // 1. DP 테이블 초기화
    // dp[mask][i] = mask 상태로 도시 i에 있을 때 최소 비용
    for all mask, i:
        dp[mask][i] = INF
    
    // 2. 시작점 (0번 도시) 초기화
    dp[1][0] = 0  // 0번 도시만 방문 (2^0 = 1)
    
    // 3. 모든 상태에 대해 반복
    for mask = 1 to (1 << N) - 1:
        for cur = 0 to N-1:
            // cur 도시를 방문하지 않았으면 스킵
            if not (mask & (1 << cur)):
                continue
            
            // 4. 다음 도시 선택
            for next = 0 to N-1:
                // 이미 방문했거나 경로가 없으면 스킵
                if (mask & (1 << next)) or dist[cur][next] == 0:
                    continue
                
                // 5. next 도시를 방문 상태로 갱신
                nextMask = mask | (1 << next)
                dp[nextMask][next] = min(dp[nextMask][next],
                                        dp[mask][cur] + dist[cur][next])
    
    // 6. 모든 도시 방문 후 시작점으로 복귀
    fullMask = (1 << N) - 1
    answer = INF
    for i = 0 to N-1:
        if dist[i][0] != 0:
            answer = min(answer, dp[fullMask][i] + dist[i][0])
    
    return answer

비트마스크 연산:
- (1 << i): i번 도시를 나타내는 비트
- mask & (1 << i): i번 도시 방문 여부 확인
- mask | (1 << i): i번 도시를 방문 상태로 설정

핵심 아이디어:
- 비트마스크로 방문 집합 표현 (2^N 가지 상태)
- DP로 중복 계산 방지
- NP-hard 문제를 지수 시간에 해결
```

#### 💻 C++ 구현
```cpp
#include <algorithm>
using namespace std;

const int MAX = 17;
const int INF = 987654321;

int N;
int W[MAX][MAX];
int dp[1 << MAX][MAX];

int tsp(int visited, int cur) {
    if (visited == (1 << N) - 1) {
        return W[cur][0] ? W[cur][0] : INF;
    }
    
    if (dp[visited][cur] != -1) {
        return dp[visited][cur];
    }
    
    dp[visited][cur] = INF;
    
    for (int next = 0; next < N; next++) {
        if (visited & (1 << next)) continue;
        if (W[cur][next] == 0) continue;
        
        int nextVisited = visited | (1 << next);
        dp[visited][cur] = min(dp[visited][cur], 
                               tsp(nextVisited, next) + W[cur][next]);
    }
    
    return dp[visited][cur];
}
```

---

### 11. 배낭 문제 (Knapsack DP)

#### 📝 설명
배낭 문제는 최대 무게 제한이 있는 배낭에 물건을 넣어 가치를 최대화하는 문제입니다. 2차원 DP 배열을 사용하여 해결합니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(NK) - N은 물건 수, K는 배낭 용량
- **공간 복잡도**: O(NK) 또는 O(K) - 1차원 최적화 가능

#### 🔄 동작 과정 (Pseudocode)
```
Knapsack_0_1(N, K, weight[], value[]):
    // 1. 2차원 DP 테이블 초기화
    // dp[i][w] = i번까지 물건으로 무게 w로 얻을 수 있는 최대 가치
    dp[0...N][0...K] = 0
    
    // 2. 각 물건에 대해 반복
    for i = 1 to N:
        for w = 0 to K:
            // 3. 현재 물건을 넣지 않는 경우
            dp[i][w] = dp[i-1][w]
            
            // 4. 현재 물건을 넣을 수 있다면
            if w >= weight[i]:
                // 5. 넣는 경우와 비교하여 최대값 선택
                dp[i][w] = max(dp[i][w],
                              dp[i-1][w - weight[i]] + value[i])
    
    return dp[N][K]

// 1차원 공간 최적화 버전
Knapsack_Optimized(N, K, weight[], value[]):
    dp[0...K] = 0
    
    // 역순으로 순회하여 각 물건을 한 번만 사용
    for i = 1 to N:
        for w = K down to weight[i]:
            dp[w] = max(dp[w], dp[w - weight[i]] + value[i])
    
    return dp[K]

핵심 아이디어:
- 부분 문제: i번까지 물건, 무게 w
- 점화식: dp[i][w] = max(넣지 않음, 넣음)
- 0-1 배낭: 각 물건 최대 1개
- 역순 순회로 1차원 최적화 가능
```

#### 💻 C++ 구현
```cpp
#include <algorithm>
using namespace std;

const int MAX_N = 101;
const int MAX_K = 100001;

int N, K;
int W[MAX_N], V[MAX_N];
int dp[MAX_K];

int knapsack() {
    for (int i = 1; i <= N; i++) {
        for (int j = K; j >= W[i]; j--) {
            dp[j] = max(dp[j], dp[j - W[i]] + V[i]);
        }
    }
    return dp[K];
}
```

---

## 자료구조

### 12. 세그먼트 트리 (Segment Tree)

#### 📝 설명
세그먼트 트리는 구간 쿼리와 업데이트를 효율적으로 처리하는 트리 구조입니다. 구간 합, 최솟값, 최댓값 등을 O(log N)에 처리할 수 있습니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(N) 구축, O(log N) 쿼리/업데이트
- **공간 복잡도**: O(4N)

#### 🔄 동작 과정 (Pseudocode)
```
// 1. 트리 구축
BuildSegmentTree(node, start, end):
    // 리프 노드: 원소 하나
    if start == end:
        tree[node] = arr[start]
        return tree[node]
    
    // 내부 노드: 왼쪽과 오른쪽 자식의 합
    mid = (start + end) / 2
    leftChild = BuildSegmentTree(node*2, start, mid)
    rightChild = BuildSegmentTree(node*2+1, mid+1, end)
    tree[node] = leftChild + rightChild
    return tree[node]

// 2. 구간 쿼리 (구간 합)
Query(node, start, end, left, right):
    // 범위를 완전히 벗어남
    if right < start OR end < left:
        return 0
    
    // 범위에 완전히 포함됨
    if left <= start AND end <= right:
        return tree[node]
    
    // 부분적으로 겹침: 분할 정복
    mid = (start + end) / 2
    leftSum = Query(node*2, start, mid, left, right)
    rightSum = Query(node*2+1, mid+1, end, left, right)
    return leftSum + rightSum

// 3. 단일 원소 업데이트
Update(node, start, end, idx, newValue):
    // 범위를 벗어남
    if idx < start OR idx > end:
        return
    
    // 리프 노드에 도달
    if start == end:
        arr[idx] = newValue
        tree[node] = newValue
        return
    
    // 내부 노드: 자식들을 재귀적으로 업데이트
    mid = (start + end) / 2
    Update(node*2, start, mid, idx, newValue)
    Update(node*2+1, mid+1, end, idx, newValue)
    tree[node] = tree[node*2] + tree[node*2+1]

핵심 아이디어:
- 완전 이진 트리 구조
- 각 노드는 구간 정보 저장
- 분할 정복으로 쿼리/업데이트
- 인덱스: 부모=i, 왼쪽자식=2i, 오른쪽자식=2i+1
```

#### 💻 C++ 구현
```cpp
#include <vector>
using namespace std;

const int MAX = 1000001;
long long arr[MAX];
vector<long long> tree;

long long buildTree(int node, int start, int end) {
    if (start == end) {
        return tree[node] = arr[start];
    }
    
    int mid = (start + end) / 2;
    return tree[node] = buildTree(node * 2, start, mid) + 
                        buildTree(node * 2 + 1, mid + 1, end);
}

long long query(int node, int start, int end, int left, int right) {
    if (right < start || end < left) {
        return 0;
    }
    
    if (left <= start && end <= right) {
        return tree[node];
    }
    
    int mid = (start + end) / 2;
    return query(node * 2, start, mid, left, right) + 
           query(node * 2 + 1, mid + 1, end, left, right);
}

void update(int node, int start, int end, int idx, long long diff) {
    if (idx < start || idx > end) {
        return;
    }
    
    tree[node] += diff;
    
    if (start != end) {
        int mid = (start + end) / 2;
        update(node * 2, start, mid, idx, diff);
        update(node * 2 + 1, mid + 1, end, idx, diff);
    }
}
```

---

### 13. Union-Find (Disjoint Set)

#### 📝 설명
Union-Find는 서로소 집합을 표현하는 자료구조로, 집합의 합치기와 원소가 속한 집합 찾기를 지원합니다. 경로 압축과 랭크 최적화를 통해 거의 O(1)에 동작합니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(α(N)) - α는 아커만 함수의 역함수 (사실상 상수)
- **공간 복잡도**: O(N)

#### 🔄 동작 과정 (Pseudocode)
```
// 초기화
Init(n):
    for i = 1 to n:
        parent[i] = i      // 각 노드가 자기 자신의 부모
        rank[i] = 0        // 트리의 높이 초기화

// Find 연산 (경로 압축)
Find(x):
    // 1. 루트 노드인 경우
    if parent[x] == x:
        return x
    
    // 2. 경로 압축: 재귀적으로 루트를 찾으면서
    //    모든 중간 노드를 직접 루트에 연결
    parent[x] = Find(parent[x])
    return parent[x]

// Union 연산 (랭크에 의한 합병)
Union(a, b):
    // 1. 각 원소의 루트 찾기
    rootA = Find(a)
    rootB = Find(b)
    
    // 2. 이미 같은 집합이면 종료
    if rootA == rootB:
        return
    
    // 3. 랭크가 낮은 트리를 높은 트리 아래에 붙임
    if rank[rootA] < rank[rootB]:
        parent[rootA] = rootB
    else if rank[rootA] > rank[rootB]:
        parent[rootB] = rootA
    else:
        // 4. 랭크가 같으면 하나를 부모로 하고 랭크 증가
        parent[rootB] = rootA
        rank[rootA]++

// 연결 여부 확인
isConnected(a, b):
    return Find(a) == Find(b)

핵심 최적화:
1. 경로 압축 (Path Compression):
   - Find 중 모든 노드를 루트에 직접 연결
   - 트리 깊이 감소

2. 랭크에 의한 합병 (Union by Rank):
   - 작은 트리를 큰 트리 아래 붙임
   - 트리 균형 유지

시간 복잡도: 거의 O(1) (Amortized)
```

#### 💻 C++ 구현
```cpp
const int MAX = 1000001;
int parent[MAX];
int rankArr[MAX];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rankArr[i] = 1;
    }
}

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    
    if (a == b) return;
    
    if (rankArr[a] < rankArr[b]) swap(a, b);
    
    parent[b] = a;
    
    if (rankArr[a] == rankArr[b]) {
        rankArr[a]++;
    }
}

bool isConnected(int a, int b) {
    return find(a) == find(b);
}
```

---

### 14. 트라이 (Trie)

#### 📝 설명
트라이는 문자열 집합을 저장하고 검색하는 트리 자료구조입니다. 접두사 검색, 자동 완성, 사전 구현 등에 효율적입니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(M) - M은 문자열 길이
- **공간 복잡도**: O(ALPHABET_SIZE × N × M) - 최악의 경우

#### 🔄 동작 과정 (Pseudocode)
```
class TrieNode:
    children[ALPHABET_SIZE]  // 자식 노드 배열
    isEndOfWord              // 단어 끝 표시

// 1. 문자열 삽입
Insert(word):
    node = root
    
    // 각 문자를 순회
    for each char in word:
        index = char - 'a'
        
        // 해당 문자 노드가 없으면 생성
        if node.children[index] == null:
            node.children[index] = new TrieNode()
        
        // 다음 노드로 이동
        node = node.children[index]
    
    // 단어의 끝 표시
    node.isEndOfWord = true

// 2. 문자열 검색
Search(word):
    node = root
    
    // 각 문자를 순회
    for each char in word:
        index = char - 'a'
        
        // 해당 경로가 없으면 false
        if node.children[index] == null:
            return false
        
        node = node.children[index]
    
    // 마지막 노드가 단어의 끝인지 확인
    return node.isEndOfWord

// 3. 접두사 검색
StartsWith(prefix):
    node = root
    
    for each char in prefix:
        index = char - 'a'
        
        if node.children[index] == null:
            return false
        
        node = node.children[index]
    
    return true  // 경로가 존재하면 접두사 존재

핵심 특징:
- 공통 접두사를 공유하여 공간 절약
- 루트에서 리프까지가 한 문자열
- 삽입/검색 모두 O(M)
```

#### 💻 C++ 구현
```cpp
#include <map>
#include <string>
using namespace std;

class Trie {
private:
    static const int ALPHABET_SIZE = 26;
    Trie* children[ALPHABET_SIZE];
    bool isEndOfWord;

public:
    Trie() {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }
    
    ~Trie() {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (children[i]) {
                delete children[i];
            }
        }
    }
    
    void insert(const string &word) {
        Trie* node = this;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new Trie();
            }
            node = node->children[idx];
        }
        node->isEndOfWord = true;
    }
    
    bool search(const string &word) {
        Trie* node = this;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!node->children[idx]) {
                return false;
            }
            node = node->children[idx];
        }
        return node->isEndOfWord;
    }
    
    bool startsWith(const string &prefix) {
        Trie* node = this;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (!node->children[idx]) {
                return false;
            }
            node = node->children[idx];
        }
        return true;
    }
};
```

---

### 15. 펜윅 트리 (Binary Indexed Tree)

#### 📝 설명
펜윅 트리는 세그먼트 트리보다 구현이 간단하면서도 누적 합 계산과 업데이트를 효율적으로 처리하는 자료구조입니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(log N) - 쿼리 및 업데이트
- **공간 복잡도**: O(N)

#### 🔄 동작 과정 (Pseudocode)
```
// 핵심: 이진 표현에서 마지막 1비트 활용
// idx & -idx = 마지막 1비트 (LSB)

// 1. 업데이트
Update(idx, value):
    while idx <= N:
        tree[idx] += value
        idx += (idx & -idx)  // 다음 구간으로 이동

예시: idx = 6 (110₂)
- 6 & -6 = 2 (010₂)
- 6 → 8 → 16 → ... (2씩, 8씩 증가)

// 2. 구간 합 (1부터 idx까지)
Sum(idx):
    result = 0
    while idx > 0:
        result += tree[idx]
        idx -= (idx & -idx)  // 이전 구간으로 이동
    return result

예시: idx = 7 (111₂)
- 7 & -7 = 1 (001₂)
- 7 → 6 → 4 → 0 (1씩, 2씩, 4씩 감소)

// 3. 구간 합 [left, right]
RangeSum(left, right):
    return Sum(right) - Sum(left - 1)

핵심 아이디어:
- 각 인덱스는 특정 구간의 합을 담당
- tree[i]는 [i-(i&-i)+1, i] 구간의 합
- 이진수의 마지막 1비트로 구간 크기 결정
- 세그먼트 트리보다 공간/상수 효율적

시간 복잡도: O(log N)
공간 복잡도: O(N)
```

#### 💻 C++ 구현
```cpp
const int MAX = 1000001;
long long tree[MAX];
int n;

void update(int idx, long long diff) {
    while (idx <= n) {
        tree[idx] += diff;
        idx += (idx & -idx);
    }
}

long long sum(int idx) {
    long long result = 0;
    while (idx > 0) {
        result += tree[idx];
        idx -= (idx & -idx);
    }
    return result;
}

long long rangeSum(int left, int right) {
    return sum(right) - sum(left - 1);
}
```

---

## 문자열 알고리즘

### 16. KMP 알고리즘 (Knuth-Morris-Pratt)

#### 📝 설명
KMP는 문자열 패턴 매칭 알고리즘으로, 실패 함수를 전처리하여 불필요한 비교를 건너뛰어 효율적으로 패턴을 찾습니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(N + M) - N은 텍스트 길이, M은 패턴 길이
- **공간 복잡도**: O(M) - 실패 함수 배열

#### 🔄 동작 과정 (Pseudocode)
```
// 1단계: 실패 함수 (Failure Function) 전처리
ComputeFailureFunction(pattern):
    M = length(pattern)
    failure[0] = 0  // 첫 문자는 항상 0
    j = 0           // 접두사 길이
    
    // 각 위치에서 최대 접두사-접미사 길이 계산
    for i = 1 to M-1:
        // 불일치 발생: 이전 실패 함수 값으로 이동
        while j > 0 AND pattern[i] != pattern[j]:
            j = failure[j-1]
        
        // 일치: 접두사 길이 증가
        if pattern[i] == pattern[j]:
            j = j + 1
            failure[i] = j
        else:
            failure[i] = 0
    
    return failure

// 2단계: KMP 문자열 매칭
KMP_Search(text, pattern):
    N = length(text)
    M = length(pattern)
    failure = ComputeFailureFunction(pattern)
    matches = []
    j = 0  // 패턴에서 현재 비교 위치
    
    for i = 0 to N-1:  // 텍스트를 순회
        // 불일치: 실패 함수로 점프 (이미 매칭된 부분 활용)
        while j > 0 AND text[i] != pattern[j]:
            j = failure[j-1]
        
        // 문자 일치
        if text[i] == pattern[j]:
            j = j + 1
            
            // 패턴 완전 매칭 성공
            if j == M:
                matches.append(i - M + 1)  // 시작 위치 저장
                j = failure[M-1]            // 다음 매칭 위치로
        
    return matches

핵심 개념:
1. 실패 함수 failure[i]:
   - pattern[0..i]의 부분 문자열에서
   - 접두사이면서 동시에 접미사인 가장 긴 문자열의 길이
   
2. 예시: pattern = "ABABC"
   - i=0: "A" → failure[0] = 0
   - i=1: "AB" → failure[1] = 0
   - i=2: "ABA" → failure[2] = 1 (접두사 "A" = 접미사 "A")
   - i=3: "ABAB" → failure[3] = 2 (접두사 "AB" = 접미사 "AB")
   - i=4: "ABABC" → failure[4] = 0

3. 불일치 시 동작:
   - 나이브: 처음부터 다시 비교 O(NM)
   - KMP: failure 함수로 점프 O(N+M)
   
4. 왜 빠른가?
   - 이미 비교한 문자 정보 재활용
   - 텍스트 포인터는 뒤로 가지 않음
   - 각 문자를 최대 2번만 비교
```

#### 💻 C++ 구현
```cpp
#include <vector>
#include <string>
using namespace std;

vector<int> failure;
string text, pattern;

void computeFailure() {
    int m = pattern.length();
    failure.resize(m, 0);
    
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = failure[j - 1];
        }
        
        if (pattern[i] == pattern[j]) {
            failure[i] = ++j;
        }
    }
}

vector<int> KMP() {
    int n = text.length();
    int m = pattern.length();
    vector<int> result;
    
    computeFailure();
    
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = failure[j - 1];
        }
        
        if (text[i] == pattern[j]) {
            if (j == m - 1) {
                result.push_back(i - m + 1);
                j = failure[j];
            } else {
                j++;
            }
        }
    }
    
    return result;
}
```

---

### 17. 라빈-카프 알고리즘 (Rabin-Karp)

#### 📝 설명
라빈-카프는 해싱을 사용한 문자열 검색 알고리즘입니다. 롤링 해시를 사용하여 평균적으로 빠른 검색을 제공합니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(N + M) 평균, O(NM) 최악
- **공간 복잡도**: O(1)

#### 💻 C++ 구현
```cpp
#include <string>
#include <vector>
using namespace std;

const long long MOD = 1e9 + 7;
const long long BASE = 256;

vector<int> rabinKarp(const string &text, const string &pattern) {
    int n = text.length();
    int m = pattern.length();
    vector<int> result;
    
    if (m > n) return result;
    
    long long patternHash = 0;
    long long textHash = 0;
    long long h = 1;
    
    for (int i = 0; i < m - 1; i++) {
        h = (h * BASE) % MOD;
    }
    
    for (int i = 0; i < m; i++) {
        patternHash = (patternHash * BASE + pattern[i]) % MOD;
        textHash = (textHash * BASE + text[i]) % MOD;
    }
    
    for (int i = 0; i <= n - m; i++) {
        if (patternHash == textHash) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) result.push_back(i);
        }
        
        if (i < n - m) {
            textHash = (BASE * (textHash - text[i] * h) + text[i + m]) % MOD;
            if (textHash < 0) textHash += MOD;
        }
    }
    
    return result;
}
```

---

### 18. Aho-Corasick 알고리즘

#### 📝 설명
Aho-Corasick은 여러 패턴을 동시에 검색하는 문자열 매칭 알고리즘입니다. Trie와 KMP의 실패 함수를 결합하여, 다중 패턴을 효율적으로 찾습니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(N + M + K) - N은 텍스트 길이, M은 패턴들의 총 길이, K는 매칭 개수
- **공간 복잡도**: O(M × ALPHABET_SIZE)

#### 🔄 동작 과정 (Pseudocode)
```
// 1단계: Trie 구축 + 실패 링크 (Failure Link) 계산
BuildAhoCorasick(patterns):
    // Trie에 모든 패턴 삽입
    for each pattern in patterns:
        InsertToTrie(pattern)
    
    // BFS로 실패 링크 계산 (KMP의 실패 함수와 유사)
    queue.enqueue(root)
    
    while queue is not empty:
        current = queue.dequeue()
        
        for each child c of current:
            if current == root:
                failure[c] = root
            else:
                // 부모의 실패 링크를 따라가면서 매칭되는 노드 찾기
                fail = failure[current]
                while fail != root AND fail에 c 자식이 없음:
                    fail = failure[fail]
                
                if fail에 c 자식 존재:
                    failure[c] = fail의 c 자식
                else:
                    failure[c] = root
            
            queue.enqueue(c)

// 2단계: 텍스트에서 패턴 검색
Search(text):
    current = root
    matches = []
    
    for i = 0 to length(text) - 1:
        char = text[i]
        
        // 현재 노드에서 매칭 실패 시 실패 링크 따라감
        while current != root AND current에 char 자식이 없음:
            current = failure[current]
        
        if current에 char 자식 존재:
            current = current의 char 자식
        else:
            current = root
        
        // 현재 위치에서 끝나는 패턴들 확인
        temp = current
        while temp != root:
            if temp가 패턴의 끝:
                matches.append(패턴 정보)
            temp = failure[temp]
    
    return matches

핵심 개념:
1. **Trie**: 모든 패턴을 트리에 저장
2. **실패 링크 (Failure Link)**: 
   - KMP의 실패 함수와 유사
   - 매칭 실패 시 이동할 노드
   - 가장 긴 접두사-접미사 매칭
3. **다중 패턴 검색**: 텍스트 한 번 순회로 모든 패턴 찾기

동작 예시: 패턴 ["he", "she", "his", "hers"], 텍스트 "ushers"
1. Trie 구축:
        root
       /  |  \
      h   s   ...
     / \   \
    e   i   h
    |   |   |
    r   s   e
    s

2. 실패 링크:
   - 'h'의 실패 링크 → root
   - 's'-'h'의 실패 링크 → 'h' (she의 he 부분)
   - 'h'-'e'-'r'-'s'의 실패 링크 → 's'

3. "ushers" 검색:
   - u: root
   - s: root → 's'
   - h: 's' → 's'-'h'
   - e: 's'-'h' → 's'-'h'-'e' (패턴 "she" 매칭!)
   - r: 실패 링크 → 'h'-'e' → 'h'-'e'-'r'
   - s: 'h'-'e'-'r' → 'h'-'e'-'r'-'s' (패턴 "hers" 매칭!)

KMP vs Aho-Corasick:
- KMP: 단일 패턴, O(N + M)
- Aho-Corasick: 다중 패턴, O(N + M₁ + M₂ + ... + Mₖ)
- 여러 패턴 검색 시 AC가 효율적

응용:
1. 바이러스 시그니처 검사
2. 스팸 필터링 (다중 금지어 검색)
3. DNA 서열 분석
4. 침입 탐지 시스템 (IDS)
```

#### 💻 C++ 구현
```cpp
#include <queue>
#include <string>
#include <vector>
using namespace std;

const int ALPHABET_SIZE = 26;

struct AhoCorasickNode {
    AhoCorasickNode* children[ALPHABET_SIZE];
    AhoCorasickNode* failure;
    vector<int> output;
    
    AhoCorasickNode() : failure(nullptr) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }
};

class AhoCorasick {
private:
    AhoCorasickNode* root;
    
public:
    AhoCorasick() {
        root = new AhoCorasickNode();
    }
    
    void insert(const string& pattern, int patternId) {
        AhoCorasickNode* current = root;
        
        for (char ch : pattern) {
            int idx = ch - 'a';
            if (!current->children[idx]) {
                current->children[idx] = new AhoCorasickNode();
            }
            current = current->children[idx];
        }
        
        current->output.push_back(patternId);
    }
    
    void buildFailureLinks() {
        queue<AhoCorasickNode*> q;
        root->failure = root;
        
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (root->children[i]) {
                root->children[i]->failure = root;
                q.push(root->children[i]);
            }
        }
        
        while (!q.empty()) {
            AhoCorasickNode* current = q.front();
            q.pop();
            
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (current->children[i]) {
                    AhoCorasickNode* child = current->children[i];
                    AhoCorasickNode* fail = current->failure;
                    
                    while (fail != root && !fail->children[i]) {
                        fail = fail->failure;
                    }
                    
                    if (fail->children[i] && fail->children[i] != child) {
                        child->failure = fail->children[i];
                    } else {
                        child->failure = root;
                    }
                    
                    for (int id : child->failure->output) {
                        child->output.push_back(id);
                    }
                    
                    q.push(child);
                }
            }
        }
    }
    
    vector<pair<int, int>> search(const string& text) {
        vector<pair<int, int>> matches;
        AhoCorasickNode* current = root;
        
        for (int i = 0; i < text.length(); i++) {
            int idx = text[i] - 'a';
            
            while (current != root && !current->children[idx]) {
                current = current->failure;
            }
            
            if (current->children[idx]) {
                current = current->children[idx];
            }
            
            for (int patternId : current->output) {
                matches.push_back({i, patternId});
            }
        }
        
        return matches;
    }
};
```

---

## 수학 알고리즘

### 19. 유클리드 호제법 (GCD/LCM)

#### 📝 설명
유클리드 호제법은 두 수의 최대공약수를 효율적으로 구하는 알고리즘입니다. 최소공배수는 GCD를 이용하여 계산할 수 있습니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(log min(a, b))
- **공간 복잡도**: O(1) 또는 O(log min(a, b)) - 재귀 스택

#### 🔄 동작 과정 (Pseudocode)
```
// 재귀적 방법
GCD_Recursive(a, b):
    // 기저 사례: b가 0이면 a가 GCD
    if b == 0:
        return a
    
    // 재귀 호출: GCD(b, a mod b)
    return GCD_Recursive(b, a mod b)

// 반복적 방법
GCD_Iterative(a, b):
    while b != 0:
        temp = b
        b = a mod b
        a = temp
    return a

// 최소공배수 (LCM)
LCM(a, b):
    return (a / GCD(a, b)) * b
    // 또는: (a * b) / GCD(a, b)
    // 주의: 오버플로우 방지를 위해 먼저 나누기

동작 예시: GCD(48, 18)
1. GCD(48, 18)
   48 mod 18 = 12
   → GCD(18, 12)

2. GCD(18, 12)
   18 mod 12 = 6
   → GCD(12, 6)

3. GCD(12, 6)
   12 mod 6 = 0
   → GCD(6, 0)

4. GCD(6, 0)
   b == 0 → return 6

핵심 원리:
- 유클리드 정리: GCD(a, b) = GCD(b, a mod b)
- 나머지 연산으로 빠르게 감소
- 피보나치 수열 경우 최악 O(log min(a,b))
```

#### 💻 C++ 구현
```cpp
#include <algorithm>
using namespace std;

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long lcm(long long a, long long b) {
    return (a / gcd(a, b)) * b;
}

long long gcdIterative(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
```

---

### 20. 에라토스테네스의 체 (Sieve of Eratosthenes)

#### 📝 설명
에라토스테네스의 체는 특정 범위 내의 모든 소수를 찾는 효율적인 알고리즘입니다. 소수의 배수들을 체거하는 방식으로 동작합니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(N log log N)
- **공간 복잡도**: O(N)

#### 🔄 동작 과정 (Pseudocode)
```
SieveOfEratosthenes(N):
    // 1. 모든 수를 소수로 가정
    isPrime[0..N] = true
    isPrime[0] = false
    isPrime[1] = false
    
    // 2. 2부터 √N까지 반복
    for i = 2 to √N:
        // 3. i가 소수라면
        if isPrime[i]:
            // 4. i의 모든 배수를 합성수로 표시
            // i²부터 시작 (작은 배수는 이미 제거됨)
            for j = i*i to N step i:
                isPrime[j] = false
    
    return isPrime

동작 예시: N = 30
1. 초기: [2,3,4,5,6,7,8,9,10,...,30] 모두 소수 후보

2. i=2: 4,6,8,10,12,14,16,18,20,22,24,26,28,30 제거
   남은 수: [2,3,5,7,9,11,13,15,17,19,21,23,25,27,29]

3. i=3: 9,15,21,27 제거
   남은 수: [2,3,5,7,11,13,17,19,23,25,29]

4. i=5: 25 제거
   최종 소수: [2,3,5,7,11,13,17,19,23,29]

최적화 포인트:
1. i*i부터 시작: i*k (k<i)는 이미 제거됨
2. √N까지만 검사: 큰 수의 배수는 작은 소수의 배수
3. 비트 최적화: 홀수만 처리 가능

시간 복잡도 분석:
- 각 소수 p에 대해 N/p 번 작업
- ∑(N/p) = N * ∑(1/p) ≈ O(N log log N)
```

#### 💻 C++ 구현
```cpp
#include <vector>
using namespace std;

vector<bool> sieve(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    return isPrime;
}

vector<int> getPrimes(int n) {
    vector<bool> isPrime = sieve(n);
    vector<int> primes;
    
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    
    return primes;
}
```

---

### 21. 분할 정복을 이용한 거듭제곱 (Fast Exponentiation)

#### 📝 설명
분할 정복을 사용하여 거듭제곱을 효율적으로 계산하는 알고리즘입니다. 행렬 거듭제곱에도 적용됩니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(log N)
- **공간 복잡도**: O(log N) - 재귀 스택

#### 🔄 동작 과정 (Pseudocode)
```
// 재귀적 방법 (분할 정복)
FastPower_Recursive(base, exp, mod):
    // 1. 기저 사례: 지수가 0이면 1 반환
    if exp == 0:
        return 1
    
    // 2. 지수를 절반으로 나누어 재귀 호출
    half = FastPower_Recursive(base, exp / 2, mod)
    
    // 3. 절반의 제곱 계산 (분할 정복의 핵심)
    result = (half * half) % mod
    
    // 4. 지수가 홀수면 base를 한 번 더 곱함
    if exp % 2 == 1:
        result = (result * base) % mod
    
    return result

// 반복적 방법 (비트 연산)
FastPower_Iterative(base, exp, mod):
    result = 1
    base = base % mod
    
    // 지수가 0이 될 때까지 반복
    while exp > 0:
        // 1. 지수의 마지막 비트가 1이면 (홀수)
        if exp & 1:  // exp의 최하위 비트 확인
            result = (result * base) % mod
        
        // 2. base를 제곱하고 지수를 절반으로
        base = (base * base) % mod
        exp = exp >> 1  // 비트 오른쪽 시프트 (나누기 2)
    
    return result

동작 예시: 2^10 계산
재귀적 방법:
1. 2^10 = (2^5)^2
2. 2^5 = (2^2)^2 × 2
3. 2^2 = (2^1)^2
4. 2^1 = (2^0)^2 × 2
5. 2^0 = 1
역추적: 1 → 2 → 4 → 32 → 1024

반복적 방법 (10 = 1010₂):
1. exp=10 (1010₂): 비트 0 → base=2^2=4
2. exp=5 (101₂): 비트 1 → result=1×4=4, base=4^2=16
3. exp=2 (10₂): 비트 0 → base=16^2=256
4. exp=1 (1₂): 비트 1 → result=4×256=1024

핵심 원리:
- a^n = (a^(n/2))^2 (n이 짝수)
- a^n = (a^(n/2))^2 × a (n이 홀수)
- 나이브: O(N) → 분할정복: O(log N)
- 비트 연산: 지수의 이진 표현 활용

응용:
- 모듈러 거듭제곱 (큰 수 계산)
- 행렬 거듭제곱 (피보나치 빠른 계산)
- 모듈러 역원 계산 (페르마의 소정리)
```

#### 💻 C++ 구현
```cpp
const long long MOD = 1e9 + 7;

long long power(long long base, long long exp) {
    if (exp == 0) return 1;
    
    long long half = power(base, exp / 2);
    long long result = (half * half) % MOD;
    
    if (exp % 2 == 1) {
        result = (result * base) % MOD;
    }
    
    return result;
}

long long powerIterative(long long base, long long exp) {
    long long result = 1;
    base %= MOD;
    
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp >>= 1;
    }
    
    return result;
}
```

---

### 22. 조합 (Combination with DP)

#### 📝 설명
조합을 동적 계획법으로 계산합니다. 파스칼의 삼각형을 이용하여 nCr을 효율적으로 구합니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(N × K)
- **공간 복잡도**: O(N × K) 또는 O(K) - 공간 최적화 가능

#### 🔄 동작 과정 (Pseudocode)
```
// DP를 이용한 조합 계산 (파스칼의 삼각형)
PrecomputeCombination(maxN):
    // 1. DP 테이블 초기화
    // C[n][r] = nCr (n개 중 r개를 선택)
    for n = 0 to maxN:
        C[n][0] = 1  // nC0 = 1 (아무것도 선택 안함)
        C[n][n] = 1  // nCn = 1 (모두 선택)
        
        // 2. 파스칼의 삼각형 점화식 적용
        for r = 1 to n-1:
            // nCr = (n-1)C(r-1) + (n-1)Cr
            // 의미: n번째 원소를 선택 + 선택 안 함
            C[n][r] = (C[n-1][r-1] + C[n-1][r]) % MOD

// 단일 조합 계산
Combination(n, r):
    // 1. 경계 조건 확인
    if r > n:
        return 0
    if r == 0 or r == n:
        return 1
    
    // 2. 최적화: nCr = nC(n-r) 활용
    if r > n - r:
        r = n - r
    
    // 3. 전처리된 값 반환
    return C[n][r]

파스칼의 삼각형 예시:
      1
     1 1
    1 2 1
   1 3 3 1
  1 4 6 4 1
 1 5 10 10 5 1

동작 예시: 5C2 계산
1. 초기화: C[0][0] = 1
2. C[1][0] = 1, C[1][1] = 1
3. C[2][0] = 1, C[2][1] = 2, C[2][2] = 1
4. C[3][0] = 1, C[3][1] = 3, C[3][2] = 3, C[3][3] = 1
5. C[4][0] = 1, C[4][1] = 4, C[4][2] = 6, C[4][3] = 4, C[4][4] = 1
6. C[5][2] = C[4][1] + C[4][2] = 4 + 6 = 10

핵심 점화식:
- C[n][r] = C[n-1][r-1] + C[n-1][r]
- 의미: 
  * C[n-1][r-1]: n번째 원소를 포함하는 경우
  * C[n-1][r]: n번째 원소를 포함하지 않는 경우

최적화 기법:
1. 공간 최적화: 1차원 배열 사용
   - 역순으로 계산하여 O(K) 공간
2. 대칭성 활용: nCr = nC(n-r)
3. 모듈러 연산: 큰 수 오버플로우 방지

다른 계산 방법 비교:
1. DP (파스칼): O(N×K) 시간, 여러 쿼리에 유리
2. 팩토리얼: nCr = n!/(r!(n-r)!) - 오버플로우 위험
3. 페르마의 소정리: 모듈러 역원 활용 - O(log MOD)
```

#### 💻 C++ 구현
```cpp
const int MAX = 1001;
const long long MOD = 10007;
long long C[MAX][MAX];

void precomputeCombination() {
    for (int i = 0; i < MAX; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
        }
    }
}

long long combination(int n, int r) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    return C[n][r];
}
```

---

## 정렬과 탐색

### 23. 이진 탐색 (Binary Search)

#### 📝 설명
이진 탐색은 정렬된 배열에서 특정 값을 O(log N)에 찾는 알고리즘입니다. 매개변수 탐색(Parametric Search)에도 활용됩니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(log N)
- **공간 복잡도**: O(1)

#### 🔄 동작 과정 (Pseudocode)
```
// 기본 이진 탐색 (특정 값 찾기)
BinarySearch(arr, target):
    left = 0
    right = length(arr) - 1
    
    while left <= right:
        // 1. 중간 인덱스 계산 (오버플로우 방지)
        mid = left + (right - left) / 2
        
        // 2. 목표값 찾음
        if arr[mid] == target:
            return mid
        
        // 3. 목표값이 더 크면 오른쪽 반 탐색
        else if arr[mid] < target:
            left = mid + 1
        
        // 4. 목표값이 더 작으면 왼쪽 반 탐색
        else:
            right = mid - 1
    
    return -1  // 찾지 못함

// Lower Bound (target 이상인 첫 위치)
LowerBound(arr, target):
    left = 0
    right = length(arr)  // 주의: length, not length-1
    
    while left < right:
        mid = left + (right - left) / 2
        
        // target보다 작으면 오른쪽 탐색
        if arr[mid] < target:
            left = mid + 1
        // target 이상이면 왼쪽 탐색 (mid 포함)
        else:
            right = mid
    
    return left

// Upper Bound (target 초과인 첫 위치)
UpperBound(arr, target):
    left = 0
    right = length(arr)
    
    while left < right:
        mid = left + (right - left) / 2
        
        // target 이하면 오른쪽 탐색
        if arr[mid] <= target:
            left = mid + 1
        // target 초과면 왼쪽 탐색
        else:
            right = mid
    
    return left

동작 예시: arr = [1, 3, 5, 7, 9, 11], target = 7
1. left=0, right=5, mid=2: arr[2]=5 < 7 → left=3
2. left=3, right=5, mid=4: arr[4]=9 > 7 → right=4
3. left=3, right=4, mid=3: arr[3]=7 == 7 → 찾음! 반환 3

Lower Bound 예시: arr = [1, 3, 5, 5, 5, 7, 9], target = 5
1. left=0, right=7, mid=3: arr[3]=5 ≥ 5 → right=3
2. left=0, right=3, mid=1: arr[1]=3 < 5 → left=2
3. left=2, right=3, mid=2: arr[2]=5 ≥ 5 → right=2
4. left=2, right=2 → 종료, 반환 2 (첫 번째 5의 위치)

Upper Bound 예시: 같은 배열, target = 5
→ 반환 5 (마지막 5 다음 위치)

핵심 차이점:
1. BinarySearch: 정확히 일치하는 값 찾기
2. LowerBound: target ≥ x인 첫 위치 (C++ lower_bound)
3. UpperBound: target > x인 첫 위치 (C++ upper_bound)

매개변수 탐색 (Parametric Search):
// 조건을 만족하는 최댓값/최솟값 찾기
ParametricSearch(predicate):
    left = min_value
    right = max_value
    answer = -1
    
    while left <= right:
        mid = left + (right - left) / 2
        
        // 조건 만족하면 답 갱신 후 더 큰 값 탐색
        if predicate(mid):
            answer = mid
            left = mid + 1
        else:
            right = mid - 1
    
    return answer

주의사항:
- 배열은 반드시 정렬되어야 함
- mid 계산 시 오버플로우 주의: mid = (left + right) / 2 ❌
- 올바른 방법: mid = left + (right - left) / 2 ✅
```

#### 💻 C++ 구현
```cpp
#include <vector>
using namespace std;

int binarySearch(vector<int> &arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

int lowerBound(vector<int> &arr, int target) {
    int left = 0;
    int right = arr.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

int upperBound(vector<int> &arr, int target) {
    int left = 0;
    int right = arr.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}
```

---

### 24. 병합 정렬 (Merge Sort)

#### 📝 설명
병합 정렬은 분할 정복을 사용한 안정적인 정렬 알고리즘입니다. 배열을 반으로 나누어 정렬한 후 병합합니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(N log N) - 모든 경우
- **공간 복잡도**: O(N)

#### 🔄 동작 과정 (Pseudocode)
```
// 병합 정렬 메인 함수
MergeSort(arr, left, right):
    // 1. 기저 사례: 원소가 1개 이하면 이미 정렬됨
    if left >= right:
        return
    
    // 2. 분할: 배열을 반으로 나눔
    mid = left + (right - left) / 2
    
    // 3. 재귀적으로 왼쪽 반 정렬
    MergeSort(arr, left, mid)
    
    // 4. 재귀적으로 오른쪽 반 정렬
    MergeSort(arr, mid + 1, right)
    
    // 5. 병합: 정렬된 두 부분을 합침
    Merge(arr, left, mid, right)

// 두 정렬된 부분 배열을 병합
Merge(arr, left, mid, right):
    // 1. 임시 배열 생성
    temp = new array[right - left + 1]
    i = left      // 왼쪽 부분의 시작
    j = mid + 1   // 오른쪽 부분의 시작
    k = 0         // temp 배열 인덱스
    
    // 2. 두 부분을 비교하며 작은 값부터 temp에 저장
    while i <= mid AND j <= right:
        if arr[i] <= arr[j]:
            temp[k] = arr[i]
            i++
        else:
            temp[k] = arr[j]
            j++
        k++
    
    // 3. 왼쪽 부분에 남은 원소 복사
    while i <= mid:
        temp[k] = arr[i]
        i++
        k++
    
    // 4. 오른쪽 부분에 남은 원소 복사
    while j <= right:
        temp[k] = arr[j]
        j++
        k++
    
    // 5. temp의 내용을 원본 배열에 복사
    for k = 0 to length(temp) - 1:
        arr[left + k] = temp[k]

동작 예시: arr = [38, 27, 43, 3, 9, 82, 10]
분할 단계:
[38, 27, 43, 3, 9, 82, 10]
      ↙              ↘
[38, 27, 43]    [3, 9, 82, 10]
  ↙      ↘        ↙         ↘
[38]  [27, 43]  [3, 9]    [82, 10]
       ↙  ↘      ↙  ↘       ↙   ↘
      [27][43]  [3] [9]   [82] [10]

병합 단계:
[27] [43] → [27, 43]
[3] [9] → [3, 9]
[82] [10] → [10, 82]
[38] [27, 43] → [27, 38, 43]
[3, 9] [10, 82] → [3, 9, 10, 82]
[27, 38, 43] [3, 9, 10, 82] → [3, 9, 10, 27, 38, 43, 82]

병합 과정 상세 예시: [27, 38] + [3, 9]
1. i=0(27), j=0(3): 3 < 27 → temp=[3], j++
2. i=0(27), j=1(9): 9 < 27 → temp=[3,9], j++
3. j > right, 왼쪽 남은 원소 복사 → temp=[3,9,27,38]

시간 복잡도 분석:
- 분할: O(log N) 레벨
- 각 레벨에서 병합: O(N)
- 총: O(N log N)

특징:
1. 안정 정렬 (Stable Sort): 같은 값의 상대적 순서 유지
2. 외부 정렬에 적합: 대용량 데이터
3. 추가 메모리 필요: O(N)
4. 분할 정복의 전형적인 예

다른 정렬 알고리즘 비교:
- Quick Sort: 평균 O(N log N), 최악 O(N²), 제자리 정렬
- Heap Sort: O(N log N), 불안정, 제자리 정렬
- Merge Sort: 항상 O(N log N), 안정, O(N) 추가 메모리

응용:
- 역순쌍(Inversion) 개수 세기
- 연결 리스트 정렬 (O(1) 공간)
- 외부 정렬 (디스크 기반)
```

#### 💻 C++ 구현
```cpp
#include <vector>
using namespace std;

void merge(vector<int> &arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    
    for (int i = 0; i < temp.size(); i++) {
        arr[left + i] = temp[i];
    }
}

void mergeSort(vector<int> &arr, int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
```

---

### 25. 투 포인터 (Two Pointers)

#### 📝 설명
투 포인터는 두 개의 포인터를 사용하여 배열이나 리스트를 효율적으로 탐색하는 기법입니다. 정렬된 배열에서 특히 유용합니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(N)
- **공간 복잡도**: O(1)

#### 🔄 동작 과정 (Pseudocode)
```
// 패턴 1: 양 끝에서 시작 (Two Sum 문제)
TwoPointers_TwoSum(arr, target):
    // 1. 배열 정렬 (이미 정렬되어 있으면 생략)
    sort(arr)
    
    // 2. 양 끝에서 시작
    left = 0
    right = length(arr) - 1
    
    while left < right:
        sum = arr[left] + arr[right]
        
        // 3. 합이 목표값과 같으면 찾음
        if sum == target:
            return true (또는 {left, right})
        
        // 4. 합이 목표값보다 작으면 왼쪽 포인터 이동
        else if sum < target:
            left++
        
        // 5. 합이 목표값보다 크면 오른쪽 포인터 이동
        else:
            right--
    
    return false

// 패턴 2: 같은 방향 (슬라이딩 윈도우)
TwoPointers_SubarraySum(arr, K):
    left = 0
    sum = 0
    count = 0
    
    // 1. 오른쪽 포인터로 확장
    for right = 0 to length(arr) - 1:
        sum += arr[right]
        
        // 2. 합이 K를 초과하면 왼쪽 포인터 이동
        while sum > K AND left <= right:
            sum -= arr[left]
            left++
        
        // 3. 합이 K와 같으면 카운트
        if sum == K:
            count++
    
    return count

// 패턴 3: 세 수의 합 (3Sum)
ThreeSum(arr, target):
    sort(arr)
    result = []
    
    // 1. 첫 번째 수 고정
    for i = 0 to length(arr) - 3:
        // 중복 제거
        if i > 0 AND arr[i] == arr[i-1]:
            continue
        
        // 2. 나머지 두 수는 투 포인터로 탐색
        left = i + 1
        right = length(arr) - 1
        
        while left < right:
            sum = arr[i] + arr[left] + arr[right]
            
            if sum == target:
                result.append([arr[i], arr[left], arr[right]])
                
                // 중복 제거
                while left < right AND arr[left] == arr[left+1]:
                    left++
                while left < right AND arr[right] == arr[right-1]:
                    right--
                
                left++
                right--
            else if sum < target:
                left++
            else:
                right--
    
    return result

동작 예시 1: Two Sum, arr = [2, 7, 11, 15], target = 9
1. left=0(2), right=3(15): 2+15=17 > 9 → right--
2. left=0(2), right=2(11): 2+11=13 > 9 → right--
3. left=0(2), right=1(7): 2+7=9 == 9 → 찾음!

동작 예시 2: Subarray Sum, arr = [1, 2, 3, 4, 5], K = 9
1. right=0: sum=1
2. right=1: sum=3
3. right=2: sum=6
4. right=3: sum=10 > 9 → left++, sum=9 (2+3+4)
5. right=4: sum=14 > 9 → left++, sum=12 > 9 → left++, sum=9 (4+5)
결과: 2개의 부분 배열

핵심 아이디어:
1. 정렬된 배열 활용
2. 포인터 이동으로 탐색 범위 축소
3. 나이브: O(N²) → 투 포인터: O(N)

투 포인터 패턴 분류:
1. 양 끝에서 접근 (Opposite Direction)
   - Two Sum, 팰린드롬 검사
   - 정렬 필수
   
2. 같은 방향 (Same Direction / Sliding Window)
   - 부분 배열 합, 최장 부분 문자열
   - 정렬 불필요
   
3. 빠른/느린 포인터 (Fast/Slow)
   - 연결 리스트 사이클 탐지
   - Floyd's Cycle Detection

주의사항:
- 배열이 정렬되어 있어야 하는지 확인
- 포인터 이동 조건 명확히 설정
- 경계 조건 체크 (left < right)
```

#### 💻 C++ 구현
```cpp
#include <vector>
#include <algorithm>
using namespace std;

bool twoSum(vector<int> &arr, int target) {
    sort(arr.begin(), arr.end());
    
    int left = 0;
    int right = arr.size() - 1;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        
        if (sum == target) {
            return true;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    return false;
}

int countSubarraySum(vector<int> &arr, int k) {
    int count = 0;
    int left = 0;
    int sum = 0;
    
    for (int right = 0; right < arr.size(); right++) {
        sum += arr[right];
        
        while (sum > k && left <= right) {
            sum -= arr[left];
            left++;
        }
        
        if (sum == k) {
            count++;
        }
    }
    
    return count;
}
```

---

## 기타 중요 알고리즘

### 26. 백트래킹 (Backtracking)

#### 📝 설명
백트래킹은 모든 가능한 경우를 탐색하되, 조건을 만족하지 않으면 즉시 되돌아가는 기법입니다. N-Queens, 스도쿠 등에 사용됩니다.

#### ⏱️ 복잡도
- **시간 복잡도**: 문제마다 다름 (일반적으로 지수 시간)
- **공간 복잡도**: O(N) - 재귀 깊이

#### 🔄 동작 과정 (Pseudocode)
```
// N-Queens 문제
NQueens(row):
    // 1. 기저 사례: 모든 행에 퀸을 배치했으면 해 발견
    if row == N:
        count++
        printSolution()
        return
    
    // 2. 현재 행의 각 열을 시도
    for col = 0 to N-1:
        // 3. 현재 위치가 안전한지 검사
        if isSafe(row, col):
            // 4. 선택: 퀸 배치
            board[row] = col
            
            // 5. 재귀: 다음 행으로 진행
            NQueens(row + 1)
            
            // 6. 되돌리기 (Backtrack): 선택 취소
            board[row] = -1

// 안전성 검사 함수
isSafe(row, col):
    // 이전 행들의 퀸 위치 확인
    for i = 0 to row-1:
        // 같은 열에 퀸이 있는지 확인
        if board[i] == col:
            return false
        
        // 대각선에 퀸이 있는지 확인
        // |행 차이| == |열 차이| 이면 대각선
        if abs(board[i] - col) == abs(i - row):
            return false
    
    return true

동작 예시: 4-Queens
행0: 퀸을 (0,0)에 배치 시도
  행1: (1,0) X (같은 열), (1,1) X (대각선)
       (1,2) O → 배치
    행2: (2,0) O → 배치
      행3: 모든 열 X → Backtrack
    행2: (2,1) X, (2,2) X, (2,3) X → Backtrack
  행1: (1,3) O → 배치
    행2: (2,0) X, (2,1) O → 배치
      행3: 모든 열 X → Backtrack
    ...
행0: 퀸을 (0,1)에 배치 시도
  행1: (1,3) O → 배치
    행2: (2,0) O → 배치
      행3: (3,2) O → 해 발견!

백트래킹 핵심 요소:
1. **선택 (Choice)**: 가능한 옵션 중 하나 선택
2. **제약 (Constraint)**: 조건 검사로 가지치기
3. **목표 (Goal)**: 해를 찾았는지 확인
4. **되돌리기 (Backtrack)**: 선택 취소 및 다른 옵션 시도

일반적인 백트래킹 템플릿:
Backtrack(state):
    if isGoal(state):
        processSolution(state)
        return
    
    for each choice in getChoices(state):
        if isValid(choice):
            makeChoice(choice)
            Backtrack(nextState)
            undoChoice(choice)  // 핵심: 상태 복원

다른 백트래킹 문제 예시:
1. 스도쿠: 각 칸에 1-9 배치
2. 순열 생성: N개 원소의 모든 순열
3. 부분집합: N개 원소의 모든 부분집합
4. 그래프 색칠: K색으로 그래프 칠하기
5. 미로 탐색: 시작점에서 끝점까지 경로

최적화 기법:
1. 가지치기 (Pruning): 불가능한 경로 조기 제거
2. 휴리스틱: 유망한 선택 우선 시도
3. 메모이제이션: 중복 계산 방지

시간 복잡도:
- N-Queens: O(N!)
- 스도쿠: O(9^(빈 칸 수))
- 순열: O(N!)
```

#### 💻 C++ 구현 (N-Queens)
```cpp
#include <vector>
using namespace std;

int N;
vector<int> board;
int count = 0;

bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || 
            abs(board[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

void solveNQueens(int row) {
    if (row == N) {
        count++;
        return;
    }
    
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row] = col;
            solveNQueens(row + 1);
            board[row] = -1;
        }
    }
}
```

---

### 27. 위상 정렬 (Topological Sort)

#### 📝 설명
위상 정렬은 방향 그래프의 정점을 간선 방향을 거스르지 않으면서 나열하는 알고리즘입니다. DAG에서만 가능합니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(V + E)
- **공간 복잡도**: O(V)

#### 🔄 동작 과정 (Pseudocode)
```
// 방법 1: 칸의 알고리즘 (Kahn's Algorithm) - BFS 기반
TopologicalSort_Kahn(graph, V):
    // 1. 각 정점의 진입 차수 계산
    indegree[1..V] = 0
    for each vertex u:
        for each edge (u, v):
            indegree[v]++
    
    // 2. 진입 차수가 0인 정점을 큐에 삽입
    queue = empty queue
    for v = 1 to V:
        if indegree[v] == 0:
            queue.enqueue(v)
    
    result = []
    
    // 3. 큐가 빌 때까지 반복
    while queue is not empty:
        // 4. 진입 차수 0인 정점 꺼내기
        current = queue.dequeue()
        result.append(current)
        
        // 5. 해당 정점과 연결된 간선 제거 (진입 차수 감소)
        for each edge (current, next):
            indegree[next]--
            
            // 6. 진입 차수가 0이 되면 큐에 추가
            if indegree[next] == 0:
                queue.enqueue(next)
    
    // 7. 사이클 검사
    if length(result) != V:
        return "사이클 존재 - 위상 정렬 불가"
    
    return result

// 방법 2: DFS 기반
TopologicalSort_DFS(graph, V):
    visited[1..V] = false
    stack = empty stack
    
    // 1. 모든 정점에 대해 DFS 수행
    for v = 1 to V:
        if not visited[v]:
            DFS_TopSort(v, visited, stack, graph)
    
    // 2. 스택에서 꺼내면서 결과 생성
    result = []
    while stack is not empty:
        result.append(stack.pop())
    
    return result

// DFS 헬퍼 함수
DFS_TopSort(v, visited, stack, graph):
    visited[v] = true
    
    // 1. 인접한 모든 정점 방문
    for each edge (v, next) in graph:
        if not visited[next]:
            DFS_TopSort(next, visited, stack, graph)
    
    // 2. 모든 후속 정점 처리 후 스택에 추가 (핵심!)
    stack.push(v)

동작 예시: 
그래프: 1→2, 1→3, 2→4, 3→4, 4→5

진입 차수:
1: 0, 2: 1, 3: 1, 4: 2, 5: 1

Kahn's Algorithm 실행:
1. 초기 큐: [1] (진입차수 0)
   결과: []

2. 1 처리: 큐: [2, 3]
   진입차수: 2: 0, 3: 0, 4: 2, 5: 1
   결과: [1]

3. 2 처리: 큐: [3]
   진입차수: 3: 0, 4: 1, 5: 1
   결과: [1, 2]

4. 3 처리: 큐: [4]
   진입차수: 4: 0, 5: 1
   결과: [1, 2, 3]

5. 4 처리: 큐: [5]
   진입차수: 5: 0
   결과: [1, 2, 3, 4]

6. 5 처리: 큐: []
   결과: [1, 2, 3, 4, 5]

핵심 개념:
- **진입 차수 (In-degree)**: 정점으로 들어오는 간선 수
- **DAG (Directed Acyclic Graph)**: 사이클 없는 방향 그래프
- **위상 순서**: u→v 간선이 있으면 u가 v보다 먼저

두 방법 비교:
1. Kahn's (BFS):
   - 진입 차수 사용
   - 사이클 탐지 용이
   - 여러 해 중 하나 (사전순 등) 선택 가능
   
2. DFS:
   - 스택 사용 (후입선출)
   - 구현이 더 간단
   - 재귀 스택 사용

응용:
1. 작업 스케줄링: 선행 작업 조건
2. 빌드 시스템: 의존성 해결
3. 교육과정 계획: 선수과목
4. 데이터 직렬화: 객체 의존성

사이클 탐지:
- Kahn's: result 길이 != V
- DFS: 재귀 스택 확인 (방문 중인 정점 재방문)
```

#### 💻 C++ 구현
```cpp
#include <vector>
#include <queue>
using namespace std;

vector<int> topologicalSort(int n, vector<vector<int>> &graph, vector<int> &indegree) {
    vector<int> result;
    queue<int> q;
    
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        result.push_back(cur);
        
        for (int next : graph[cur]) {
            indegree[next]--;
            if (indegree[next] == 0) {
                q.push(next);
            }
        }
    }
    
    return result;
}
```

---

## 📚 참고사항

### 일반적인 헤더 파일
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <set>
#include <cstring>
using namespace std;
```

### 유용한 매크로와 상수
```cpp
#define MAX 100001
#define INF 987654321
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>

const int MOD = 1e9 + 7;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
```

### 입출력 최적화
```cpp
ios_base::sync_with_stdio(false);
cin.tie(NULL);
cout.tie(NULL);
```

---

## 🎯 알고리즘 선택 가이드

| 문제 유형 | 추천 알고리즘 | 시간 복잡도 |
|----------|-------------|-----------|
| 최단 경로 (양수) | Dijkstra | O((V+E) log V) |
| 최단 경로 (음수) | Bellman-Ford | O(VE) |
| 모든 쌍 최단 경로 | Floyd-Warshall | O(V³) |
| 최소 신장 트리 | Kruskal/Prim | O(E log E) |
| 문자열 검색 | KMP | O(N+M) |
| 구간 쿼리 | Segment Tree | O(log N) |
| 집합 관리 | Union-Find | O(α(N)) |
| 정렬된 배열 검색 | Binary Search | O(log N) |
| 순열/조합 | Backtracking | O(N!) |
| 최장 증가 수열 | DP + Binary Search | O(N log N) |

---

## 계산 기하학

### 28. CCW (Counter-Clockwise) 알고리즘

#### 📝 설명
CCW 알고리즘은 3개의 점이 이루는 방향을 판단하는 기하학 알고리즘입니다. 세 점이 반시계 방향, 시계 방향, 또는 일직선상에 있는지를 판별합니다. 선분 교차 판정, Convex Hull 등에 활용됩니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(1)
- **공간 복잡도**: O(1)

#### 🔄 동작 과정 (Pseudocode)
```
// CCW 계산 (외적 벡터 사용)
CCW(p1, p2, p3):
    // 벡터의 외적 계산
    // (p2 - p1) × (p3 - p1)
    // = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x)
    
    result = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x)
    
    // 1. 양수: 반시계 방향 (CCW)
    if result > 0:
        return 1
    
    // 2. 음수: 시계 방향 (CW)
    else if result < 0:
        return -1
    
    // 3. 0: 일직선 (Collinear)
    else:
        return 0

// 선분 교차 판정
LineIntersection(p1, p2, p3, p4):
    // 선분 (p1, p2)와 (p3, p4)의 교차 여부
    
    // 1. 각 선분에 대해 다른 선분의 두 점이 양쪽에 있는지 확인
    ccw1 = CCW(p1, p2, p3) * CCW(p1, p2, p4)
    ccw2 = CCW(p3, p4, p1) * CCW(p3, p4, p2)
    
    // 2. 일직선상에 있는 경우 (ccw1 == 0 AND ccw2 == 0)
    if ccw1 == 0 AND ccw2 == 0:
        // 두 선분이 겹치는지 확인
        // 좌표 정렬 후 범위 비교
        if p1 > p2: swap(p1, p2)
        if p3 > p4: swap(p3, p4)
        return p3 <= p2 AND p1 <= p4
    
    // 3. 일반적인 경우: 두 값이 모두 ≤ 0이면 교차
    return ccw1 <= 0 AND ccw2 <= 0

동작 예시 1: CCW 판정
점 A(0, 0), B(2, 2), C(4, 0)
외적 = (2-0)*(0-0) - (2-0)*(4-0)
     = 2*0 - 2*4
     = -8 < 0
결과: 시계 방향 (CW)

시각화:
    B(2,2)
   /  \
  /    \
A(0,0)--C(4,0)

점 A(0, 0), B(2, 2), C(0, 4)
외적 = (2-0)*(4-0) - (2-0)*(0-0)
     = 2*4 - 2*0
     = 8 > 0
결과: 반시계 방향 (CCW)

시각화:
C(0,4)
  |  \
  |   \
A(0,0)-B(2,2)

동작 예시 2: 선분 교차
선분1: (0,0)-(2,2)
선분2: (0,2)-(2,0)

ccw1 = CCW(0,0, 2,2, 0,2) * CCW(0,0, 2,2, 2,0)
     = 1 * (-1) = -1
ccw2 = CCW(0,2, 2,0, 0,0) * CCW(0,2, 2,0, 2,2)
     = 1 * (-1) = -1

ccw1 <= 0 AND ccw2 <= 0 → 교차함!

수학적 배경:
1. 외적 (Cross Product):
   - 벡터 u × v = |u||v|sin(θ)
   - 2D: (u.x, u.y) × (v.x, v.y) = u.x*v.y - u.y*v.x
   
2. 기하학적 의미:
   - 외적 > 0: 좌회전 (반시계)
   - 외적 < 0: 우회전 (시계)
   - 외적 = 0: 직진 (일직선)

3. 선분 교차 조건:
   - 선분 AB에 대해 C와 D가 서로 반대편
   - 선분 CD에 대해 A와 B가 서로 반대편

응용:
1. **Convex Hull (Graham Scan)**:
   - 각도 순으로 정렬
   - CCW로 볼록성 판정
   
2. **선분 교차 판정**:
   - 충돌 감지
   - 지도 앱 경로 계산
   
3. **다각형 내부 점 판정**:
   - Ray Casting 알고리즘
   
4. **면적 계산**:
   - 삼각형 면적 = |외적| / 2

주의사항:
- 정수 오버플로우: long long 사용
- 부동소수점 오차: epsilon 비교
- 평행/일치 선분 처리
```

#### 💻 C++ 구현
```cpp
struct Point {
    long long x, y;
};

int ccw(Point p1, Point p2, Point p3) {
    long long result = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    
    if (result > 0) return 1;
    if (result < 0) return -1;
    return 0;
}

int ccw(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3) {
    long long result = x1 * y2 + x2 * y3 + x3 * y1 - (x2 * y1 + x3 * y2 + x1 * y3);
    
    if (result > 0) return 1;
    if (result < 0) return -1;
    return 0;
}

bool lineIntersection(Point p1, Point p2, Point p3, Point p4) {
    int ccw1 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
    int ccw2 = ccw(p3, p4, p1) * ccw(p3, p4, p2);
    
    if (ccw1 == 0 && ccw2 == 0) {
        if (p1 > p2) swap(p1, p2);
        if (p3 > p4) swap(p3, p4);
        return p3 <= p2 && p1 <= p4;
    }
    
    return ccw1 <= 0 && ccw2 <= 0;
}
```

---

## 고급 알고리즘

### 29. Berlekamp-Massey 알고리즘

#### 📝 설명
Berlekamp-Massey는 주어진 수열에 대한 최소 선형 점화식을 찾는 알고리즘입니다. 수열의 N번째 항을 효율적으로 구하거나, 행렬식 계산 등에 활용됩니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(N²)
- **공간 복잡도**: O(N)

#### 🔄 동작 과정 (Pseudocode)
```
// 최소 선형 점화식 찾기
BerlekampMassey(sequence):
    // 수열 S[0], S[1], ..., S[n-1]에 대해
    // S[i] = c[1]*S[i-1] + c[2]*S[i-2] + ... + c[L]*S[i-L]
    // 를 만족하는 최소 길이 L의 계수 c[] 찾기
    
    cur = []      // 현재 점화식 계수
    ls = []       // 이전 최적 점화식
    lf = 0        // 마지막 불일치 위치
    ld = 0        // 마지막 불일치 값
    
    for i = 0 to n-1:
        // 1. 현재 점화식으로 S[i] 예측
        predicted = 0
        for j = 0 to length(cur)-1:
            predicted += S[i-j-1] * cur[j]
        
        // 2. 예측이 정확하면 계속
        if predicted == S[i]:
            continue
        
        // 3. 첫 불일치 발견: 점화식 초기화
        if cur is empty:
            cur = [0] * (i+1)
            lf = i
            ld = S[i] - predicted
            continue
        
        // 4. 보정 계수 계산
        discrepancy = S[i] - predicted
        k = -discrepancy / ld  // 모듈러 역원
        
        // 5. 점화식 업데이트
        correction = [0] * (i - lf - 1) + [k] + [-k * c for c in ls]
        
        // 6. 현재 점화식에 보정 추가
        new_cur = cur + correction
        
        // 7. 점화식 길이 증가 필요한 경우
        if i - lf + length(ls) >= length(cur):
            ls = cur
            lf = i
            ld = discrepancy
        
        cur = new_cur
    
    return cur

동작 예시: 피보나치 수열 [0, 1, 1, 2, 3, 5, 8, 13]
목표: F[n] = a*F[n-1] + b*F[n-2] 찾기

i=0: S[0]=0, cur=[]
i=1: S[1]=1, cur=[] → 첫 불일치, cur=[0]
i=2: S[2]=1
     predicted = 0*1 = 0 ≠ 1
     보정 후 cur=[1, 1] (즉, F[n] = F[n-1] + F[n-2])
i=3: S[3]=2, predicted = 1*1 + 1*1 = 2 ✓
i=4: S[4]=3, predicted = 1*2 + 1*1 = 3 ✓
...
결과: [1, 1] → F[n] = F[n-1] + F[n-2]

핵심 아이디어:
1. 탐욕적 접근: 불일치 발생 시에만 점화식 갱신
2. 최소성 보장: 가능한 가장 짧은 점화식
3. 선형 대수: LFSR (Linear Feedback Shift Register)

응용:
1. **수열 N번째 항 계산**:
   - 점화식 찾기: O(N²)
   - 행렬 거듭제곱: O(L³ log N)
   - 총: O(N² + L³ log N)
   
2. **행렬식 계산**: 특성 다항식
3. **오류 정정 코드**: BCH, Reed-Solomon
4. **암호학**: 스트림 암호 분석

예제: 수열 [1, 1, 2, 3, 5, 8]
- 점화식 발견: a[n] = a[n-1] + a[n-2]
- 계수: [1, 1]
- 100번째 항 계산 가능

주의사항:
- 최소 2L개 항 필요 (L = 점화식 차수)
- 모듈러 연산 필요
- 부동소수점 오차 주의
```

#### 💻 C++ 구현
```cpp
#include <vector>
using namespace std;

typedef long long lint;
const int MOD = 1e9 + 7;

lint ipow(lint x, lint p, lint mod) {
    lint ret = 1, piv = x;
    while (p) {
        if (p & 1) ret = ret * piv % mod;
        piv = piv * piv % mod;
        p >>= 1;
    }
    return ret;
}

vector<int> berlekampMassey(vector<int> x) {
    vector<int> ls, cur;
    int lf, ld;
    
    for (int i = 0; i < x.size(); i++) {
        lint t = 0;
        for (int j = 0; j < cur.size(); j++) {
            t = (t + 1LL * x[i - j - 1] * cur[j]) % MOD;
        }
        
        if ((t - x[i]) % MOD == 0) continue;
        
        if (cur.empty()) {
            cur.resize(i + 1);
            lf = i;
            ld = (t - x[i]) % MOD;
            continue;
        }
        
        lint k = -(x[i] - t) * ipow(ld, MOD - 2, MOD) % MOD;
        vector<int> c(i - lf - 1);
        c.push_back(k);
        
        for (auto &j : ls) {
            c.push_back(-j * k % MOD);
        }
        
        if (c.size() < cur.size()) c.resize(cur.size());
        
        for (int j = 0; j < cur.size(); j++) {
            c[j] = (c[j] + cur[j]) % MOD;
        }
        
        if (i - lf + (int)ls.size() >= (int)cur.size()) {
            ls = cur;
            lf = i;
            ld = (t - x[i]) % MOD;
        }
        cur = c;
    }
    
    for (auto &i : cur) {
        i = (i % MOD + MOD) % MOD;
    }
    
    return cur;
}
```

---

### 30. Mo's Algorithm (오프라인 쿼리)

#### 📝 설명
Mo's Algorithm은 구간 쿼리를 효율적으로 처리하는 오프라인 알고리즘입니다. 쿼리를 특정 순서로 정렬하여 처리하며, 구간의 확장/축소 연산이 빠를 때 효과적입니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O((N + Q) × √N)
- **공간 복잡도**: O(N + Q)

#### 💻 C++ 구현
```cpp
#include <algorithm>
#include <cmath>
using namespace std;

const int MAX = 100001;
int sqrtN;
int arr[MAX];
int cnt[MAX];
int answer[MAX];

struct Query {
    int idx, left, right;
    
    bool operator<(const Query &other) const {
        int blockA = left / sqrtN;
        int blockB = other.left / sqrtN;
        
        if (blockA != blockB) return blockA < blockB;
        return right < other.right;
    }
};

void add(int pos, int &result) {
    if (cnt[arr[pos]]++ == 0) result++;
}

void remove(int pos, int &result) {
    if (--cnt[arr[pos]] == 0) result--;
}

void moAlgorithm(Query queries[], int Q, int N) {
    sqrtN = sqrt(N);
    sort(queries, queries + Q);
    
    int currentL = 0, currentR = -1, result = 0;
    
    for (int i = 0; i < Q; i++) {
        int L = queries[i].left;
        int R = queries[i].right;
        
        while (currentR < R) add(++currentR, result);
        while (currentL > L) add(--currentL, result);
        while (currentR > R) remove(currentR--, result);
        while (currentL < L) remove(currentL++, result);
        
        answer[queries[i].idx] = result;
    }
}
```

---

### 31. SCC (강한 연결 요소) - Kosaraju's Algorithm

#### 📝 설명
SCC는 방향 그래프에서 서로 도달 가능한 정점들의 집합을 찾는 알고리즘입니다. 2-SAT 문제, 그래프 연결성 분석 등에 활용됩니다. Kosaraju 알고리즘은 두 번의 DFS로 SCC를 찾습니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(V + E)
- **공간 복잡도**: O(V + E)

#### 💻 C++ 구현
```cpp
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int MAX = 10001;
vector<int> graph[MAX];
vector<int> reverseGraph[MAX];
bool visited[MAX];
stack<int> finishStack;
int sccNumber[MAX];
int sccCount = 0;

void dfs1(int node) {
    visited[node] = true;
    
    for (int next : graph[node]) {
        if (!visited[next]) {
            dfs1(next);
        }
    }
    
    finishStack.push(node);
}

void dfs2(int node, int sccNum) {
    visited[node] = true;
    sccNumber[node] = sccNum;
    
    for (int next : reverseGraph[node]) {
        if (!visited[next]) {
            dfs2(next, sccNum);
        }
    }
}

void findSCC(int V) {
    fill(visited, visited + V + 1, false);
    
    for (int i = 1; i <= V; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }
    
    fill(visited, visited + V + 1, false);
    
    while (!finishStack.empty()) {
        int node = finishStack.top();
        finishStack.pop();
        
        if (!visited[node]) {
            dfs2(node, sccCount++);
        }
    }
}
```

---

### 32. Articulation Point (단절점) - Tarjan's Algorithm

#### 📝 설명
단절점은 제거했을 때 그래프가 둘 이상의 컴포넌트로 분리되는 정점입니다. 네트워크 신뢰성 분석, 중요 노드 찾기 등에 활용됩니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(V + E)
- **공간 복잡도**: O(V)

#### 💻 C++ 구현
```cpp
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 10001;
vector<int> graph[MAX];
int visitOrder[MAX];
bool isArticulation[MAX];
int orderCounter = 0;

int findArticulation(int cur, bool isRoot) {
    visitOrder[cur] = ++orderCounter;
    int minOrder = visitOrder[cur];
    int childCount = 0;
    
    for (int next : graph[cur]) {
        if (visitOrder[next]) {
            minOrder = min(minOrder, visitOrder[next]);
        } else {
            childCount++;
            int subtreeMin = findArticulation(next, false);
            minOrder = min(minOrder, subtreeMin);
            
            if (!isRoot && subtreeMin >= visitOrder[cur]) {
                isArticulation[cur] = true;
            }
        }
    }
    
    if (isRoot && childCount >= 2) {
        isArticulation[cur] = true;
    }
    
    return minOrder;
}
```

---

### 33. Lazy Propagation (느긋한 전파)

#### 📝 설명
세그먼트 트리에서 구간 업데이트를 효율적으로 처리하는 기법입니다. 업데이트를 지연시켜 필요할 때만 적용함으로써 성능을 향상시킵니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(log N) - 쿼리 및 업데이트
- **공간 복잡도**: O(N)

#### 💻 C++ 구현
```cpp
#include <vector>
using namespace std;

const int MAX = 100001;
long long tree[MAX * 4];
long long lazy[MAX * 4];

void updateLazy(int node, int start, int end) {
    if (lazy[node] == 0) return;
    
    tree[node] += (end - start + 1) * lazy[node];
    
    if (start != end) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
    }
    
    lazy[node] = 0;
}

void updateRange(int node, int start, int end, int left, int right, long long diff) {
    updateLazy(node, start, end);
    
    if (start > right || end < left) return;
    
    if (start >= left && end <= right) {
        tree[node] += (end - start + 1) * diff;
        
        if (start != end) {
            lazy[node * 2] += diff;
            lazy[node * 2 + 1] += diff;
        }
        return;
    }
    
    int mid = (start + end) / 2;
    updateRange(node * 2, start, mid, left, right, diff);
    updateRange(node * 2 + 1, mid + 1, end, left, right, diff);
    
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long queryRange(int node, int start, int end, int left, int right) {
    updateLazy(node, start, end);
    
    if (start > right || end < left) return 0;
    
    if (start >= left && end <= right) {
        return tree[node];
    }
    
    int mid = (start + end) / 2;
    return queryRange(node * 2, start, mid, left, right) + 
           queryRange(node * 2 + 1, mid + 1, end, left, right);
}
```

---

### 34. Extended GCD (확장 유클리드 호제법)

#### 📝 설명
확장 유클리드 호제법은 GCD를 구하면서 동시에 베주 항등식(ax + by = gcd(a,b))의 계수 x, y를 구하는 알고리즘입니다. 모듈러 역원 계산, 선형 디오판토스 방정식 해결 등에 활용됩니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(log min(a, b))
- **공간 복잡도**: O(1)

#### 💻 C++ 구현
```cpp
#include <tuple>
using namespace std;

tuple<long long, long long, long long> extendedGCD(long long a, long long b) {
    if (b == 0) {
        return {a, 1, 0};
    }
    
    auto [gcd, x1, y1] = extendedGCD(b, a % b);
    
    long long x = y1;
    long long y = x1 - (a / b) * y1;
    
    return {gcd, x, y};
}

long long modInverse(long long a, long long m) {
    auto [gcd, x, y] = extendedGCD(a, m);
    
    if (gcd != 1) {
        return -1;
    }
    
    return (x % m + m) % m;
}

bool solveDiophantine(long long a, long long b, long long c, long long &x, long long &y) {
    auto [gcd, x0, y0] = extendedGCD(a, b);
    
    if (c % gcd != 0) {
        return false;
    }
    
    x = x0 * (c / gcd);
    y = y0 * (c / gcd);
    
    return true;
}
```

---

## 📚 추가 참고사항

### 알고리즘별 난이도 및 활용도

| 알고리즘 | 난이도 | 활용 빈도 | 주요 활용 분야 |
|---------|--------|----------|-------------|
| DFS/BFS | ⭐⭐ | 매우 높음 | 그래프 탐색, 최단경로 |
| Dijkstra | ⭐⭐⭐ | 높음 | 최단경로 |
| DP | ⭐⭐⭐⭐ | 매우 높음 | 최적화 문제 |
| Segment Tree | ⭐⭐⭐⭐ | 높음 | 구간 쿼리 |
| Union-Find | ⭐⭐ | 높음 | 집합 관리, MST |
| KMP | ⭐⭐⭐ | 중간 | 문자열 검색 |
| LCA | ⭐⭐⭐⭐ | 중간 | 트리 쿼리 |
| SCC | ⭐⭐⭐⭐ | 중간 | 2-SAT, 그래프 분석 |
| Mo's Algorithm | ⭐⭐⭐⭐⭐ | 낮음 | 오프라인 구간 쿼리 |
| CCW | ⭐⭐⭐ | 낮음 | 계산 기하학 |
| Berlekamp-Massey | ⭐⭐⭐⭐⭐ | 매우 낮음 | 선형 점화식 |
| 0-1 BFS | ⭐⭐⭐ | 중간 | 0-1 가중치 최단경로 |
| Red-Black Tree | ⭐⭐⭐⭐⭐ | 중간 | 균형 이진 탐색 트리 |

---

### 35. 0-1 BFS (Deque 최적화)

#### 📝 설명
0-1 BFS는 간선의 가중치가 0 또는 1만 존재하는 그래프에서 최단 경로를 찾는 최적화된 알고리즘입니다. 일반 BFS에 가중치 개념을 추가하되, Dijkstra보다 효율적으로 동작합니다. 가중치 0인 간선은 덱의 앞에, 가중치 1인 간선은 덱의 뒤에 추가하여 처리합니다.

#### ⏱️ 복잡도
- **시간 복잡도**: O(V + E)
- **공간 복잡도**: O(V)

#### 🔄 동작 과정 (Pseudocode)
```
// 0-1 BFS (Deque 사용)
BFS_01(start, graph):
    // 1. 초기화
    deque = empty deque
    dist[start] = 0
    for all v != start:
        dist[v] = INF
    
    deque.push_back(start)
    
    // 2. Deque가 빌 때까지 반복
    while deque is not empty:
        // 3. 덱의 앞에서 노드 꺼내기
        current = deque.pop_front()
        
        // 4. 이미 처리된 노드면 스킵
        if visited[current]:
            continue
        visited[current] = true
        
        // 5. 인접 노드 처리
        for each edge (current, next, weight) in graph:
            newDist = dist[current] + weight
            
            // 6. 더 짧은 경로 발견 시 갱신
            if newDist < dist[next]:
                dist[next] = newDist
                
                // 7. 가중치에 따라 덱에 추가
                if weight == 0:
                    deque.push_front(next)  // 우선순위 높음
                else:  // weight == 1
                    deque.push_back(next)   // 우선순위 낮음
    
    return dist

동작 예시: 숨바꼭질 문제
위치 N에서 K로 이동
- N-1 또는 N+1: 비용 1 (걷기)
- N*2: 비용 0 (순간이동)

N=5, K=17일 때:
1. 초기: deque=[5], dist[5]=0
2. 5 처리:
   - 5*2=10: 비용 0 → push_front
   - 4: 비용 1 → push_back
   - 6: 비용 1 → push_back
   deque=[10, 4, 6], dist[10]=0, dist[4]=1, dist[6]=1

3. 10 처리 (비용 0):
   - 10*2=20: 비용 0 → push_front
   - 9: 비용 1 → push_back
   - 11: 비용 1 → push_back
   deque=[20, 4, 6, 9, 11]

4. 20 처리 (비용 0):
   - 19: 비용 1 → push_back
   - 21: 비용 1 → push_back
   deque=[4, 6, 9, 11, 19, 21]

5. 계속... 17에 도달 시 최소 비용 = 2

핵심 아이디어:
1. **Deque 불변성 유지**:
   - 덱 내 거리는 비감소 순서
   - [0, 0, 0, 1, 1, 1, 2, 2, ...]
   
2. **가중치 0 우선 처리**:
   - 현재 거리와 동일 → 앞에 추가
   - 현재 거리 + 1 → 뒤에 추가
   
3. **BFS vs Dijkstra vs 0-1 BFS**:
   - BFS: 가중치 모두 1, O(V+E)
   - Dijkstra: 임의 양수 가중치, O((V+E) log V)
   - 0-1 BFS: 가중치 0 또는 1, O(V+E)

Deque 상태 변화:
초기: [start]
처리 중: [거리 d인 노드들... 거리 d+1인 노드들...]
가중치 0 간선: 같은 거리 유지 → push_front
가중치 1 간선: 거리 증가 → push_back

응용:
1. **격자 탐색**:
   - 대각선: 비용 0
   - 상하좌우: 비용 1
   
2. **그래프 변형**:
   - 간선 추가: 비용 1
   - 기존 간선: 비용 0
   
3. **문자열 편집**:
   - 유지: 비용 0
   - 삽입/삭제: 비용 1

Dijkstra와 비교:
- Dijkstra: 우선순위 큐 O(log V)
- 0-1 BFS: 덱 O(1)
- 가중치 제한 있지만 훨씬 빠름

정당성 증명:
- 덱에서 꺼낸 노드는 항상 최단 거리 확정
- 가중치 0: 현재 거리 유지, 먼저 처리
- 가중치 1: 거리 증가, 나중에 처리
```

#### 💻 C++ 구현
```cpp
#include <deque>
#include <vector>
using namespace std;

const int MAX = 100001;
const int INF = 987654321;
int dist[MAX];
bool visited[MAX];

void bfs01(int start, vector<pair<int, int>> graph[], int n) {
    deque<int> dq;
    
    fill(dist, dist + n, INF);
    dist[start] = 0;
    dq.push_back(start);
    
    while (!dq.empty()) {
        int cur = dq.front();
        dq.pop_front();
        
        if (visited[cur]) continue;
        visited[cur] = true;
        
        for (auto &edge : graph[cur]) {
            int next = edge.first;
            int weight = edge.second;
            
            if (dist[cur] + weight < dist[next]) {
                dist[next] = dist[cur] + weight;
                
                if (weight == 0) {
                    dq.push_front(next);
                } else {
                    dq.push_back(next);
                }
            }
        }
    }
}

void simpleBFS01(int start, int target) {
    queue<int> q;
    bool visited[MAX] = {false};
    int dist[MAX] = {0};
    
    q.push(start);
    
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        
        if (visited[cur]) continue;
        visited[cur] = true;
        
        if (cur == target) break;
        
        if (cur * 2 < MAX && !visited[cur * 2]) {
            dist[cur * 2] = dist[cur];
            q.push(cur * 2);
        }
        
        if (cur - 1 >= 0 && !visited[cur - 1]) {
            dist[cur - 1] = dist[cur] + 1;
            q.push(cur - 1);
        }
        
        if (cur + 1 < MAX && !visited[cur + 1]) {
            dist[cur + 1] = dist[cur] + 1;
            q.push(cur + 1);
        }
    }
}
```

---

### 36. Red-Black Tree (레드-블랙 트리)

#### 📝 설명
Red-Black Tree는 자가 균형 이진 탐색 트리로, 각 노드가 red 또는 black 색상을 가지며 특정 규칙을 통해 트리의 균형을 유지합니다. AVL 트리보다 삽입/삭제가 빠르며, C++ STL의 map, set 내부 구현에 사용됩니다.

**Red-Black Tree 속성:**
1. 모든 노드는 red 또는 black
2. 루트는 black
3. 모든 리프(NIL)는 black
4. red 노드의 자식은 반드시 black (연속된 red 노드 불가)
5. 모든 경로에서 black 노드의 수는 동일

#### ⏱️ 복잡도
- **시간 복잡도**: O(log N) - 검색, 삽입, 삭제
- **공간 복잡도**: O(N)
- **재조정 시간**: O(1) - 회전 및 색상 변경

#### 🔄 동작 과정 (Pseudocode)
```
// Red-Black Tree 삽입
Insert(value):
    // 1. 일반 BST 삽입
    newNode = CreateNode(value)
    newNode.color = RED  // 새 노드는 항상 RED
    
    parent = null
    current = root
    
    // BST 방식으로 삽입 위치 찾기
    while current != null:
        parent = current
        if value < current.value:
            current = current.left
        else:
            current = current.right
    
    newNode.parent = parent
    
    // 2. 부모에 연결
    if parent == null:
        root = newNode
        newNode.color = BLACK  // 루트는 항상 BLACK
        return
    else if value < parent.value:
        parent.left = newNode
    else:
        parent.right = newNode
    
    // 3. RB 속성 복구
    FixInsert(newNode)

// 삽입 후 속성 복구
FixInsert(node):
    // 부모가 RED인 동안 반복 (속성 4 위반)
    while node != root AND node.parent.color == RED:
        parent = node.parent
        grandparent = parent.parent
        
        // Case A: 부모가 조부모의 왼쪽 자식
        if parent == grandparent.left:
            uncle = grandparent.right
            
            // Case 1: 삼촌이 RED → Recoloring
            if uncle != null AND uncle.color == RED:
                parent.color = BLACK
                uncle.color = BLACK
                grandparent.color = RED
                node = grandparent  // 조부모에서 다시 확인
            
            // Case 2 & 3: 삼촌이 BLACK → Rotation
            else:
                // Case 2: 노드가 오른쪽 자식 → 왼쪽 회전
                if node == parent.right:
                    node = parent
                    RotateLeft(node)
                    parent = node.parent
                
                // Case 3: 노드가 왼쪽 자식 → 오른쪽 회전
                parent.color = BLACK
                grandparent.color = RED
                RotateRight(grandparent)
        
        // Case B: 부모가 조부모의 오른쪽 자식 (대칭)
        else:
            uncle = grandparent.left
            
            if uncle != null AND uncle.color == RED:
                parent.color = BLACK
                uncle.color = BLACK
                grandparent.color = RED
                node = grandparent
            else:
                if node == parent.left:
                    node = parent
                    RotateRight(node)
                    parent = node.parent
                
                parent.color = BLACK
                grandparent.color = RED
                RotateLeft(grandparent)
    
    root.color = BLACK  // 루트는 항상 BLACK

// 왼쪽 회전
RotateLeft(node):
    //     node              right
    //    /    \            /    \
    //   A    right  →   node    C
    //        /   \      /   \
    //       B     C    A     B
    
    right = node.right
    node.right = right.left
    
    if right.left != null:
        right.left.parent = node
    
    right.parent = node.parent
    
    if node.parent == null:
        root = right
    else if node == node.parent.left:
        node.parent.left = right
    else:
        node.parent.right = right
    
    right.left = node
    node.parent = right

// 오른쪽 회전
RotateRight(node):
    //      node           left
    //     /    \         /    \
    //   left    C  →   A    node
    //  /   \                /   \
    // A     B              B     C
    
    left = node.left
    node.left = left.right
    
    if left.right != null:
        left.right.parent = node
    
    left.parent = node.parent
    
    if node.parent == null:
        root = left
    else if node == node.parent.right:
        node.parent.right = left
    else:
        node.parent.left = left
    
    left.right = node
    node.parent = left

삽입 예시: 7, 3, 18, 10, 22, 8 순서로 삽입

1. 7 삽입: BLACK 루트
       7(B)

2. 3 삽입: RED 노드, 부모 BLACK → OK
       7(B)
      /
    3(R)

3. 18 삽입: RED 노드, 부모 BLACK → OK
       7(B)
      /   \
    3(R)  18(R)

4. 10 삽입: RED, 부모 18(R) → 위반!
   삼촌 3(R), Recoloring:
       7(B)
      /   \
    3(B)  18(B)
         /
       10(R)

5. 22 삽입: RED, 부모 18(B) → OK
       7(B)
      /    \
    3(B)   18(B)
          /    \
       10(R)  22(R)

6. 8 삽입: RED, 부모 10(R) → 위반!
   삼촌 22(R), Recoloring 후 회전...

핵심 개념:
1. **Black Height**: 루트부터 리프까지 BLACK 노드 수
   - 모든 경로에서 동일 → 균형 보장
   
2. **높이 제한**: 
   - 최대 높이 ≤ 2 log(N+1)
   - AVL보다 느슨하지만 회전 적음
   
3. **색상 규칙**:
   - RED 노드는 BLACK 부모/자식만
   - 연속 RED 불가

AVL vs Red-Black Tree:
- AVL: 엄격한 균형, 검색 빠름
- RB: 느슨한 균형, 삽입/삭제 빠름
- STL은 RB 트리 사용 (삽입/삭제 많음)

응용:
- C++ map, set, multimap, multiset
- Java TreeMap, TreeSet
- Linux 커널 스케줄러
```

#### 💻 C++ 구현
```cpp
#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;
    
    Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;
    
    void rotateLeft(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;
        
        if (node->right != nullptr) {
            node->right->parent = node;
        }
        
        rightChild->parent = node->parent;
        
        if (node->parent == nullptr) {
            root = rightChild;
        } else if (node == node->parent->left) {
            node->parent->left = rightChild;
        } else {
            node->parent->right = rightChild;
        }
        
        rightChild->left = node;
        node->parent = rightChild;
    }
    
    void rotateRight(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;
        
        if (node->left != nullptr) {
            node->left->parent = node;
        }
        
        leftChild->parent = node->parent;
        
        if (node->parent == nullptr) {
            root = leftChild;
        } else if (node == node->parent->left) {
            node->parent->left = leftChild;
        } else {
            node->parent->right = leftChild;
        }
        
        leftChild->right = node;
        node->parent = leftChild;
    }
    
    void fixInsert(Node* node) {
        while (node != root && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                Node* uncle = node->parent->parent->right;
                
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateRight(node->parent->parent);
                }
            } else {
                Node* uncle = node->parent->parent->left;
                
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateLeft(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }
    
public:
    RedBlackTree() : root(nullptr) {}
    
    void insert(int data) {
        Node* newNode = new Node(data);
        Node* parent = nullptr;
        Node* current = root;
        
        while (current != nullptr) {
            parent = current;
            if (newNode->data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        
        newNode->parent = parent;
        
        if (parent == nullptr) {
            root = newNode;
        } else if (newNode->data < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        
        fixInsert(newNode);
    }
    
    Node* search(int data) {
        Node* current = root;
        
        while (current != nullptr) {
            if (data == current->data) {
                return current;
            } else if (data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        
        return nullptr;
    }
};
```

---

이 가이드는 실제 코딩 테스트와 알고리즘 문제 해결에 즉시 활용할 수 있는 검증된 구현을 제공합니다.

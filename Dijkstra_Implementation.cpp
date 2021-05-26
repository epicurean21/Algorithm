#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;
#define INF 1000000

int n, m, q, source, destination, weight;
char query;

class Region {
private:
    int nodeIdx;
    int regionIdx;
    string regionName;
    bool isFlooded;
    vector<pair<Region *, int>> neighbor;
public:

    Region() {
        this->nodeIdx = 0;
        this->regionIdx = 0;
        this->regionName = "";
        this->isFlooded = false;
        this->neighbor.clear();
    }

    Region(int nodeIdx, int regionIdx, string regionName, bool isFlooded) {
        this->nodeIdx = nodeIdx;
        this->regionIdx = regionIdx;
        this->regionName = regionName;
        this->isFlooded = isFlooded;
        this->neighbor.clear();
    }

    int getRegionIdx() {
        return this->regionIdx;
    }

    string getRegionName() {
        return this->regionName;
    }

    int getNodeIdx() {
        return this->nodeIdx;
    }

    bool getIsFlooded() {
        return this->isFlooded;
    }

    vector<pair<Region *, int>> getNeighbor() {
        return this->neighbor;
    }

    void insertNeighbor(Region *neighborhood, int weight) {
        this->neighbor.emplace_back(neighborhood, weight);
    }
};

class Graph {
private:
    map<int, Region *> regions;
public:
    Graph() {
        this->regions.clear();
    }

    void insertRegion(int nodeIdx, int regionIdx, string regionName, bool isFlooded) {
        Region *new_region = new Region(nodeIdx, regionIdx, regionName, isFlooded);
        regions[regionIdx] = new_region;
    }

    Region *findRegion(int regionIdx) {
        if (regions.count(regionIdx))
            return regions[regionIdx];
        return nullptr;
    }

    void insertEdge(int s, int d, int weight) {
        Region *S = findRegion(s);
        Region *D = findRegion(d);
        S->insertNeighbor(D, weight);
        D->insertNeighbor(S, weight);
    }

    vector<int> Dijkstra_Distance(Region *s, Region *d) { // O(MlogN) 이어야한다..
        int treeVertex = 1;
        priority_queue<pair<int, pair<int, Region *>>, vector<pair<int, pair<int, Region *>>>, greater<pair<int, pair<int, Region *>>>> pq; // min-heap
        pq.push({0, {s->getRegionIdx(), s}}); // 우선순위 {weight > regionIdx > }
        vector<int> dist(n + 2, INT32_MAX);
        dist[s->getNodeIdx()] = 0;
        int cnt = 0;
        while (!pq.empty()) {
            int cost = pq.top().first;
            Region *here = pq.top().second.second;
            pq.pop();

            if (here == d) {
                treeVertex = cnt + 1;
                break;
            }

            if (here->getIsFlooded()) // 침수된 지역
                continue;

            if (dist[here->getNodeIdx()] < cost)
                continue;

            cnt++;
            vector<pair<Region *, int>> neighbors = here->getNeighbor();

            for (int i = 0; i < neighbors.size(); i++) {
                Region *there = neighbors[i].first;
                int nextDist = neighbors[i].second + cost;

                if (dist[there->getNodeIdx()] > nextDist) {
                    dist[there->getNodeIdx()] = nextDist;
                    if (there->getIsFlooded())
                        continue;
                    pq.push({nextDist, {there->getRegionIdx(), there}});
                }
            }
        }

        dist[0] = treeVertex;

        return dist;
    }

    vector<pair<int, int>> Dijkstra_Path(Region *s, Region *d) { // O(MlogN) 이어야한다..
        int treeVertex = 1;
        priority_queue<pair<int, pair<int, Region *>>, vector<pair<int, pair<int, Region *>>>, greater<pair<int, pair<int, Region *>>>> pq; // min-heap
        pq.push({0, {s->getRegionIdx(), s}}); // 우선순위 {weight > regionIdx > }
        vector<int> dist(n + 2, INT32_MAX);
        vector<pair<int, int>> predecessor(n + 2);
        dist[s->getNodeIdx()] = 0;
        predecessor[s->getNodeIdx()].second = 0;
        int cnt = 0;
        while (!pq.empty()) {
            int cost = pq.top().first;
            Region *here = pq.top().second.second;
            pq.pop();

            if (here == d) {
                treeVertex = cnt + 1;
                break;
            }

            if (here->getIsFlooded()) // 침수된 지역
                continue;

            if (dist[here->getNodeIdx()] < cost)
                continue;

            cnt++;
            vector<pair<Region *, int>> neighbors = here->getNeighbor();

            for (int i = 0; i < neighbors.size(); i++) {
                Region *there = neighbors[i].first;
                int nextDist = neighbors[i].second + cost;

                if (dist[there->getNodeIdx()] > nextDist) {
                    dist[there->getNodeIdx()] = nextDist;
                    predecessor[there->getNodeIdx()].first = here->getRegionIdx();
                    predecessor[there->getNodeIdx()].second = here->getNodeIdx();
                    if (there->getIsFlooded())
                        continue;
                    pq.push({nextDist, {there->getRegionIdx(), there}});
                }
            }
        }
        predecessor[0].first = treeVertex;
        predecessor[n + 1].second = dist[d->getNodeIdx()];

        return predecessor;
    }

    pair<pair<int, int>, pair<string, string>> findShortestDistance(int s, int d) {
        Region *S = findRegion(s); // O(N)
        Region *D = findRegion(d);
        if (S == nullptr || D == nullptr)
            return {{-1, -1},
                    {"", ""}};
        if (S->getIsFlooded() || D->getIsFlooded())
            return {{-1, -1},
                    {"", ""}};
        vector<int> ans = Dijkstra_Distance(S, D); // O(MlogN)
        int treeVertex = ans[0];
        int distance = ans[D->getNodeIdx()];
        if (distance == INT32_MAX || distance > INF)
            return {{-1, -1},
                    {"", ""}};

        return {{treeVertex,         distance},
                {S->getRegionName(), D->getRegionName()}};
    }

    pair<int, vector<int>> findShortestPath(int s, int d) {
        Region *S = findRegion(s);
        Region *D = findRegion(d);
        vector<pair<int, int>> ans;
        vector<int> path;
        if (S == nullptr || D == nullptr)
            return {-1, path};
        if (S->getIsFlooded() || D->getIsFlooded())
            return {-1,
                    path};
        ans = Dijkstra_Path(S, D);
        int treeVertex = ans[0].first;
        int distance = ans[n - 1].second;
        if (distance == INT32_MAX || distance > INF)
            return {-1, path};
        int cur = D->getNodeIdx();
        int now = D->getRegionIdx();
        path.emplace_back(now);
        while (cur != S->getNodeIdx()) {
            now = ans[cur].first;
            cur = ans[cur].second;
            path.emplace_back(now);
        }

        return {treeVertex, path};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> q;
    Graph graph;
    for (int i = 0; i < n; i++) { // 지역 정보
        int regionIdx, isFlooded;
        string regionName;
        cin >> regionIdx >> regionName >> isFlooded;
        graph.insertRegion(i + 1, regionIdx, regionName, isFlooded);
    }
    for (int i = 0; i < m; i++) {
        cin >> source >> destination >> weight;
        graph.insertEdge(source, destination, weight);
    }

    while (q--) {
        cin >> query;
        if (query == 'A') { // 두 지역간의 최단거리 찾기: return {지역수, 거리, source, destination}
            cin >> source >> destination;
            pair<pair<int, int>, pair<string, string>> ans = graph.findShortestDistance(source, destination);
            if (ans.first.first == -1)
                cout << "None\n";
            else {
                cout << ans.first.first << " " << ans.first.second << " " << ans.second.first << " "
                     << ans.second.second << "\n";
            }
        } else if (query == 'B') { // 두 지역간의 최단경로 찾기: return {지역 수, vertices}
            cin >> source >> destination;
            pair<int, vector<int>> ans = graph.findShortestPath(source, destination);
            if (ans.first == -1)
                cout << "None\n";
            else {
                cout << ans.first << " ";
                for (int i = ans.second.size() - 1; i >= 0; i--)
                    cout << ans.second[i] << " ";
                cout << '\n';
            }
        }
    }
    return 0;
}
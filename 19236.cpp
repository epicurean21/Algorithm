/**
 * 19236 청소년 상어
 * 삼성 SW 출제 문제
 * 구현, 백트레킹
 */
#include "iostream"
#include "unordered_map"

using namespace std;
#define shark (-1)
#define empty 0
pair<int, int> dir[] = {{0,  1},
                        {-1, 1},
                        {-1, 0},
                        {-1, -1},
                        {0,  -1},
                        {1,  -1},
                        {1,  0},
                        {1,  1}},
        map[4][4];

int a, b, eatCount;
unordered_map<int, pair<int, int>> fishPosition;

void printMap() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << "#" << map[i][j].first << ", dir: " << map[i][j].second;
        }
        cout << "\n";
    }
}

bool isMovable(int x, int y) {
    if (x < 0 || y < 0 || x >= 4 || y >= 4) {
        return false;
    }

    if (map[y][x].first == shark) {
        return false;
    }

    if (map[y][x].first == empty) {
        return false;
    }

    return true;
}

bool isSharkMovable(int x, int y, int direction) {
    int nextPositionX = x + dir[direction % 8].first;
    int nextPositionY = y + dir[direction % 8].second;
    if (nextPositionX < 0 || nextPositionY < 0 || nextPositionX >= 4 || nextPositionY >= 4) {
        false;
    }

    while (nextPositionX >= 0 && nextPositionX <= 3 && nextPositionY >= 0 && nextPositionY <= 3) {
        if (map[nextPositionY][nextPositionX].first != empty) {
            return true;
        }
        direction++;
        nextPositionX += dir[direction % 8].first;
        nextPositionY += dir[direction % 8].second;
    }

    return false;
}

void switchFishPosition(int fishA, int fishB) {
    auto positionA = fishPosition.find(fishA)->second;
    auto positionB = fishPosition.find(fishB)->second;
    int directionA = map[positionA.second][positionA.first].second;
    int directionB = map[positionB.second][positionA.first].second;

    map[positionA.second][positionA.first] = {fishB, directionB};
    map[positionB.second][positionB.first] = {fishA, directionA};

    fishPosition.erase(fishA);
    fishPosition.erase(fishB);

    fishPosition.insert({fishA, {positionA.first, positionA.second}});
    fishPosition.insert({fishB, {positionB.first, positionB.second}});
}

void moveShark(int x, int y) {
    int fishNumber = map[y][x].first;
    fishPosition.erase(fishNumber);
    eatCount++;
    map[y][x].first = shark;
}

void moveFish(int fishNumber) {
    auto fish = fishPosition.find(fishNumber);
    auto position = fish->second;
    int direction = map[position.second][position.first].second;

    int curX = position.first;
    int curY = position.second;
    while (!isMovable(curX + dir[direction % 8].first, curY + dir[direction % 8].second)) {
        direction++;
    }

    int otherFish = map[curX + dir[direction % 8].first][curY + dir[direction % 8].second].first;
    switchFishPosition(fishNumber, otherFish);
}

void operate() {

}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> a >> b;
            map[i][j] = {a, --b};
            fishPosition.insert({a, {j, i}});
        }
    }

    fishPosition.erase(map[0][0].first);
    map[0][0].first = shark;
    eatCount++;

    moveFish(1);

    return 0;
}
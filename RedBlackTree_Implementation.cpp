#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Patient {
public:
    int code; // 환자 번호
    string name; // 이름
    string contact; // 연락처
    pair<int, int> address; // 주소 x, y
    vector<pair<string, int>> treatRecord; // 진료기록, <병명, 진료비>

    Patient() {
        this->code = 0;
        this->name = "";
        this->contact = "";
        this->address = {0, 0};
        this->treatRecord.clear();
    }

    Patient(int code, string name, string contact,
            pair<int, int> address, pair<string, int> treatRecord) {
        this->code = code;
        this->name = name;
        this->contact = contact;
        this->address = address;
        this->treatRecord.push_back(treatRecord);
    };
};

class Node {
public:
    Patient *patient;
    bool isBlack; // true 이면 검정색 노드, false 이면 흰색 노드
    Node *parent;
    Node *left_child;
    Node *right_child;

    Node() {
        this->patient = new Patient();
        this->isBlack = false; // 기본 빨간색
        this->parent = nullptr;
        this->left_child = nullptr;
        this->right_child = nullptr;
    }
};

class Red_Black_Tree {
private:
    Node *root;
    int diagnose_count;
public:
    Red_Black_Tree() {
        this->root = nullptr;
        this->diagnose_count = 0;
    }

    int countDepth(Node *node) { // O(log N)
        Node *tmp_root = this->root;
        int depth_count = 0;

        while (tmp_root != nullptr) { // 리프까지 내려간다
            if (node->patient->code > tmp_root->patient->code) { // 더 큼, 즉 오른쪽
                tmp_root = tmp_root->right_child;
                depth_count++;
            } else if (node->patient->code < tmp_root->patient->code) { // 작거나 같음
                tmp_root = tmp_root->left_child;
                depth_count++;
            } else { // 같은 key값 발견
                return depth_count; // 해당 깊이와 거절
            }
        }
        return -1;
    }

    void restructuring(Node *node) { // O(1) 상수시간 처리
        Node *parent_node = node->parent;
        Node *grand_parent_node = parent_node->parent;
        if (parent_node == parent_node->parent->left_child) { // 왼쪽자식 restructure
            if (node == parent_node->left_child) {
                // node의 무보가 위로 올라가고, node는 왼쪽 자식, 조상노드는 오른 쪽 자식이 된다.
                grand_parent_node->left_child = parent_node->right_child;
                if (parent_node->right_child != nullptr)
                    parent_node->right_child->parent = grand_parent_node;
                parent_node->parent = grand_parent_node->parent;
                if (parent_node->parent == nullptr)
                    this->root = parent_node;
                else { // 만약 조상이 왼쪽 자식 이었다
                    if (grand_parent_node == grand_parent_node->parent->left_child)
                        grand_parent_node->parent->left_child = parent_node;
                    else if (grand_parent_node == grand_parent_node->parent->right_child)
                        grand_parent_node->parent->right_child = parent_node;
                }
                parent_node->right_child = grand_parent_node;
                grand_parent_node->parent = parent_node;
                // coloring
                parent_node->isBlack = true;
                grand_parent_node->isBlack = false;
                node->isBlack = false;
            } else if (node == parent_node->right_child) {
                // 노드가 위로 올라가고, 부모 노드가 인쪽 조상 노드가 오른쪽
                grand_parent_node->left_child = node->right_child;
                if (node->right_child != nullptr)
                    node->right_child->parent = grand_parent_node;

                parent_node->right_child = node->left_child;
                if (node->left_child != nullptr)
                    node->left_child->parent = parent_node;

                node->parent = grand_parent_node->parent;
                if (node->parent == nullptr)
                    this->root = node;
                else {
                    if (grand_parent_node == grand_parent_node->parent->left_child)
                        grand_parent_node->parent->left_child = node;
                    else
                        grand_parent_node->parent->right_child = node;
                }

                node->left_child = parent_node;
                parent_node->parent = node;
                node->right_child = grand_parent_node;
                grand_parent_node->parent = node;
                //coloring
                node->isBlack = true;
                grand_parent_node->isBlack = false;
                parent_node->isBlack = false;
            }
        } else if (parent_node == parent_node->parent->right_child) { // 오른쪽
            if (node == parent_node->left_child) {
                // 노드가 위로 올라감
                parent_node->left_child = node->right_child;
                if (node->right_child != nullptr)
                    node->right_child->parent = parent_node;

                grand_parent_node->right_child = node->left_child;
                if (node->left_child != nullptr)
                    node->left_child->parent = grand_parent_node;

                node->parent = grand_parent_node->parent;
                if (node->parent == nullptr)
                    this->root = node;
                else {
                    if (grand_parent_node == grand_parent_node->parent->left_child)
                        grand_parent_node->parent->left_child = node;
                    else
                        grand_parent_node->parent->right_child = node;
                }
                node->right_child = parent_node;
                parent_node->parent = node;
                node->left_child = grand_parent_node;
                grand_parent_node->parent = node;

                // coloring
                node->isBlack = true;
                grand_parent_node->isBlack = false;
                parent_node->isBlack = false;
            } else if (node == parent_node->right_child) {
                // 부모 노드가 위로 올라감
                grand_parent_node->right_child = parent_node->left_child;
                if (parent_node->left_child != nullptr)
                    parent_node->left_child->parent = grand_parent_node;

                parent_node->parent = grand_parent_node->parent;
                if (parent_node->parent == nullptr)
                    this->root = parent_node;
                else {
                    if (grand_parent_node == grand_parent_node->parent->left_child)
                        grand_parent_node->parent->left_child = parent_node;
                    else
                        grand_parent_node->parent->right_child = parent_node;
                }
                parent_node->left_child = grand_parent_node;
                grand_parent_node->parent = parent_node;

                // coloring
                parent_node->isBlack = true;
                grand_parent_node->isBlack = false;
                node->isBlack = false;
            }
        }
    }

    void fixTree(Node *node) { // O (log N)
        Node *uncle_node;
        while (node != this->root && !node->parent->isBlack) { // 루트 노드까지 반복적으로 올라감
            if (node->parent == node->parent->parent->right_child) {
                uncle_node = node->parent->parent->left_child; // 삼촌 노드
                if (uncle_node != nullptr && !uncle_node->isBlack) { // 삼촌노드가 빨간색 ! recoloring !
                    node->parent->isBlack = true; // 부모 검정색으로
                    uncle_node->isBlack = true; // 삼촌 검정색으로
                    node->parent->parent->isBlack = false; // 조상 빨간색으로
                    node = node->parent->parent; // 현 위치를 조상으로
                } else { // Restructure !!
                    restructuring(node);
                    this->root->isBlack = true;
                    return;
                }
            } else if (node->parent == node->parent->parent->left_child) {
                uncle_node = node->parent->parent->right_child;
                if (uncle_node != nullptr && !uncle_node->isBlack) { // 삼촌이 빨간색, recoloring
                    node->parent->isBlack = true;
                    uncle_node->isBlack = true;
                    node->parent->parent->isBlack = false;
                    node = node->parent->parent; // 현 위치를 조상으로
                } else {
                    restructuring(node);
                    this->root->isBlack = true;
                    return;
                }
            }
        }

        this->root->isBlack = true; // 루트를 검정색으로
    }

    // O(log N): insert + O (log N): fixTree + O(log N): findDepth
    pair<int, int> insertNode(int patient_code, string name, string address, int Ax, int Ay, string DI, int C) {
        Patient *patient = new Patient(patient_code, name, address, {Ax, Ay}, {DI, C});
        Node *node = new Node();
        node->patient = patient;
        Node *tmp_root = this->root;
        Node *tmp_node = nullptr;
        int depth_count = 0;

        while (tmp_root != nullptr) { // 리프까지 내려간다
            tmp_node = tmp_root;
            if (node->patient->code > tmp_root->patient->code) { // 더 큼, 즉 오른쪽
                tmp_root = tmp_root->right_child;
                depth_count++;
            } else if (node->patient->code < tmp_root->patient->code) { // 작거나 같음
                tmp_root = tmp_root->left_child;
                depth_count++;
            } else { // 같은 key값 발견
                return {depth_count, 0}; // 해당 깊이와 거절
            }
        }

        // 존재하지 않는 key값으로 삽입 확인
        node->parent = tmp_node; // tmp_node는 리프 전꺼까지
        if (tmp_node == nullptr) { // 빈 트리
            node->isBlack = true;
            this->root = node;
            return {0, 1}; // 빈 트리에서 루트 추가, 성공
        } else if (tmp_node->patient->code > node->patient->code) {
            tmp_node->left_child = node;
        } else if (tmp_node->patient->code < node->patient->code) {
            tmp_node->right_child = node;
        }

        if (node->parent->parent == nullptr) // 즉 루트가 부모였다
            return {1, 1};

        // 트리 수정 !
        fixTree(node);
        return {countDepth(node), 1};
    }

    pair<int, Patient *> findPatient(int patient_code) { // 환자와 깊이 리턴
        Node *tmp_root = this->root;
        int depth = 0;
        while (tmp_root != nullptr) {
            if (tmp_root->patient->code == patient_code) {
                return {depth, tmp_root->patient}; // 찾음
            } else if (tmp_root->patient->code > patient_code) {
                tmp_root = tmp_root->left_child;
                depth++;
            } else if (tmp_root->patient->code < patient_code) {
                tmp_root = tmp_root->right_child;
                depth++;
            }
        }
        return {-1, nullptr};
    }

    int addTreatment(int patient_code, string DI, int cost) {
        pair<int, Patient *> patient = findPatient(patient_code);
        if (patient.second == nullptr)
            return -1;
        patient.second->treatRecord.emplace_back(DI, cost);

        return patient.first;
    }

    void countByPreorder(Node *node, string DI) {
        if (node == nullptr)
            return;

        if (node->patient->treatRecord[node->patient->treatRecord.size() - 1].first == DI)
            this->diagnose_count++;
        countByPreorder(node->left_child, DI);
        countByPreorder(node->right_child, DI);
    }

    int countDI(string DI) {
        this->diagnose_count = 0;
        if (this->root == nullptr)
            return 0;
        countByPreorder(this->root, DI);
        return this->diagnose_count;
    }
};

int test_case, patient_code, Ax, Ay, c;
string name, address, DI;
char inquiry;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> test_case;

    Red_Black_Tree rbt; // red black tree

    while (test_case--) {
        cin >> inquiry;

        if (inquiry == 'I') {
            cin >> patient_code >> name >> address >> Ax >> Ay >> DI >> c;
            pair<int, int> result = rbt.insertNode(patient_code, name, address, Ax, Ay, DI, c);
            cout << result.first << " " << result.second << '\n';
        } else if (inquiry == 'F') {
            cin >> patient_code;
            pair<int, Patient *> result = rbt.findPatient(patient_code);
            if (result.first == -1) { // 존재안함
                cout << "Not found\n";
            } else {
                cout << result.first << " " << result.second->name << " " << result.second->contact << " "
                     << result.second->address.first << " "
                     << result.second->address.second << '\n';
            }
        } else if (inquiry == 'A') {
            cin >> patient_code >> DI >> c;
            int result = rbt.addTreatment(patient_code, DI, c);
            if (result == -1) {
                cout << "Not found\n";
            } else {
                cout << result << '\n';
            }
        } else if (inquiry == 'E') {
            cin >> DI;
            int T = rbt.countDI(DI);
            cout << T << '\n';
        }
    }
    return 0;
}
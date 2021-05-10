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
        this->treatRecord.empty();
    }

    Patient(int code, string name, string contact, pair<int, int> address, pair<string, int> treatRecord) {
        this->code = code;
        this->name = name;
        this->contact = contact;
        this->address = address;
        this->treatRecord.push_back(treatRecord);
    };
};

class Node {
public:
    Patient *patient; // patient의 code로 redblacktree 정렬 이 값이 노드의 값
    bool isBlack; // true 이면 검정색 노드, false 이면 흰색 노드
    Node *parent;
    Node *left_child;
    Node *right_child;
    int depth;

    Node() {
        this->patient = new Patient();
        this->isBlack = false; // 기본 빨간색
        this->parent = nullptr;
        this->left_child = nullptr;
        this->right_child = nullptr;
        this->depth = 0;
    }

    Node(Patient *patient, Node *parent) { // 신규 가입 노드
        this->patient = patient;
        this->isBlack = false; // 빨간색
        this->parent = parent;
        this->left_child = new Node();
        this->right_child = new Node();
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

    int findDepth(int patient_code) {
        int depth_count = 0;
        if (this->root->patient->code == patient_code) {
            return 0;
        }

        Node *tmp_root = this->root;
        while (tmp_root != nullptr) { // 리프까지 내려간다
            if (patient_code > tmp_root->patient->code) { // 더 큼, 즉 오른쪽
                tmp_root = tmp_root->right_child;
                depth_count++;
            } else if (patient_code < tmp_root->patient->code) { // 작거나 같음
                tmp_root = tmp_root->left_child;
                depth_count++;
            } else { // 같은 key값 발견
                return depth_count; // 해당 깊이 리턴
            }
        }
        return depth_count; // 존재하지 않음
    }

    void rotateRight(Node *node) { // restructure, 오른쪽 자식 기준
        Node *left_child = node->left_child;
        node->left_child = left_child->right_child;
        if (left_child->right_child != nullptr)
            left_child->right_child->parent = node;
        left_child->parent = node->parent;
        if (node->parent == nullptr) { // 만약 부모가 없다 즉 루트였다
            this->root = left_child; // 왼쪽에 있던 자식이 루트가 된다
        } else {
            if (node == node->parent->right_child) { // 오른쪽 자식이었으면
                node->parent->right_child = left_child; // 이제 오른쪽 자식은 왼쪽 자식으로
            } else {
                node->parent->left_child = left_child;
            }
        }
        left_child->parent = node;
        node->right_child = left_child;
    }

    void rotateLeft(Node *node) { // restruture, 왼쪽 자식 기준
        Node *right_child = node->right_child;
        node->right_child = right_child->left_child;
        if (right_child->left_child != nullptr)
            right_child->left_child->parent = node;
        right_child->parent = node->parent;
        if (node->parent == nullptr) {
            this->root = right_child;
        } else {
            if (node == node->parent->right_child) {
                node->parent->left_child = right_child;
            } else {
                node->parent->right_child = right_child;
            }
        }
        right_child->left_child = node;
        node->parent = right_child;
    }

    void fixTree(Node *node) {
        Node *uncle_node;
        Node *parent_node = node->parent;
        while (node != this->root && !parent_node->isBlack) { // red node까지 반복적으로 올라감
            if (parent_node == parent_node->parent->right_child) {
                uncle_node = parent_node->parent->left_child; // 삼촌 노드
                if (uncle_node != nullptr && !uncle_node->isBlack) { // 삼촌노드가 빨간색 ! recoloring !
                    parent_node->isBlack = true; // 부모 검정색으로
                    uncle_node->isBlack = true; // 삼촌 검정색으로
                    parent_node->parent->isBlack = false; // 조상 빨간색으로
                    node = parent_node->parent;
                } else { // Restructure !!
                    if (node == parent_node->left_child) { // 오른쪽 자식에 대한 restructure
                        node = parent_node;
                        rotateRight(node); //
                    }
                    parent_node->isBlack = true;
                    parent_node->parent->isBlack = false;
                    rotateLeft(parent_node->parent);
                }
            } else if (parent_node == parent_node->parent->left_child) {
                uncle_node = parent_node->parent->right_child;
                if (uncle_node != nullptr && !uncle_node->isBlack) { // 삼촌이 빨간색, recoloring
                    parent_node->isBlack = true;
                    uncle_node->isBlack = true;
                    parent_node->parent->isBlack = false;
                    node = parent_node->parent;
                } else {
                    if (node == parent_node->right_child) {
                        node = parent_node;
                        rotateLeft(node);
                    }
                    parent_node->isBlack = true;
                    parent_node->parent->isBlack = false;
                    rotateRight(parent_node->parent);
                }
            }
        }

        this->root->isBlack = true; // 루트를 검정색으로
    }

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

        node->parent = tmp_node; // tmp_node는 리프 전꺼까지
        node->depth = depth_count;
        if (tmp_node == nullptr) { // 빈 트리
            node->isBlack = true;
            this->root = node;
            return {node->depth, 1}; // 빈 트리에서 루트 추가, 성공
        } else if (tmp_node->patient->code > node->patient->code) {
            tmp_node->left_child = node;
        } else if (tmp_node->patient->code < node->patient->code) {
            tmp_node->right_child = node;
        }

        fixTree(node);

        depth_count = findDepth(patient_code);
        return {depth_count, 1};
    }

    pair<int, Patient *> findPatient(int patient_code) { // 깊이와 환자 리턴
        Node *tmp_root = this->root;
        while (tmp_root != nullptr) {
            if (tmp_root->patient->code == patient_code) {
                return {tmp_root->depth, tmp_root->patient};
            } else if (tmp_root->patient->code > patient_code) {
                tmp_root = tmp_root->left_child;
            } else if (tmp_root->patient->code < patient_code) {
                tmp_root = tmp_root->right_child;
            }
        }
        return {-1, NULL};
    }

    int addTreatment(int patient_code, string DI, int cost) {
        pair<int, Patient *> patient = findPatient(patient_code);
        if (patient.first == -1) {
            return -1;
        }

        patient.second->treatRecord.push_back({DI, cost});
        return patient.first;
    }

    void countByInorder(Node *node, string DI) {
        if (node == nullptr)
            return;
        if (node->patient->treatRecord[node->patient->treatRecord.size() - 1].first == DI)
            this->diagnose_count++;
        countByInorder(node->left_child, DI);
        countByInorder(node->right_child, DI);
    }

    int countDI(string DI) {
        this->diagnose_count = 0;
        if (this->root == nullptr)
            return 0;
        countByInorder(this->root, DI);
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
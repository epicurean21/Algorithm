#include<iostream>

#include<utility>

#include<fstream>

#include<string>

using namespace std;


/*

트리를 구성할 노드

왼쪽 자식포인터와 오른쪽 자식 포인터, 그리고 부모 포인터를 갖고

컬러값을 가진다.



RedBlackTree 연산시 판단을 쉽게하기 위해 IDENTITY로 해당 노드가 어떤타입인지 식별하도록 하였다.
*/
/*
        TreatInfo class
        레코드 정보 중 진료정보에 관한 데이터필드 정의
        */
class TreatInfo {
public:
    pair<int, int> day;    //진료날짜 : YYYYMMDD, HHMM
    string dept;            //진료과 : 10자를 넘지 않는다.
    string diagnosis;    //진단 병명 : 10자를 넘지 않는다.
    int cost;                //진단비용 : 100,000,000(1억)을 넘지않는다.
    TreatInfo() {
        day.first = -1;
        day.second = -1;
        diagnosis = "";
        cost = -1;
    }

    TreatInfo(int DayYMD, int DayHM, const char *Dept, const char *Diagnosis, int Cost) {
        day.first = DayYMD;
        day.second = DayHM;
        dept = Dept;
        diagnosis = Diagnosis;
        cost = Cost;
    }
};

class Record {
public:


    //data field
    int regi_num;                //등록번호 : 유일한 8자리의 수 (10000000) 부터 시작.  RBT의 키로 사용
    string name;                    //이름 : 한글 10자를 넘지 않는다. (유일하지 않을 수 있음)
    int birthday;                    //생년월일 : YYYYMMDD 의 8자리값
    TreatInfo treat_info;        //진료기록 : 진료과, 진료일자, 진료내역, 진료비 로 구성된 sequence
    pair<int, int> residence;    //거주지 : x, y 두 양의 좌표



    Record() {
        regi_num = -1;
        name = "";
        birthday = -1;
        treat_info = TreatInfo();
        residence.first = -1;
        residence.second = -1;
    }

    Record(int RegiNum, string Name, int BirthDay, TreatInfo Treat_Info, pair<int, int> Residence) {
        regi_num = RegiNum;
        name = Name;
        birthday = BirthDay;
        treat_info.day.first = Treat_Info.day.first;
        treat_info.day.second = Treat_Info.day.second;
        treat_info.dept = Treat_Info.dept;
        treat_info.diagnosis = Treat_Info.diagnosis;
        treat_info.cost = Treat_Info.cost;
        residence = Residence;
    }

    Record(int RegiNum, string Name, int BirthDay, int TreatDayYMD, int TreatDayHM,

           const char *TreatDept, const char *TreatDiagnosis, int TreatCost, pair<int, int> Residence) {

        regi_num = RegiNum;

        name = Name;

        birthday = BirthDay;

        treat_info = TreatInfo(TreatDayYMD, TreatDayHM, TreatDept, TreatDiagnosis, TreatCost);

        residence = Residence;

    }


    Record &operator=(const Record &operand) {

        regi_num = operand.regi_num;

        name = operand.name;

        birthday = operand.birthday;


        treat_info.day.first = operand.treat_info.day.first;

        treat_info.day.second = operand.treat_info.day.second;

        treat_info.dept = operand.treat_info.dept;

        treat_info.diagnosis = operand.treat_info.diagnosis;

        treat_info.cost = operand.treat_info.cost;


        residence.first = operand.residence.first;

        residence.second = operand.residence.second;

        return *this;

    }


    void printRecord() {

        cout << "환자명 : " << name << endl

             << "거주지 : " << residence.first << ',' << residence.second << endl

             << "등록번호 : " << regi_num << endl

             << "생년월일 : " << birthday << endl

             << "진료일자 : " << treat_info.day.first << ' ' << treat_info.day.second << endl

             << "진료 과 : " << treat_info.dept << endl

             << "병 명 : " << treat_info.diagnosis << endl

             << "진료비 : " << treat_info.cost << endl;

    }

    ~Record() {}

};//end Record class

class Node {

public:
    /*
    Node 클래스의 레코드
    */



    enum COLOR {
        RED, BLACK
    };

    enum IDENTITY {
        LEFTCHILD, RIGHTCHILD, ROOT, EXTERNAL
    };

private:

    Record record;

    IDENTITY identity;

    Node *parent;

    Node *left;

    Node *right;

    COLOR color;

public:

    Node(Node *Parent = NULL)    //기본생성은 EXTERNAL상태

    {

        memset(&record, 0, sizeof(Record));

        identity = EXTERNAL;

        parent = Parent;

        left = NULL;

        right = NULL;

        color = BLACK;    //EXTERNAL은 까만색

    }

    //기본적으로 호출되는 생성자. RED를 기본색값으로 가지고, EXTERNAL 자식을 생성시킨다.

    Node(Record &RecordData, Node *Parent, IDENTITY Identity, COLOR Color = RED) {

        record = RecordData;


        identity = Identity;

        parent = Parent;

        left = new Node(this);    //EXTERNAL노드 를 달아서 생성한다.

        right = new Node(this);

        color = Color;

    }



    //set, get함수들

    void setNode(Record &RecordData, Node *Parent, IDENTITY Identity, COLOR Color = RED) {

        record = RecordData;


        identity = Identity;

        parent = Parent;

        left = new Node(this);

        right = new Node(this);

        color = Color;

    }


    Record *getRecord() { return &record; }

    void setRecord(Record &RecordData) { record = RecordData; }


    IDENTITY getIdentity() { return identity; }

    void setIdentity(IDENTITY Identity) { identity = Identity; }


    COLOR getColor() { return color; }

    void setColor(COLOR Color) { color = Color; }


    Node *getLeftChild() { return left; }

    void setLeftChild(Record &RecordData) {

        this->getLeftChild()->setNode(RecordData, this, LEFTCHILD);

    }

    void setLeftChild(Node *Left) {

        left = Left;

        if (Left->getIdentity() != EXTERNAL)

            Left->setIdentity(LEFTCHILD);

    }


    Node *getRightChild() { return right; }

    void setRightChild(Record &RecordData) {

        this->getRightChild()->setNode(RecordData, this, RIGHTCHILD);

    }

    void setRightChild(Node *Right) {

        right = Right;

        if (Right->getIdentity() != EXTERNAL)

            Right->setIdentity(RIGHTCHILD);

    }


    Node *getParent() { return parent; }

    void setParent(Node *Parent) {

        parent = Parent;

    }



    //삼촌노드 반환

    Node *getUncle() {

        if (parent == NULL || parent->getParent() == NULL)

            return NULL;


        if (parent->getIdentity() == LEFTCHILD)

            return parent->getParent()->getRightChild();

        else

            return parent->getParent()->getLeftChild();

    }



    //할아버지노드 반환

    Node *getGrandparent() {

        if (parent == NULL)

            return NULL;

        return parent->getParent();

    }

    ~Node() {}

};


/*

RedBlackTree class

1. 모든 노드는 검정 or 빨간색을 가진다.

2. 루트노드는 검정색

3. 빨간노드의 자식은 검정노드

4. 모든 black depth는 동일

5. 단말노드는 검정색

*/

class RedBlackTree {

private:

    Node *root;

    int blackCnt;

    int nodeCnt;    //노드 수

public:

    RedBlackTree() {

        root = NULL;

        blackCnt = 0;

        nodeCnt = 0;

    }


    int getBlackCount() { return blackCnt; }

    int Count() { return nodeCnt; }


private:    //재귀 관련 함수들
    //삽입 재귀함수
    //EXTERNAL노드가 나올 때 까지 재귀적으로 삽입과정이 일어난다.
    Node *recInsert(Node *parent, Node::Record &_record) {
        if (_record.regi_num < parent->getRecord()->regi_num) {
            if (parent->getLeftChild()->getIdentity() == Node::EXTERNAL) {
                parent->setLeftChild(_record);
                return parent->getLeftChild();
            }
            return recInsert(parent->getLeftChild(), _record);
        } else {
            if (parent->getRightChild()->getIdentity() == Node::EXTERNAL) {
                parent->setRightChild(_record);
                return parent->getRightChild();
            }
            return recInsert(parent->getRightChild(), _record);
        }
    }

    //검색 재귀함수
    Node::Record *recSearch(Node *now, int Key, int &depth) {
        if (now->getIdentity() == Node::EXTERNAL)
            return NULL;

        if (now->getRecord()->regi_num == Key)
            return now->getRecord();
        else if (now->getRecord()->regi_num > Key) {
            depth++;
            return recSearch(now->getLeftChild(), Key, depth);
        } else {
            depth++;
            return recSearch(now->getRightChild(), Key, depth);
        }
    }

    //Restructuring 은 더블레드이고 삼촌노드가 까만색일 때 호출. RR RL LR LL  케이스에 따라 작동.
    void Restructuring(Node *node) {
        Node *p = node->getParent();
        Node *g = node->getGrandparent();
        if (p->getIdentity() == Node::LEFTCHILD) {    //L-
            if (node->getIdentity() == Node::RIGHTCHILD) {    //L-R case
                g->setLeftChild(node->getRightChild());
                p->setRightChild(node->getLeftChild());
                node->setParent(g->getParent());
                node->setIdentity(g->getIdentity());
                if (node->getIdentity() == Node::ROOT)
                    root = node;

                node->setRightChild(g);
                g->setParent(node);
                node->setLeftChild(p);
                p->setParent(node);
                node->setColor(Node::BLACK);
                g->setColor(Node::RED);
                //p->setColor(Node::RED);
            } else {    //L-L case
                g->setLeftChild(p->getRightChild());
                p->setParent(g->getParent());
                p->setIdentity(g->getIdentity());

                if (p->getIdentity() == Node::ROOT)
                    root = p;

                p->setRightChild(g);
                g->setParent(p);
                p->setColor(Node::BLACK);
                g->setColor(Node::RED);
                //node->setColor(Node::RED);
            }
        } else {    //R-
            if (node->getIdentity() == Node::LEFTCHILD) {    //R-L case
                g->setRightChild(node->getLeftChild());
                p->setLeftChild(node->getRightChild());
                node->setParent(g->getParent());
                node->setIdentity(g->getIdentity());

                if (node->getIdentity() == Node::ROOT)
                    root = node;

                node->setLeftChild(g);
                g->setParent(node);
                node->setRightChild(p);
                p->setParent(node);
                node->setColor(Node::BLACK);
                g->setColor(Node::RED);
                //p->setColor(Node::RED);
            } else { //R-R case
                g->setRightChild(p->getLeftChild());
                p->setParent(g->getParent());
                p->setIdentity(g->getIdentity());
                if (p->getIdentity() == Node::ROOT)
                    root = p;
                p->setLeftChild(g);
                g->setParent(p);
                p->setColor(Node::BLACK);
                g->setColor(Node::RED);
                //node->setColor(Node::RED);
            }
        }
    }

    //Recoloring 은 더블레드이고 삼촌노드가 빨간색일 때 호출.
    //node의 할아버지노드포인터 반환되어 재귀적으로 더블레드를 검사한다.
    Node *Recoloring(Node *node) {
        node->getParent()->setColor(Node::BLACK);
        node->getUncle()->setColor(Node::BLACK);
        Node *grandp = node->getGrandparent();
        grandp->setColor(Node::RED);
        return grandp;
    }

public:
    //레코드 삽입
    void Insert(Node::Record &RecordData) {
        if (root == NULL) {
            root = new Node(RecordData, NULL, Node::ROOT, Node::BLACK);
            blackCnt = 1;
            nodeCnt = 1;
            return;
        }
        //else
        Node *node = recInsert(root, RecordData);    //재귀삽입 호출
        nodeCnt++;

        //트리 Fix과정
        while (node->getParent() != NULL) {
            if (node->getParent()->getColor() != Node::RED)
                return;
            if (node->getUncle()->getColor() == Node::BLACK) {
                Restructuring(node);    //Restructuring이 일어나면 black depth가 1 증가하고 Fix가 종료된다.
                blackCnt++;
                return;
            } else {
                node = Recoloring(node);
                if (node->getIdentity() == Node::ROOT) {    //Recoloring 중 root까지 오면 ret->black으로 바꾸고 종료
                    node->setColor(Node::BLACK);
                    return;
                }
            }
        }//end while
    }//end Insert

    //검색
    //입력된 키(등록번호)의 레코드를 반환한다.
    //해당 키의 레코드가 없다면 NULL반환
    Node::Record *Search(int Key, int &depth) {
        if (root == NULL)
            return NULL;

        depth = 0;
        Node::Record *reco = recSearch(root, Key, depth);
        if (reco == NULL)
            return NULL;
        return reco;
    }


private:
    //파일 기록
    void recFileWrite(Node *now, ofstream &fout) {
        if (now->getIdentity() == Node::EXTERNAL)
            return;
        recFileWrite(now->getLeftChild(), fout);
        //등록번호, 이름, 생년월일

        //최초진료기록(진료일자yyymmdd, 진료일자hhmm, 진료과, 병명, 진료비, 거주지x, 거주지y)
        Node::Record *tmp = now->getRecord();
        fout << tmp->regi_num << ' ' << tmp->name << ' ' << tmp->birthday << endl

             << tmp->treat_info.day.first << ' ' << tmp->treat_info.day.second << ' ' << tmp->treat_info.dept << ' '
             << tmp->treat_info.diagnosis << ' '

             << tmp->treat_info.cost << ' ' << tmp->residence.first << ' ' << tmp->residence.second << endl;
        recFileWrite(now->getRightChild(), fout);
        return;
    }

    //검사 과에 따라 파일 기록
    void recCondFileWriteByDept(Node *now, string &deptCond, ofstream &fout, int depth) {
        if (now->getIdentity() == Node::EXTERNAL)
            return;

        recCondFileWriteByDept(now->getLeftChild(), deptCond, fout, depth + 1);
        Node::Record *tmp = now->getRecord();
        if (tmp->treat_info.dept == deptCond) {
            fout << tmp->regi_num << ' ' << tmp->name << ' ' << tmp->birthday << endl

                 << tmp->treat_info.day.first << ' ' << tmp->treat_info.day.second << ' ' << tmp->treat_info.dept << ' '
                 << tmp->treat_info.diagnosis << ' '

                 << tmp->treat_info.cost << ' ' << tmp->residence.first << ' ' << tmp->residence.second << endl << depth
                 << endl;
        }
        recCondFileWriteByDept(now->getRightChild(), deptCond, fout, depth + 1);
        return;
    }

    //모든 정보 기록
    void recCondFileWriteAll(Node *now, ofstream &fout, int depth) {
        if (now->getIdentity() == Node::EXTERNAL)
            return;
        recCondFileWriteAll(now->getLeftChild(), fout, depth + 1);
        Node::Record *tmp = now->getRecord();
        fout << tmp->regi_num << ' ' << tmp->name << ' ' << tmp->birthday << endl

             << tmp->treat_info.day.first << ' ' << tmp->treat_info.day.second << ' ' << tmp->treat_info.dept << ' '
             << tmp->treat_info.diagnosis << ' '

             << tmp->treat_info.cost << ' ' << tmp->residence.first << ' ' << tmp->residence.second << endl << depth
             << endl;

        recCondFileWriteAll(now->getRightChild(), fout, depth + 1);
        return;
    }

    //병명에 따라 파일기록
    void recCondFileWriteByDiagnosis(Node *now, string &diagCond, ofstream &fout, int depth) {
        if (now->getIdentity() == Node::EXTERNAL)
            return;

        recCondFileWriteByDiagnosis(now->getLeftChild(), diagCond, fout, depth + 1);

        Node::Record *tmp = now->getRecord();
        if (tmp->treat_info.diagnosis == diagCond) {
            fout << tmp->regi_num << ' ' << tmp->name << ' ' << tmp->birthday << endl
                 << tmp->treat_info.day.first << ' ' << tmp->treat_info.day.second << ' ' << tmp->treat_info.dept << ' '
                 << tmp->treat_info.diagnosis << ' '
                 << tmp->treat_info.cost << ' ' << tmp->residence.first << ' ' << tmp->residence.second << endl << depth
                 << endl;
        }
        recCondFileWriteByDiagnosis(now->getRightChild(), diagCond, fout, depth + 1);
        return;
    }

public:
    bool FileWrite(ofstream &fout) {
        if (root == NULL)
            return false;

        recFileWrite(root, fout);
        return true;
    }

    bool CondFileWriteAll(ofstream &fout) {
        if (root == NULL)
            return false;
        recCondFileWriteAll(root, fout, 0);
        return true;
    }

    bool CondFileWriteByDept(string &deptCond, ofstream &fout) {
        if (root == NULL)
            return false;
        recCondFileWriteByDept(root, deptCond, fout, 0);
        return true;
    }

    bool CondFileWriteByDiagnosis(string &diagCond, ofstream &fout) {
        if (root == NULL)
            return false;
        recCondFileWriteByDiagnosis(root, diagCond, fout, 0);
        return true;
    }
};

// Red Black Tree implementation in C++
// Author: Algorithm Tutor
// Tutorial URL: https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/

#include <iostream>

using namespace std;

// data structure that represents a node in the tree
struct Node {
    int data; // holds the key
    Node *parent; // pointer to the parent
    Node *left; // pointer to left child
    Node *right; // pointer to right child
    int color; // 1 -> Red, 0 -> Black
};

typedef Node *NodePtr;

// class RBTree implements the operations in Red Black Tree
class RBTree {
private:
    NodePtr root;
    NodePtr TNULL;

    // initializes the nodes with appropirate values
    // all the pointers are set to point to the null pointer
    void initializeNULLNode(NodePtr node, NodePtr parent) {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }

    void preOrderHelper(NodePtr node) {
        if (node != TNULL) {
            cout << node->data << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    void inOrderHelper(NodePtr node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

    void postOrderHelper(NodePtr node) {
        if (node != TNULL) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->data << " ";
        }
    }

    NodePtr searchTreeHelper(NodePtr node, int key) {
        if (node == TNULL || key == node->data) {
            return node;
        }

        if (key < node->data) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    // fix the rb tree modified by the delete operation
    void fixDelete(NodePtr x) {
        NodePtr s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    // case 3.1
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    // case 3.2
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->right->color == 0) {
                        // case 3.3
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == 1) {
                    // case 3.1
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0) {
                    // case 3.2
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->left->color == 0) {
                        // case 3.3
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }


    void rbTransplant(NodePtr u, NodePtr v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(NodePtr node, int key) {
        // find the node containing key
        NodePtr z = TNULL;
        NodePtr x, y;
        while (node != TNULL) {
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            cout << "Couldn't find key in the tree" << endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            fixDelete(x);
        }
    }

    // fix the red-black tree
    void fixInsert(NodePtr k) {
        NodePtr u;
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left; // uncle
                if (u->color == 1) {
                    // case 3.1
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        // case 3.2.2
                        k = k->parent;
                        rightRotate(k);
                    }
                    // case 3.2.1
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right; // uncle

                if (u->color == 1) {
                    // mirror case 3.1
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        // mirror case 3.2.2
                        k = k->parent;
                        leftRotate(k);
                    }
                    // mirror case 3.2.1
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }

    void printHelper(NodePtr root, string indent, bool last) {
        // print the tree structure on the screen
        if (root != TNULL) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "     ";
            } else {
                cout << "L----";
                indent += "|    ";
            }

            string sColor = root->color ? "RED" : "BLACK";
            cout << root->data << "(" << sColor << ")" << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
        // cout<<root->left->data<<endl;
    }

public:
    RBTree() {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    // Pre-Order traversal
    // Node->Left Subtree->Right Subtree
    void preorder() {
        preOrderHelper(this->root);
    }

    // In-Order traversal
    // Left Subtree -> Node -> Right Subtree
    void inorder() {
        inOrderHelper(this->root);
    }

    // Post-Order traversal
    // Left Subtree -> Right Subtree -> Node
    void postorder() {
        postOrderHelper(this->root);
    }

    // search the tree for the key k
    // and return the corresponding node
    NodePtr searchTree(int k) {
        return searchTreeHelper(this->root, k);
    }

    // find the node with the minimum key
    NodePtr minimum(NodePtr node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    // find the node with the maximum key
    NodePtr maximum(NodePtr node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    // find the successor of a given node
    NodePtr successor(NodePtr x) {
        // if the right subtree is not null,
        // the successor is the leftmost node in the
        // right subtree
        if (x->right != TNULL) {
            return minimum(x->right);
        }

        // else it is the lowest ancestor of x whose
        // left child is also an ancestor of x.
        NodePtr y = x->parent;
        while (y != TNULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    // find the predecessor of a given node
    NodePtr predecessor(NodePtr x) {
        // if the left subtree is not null,
        // the predecessor is the rightmost node in the
        // left subtree
        if (x->left != TNULL) {
            return maximum(x->left);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    // rotate left at node x
    void leftRotate(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // rotate right at node x
    void rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // insert the key to the tree in its appropriate position
    // and fix the tree
    void insert(int key) {
        // Ordinary Binary Search Insertion
        NodePtr node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1; // new node must be red

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        // y is parent of x
        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        // if new node is a root node, simply return
        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }

        // if the grandparent is null, simply return
        if (node->parent->parent == nullptr) {
            return;
        }

        // Fix the tree
        fixInsert(node);
    }

    NodePtr getRoot() {
        return this->root;
    }

    // delete the node from the tree
    void deleteNode(int data) {
        deleteNodeHelper(this->root, data);
    }

    // print the tree structure on the screen
    void prettyPrint() {
        if (root) {
            printHelper(this->root, "", true);
        }
    }

};

int main() {
    RBTree bst;
    bst.insert(8);
    bst.insert(18);
    bst.insert(5);
    bst.insert(15);
    bst.insert(17);
    bst.insert(25);
    bst.insert(40);
    bst.insert(80);
    bst.deleteNode(25);
    bst.prettyPrint();
    return 0;
}
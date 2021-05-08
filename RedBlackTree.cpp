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

class Node {

public:
    /*
    Node 클래스의 레코드
    */

    class Record {
    public:
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
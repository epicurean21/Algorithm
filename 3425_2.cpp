#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;
#define ll long long
#define MAX 1000000000

stack<ll> st;
vector<string> cmd;
vector<ll> NUM_X;
int n, first, state, NUM_top;
ll x;
string str;

void init() {
    state = 0;
    NUM_X.clear();
    cmd.clear();
}

int NUMX(ll x) {
    st.push(x);
    return 0;
}

int POP() {
    if (st.empty())
        return 1;
    st.pop();
    return 0;
}

int INV() {
    if (st.empty())
        return 1;

    ll x = -(st.top());
    st.pop();
    st.push(x);
    return 0;
}

int DUP() {
    if (st.empty())
        return 1;

    st.push(st.top());
    return 0;
}

int SWP() {
    if (st.empty())
        return 1;

    ll x = st.top();
    st.pop();

    if (st.empty()) {
        return 1;
    }

    ll y = st.top();
    st.pop();
    st.push(x);
    st.push(y);
    return 0;
}

int ADD() {
    if (st.empty())
        return 1;

    ll x = st.top();
    st.pop();

    if (st.empty())
        return 1;

    x += st.top();
    st.pop();
    st.push(x);

    return 0;
}

int SUB() {
    if (st.empty())
        return 1;

    ll x = st.top();
    st.pop();

    if (st.empty())
        return 1;

    x = st.top() - x;
    st.pop();
    st.push(x);

    return 0;
}

int MUL() {
    if (st.empty())
        return 1;

    ll x = st.top();
    st.pop();

    if (st.empty())
        return 1;

    x *= st.top();
    st.pop();
    st.push(x);

    return 0;
}

int DIV() {
    int neg = 0;
    if (st.empty())
        return 1;
    ll x = st.top();
    if (x < 0) ++neg;
    st.pop();

    if (st.empty())
        return 1;
    ll y = st.top();
    if (y < 0) ++neg;

    if (x == 0)
        return 1;
    x = y / x;
    if (neg == 1) x = -(abs(x));
    else x = abs(x);

    st.pop();
    st.push(x);
    return 0;
}

int MOD() {
    int neg = 0;

    if (st.empty())
        return 1;

    ll x = st.top();

    st.pop();

    if (st.empty())
        return 1;

    ll y = st.top();
    if (y < 0) ++neg;

    if (x == 0)
        return 1;

    x = y % x;
    if (neg == 1) x = -(abs(x));
    else x = abs(x);

    st.pop();
    st.push(x);

    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    while (1) {
        init();
        while (1) { // 명령어 입력받기
            cin >> str;
            if (str == "NUM") {
                cin >> x;
                NUM_X.push_back(x);
            } else if (str == "QUIT") {
                return 0;
            } else if (str == "END") {
                break;
            }
            cmd.push_back(str);
        }

        cin >> n;
        while (n--) {
            NUM_top = 0;
            cin >> first;
            st.push(first);

            for (int i = 0; i < cmd.size(); ++i) {
                if (cmd[i] == "NUM")
                    state = NUMX(NUM_X[NUM_top++]);
                else if (cmd[i] == "POP")
                    state = POP();
                else if (cmd[i] == "INV")
                    state = INV();
                else if (cmd[i] == "DUP")
                    state = DUP();
                else if (cmd[i] == "SWP")
                    state = SWP();
                else if (cmd[i] == "ADD")
                    state = ADD();
                else if (cmd[i] == "SUB")
                    state = SUB();
                else if (cmd[i] == "MUL")
                    state = MUL();
                else if (cmd[i] == "DIV")
                    state = DIV();
                else if (cmd[i] == "MOD")
                    state = MOD();

                if (!st.empty() && (st.top() > MAX || st.top() < -MAX))
                    state = 1;
                if (state)
                    break;
            }

            if (state == 1 || st.size() != 1)
                cout << "ERROR\n";
            else
                cout << st.top() << "\n";
            while (!st.empty())
                st.pop();
        }
        cout << "\n";
    }
}
#include <iostream>
#include <stack>
#include <string>
#include <queue>
#include <cmath>
using namespace std;
#define MAX 1000000000
#define ll long long
int N;
string cmd;
stack<ll> st;
queue<ll> numSt;
queue<string> cmdSt;

void init() {
    while (!cmdSt.empty())
        cmdSt.pop();
    while (!numSt.empty())
        numSt.pop();
    cout << "\n";
}

void NUMX(ll x) {
    st.push(x);
}

bool POP() {
    if (!st.empty()) {
        st.pop();
        return true;
    } else
        return false;
}

bool INV() {
    if (!st.empty()) {
        ll tmp = st.top();
        st.pop();
        tmp *= -1;
        st.push(tmp);
        return true;
    } else
        return false;
}

bool DUP() {
    if (!st.empty()) {
        st.push(st.top());
        return true;
    } else
        return false;
}

bool SWP() {
    if (!st.empty()) {
        ll tmp1 = st.top();
        st.pop();
        if (!st.empty()) {
            ll tmp2 = st.top();
            st.pop();
            st.push(tmp1);
            st.push(tmp2);
            return true;
        } else {
            st.push(tmp1);
            return false;
        }
    } else
        return false;
}

bool ADD() {
    if (!st.empty()) {
        ll tmp1 = st.top();
        st.pop();
        if (!st.empty()) {
            ll tmp2 = st.top();
            st.pop();
            st.push(tmp1 + tmp2);
            return true;
        } else {
            st.push(tmp1);
            return false;
        }
    } else
        return false;
}

bool SUB() {
    if (!st.empty()) {
        ll tmp1 = st.top();
        st.pop();
        if (!st.empty()) {
            ll tmp2 = st.top();
            st.pop();
            st.push(tmp2 - tmp1);
            return true;
        } else {
            st.push(tmp1);
            return false;
        }
    } else
        return false;
}

bool MUL() {
    if (!st.empty()) {
        ll tmp1 = st.top();
        st.pop();
        if (!st.empty()) {
            ll tmp2 = st.top();
            st.pop();
            st.push(tmp1 * tmp2);
            return true;
        } else {
            st.push(tmp1);
            return false;
        }
    } else
        return false;
}

bool DIV() {
    if (!st.empty()) {
        ll tmp1 = st.top();
        st.pop();
        if (!st.empty()) {
            ll tmp2 = st.top();
            st.pop();
            if(tmp1 != 0) {
                ll tmp3 = tmp2 / tmp1;
                if((tmp1 < 0 && tmp2 > 0) || (tmp2 < 0 && tmp1 > 0))
                    tmp3 = -1 * abs(tmp3);
                else
                    tmp3 = abs(tmp3);
                st.push(tmp3);
                return true;
            }
            else
                return false;
        } else {
            st.push(tmp1);
            return false;
        }
    } else
        return false;
}

bool MOD() {
    if (!st.empty()) {
        ll tmp1 = st.top();
        st.pop();
        if (!st.empty()) {
            ll tmp2 = st.top();
            st.pop();
            if(tmp1 != 0) {
                ll tmp3 = tmp2 % tmp1;
                if(tmp2 < 0)
                    tmp3 = -1 * abs(tmp3);
                else
                    tmp3 = abs(tmp3);
                st.push(tmp3);
                return true;
            }
            else
                return false;
        } else {
            st.push(tmp1);
            return false;
        }
    } else
        return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    while (1) {
        init();
        while (cin >> cmd) {
            if (cmd == "END")
                break;
            if (cmd == "QUIT")
                return 0;
            if (cmd == "NUM") {
                int tmp;
                cin >> tmp;
                numSt.push(tmp);
            }
            cmdSt.push(cmd);
        }
        cin >> N;
        while (N--) {
            int num;
            bool state = true;
            cin >> num;
            st.push(num);
            for (int i = 0; i < cmdSt.size(); i++) {
                string tmp = cmdSt.front();
                cmdSt.pop();
                cmdSt.push(tmp);
                if (tmp == "NUM") {
                    NUMX(numSt.front());
                    numSt.push(numSt.front());
                    numSt.pop();
                } else if (tmp == "POP")
                    state = POP();
                else if (tmp == "INV")
                    state = INV();
                else if (tmp == "DUP")
                    state = DUP();
                else if (tmp == "SWP")
                    state = SWP();
                else if (tmp == "ADD")
                    state = ADD();
                else if (tmp == "SUB")
                    state = SUB();
                else if (tmp == "MUL")
                    state = MUL();
                else if (tmp == "DIV")
                    state = DIV();
                else if (tmp == "MOD")
                    state = MOD();

                if (!st.empty() && (st.top() > MAX || st.top() < -1 * MAX)) state = false;
                if (!state) break;
            }
            if (!state || st.size() != 1)
                cout << "ERROR\n";
            else
                cout << st.top() << "\n";
            while (!st.empty())
                st.pop();
        }
    }
    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

vector<int> eGcd(int a, int b) {
    vector<int> re;
    int s0 = 1, t0 = 0, r0 = a;
    int s1 = 0, t1 = 1, r1 = b;

    int tmp;
    while(r1 != 0) {
        int q = r0 / r1;
        tmp = r0 - q * r1;
        r0 = r1;
        r1 = tmp;

        tmp = s0 - q * s1;
        s0 = s1;
        s1 = tmp;

        tmp  = t0 - q * t1;
        t0 = t1;
        t1 = tmp;
    }
    re.push_back(s0);
    re.push_back(t0);
    re.push_back(r0);
    return re;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    vector<int> print;
    print = eGcd(71, 240);
    cout << print[0] << " " << print[1] << " " << print[2] << "\n";
    return 0;
}
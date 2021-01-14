#include <iostream>
#include <string>
#include <map>
using namespace std;

int cnt;
string str;
map<string, double> tree;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    while(getline(cin, str)) {
        tree[str]++;
        cnt++;
    }
    cout.precision(4);
    cout << fixed;
    for(auto i : tree)
        cout << i.first << " " << i.second / cnt * 100 << "\n";
    return 0;
}
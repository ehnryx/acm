#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  string a, b; cin >> a >> b;
  multiset<char> c(a.begin(), a.end());

  int ptr = 0;
  for (char cc : a) {
    while (ptr < b.size() && b[ptr] != cc) {
      if (c.count(b[ptr])) {
        cout << "FAIL" << endl;
        return 0;
      }
      ptr++;
    }
    if (ptr == b.size()) {
      cout << "FAIL" << endl;
      return 0;
    }
    c.erase(c.find(cc));
    ptr++;
  }
  cout << "PASS" << endl;

  return 0;
}

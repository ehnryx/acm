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

  int a = 0, b = 0;
  map<char, int> wrong;
  int t;
  while (cin >> t) {
    if (t == -1) break;
    char c; string s; cin >> c >> s;
    if (s[0] == 'r')
      a++, b += t + wrong[c] * 20;
    else
      wrong[c]++;
  }
  cout << a << " " << b << endl;

  return 0;
}

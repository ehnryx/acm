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
#define pt complex<ldouble>

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  vector<pt> ans;
  double x, y;
  ans.push_back(pt(0,0));
  while (cin >> x >> y) {
    ans.push_back(pt(x,y));
  }
  for (int i = 1; i < ans.size(); i++) {
    cout << abs(ans[i] - ans[i-1]) << nl;
  }

  return 0;
}

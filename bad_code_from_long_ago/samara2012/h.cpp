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

  int n, temp;
  cin >> n;
  int pile = 0;
  for (int i = 0; i < n; i++) {
    cin >> temp;
    pile = max(pile, temp);
  }
  if (__builtin_popcount(pile+1) == 1) {
    cout << "Mike" << nl;
  }
  else {
    cout << "Constantine" << nl;
  }

  return 0;
}

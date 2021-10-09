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

  map<int,int> div; // divisor, multiplier
  ll prefix[10001];
  ll arr[10001];
  int id, m;
  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    div.clear();
    cin >> id >> m;
    for (int i = 0; i < m; i++) {
      cin >> arr[i];
    }
    prefix[0] = 0;
    for (int i = 0; i < m; i++) {
      prefix[i+1] = prefix[i] + arr[i];
    }
  }

  return 0;
}

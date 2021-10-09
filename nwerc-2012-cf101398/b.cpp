#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

unordered_map<int,ld> ans[51];
const int mask = (1<<6)-1;
int a[5];
ld res[5];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(2);

  int n, k;
  while (cin >> n >> k) {
    int h = 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      sum += a[i];
      h |= a[i] << (6*i);
    }

    fill(ans, ans+k+1, unordered_map<int,ld>());
    ans[sum][h] = 1;
    for (int i = sum; i < k; i++) {
      for (const pair<int,ld>& it : ans[i]) {
        for (int j = 0; j < n; j++) {
          int v = (it.first & mask<<(6*j)) >> (6*j);
          ld p = (ld)v/i;
          ans[i+1][it.first + (1<<(6*j))] += p*it.second;
        }
      }
    }

    fill(res, res+n, 0);
    for (const pair<int,ld>& it : ans[k]) {
      int cur = 0;
      int best = 0;
      //cerr << it.first << ": ";
      for (int j = 0; j < n; j++) {
        int v = (it.first & mask<<(6*j)) >> (6*j);
        //cerr << v << " ";
        if (v > best) {
          best = v;
          cur = 0;
        }
        if (v == best) {
          cur |= 1<<j;
        }
      }
      //cerr << nl;

      int cnt = __builtin_popcount(cur);
      for (int j = 0; j < n; j++) {
        if (cur & 1<<j) {
          res[j] += ((ld)1/cnt) * it.second;
        }
      }
    }

    for (int i = 0; i < n; i++) {
      cout << "pub " << i+1 << ": " << 100*res[i] << " %" << nl;
    }
  }

  return 0;
}

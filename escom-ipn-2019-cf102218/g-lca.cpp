#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int lcis_len(vector<int>& a, vector<int>& b) {
  //bool swapped = false;
  //if (a.size() < b.size()) {
    //swap(a,b);
    //swapped = true;
  //}
  int n = a.size();
  int m = b.size();
  int lcis[2][m];
  memset(lcis[1], 0, sizeof lcis[1]);
  for (int i = 0; i < n; i++) {
    int maxv = 0;
    for (int j = 0; j < m; j++) {
      lcis[i&1][j] = lcis[(i&1)^1][j];
      if (a[i] == b[j]) {
        lcis[i&1][j] = maxv+1;
      } else if (a[i] > b[j]) {
        maxv = max(maxv, lcis[(i&1)^1][j]);
      }
    }
  }
  //if (swapped) {
    //swap(a,b);
  //}
  int res = 0;
  for (int j = 0; j < m; j++) {
    res = max(res, lcis[(n&1)^1][j]);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  vector<int> a, b;
  For(i,n) {
    int v;
    cin >> v;
    a.push_back(v);
  }
  For(j,m) {
    int v;
    cin >> v;
    b.push_back(v);
  }

  cout << 2*lcis_len(a,b) << nl;

  return 0;
}

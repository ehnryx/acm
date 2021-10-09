//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1 << 19;
int val[N];

unordered_map<int,int> st[2*N];
int get(int x, int v) {
  auto it = st[x].find(v);
  if(it == st[x].end()) return 0;
  else return it->second;
}
void insert(int x, int v, int c) {
  for(x+=N; x>0; x/=2) {
    if((st[x][v] += c) == 0) {
      st[x].erase(v);
    }
  }
}
int query(int l, int r, int v) {
  int res = 0;
  for(l+=N, r+=N+1; l<r; l/=2, r/=2) {
    if(l&1) res += get(l++, v);
    if(r&1) res += get(--r, v);
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    insert(i, 0, 1);
  }
  for(int i=0; i<m; i++) {
    int t;
    cin >> t;
    if(t == 1) {
      int x;
      cin >> x;
      insert(x, val[x], -1);
      insert(x, ++val[x], 1);
    } else if(t == 2) {
      int x;
      cin >> x;
      insert(x, val[x], -1);
      insert(x, --val[x], 1);
    } else {
      int l, r, c;
      cin >> l >> r >> c;
      cout << query(l, r, c) << nl;
    }
  }

  return 0;
}

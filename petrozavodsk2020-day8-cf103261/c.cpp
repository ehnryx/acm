#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int N = 1 << 19;
int st[2*N];
void insert(int i, int v) {
  st[i+=N] = v;
  for(i/=2; i; i/=2) {
    st[i] = max(st[2*i], st[2*i+1]);
  }
}
int query(int l, int r) {
  int res = -INF;
  for(l+=N, r+=N; l<r; l/=2, r/=2) {
    if(l&1) res = max(res, st[l++]);
    if(r&1) res = max(res, st[--r]);
  }
  return res;
}

struct Column {
  int y;
  vector<int> below;
  Column(int _y): y(_y), below() {}
};

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;

  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
    insert(i, -INF);
  }

  vector<int> len(n+1);
  stack<Column> line;
  line.emplace(0);
  insert(0, 0);
  for(int i=1; i<=n; i++) {
    len[i] = query(0, a[i]) + 1;
    insert(a[i], len[i]);
    Column cur(a[i]);
    while(!empty(line) && line.top().y < a[i]) {
      cur.below.push_back(line.top().y);
      for(int rem : line.top().below) {
        insert(rem, -INF);
      }
      line.pop();
    }
    line.push(move(cur));
  }
  cout << n - *max_element(begin(len), end(len)) << nl;

  return 0;
}

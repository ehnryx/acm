#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
template <typename T> inline void read(T &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

const int N = 1 << 19;
pair<int,int> st[2*N];
int ans[N];

void insert(int i, pair<int,int> v) {
  st[i+=N] = v;
  for(i/=2; i; i/=2) {
    st[i] = min(st[2*i], st[2*i+1]);
  }
}

int query(int l, int r) {
  int res = INF;
  for(l+=N, r+=N+1; l<r; l/=2, r/=2) {
    if(l&1) res = min(res, st[l++].first);
    if(r&1) res = min(res, st[--r].first);
  }
  return res;
}

void remove(int l, int r, int v, int y, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l || st[i].first>v) return;
  if(s == e) {
    st[i].first = INF;
    ans[st[i].second] = y;
    return;
  }
  int m = (s+e)/2;
  remove(l, r, v, y, 2*i, s, m);
  remove(l, r, v, y, 2*i+1, m+1, e);
  st[i] = min(st[2*i], st[2*i+1]);
}

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

  memset(st, INF, sizeof st);

  int n, m;
  cin >> n >> m;
  vector<tuple<int,int,int>> order;
  vector<tuple<int,int,int>> ev;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    ev.emplace_back(x, -i, y);
    order.emplace_back(x, 0, i);
  }
  for(int i=0; i<m; i++) {
    int a, b, y;
    cin >> a >> b >> y;
    ev.emplace_back(a, b, y);
    order.emplace_back(a, -1, n+i);
    order.emplace_back(b, 1, n+i);
  }
  sort(order.begin(), order.end());

  for(int i=0; i<order.size(); i++) {
    auto [_, t, j] = order[i];
    if(t == -1) {
      get<0>(ev[j]) = i;
    } else if(t == 1) {
      get<1>(ev[j]) = i;
    } else {
      get<0>(ev[j]) = i;
    }
  }
  sort(ev.begin(), ev.end(), [](const auto& a, const auto& b) {
    return get<2>(a) > get<2>(b);
  });

  for(auto [a, b, y] : ev) {
    if(b <= 0) {
      insert(a, pair(y, -b));
    } else {
      int target = query(a, b);
      if(target < INF) {
        remove(a, b, target, y);
      }
    }
  }

  for(int i=0; i<n; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int N = 1 << 18;
int st[2*N], total[2*N];
int len[N];

void pull(int i, int all) {
  if(st[i]) {
    total[i] = all;
  } else if(i < N) {
    total[i] = total[2*i] + total[2*i+1];
  } else {
    total[i] = 0;
  }
}

void insert(int l, int r, int t, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return;
  if(l<=s && e<=r) {
    st[i] += t;
    pull(i, len[e+1] - len[s]);
    return;
  }
  int m = (s+e)/2;
  insert(l, r, t, 2*i, s, m);
  insert(l, r, t, 2*i+1, m+1, e);
  pull(i, len[e+1] - len[s]);
}

int query() {
  return total[1];
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  vector<tuple<int, int, int, int>> ev;
  set<int> all;
  for(int i=0; i<n; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    ev.emplace_back(a, b, y, 1);
    ev.emplace_back(x, b, y, -1);
    all.insert(b);
    all.insert(y);
  }
  sort(begin(ev), end(ev));

  vector<int> pts(begin(all), end(all));
  map<int, int> remap;
  for(int i=0; i<size(pts); i++) {
    len[i] = pts[i]; // uhh
    remap[pts[i]] = i;
  }

  int last_x = 0;
  ll ans = 0;
  for(auto [x, a, b, t] : ev) {
    ans += (ll)query() * (x - last_x);
    insert(remap[a], remap[b] - 1, t); // remapped inclusive range
    last_x = x;
  }
  cout << ans << nl;

  return 0;
}

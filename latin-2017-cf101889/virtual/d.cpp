#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1<<17;
int segt[2*N];
int cnt[N];

int query(int x) {
  return cnt[x];
}

void push(int i) {
  if (segt[i] != -1) {
    segt[2*i] = segt[2*i+1] = segt[i];
  }
}

void pull(int i) {
  if (segt[2*i] == segt[2*i+1]) {
    segt[i] = segt[2*i];
  } else {
    segt[i] = -1;
  }
}

void update(int l, int r, int x, int i=1, int s=0, int e=N-1) {
  if (e < l || s > r) return;
  if (l <= s && e <= r && segt[i] != -1) {
    cnt[segt[i]] -= e-s+1;
    cnt[x] += e-s+1;
    segt[i] = x;
    return;
  }
  push(i);
  int mid = (s+e)/2;
  update(l, r, x, 2*i, s, mid);
  update(l, r, x, 2*i+1, mid+1, e);
  pull(i);
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int l, c, n, p, x, a, b;
  cin >> l >> c >> n;

  cnt[1] = l;
  fill(segt, segt+N, 1);

  for (int i=0; i<n; i++) {
    cin >> p >> x >> a >> b;
    ll s = query(p);
    int m1 = (a+s*s) % l;
    int m2 = (a+(s+b)*(s+b)) % l;
    if (m1 > m2) swap(m1, m2);
    update(m1, m2, x);
  }

  int ans = 0;
  for (int i=1; i<=c; i++) {
    ans = max(ans, query(i));
  }
  cout << ans << nl;

  return 0;
}

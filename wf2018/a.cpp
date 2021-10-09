#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Bus {
  int a, b;
  ll s, t;
  ld p;
  bool operator < (const Bus& v) const { return s < v.s; }
  bool operator > (const Bus& v) const { return s > v.s; }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int m, n;
  cin >> m >> n;

  ll k;
  cin >> k;

  int a, b;
  ll s, t;
  ld p;
  vector<Bus> bus;
  for (int i = 0; i < m; i++) {
    cin >> a >> b >> s >> t >> p;
    bus.push_back({a,b,s,t,p});
  }
  sort(bus.begin(), bus.end(), greater<Bus>());

  const int source = 0;
  const int sink = 1;

  map<ll,ld> memo[n];
  memo[sink][k+1] = 1;

  for (const Bus& bs : bus) {
    auto take = memo[bs.b].upper_bound(bs.t);
    auto next = memo[bs.a].upper_bound(bs.s);
    if (take != memo[bs.b].end() && next != memo[bs.a].end()) {
      if (take->second > next->second) {
        memo[bs.a][bs.s] = max(memo[bs.a][bs.s], bs.p * take->second + (1-bs.p) * next->second);
      } else {
        memo[bs.a][bs.s] = max(memo[bs.a][bs.s], next->second);
      }
    }
    else if (take != memo[bs.b].end()) {
      memo[bs.a][bs.s] = max(memo[bs.a][bs.s], bs.p * take->second);
    }
    else if (next != memo[bs.a].end()) {
      memo[bs.a][bs.s] = max(memo[bs.a][bs.s], next->second);
    }
  }

  if (memo[source].empty()) cout << 0 << nl;
  else cout << memo[source].lower_bound(0)->second << nl;

  return 0;
}

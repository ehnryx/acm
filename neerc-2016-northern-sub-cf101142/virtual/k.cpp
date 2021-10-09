#include <bits/stdc++.h>
using namespace std;
#define problem_name "king"

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

struct date {
  int d, m, y, i;
  bool good(const date& o) const {
    if (o.y - y > 18) return 1;
    if (o.y - y < 18) return 0;
    if (o.m - m > 0) return 1;
    if (o.m - m < 0) return 0;
    if (o.d - d > 0) return 1;
    if (o.d - d < 0) return 0;
    return 1;
  }
  bool operator<(const date& o) const {
    return tie(y, m, d) < tie(o.y, o.m, o.d);
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(problem_name ".in", "r", stdin);
  freopen(problem_name ".out", "w", stdout);
#endif

  date dead; cin >> dead.d >> dead.m >> dead.y;
  int n; cin >> n;
  vector<date> ds;
  for (int i = 0; i < n; i++) {
    date d; cin >> d.d >> d.m >> d.y; d.i = i;
    if (d.good(dead)) ds.push_back(d);
  }
  //for (auto& d : ds) cerr << d.i << nl;
  if (ds.empty()) {
    puts("-1");
  } else {
    cout << max_element(ds.begin(), ds.end())->i + 1 << nl;
  }

  return 0;
}

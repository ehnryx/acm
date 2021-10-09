#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const ll INF = 0x3f3f3f3f;

struct Segment {
  int x, yl, yr, id, t;
  bool operator < (const Segment& o) const {
    if (x != o.x) return x < o.x;
    return t < o.t;
  }
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T;
  cin >> T;
  while (T--) {

    int n, m;
    cin >> n >> m;
    for (int i=0; i<n; i++) {
      cin >> xl >> xr >> yl >> yr;
      p.push_back({xl, yl, yr, i, 1});
      p.push_back({xr, yl, yr, i, -1});
    }
    sort(p.begin(), p.end());

    int px, pt;
    px = pt = -7;
    for (const Segment& s : p) {
    }

  }

  return 0;
}

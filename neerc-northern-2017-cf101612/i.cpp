#include <bits/stdc++.h>
using namespace std;

#define FILENAME "intel"

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int INF = 0x3f3f3f3f;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  if(fopen(FILENAME ".in", "r")) {
    freopen(FILENAME ".in", "r", stdin);
    freopen(FILENAME ".out", "w", stdout);
  }

  int n;
  cin >> n;
  vector<pair<int,int>> p;
  int minx, maxx, miny, maxy;
  minx = miny = INF;
  maxx = maxy = -INF;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    p.push_back(make_pair(x,y));
    minx = min(minx, x);
    maxx = max(maxx, x);
    miny = min(miny, y);
    maxy = max(maxy, y);
  }

  ll tot = 0;
  for(int i=0,j=n-1; i<n; j=i++) {
    tot += abs(p[i].first-p[j].first) + abs(p[i].second-p[j].second);
  }

  int perim = (maxx-minx + maxy-miny) * 2;
  cout << tot - perim << nl;

  return 0;
}

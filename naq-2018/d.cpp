#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
//typedef complex<int> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct pt {
  int i, j;
  pt(int i, int j): i(i), j(j) {}
  void operator += (const pt& o) {
    i += o.i; j += o.j;
  }
};

vector<int> nxt;

int n, m;
struct Lane {
  int offset, space, speed, rev;
  vector<int> cur;
  Lane(int oo, int ii, int ss, int rr): offset(oo), space(ii), speed(ss), rev(rr) {
    for (int i=offset; i<m; i+=space) {
      cur.push_back(i);
    }
  }

  bool rip(int x) {
    for (int s = cur[0] - space; s + speed >= 0; s -= space) {
      for (int j=1; j<=speed; j++) {
        int p = s+j;
        if (rev) p = m-1-p;
        if (x == p) return true;
      }
    }
    for (int s : cur) {
      for (int j=1; j<=speed; j++) {
        int p = s+j;
        if (rev) p = m-1-p;
        if (x == p) return true;
      }
    }
    return false;
  }

  void move() {
    nxt.clear();
    int first = cur[0] + speed;
    for (int it : cur) {
      if (it + speed < m) {
        nxt.push_back(it + speed);
      }
    }
    for (int i = first - space; i >= 0; i -= space) {
      nxt.push_back(i);
    }
    sort(nxt.begin(), nxt.end());
    cur = nxt;
  }

  void print() {
    for (int it : cur) {
      if (rev) it = m-1-it;
      cout << it << " ";
    }
    cout << nl;
  }
};

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  cin >> n >> m;

  vector<Lane> lanes;
  int a, b, c;
  for (int i=0; i<n; i++) {
    cin >> a >> b >> c;
    lanes.push_back(Lane(a, b, c, i%2));
  }
  reverse(lanes.begin(), lanes.end());

  int p;
  cin >> p;
  pt pos = pt(p, -1);

  string s;
  cin >> s;
  for (char c : s) {
    //cerr << "start: " << (ld)clock()/CLOCKS_PER_SEC << nl;
    //cerr << "MOVE " << c << nl;
    pt dir = pt(0,1);
    if (c == 'L') dir = pt(-1,0);
    else if (c == 'R') dir = pt(1,0);
    else if (c == 'D') dir = pt(0,-1);

    // move frog
    pos += dir;

    // check done
    if (pos.j >= n) {
      cout << "safe" << nl;
      return 0;
    }

    //cerr << "init: " << (ld)clock()/CLOCKS_PER_SEC << nl;

    // check frog
    if (pos.j >= 0) {
      //cerr << "pos.j: " << pos.j << nl;
      if (lanes[pos.j].rip(pos.i)) {
        cout << "squish" << nl;
        return 0;
      }
    }

    //cerr << "checked: " << (ld)clock()/CLOCKS_PER_SEC << nl;

    // move cars
    for (int i=0; i<n; i++) {
      //cerr << "MOVE " << i << nl;
      //cerr << "before: "; lanes[i].print();
      lanes[i].move();
      //cerr << "&after: "; lanes[i].print();
    }

    //cerr << "moved: " << (ld)clock()/CLOCKS_PER_SEC << nl;
  }

  cout << "squish" << nl;

  return 0;
}

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
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) { os << it << " "; } return os;
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) { os << it << " "; }
  return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) { os << it << " "; }
  return os << '}';
}

void casesolve();

////////////////////////////////////////////////////////////////////////



int main(int argc, char** argv) {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T, A, B;
  cin >> T >> A >> B;
  for (int cc = 1; cc <= T; cc++) {
    //cout << "Case #" << cc << ": ";
    casesolve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

const int L = -1e9;
const int R = 1e9;
const int S = 1e9/2;
const int N = 3;
const int M = 5;
const ll O = INF;

int query(int x, int y) {
  cout << x << " " << y << endl;
  string s;
  cin >> s;
  if(s == "HIT") {
    return 1;
  } else if(s == "MISS") {
    return -1;
  } else if(s == "CENTER") {
    return 0;
  } else {
    exit(0); // sad
  }
}

pair<int,int> search_up(int x, int y) {
  int l = y;
  int r = R;
  while(l < r) {
    int m = (2*O + l+r+1) / 2 - O;
    int res = query(x, m);
    if(res == 0) return make_pair(INF, INF);
    if(res == 1) {
      l = m;
    } else {
      r = m-1;
    }
  }
  return make_pair(x, r);
}

pair<int,int> search_down(int x, int y) {
  int l = L;
  int r = y;
  while(l < r) {
    int m = (2*O + l+r) / 2 - O;
    int res = query(x, m);
    if(res == 0) return make_pair(INF, INF);
    if(res == 1) {
      r = m;
    } else {
      l = m+1;
    }
  }
  return make_pair(x, r);
}

pair<int,int> search_right(int x, int y) {
  int l = x;
  int r = R;
  while(l < r) {
    int m = (2*O + l+r+1) / 2 - O;
    int res = query(m, y);
    if(res == 0) return make_pair(INF, INF);
    if(res == 1) {
      l = m;
    } else {
      r = m-1;
    }
  }
  return make_pair(r, y);
}

pair<int,int> search_left(int x, int y) {
  int l = L;
  int r = x;
  while(l < r) {
    int m = (2*O + l+r) / 2 - O;
    int res = query(m, y);
    if(res == 0) return make_pair(INF, INF);
    if(res == 1) {
      r = m;
    } else {
      l = m+1;
    }
  }
  return make_pair(r, y);
}

void solve(int x, int y) {
  int ax, ay, bx, by, cx, cy, dx, dy;
  tie(ax, ay) = search_up(x, y);
  if(ax == INF) return;
  tie(bx, by) = search_down(x, y);
  if(bx == INF) return;

  int mx = (ax+bx) / 2;
  int my = (ay+by) / 2;
  tie(cx, cy) = search_left(mx, my);
  if(cx == INF) return;
  tie(dx, dy) = search_right(mx, my);
  if(dx == INF) return;

  x = (cx+dx) / 2;
  y = (cy+dy) / 2;
  //cerr<<"guess: "<<x<<" "<<y<<nl;
  for(int i=x-M; i<=x+M; i++) {
    for(int j=y-M; j<=y+M; j++) {
      if(query(i, j) == 0) {
        return;
      }
    }
  }
}

void casesolve() {

  for(int i=1; i<=N; i++) {
    for(int j=1; j<=N; j++) {
      int x = L + i*S;
      int y = L + j*S;
      int res = query(x, y);
      if(res == 0) {
        return;
      } else if(res == 1) {
        solve(x, y);
        return;
      }
    }
  }

  return;
}


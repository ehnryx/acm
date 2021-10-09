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

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}

vector<int> dx = { 1, 1, -1, -1, 2, 2, -2, -2 };
vector<int> dy = { 2, -2, 2, -2, 1, -1, 1, -1 };

const int MAGIC = 9;
const int MAGIC2 = 5;
vector<pair<pii,int>> magic(int n, int m, pii s) {
  vector<pair<pii,int>> out;
  set<pii> vis;
  queue<pair<pii,int>> bfs;
  bfs.push({s,0});
  while (!bfs.empty()) {
    pii cur;
    int x, y, dist;
    tie(cur,dist) = bfs.front();
    tie(x,y) = cur;
    bfs.pop();
    if (x<0||x>=n||y<0||y>=m) continue;
    if (!vis.count(pii(x,y))) {
      vis.insert(pii(x,y));
      out.push_back({pii(x,y), dist});
      if (dist < MAGIC) {
        for (int d=0; d<8; d++) {
          bfs.push({pii(x+dx[d],y+dy[d]), dist+1});
        }
      }
    }
  }
  return out;
}

ll solve(int x, int y) {
  if (x>y) swap(x,y);
  if (x==0) {
    if (y==0) return 0;
    if (y==1) return 3;
    if (y==2) return 2;
    if (y==3) return 3;
    if (y==4) return 2;
    else return INF*2;
  }
  if (x==1) {
    if (y==1) return 2;
    if (y==2) return 1;
    if (y==3) return 2;
    if (y==4) return 3;
    else return INF*2;
  }
  if (x==2) {
    if (y==2) return 4;
    if (y==3) return 3;
    if (y==4) return 2;
    else return INF*2;
  }
  if (x==3) {
    if (y==3) return 2;
    if (y==4) return 3;
    else return INF*2;
  }
  return INF*2;
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

  int nx, ny, kx, ky, cx, cy;
  cin >> nx >> ny >> kx >> ky >> cx >> cy;

  vector<pair<pii,int>> front = magic(nx, ny, pii(kx,ky));
  vector<pair<pii,int>> back = magic(nx, ny, pii(cx,cy));

  ll ans = INF*2;
  for (const pair<pii,int>& it : front) {
    for (const pair<pii,int>& jt : back) {
      pii cur;
      int a, b, x, y, c, d;
      tie(cur,c) = it;
      tie(a,b) = cur;
      tie(cur,d) = jt;
      tie(x,y) = cur;
      if (x<2||x+2>=nx||y<2||y+2>=ny) continue;
      int diffx = abs(a-x);
      int diffy = abs(b-y);
      if (2*diffx < diffy+MAGIC) {
        int m = diffx;
        for (int i=max(0,m-MAGIC2); i<=m+MAGIC2; i++) {
          int n = (diffy-2*m)/4;
          if (m<0||n<0) continue;
          for (int j=max(0,n-MAGIC2); j<=n+MAGIC2; j++) {
            int na, nb;
            {
              if (a<x) na = a + (i+n-j);
              else na = a - (i+n-j);
              if (b<y) nb = b + (2*i+2*j+2*n);
              else nb = b - (2*i+2*j+2*n);
              if (na<2||na+2>=nx||nb<2||nb+2>=ny) continue;
              ll nxt = c + d + i+j+n + solve(abs(na-x), abs(nb-y));
              ans = min(ans, nxt);
            }
            {
              if (a<x) na = a + (i-n+j);
              else na = a - (i-n+j);
              if (b<y) nb = b + (2*i+2*j+2*n);
              else nb = b - (2*i+2*j+2*n);
              if (na<2||na+2>=nx||nb<2||nb+2>=ny) continue;
              ll nxt = c + d + i+j+n + solve(abs(na-x), abs(nb-y));
              ans = min(ans, nxt);
            }
          }
        }
      }
      if (2*diffy < diffx+MAGIC) {
        int m = diffy;
        for (int i=max(0,m-MAGIC2); i<=m+MAGIC2; i++) {
          int n = (diffx-2*m)/4;
          if (m<0||n<0) continue;
          for (int j=max(0,n-MAGIC2); j<=n+MAGIC2; j++) {
            int na, nb;
            {
              if (b<y) nb = b + (i+n-j);
              else nb = b - (i+n-j);
              if (a<x) na = a + (2*i+2*j+2*n);
              else na = a - (2*i+2*j+2*n);
              if (na<2||na+2>=nx||nb<2||nb+2>=ny) continue;
              ll nxt = c + d + i+j+n + solve(abs(na-x), abs(nb-y));
              ans = min(ans, nxt);
            }
            {
              if (b<y) nb = b + (i-n+j);
              else nb = b - (i-n+j);
              if (a<x) na = a + (2*i+2*j+2*n);
              else na = a - (2*i+2*j+2*n);
              if (na<2||na+2>=nx||nb<2||nb+2>=ny) continue;
              ll nxt = c + d + i+j+n + solve(abs(na-x), abs(nb-y));
              ans = min(ans, nxt);
            }
          }
        }
      }
      if (2*diffy > diffx-MAGIC && 2*diffx > diffy-MAGIC) {
        int sum = (diffx+diffy)/3;
        for (int i=max(0,sum-MAGIC2); i<=sum+MAGIC2; i++) {
          int m = diffx-i;
          int n = diffy-i;
          if (m<0||n<0) continue;
          int na, nb;
          if (a<x) na = a + (m*2+n);
          else na = a - (m*2+n);
          if (b<y) nb = b + (m+n*2);
          else nb = b - (m+n*2);
          if (na<2||na+2>=nx||nb<2||nb+2>=ny) continue;
          ll nxt = c + d + m+n + solve(abs(na-x), abs(nb-y));
          ans = min(ans, nxt);
        }
      }
    }
  }
  cout << ans << nl;

  return 0;
}

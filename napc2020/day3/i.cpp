#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef double ld;
const ld EPS = 1e-9;

const int N = 500 + 7;
ld c[N][N];

struct pt {
  ld x, y;
  pt(ld _x=0, ld _y=0): x(_x), y(_y) {}
  pt operator + (const pt& o) const { return pt(x+o.x, y+o.y); }
  pt operator - (const pt& o) const { return pt(x-o.x, y-o.y); }
  pt operator * (const pt& o) const { return pt(x*o.x-y*o.y, x*o.y+y*o.x); }
};
pt conj(const pt& v) {
  return pt(v.x, -v.y);
}
ld abs(const pt& v) {
  return sqrt(v.x*v.x + v.y*v.y);
}

ld cp(const pt& a, const pt& b) {
  return (conj(a) * b).y;
}
ld dp(const pt& a, const pt& b) {
  return (conj(a) * b).x;
}
ld lsp_dist(const pt& a, const pt& b, const pt& p) {
  return dp(b-a, p-a) > 0 && dp(a-b, p-b) > 0 ?
    abs(cp(b-a, p-a) / abs(b-a)) : min(abs(a-p), abs(b-p));
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n;
  cin >> n;
  for(int i=0; i<n; i++) {
    int x, y; ld r;
    cin >> x >> y >> r;
    c[x][y] = r;
  }
  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    if(a == x || b == y) {
      int ans = 0;
      for(int j=min(a,x); j<=max(a,x); j++) {
        for(int k=min(b,y); k<=max(b,y); k++) {
          ans += (c[j][k] > EPS);
        }
      }
      cout << ans << nl;
      continue;
    }
    ld s = (ld) (b-y) / (a-x);
    ld t = y - s*x;
    bool trans = (abs(s)>1);
    if(trans) {
      swap(a,b);
      swap(x,y);
      s = 1/s;
      t = y - s*x;
    }
    pt A(a,b), B(x,y);
    int ans = 0;
    for(int j=min(a,x); j<=max(a,x); j++) {
      int v = round(s*j + t);
      for(int k=max(0,v-1); k<=v+1; k++) {
        if(trans) {
          if(c[k][j] > EPS && lsp_dist(A, B, pt(k,j)) <= c[k][j]) {
            ans++;
          }
        } else {
          if(c[j][k] > EPS && lsp_dist(A, B, pt(j,k)) <= c[j][k]) {
            ans++;
          }
        }
      }
    }
    cout << ans << nl;
  }

  return 0;
}

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
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e3+1;
int g[N][N];

int query(int x, int y, bool f) {
  if(f) swap(x,y);
  if(!g[x][y]) {
    cout << "? " << x << " " << y << endl;
    cin >> g[x][y];
  }
  return g[x][y];
}

void solve(int a, int b, int l, int r, bool f=false, int defval=0, int dx=0, int dy=0) {
  int m = (l+r)/2;
  vector<tuple<int,int,int>> v;
  for(int i=a; i<=b; i++) {
    v.push_back(make_tuple(query(i,m,f), i, m));
  }
  int val, x, y;
  tie(val, x, y) = *max_element(v.begin(), v.end());

  if(val < defval) {
    if(dy<m) solve(l, m-1, a, b, f^1, defval, dy, dx);
    if(dy>m) solve(m+1, r, a, b, f^1, defval, dy, dx);
    assert(false);
  }

  v.clear();
  for(int i=x-1; i<=x+1; i++) {
    for(int j=y-1; j<=y+1; j++) {
      if(a<=i && i<=b && l<=j && j<=r) {
        v.push_back(make_tuple(query(i,j,f), i, j));
      }
    }
  }
  int best, nx, ny;
  tie(best, nx, ny) = *max_element(v.begin(), v.end());

  if(nx == x && ny == y) {
    if(f) swap(x,y);
    cout << "! " << x << " " << y << endl;
    exit(0);
  }

  if(ny<m) solve(l, m-1, a, b, f^1, best, ny, nx);
  if(ny>m) solve(m+1, r, a, b, f^1, best, ny, nx);
  assert(false);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  solve(1, n, 1, n);
  assert(false);

  return 0;
}

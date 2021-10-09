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

const int N = 50;
char g[N][N];
bool valid[N][N];

int n, m, id;
int bs[N];
int mask = (1<<8) - 1;

bool attack(int i, int j) {
  int xi = bs[i] >> 8;
  int yi = bs[i] & mask;
  int xj = bs[j] >> 8;
  int yj = bs[j] & mask;
  return (xi == xj || yi == yj || abs(xi-xj) == abs(yi-yj));
}

bool bad(int i, int j, int k) {
  return (attack(i,j) && attack(j,k) && attack(k,i));
}

pair<int,int> solve(int r, int best) {
  if(r == n) return make_pair(0, 1);
  if(2*(n-r) < best-id) return make_pair(0, 1);

  for(int i=0; i<m; i++) {
    if(g[r][i] == '#') {
      valid[r][i] = false;
    } else {
      valid[r][i] = true;
      bs[id] = r<<8 | i;
      for(int j=0; j<id && valid[r][i]; j++) {
        for(int k=0; k<j; k++) {
          if(bad(id,j,k)) {
            valid[r][i] = false;
            break;
          }
        }
      }
    }
  }

  auto [res, cnt] = solve(r+1, best);
  for(int i=0; i<m; i++) {
    if(!valid[r][i]) {
      continue;
    } else {
      bs[id] = r<<8 | i;
      id++;
      pair<int,int> cur = solve(r+1, max(best, res));
      id--;
      if(cur.first + 1 > res) {
        res = cur.first + 1;
        cnt = cur.second;
      } else if(cur.first + 1 == res) {
        cnt += cur.second;
      }
    }
    for(int j=0; j<i; j++) {
      if(!valid[r][j]) continue;
      bool ok = true;
      bs[id+1] = r<<8 | j;
      for(int k=0; k<id; k++) {
        if(bad(id,id+1,k)) {
          ok = false;
          break;
        }
      }
      if(ok) {
        id+=2;
        pair<int,int> cur = solve(r+1, max(best, res));
        id-=2;
        if(cur.first + 2 > res) {
          res = cur.first + 2;
          cnt = cur.second;
        } else if(cur.first + 2 == res) {
          cnt += cur.second;
        }
      }
    }
  }
  return make_pair(res, cnt);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  cin >> n >> m;
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> g[i][j];
    }
  }
  if(n > m) {
    for(int i=0; i<n; i++) {
      for(int j=0; j<m; j++) {
        swap(g[i][j], g[j][i]);
      }
    }
    swap(n, m);
  }
  auto [res, cnt] = solve(0, 0);
  cout << res << " " << cnt << nl;

  return 0;
}

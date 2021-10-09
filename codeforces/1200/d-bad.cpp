#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 1<<11;
ordered_set<pii> rmq[2*N];
int uid = 0;
void clear() {
  uid = 0;
  For(i,2*N) {
    rmq[i].clear();
  }
}
void insert(int i, int x) {
  rmq[i+=N].insert(pii(x,uid));
  for (i/=2; i>0; i/=2) {
    rmq[i].insert(pii(x,uid));
  }
  uid++;
}
bool erase(int i, int x) {
  auto it = rmq[i+=N].lower_bound(pii(x,0));
  if (it->first != x) return false;
  rmq[i].erase(it);
  for (i/=2; i>0; i/=2) {
    rmq[i].erase(rmq[i].lower_bound(pii(x,0)));
  }
  return true;
}
int query(int l, int r, int k) {
  int res = 0;
  for (l+=N,r+=N+1; l<r; l/=2,r/=2) {
    if (l&1) res += rmq[l++].order_of_key(pii(k,INF));
    if (r&1) res += rmq[--r].order_of_key(pii(k,INF));
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, k;
  cin >> n >> k;
  string grid[n], trans[n];
  For(i,n) {
    cin >> grid[i];
    For(j,n) {
      trans[j].push_back(grid[i][j]);
    }
  }

  int last[n];
  int ans[n][n];
  memset(ans, 0, sizeof ans);

  For(i,n) {
    insert(i, last[i] = grid[i].find_last_of('B'));
  }
  For(j,n-k+1) {
    For(i,n-k+1) {
      ans[i][j] += query(i, i+k-1, j+k-1) + query(0, i-1, -1) + query(i+k, n-1, -1);
    }
    For(i,n) {
      if (grid[i][j] == 'B') {
        if (erase(i, last[i])) {
          insert(i, INF);
        }
      }
    }
  }

  clear();
  For(i,n) {
    insert(i, last[i] = trans[i].find_last_of('B'));
  }
  For(j,n-k+1) {
    For(i,n-k+1) {
      ans[j][i] += query(i, i+k-1, j+k-1) + query(0, i-1, -1) + query(i+k, n-1, -1);
    }
    For(i,n) {
      if (trans[i][j] == 'B') {
        if (erase(i, last[i])) {
          insert(i, INF);
        }
      }
    }
  }

  cout << *max_element(&ans[0][0], &ans[0][0]+n*n) << nl;

  return 0;
}

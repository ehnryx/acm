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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int L = 19;
const int N = 1<<L;

struct RMQ {
  int rmq[N][L];
  RMQ() {
    memset(rmq, INF, sizeof rmq);
  }
  void set(int i, int v) {
    rmq[i][0] = v;
  }
  void build() {
    for(int j=1; j<L; j++) {
      for(int i=0; i+(1<<j)<=N; i++) {
        rmq[i][j] = min(rmq[i][j-1], rmq[i+(1<<(j-1))][j-1]);
      }
    }
  }
  int query(int l, int r) {
    l = max(l, 0);
    r = min(r, N-1);
    int j = 31 - __builtin_clz(r-l+1);
    return min(rmq[l][j], rmq[r-(1<<j)+1][j]);
  }
};

RMQ maxv[2], minv[2];
int a[N], ans[N], cnt[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  for(int i=1; i<=n; i++) {
    cin >> a[i];
    maxv[i%2].set(i, -a[i]);
    minv[i%2].set(i, a[i]);
    ans[i] = a[i];
  }
  maxv[0].build();
  maxv[1].build();
  minv[0].build();
  minv[1].build();

  function<bool(int,int)> valid = [&] (int i, int k) {
    if(i-k < 1 || i+k > n) return false;
    if(a[i] <= a[i-1] && a[i] <= a[i+1]) {
      if(k%2 == 0) {
        return a[i-k] < a[i-k+1] && a[i+k] < a[i+k-1];
      } else {
        return a[i-k] > a[i-k+1] && a[i+k] > a[i+k-1];
      }
    } else {
      if(k%2 == 0) {
        return a[i-k] > a[i-k+1] && a[i+k] > a[i+k-1];
      } else {
        return a[i-k] < a[i-k+1] && a[i+k] < a[i+k-1];
      }
    }
  };

  function<int(int,int)> get = [&] (int i, int k) {
    if(i == 1 || i == n) return a[i];
    int t = (i%2) ^ (k%2);
    if(a[i] <= a[i-1] && a[i] <= a[i+1]) {
      if(k%2 == 0) {
        return -maxv[t].query(i-k, i+k);
      } else {
        return minv[t].query(i-k, i+k);
      }
    } else {
      if(k%2 == 0) {
        return minv[t].query(i-k, i+k);
      } else {
        return -maxv[t].query(i-k, i+k);
      }
    }
  };

  for(int i=2; i<n; i++) {
    if(a[i-1] <= a[i] && a[i] <= a[i+1]) continue;
    if(a[i-1] >= a[i] && a[i] >= a[i+1]) continue;
    for(int k=cnt[i-1]-1; k<=cnt[i-1]+1; k++) {
      if(k<=0) continue;
      if(!valid(i, k)) break;
      int left = get(i-1, k-1);
      int right = get(i+1, k-1);
      int mid = get(i, k-1);
      if(left <= mid && mid <= right) break;
      if(left >= mid && mid >= right) break;
      if(mid <= left && mid <= right) {
        ans[i] = min(left, right);
      } else {
        ans[i] = max(left, right);
      }
      cnt[i] = k;
    }
  }
  assert(cnt[n-1] <= 1);

  cout << *max_element(cnt+1, cnt+1+n) << nl;
  for(int i=1; i<=n; i++) {
    cout << ans[i] << " ";
  }
  cout << nl;

  return 0;
}

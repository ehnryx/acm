//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

void answer(const vector<ll>& v) {
  for(int i=1; i<v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << nl;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  vector<int> a(2*n-2);
  for(int i=0; i<2*n-2; i++) {
    cin >> a[i];
  }
  sort(a.begin(), a.end());

  vector<ll> ans(n, -1);
  for(int i=0; i<2*n-2; i++) {
    if(a[i] > i+1) {
      answer(ans);
      return 0;
    }
  }

  int cnt = 0;
  int last = 0;
  for(int i=0; i<2*n-2; i++) {
    if(a[i] == i+1) {
      cnt++;
      last = i;
    }
  }

  ll sum = 0;
  int right = 2*n-2 - 1;
  for(int i=0; i<cnt; i++) {
    sum += a[right--];
  }
  ans[cnt] = sum;

  int cur = a[last];
  for(int i=last+1; i<2*n-2; i++) {
    if(a[i] == cur) continue;
    cur = a[i];
    a[i] = 0;
    if(right < i) {
      sum -= cur;
      while(a[right] == 0) right--;
      sum += a[right--];
    }
    while(a[right] == 0) right--;
    sum += a[right--];
    ans[++cnt] = sum;
  }
  assert(cnt < n);

  answer(ans);

  return 0;
}

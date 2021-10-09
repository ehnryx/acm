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

int query(int x) {
  cout << 1 << " " << x << endl;
  int res;
  cin >> res;
  return res;
}

vector<int> query_set(const vector<int>& v) {
  int n = v.size();
  if(n < 2) return {};
  cout << 2 << " " << n << " ";
  for(int it : v) {
    cout << it << " ";
  }
  cout << endl;
  vector<int> res(n*(n-1)/2);
  for(int i=0; i<n*(n-1)/2; i++) {
    cin >> res[i];
  }
  return res;
}

void answer(const vector<int>& v) {
  cout << 3 << " ";
  for(int it : v) {
    cout << it << " ";
  }
  cout << endl;
}

int find_end(int n) {
  vector<int> all(n);
  iota(all.begin(), all.end(), 1);
  vector<int> res = query_set(all);
  int big = *max_element(res.begin(), res.end());
  int l = 2;
  int r = n;
  while(l < r) {
    int m = (l+r) / 2;
    vector<int> cur(m);
    iota(cur.begin(), cur.end(), 1);
    res = query_set(cur);
    if(*max_element(res.begin(), res.end()) < big) {
      l = m+1;
    } else {
      r = m;
    }
  }
  return r;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  if(n == 1) {
    answer({query(1)});
    return 0;
  }

  int x = find_end(n);
  unordered_map<int,int> idx;
  for(int b=0; b<8; b++) {
    vector<int> cur;
    for(int i=1; i<=n; i++) {
      if(i == x || !(i & 1<<b)) continue;
      cur.push_back(i);
    }
    vector<int> res = query_set(cur);
    unordered_multiset<int> base(res.begin(), res.end());
    cur.push_back(x);
    res = query_set(cur);
    for(int it : res) {
      if(base.count(it)) {
        base.erase(base.find(it));
      } else {
        idx[it] |= 1<<b;
      }
    }
  }

  vector<int> ans(n);
  int xval = query(x);
  bool sub = (query(x == n ? 1 : x+1) < xval);
  for(auto [v, i] : idx) {
    ans[i-1] = (sub ? xval - v : xval + v);
  }
  ans[x-1] = xval;
  answer(ans);

  return 0;
}

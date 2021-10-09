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

struct Node {
  int res[2][2]; int t;
  Node(int v=0): t(v) {
    for(int i=0; i<2; i++) {
      res[i][i^1] = INF;
      res[i][i] = (i != t);
    }
  }
  Node operator + (const Node& o) const {
    if(t < 0) return o;
    if(o.t < 0) return *this;
    Node out(true);
    for(int i=0; i<2; i++) {
      for(int j=0; j<2; j++) {
        int cur = INF;
        for(int ii=0; ii<2; ii++) {
          for(int jj=0; jj<2; jj++) {
            cur = min(cur, res[i][ii] + (ii != jj) + o.res[jj][j]);
          }
        }
        out.res[i][j] = cur;
      }
    }
    return out;
  }
};

const int N = 1<<19;
Node st[2*N];

void insert(int i) {
  st[i+=N] = Node(1);
  for(i/=2; i>0; i/=2) {
    st[i] = st[2*i] + st[2*i+1];
  }
}

Node query(int l, int r, int i=1, int s=0, int e=N-1) {
  if(r<s || e<l) return Node(-1);
  if(l<=s && e<=r) {
    return st[i];
  }
  int m = (s+e) / 2;
  return query(l, r, 2*i, s, m) + query(l, r, 2*i+1, m+1, e);
}

int a[N];
vector<int> idx[N];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  for(int i=0; i<n; i++) {
    cin >> a[i];
    idx[a[i]].push_back(i);
  }
  for(int i=N-1; i>0 ;i--) {
    st[i] = st[2*i] + st[2*i+1];
  }

  for(int v=1; v<=m; v++) {
    //cerr<<"SOLVE "<<v<<endl;
    if(idx[v].empty()) {
      cout << -1 << " ";
      //cerr<<nl<<endl;
      continue;
    }
    int cur = 0;
    int k = idx[v].size();
    for(int i=0; i<k; i++) {
      int l = idx[v][i];
      int r = idx[v][(i+1)%k];
      //cerr<<"@ "<<l<<" "<<r<<endl;
      if((l+1)%n == r) continue;
      if(r <= l) r += n;
      assert(l <= r);
      Node res = query(l+1, r-1);
      int value = INF;
      for(int ii=0; ii<2; ii++) {
        for(int jj=0; jj<2; jj++) {
          value = min(value, res.res[ii][jj]);
        }
      }
      //cerr<<"QUERY "<<l+1<<" "<<r-1<<" -> "<<value<<nl;
      cur += r-l-1 + value;
    }
    for(int i : idx[v]) {
      insert(i);
      insert(i+n);
    }
    cout << cur << " ";
    //cerr<<nl<<endl;
  }

  cout << nl;

  return 0;
}

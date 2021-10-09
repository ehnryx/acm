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

int query(const vector<int>& a, const vector<int>& b) {
  cout << "? " << a.size() << " " << b.size() << nl;
  for(int it : a) {
    cout << it << " ";
  }
  cout << nl;
  for(int it : b) {
    cout << it << " ";
  }
  cout << endl;

  string res;
  cin >> res;
  if(res == "FIRST") return 1;
  else if(res == "SECOND") return -1;
  else if(res == "EQUAL") return 0;
  else assert(false);
}

void answer(int v) {
  cout << "! " << v << endl;
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while(T--) {
    int n, k;
    cin >> n >> k;

    int cnt = 0;
    int flag = 0;
    for(int i=1; !flag && 2*i<=n; i*=2) {
      cnt++;
      vector<int> a(i), b(i);
      iota(a.begin(), a.end(), 1);
      iota(b.begin(), b.end(), i+1);
      int res = query(a, b);
      if(res == -1) {
        flag = -1;
      } else if(res == 1) {
        flag = i;
      }
    }
    if(flag == -1) {
      answer(1);
      continue;
    }

    // now search (flag, 2*flag]
    int s = flag + 1;
    for(int len=flag; len>1; len/=2) {
      cnt++;
      vector<int> a(len/2), b(len/2);
      iota(a.begin(), a.end(), 1);
      iota(b.begin(), b.end(), s);
      int res = query(a, b);
      if(res == -1) {
        flag = -1;
        break;
      } else if(res == 0) {
        s += len/2;
      }
    }
    if(flag == -1) {
      answer(1);
      continue;
    }

    vector<int> v(n-2*flag);
    iota(v.begin(), v.end(), 2*flag+1);
    shuffle(v.begin(), v.end(), rng);
    for(int i=0; i<min(50-cnt,(int)v.size()); i++) {
      int res = query({1}, {v[i]});
      if(res == -1) {
        flag = -1;
        break;
      }
    }
    if(flag == -1) {
      answer(1);
      continue;
    }

    answer(s);
  }

  return 0;
}

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
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) { os << it << " "; } return os;
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) { os << it << " "; }
  return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) { os << it << " "; }
  return os << '}';
}

void casesolve();

////////////////////////////////////////////////////////////////////////



int main(int argc, char** argv) {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cout << "Case #" << cc << ": ";
    casesolve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

vector<int> read(int n, int k, int m) {
  vector<int> r(n);
  for(int i=0; i<k; i++) {
    cin >> r[i];
  }
  ll a, b, c;
  cin >> a >> b >> c;
  for(int i=k; i<n; i++) {
    r[i] = (a*r[i-2] + b*r[i-1] + c) % m;
  }
  return r;
}

void casesolve() {

  int n, m, q, k;
  cin >> n >> m >> q >> k;

  vector<int> x = read(n, k, m);
  vector<int> y = read(n, k, m);
  vector<int> e = read(q, k, n*m + n);
  vector<int> w = read(q, k, 1e9);

  vector<set<pair<int,int>>> left(n), right(n);
  set<pair<int,int>> cons;
  vector<int> val(n*m + n);

  ll sum = n*m + n;
  ll rem = n + 1;
  for(int i=0; i<n; i++) {
    if(x[i] > y[i]) swap(x[i], y[i]);
    for(int j=0; j<m; j++) {
      int u = i*m + j;
      val[u] = 1;
      if(x[i] <= u%m && u%m < y[i]) {
        left[i].insert(make_pair(1, u));
      } else {
        right[i].insert(make_pair(1, u));
      }
    }
    assert(!right[i].empty());
    if(left[i].empty()) {
      left[i].insert(make_pair(-1, -i-1));
    }

    val[n*m + i] = 1;
    cons.insert(make_pair(1, n*m + i));
    cons.insert(min(*left[i].rbegin(), *right[i].rbegin()));
  }

  ll ans = 1;
  for(int i=0; i<q; i++) {
    if(e[i] < n*m) {
      int u = e[i], v = w[i], c = u/m;
      pair<int,int> old(val[u], u);
      sum += v - val[u];
      val[u] = v;

      pair<int,int> ml = *left[c].rbegin();
      pair<int,int> mr = *right[c].rbegin();
      rem -= max(ml.first, mr.first) + cons.rbegin()->first;
      assert(cons.count(min(ml, mr)));
      cons.erase(min(ml, mr));
      assert(x[c] == y[c] || min(ml, mr).first >= 0);

      if(x[c] <= u%m && u%m < y[c]) {
        assert(left[c].count(old));
        left[c].erase(old);
        left[c].insert(make_pair(v, u));
      } else {
        assert(right[c].count(old));
        right[c].erase(old);
        right[c].insert(make_pair(v, u));
      }

      ml = *left[c].rbegin();
      mr = *right[c].rbegin();
      cons.insert(min(ml, mr));
      rem += max(ml.first, mr.first) + cons.rbegin()->first;
    }

    else {
      sum += w[i] - val[e[i]];
      rem -= cons.rbegin()->first;
      assert(cons.count(make_pair(val[e[i]], e[i])));
      cons.erase(make_pair(val[e[i]], e[i]));
      val[e[i]] = w[i];
      cons.insert(make_pair(val[e[i]], e[i]));
      rem += cons.rbegin()->first;
    }

    ll cur = sum - rem;
    assert(cur >= 0);
    ans = ans * (cur % MOD) % MOD;
  }

  cout << ans << nl;

  return;
}


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

template <class T, bool lin=true, bool rin=false>
struct IntervalSet {
  T inf; set<pair<T,T>> s;
  IntervalSet(T F): inf(F) {}
  bool cmp(const T& a, const T& b, bool l, bool r=false) {
    if (l||r) return a < b || a == b; else return a < b;
  }
  pair<int,int> insert(T a, T b) {
    auto it = s.upper_bound({a,inf});
    int rem = 0;
    int cnt = 0;
    while (it != s.end() && cmp(it->first, b, lin, rin)) {
      cnt++;
      rem += it->second - it->first;
      b = max(b, it->second); it = s.erase(it);
    }
    if (it != s.begin() && cmp(a, (--it)->second, lin, rin)) {
      cnt++;
      rem += it->second - it->first;
      a = min(a, it->first); b = max(b, it->second); s.erase(it);
    }
    s.insert({a,b});
    assert(rem <= b-a);
    return make_pair(b-a - rem, cnt);
  }
  pair<T,T> find(T x) {
    if (s.empty()) { return {inf,inf}; }
    auto it = s.upper_bound({x,inf});
    if (it == s.begin()) return {inf,inf};
    if (cmp((--it)->second,x,!rin)) return {inf,inf};
    if (cmp(x,it->first,!lin)) return {inf,inf};
    return *it;
  }
};

vector<int> read(int n, int k) {
  vector<int> v(n+1);
  for(int i=1; i<=k; i++) {
    cin >> v[i];
  }
  ll a, b, c, d;
  cin >> a >> b >> c >> d;
  for(int i=k+1; i<=n; i++) {
    v[i] = (a*v[i-2] + b*v[i-1] + c) % d + 1;
  }
  return v;
}

void casesolve() {

  int n, k;
  cin >> n >> k;
  vector<int> l = read(n, k);
  vector<int> w = read(n, k);
  vector<int> h = read(n, k);

  IntervalSet<int,true,true> iset(2*INF);
  ll ans = 1;
  ll perim = 0;
  for(int i=1; i<=n; i++) {
    auto [add, cnt] = iset.insert(l[i], l[i] + w[i]);
    perim += 2 * (add + h[i]);
    perim -= 2 * cnt * h[i];
    assert(perim > 0);
    ans = ans * (perim % MOD) % MOD;
  }
  cout << ans << nl;

  return;
}


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

struct IntervalSet {
  map<pair<int,int>,int> s;
  int inf;
  IntervalSet(int F): inf(F) {}

  pair<ll,ll> insert(int a, int b, int c) {
    int l = a, r = b;
    int left = -1, right = -1;
    int rem = 0;
    ll sub = 0;

    auto it = s.lower_bound(make_pair(a, inf));
    pair<int,int> first(-1, -1);
    pair<int,int> last(-1, -1);

    while(it != s.end() && it->first.first <= b) {
      sub += 2 * it->second;
      if(it->first.first == last.first) {
        sub -= 2 * min(it->second, last.second);
      }
      last = make_pair(it->first.second, it->second);
      if(first.first == -1) {
        first = make_pair(it->first.first, it->second);
      }

      right = it->second;
      rem += it->first.second - it->first.first;
      r = max(r, it->first.second);
      it = s.erase(it);
    }

    if(it != s.begin() && (--it)->first.second >= a) {
      sub += 2 * it->second;
      if(it->first.second == first.first) {
        sub -= 2 * min(it->second, first.second);
      }
      left = it->second;
      if(right == -1) {
        right = it->second;
      }

      rem += it->first.second - it->first.first;
      l = min(l, it->first.first);
      r = max(r, it->first.second);
      s.erase(it);
    }

    s[make_pair(a, b)] = c;
    if(l < a) {
      assert(left != -1);
      s[make_pair(l, a)] = left;
    }
    if(b < r) {
      assert(right != -1);
      s[make_pair(b, r)] = right;
    }

    assert(rem <= r - l);
    return make_pair(r - l - rem, sub);
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

  IntervalSet iset(2*INF);
  ll ans = 1;
  ll perim = 0;
  for(int i=1; i<=n; i++) {
    auto [add, sub] = iset.insert(l[i], l[i] + w[i], h[i]);
    perim += 2 * (add + h[i]) - sub;
    assert(perim > 0);
    assert(perim % 2 == 0);
    ans = ans * (perim % MOD) % MOD;
  }
  cout << ans << nl;

	return;
}


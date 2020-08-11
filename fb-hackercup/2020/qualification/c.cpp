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



void casesolve() {

	int n;
  cin >> n;
  map<int,pair<int,int>> dp;
  map<int,int> logs;
  map<int,vector<int>> jump;
  for(int i=0; i<n; i++) {
    int x, h;
    cin >> x >> h;
    dp[x];
    dp[x+h];
    logs[x] = h;
    jump[x+h].push_back(h);
  }

  int ans = 0;
  for(auto& [x, res] : dp) {
    // res = pair(used, unused)
    res = make_pair(0, 0);
    if(logs.count(x)) {
      int h = logs[x];
      int val = h + (dp.count(x-h) ? max(dp[x-h].first, dp[x-h].second) : 0);
      res.first = max(res.first, val);
    }
    if(jump.count(x)) {
      for(int h : jump[x]) {
        int val = h + (dp.count(x-h) ? dp[x-h].second : 0);
        res.second = max(res.second, val);
      }
    }
    ans = max(ans, max(res.first, res.second));
  }

  cout << ans << nl;

	return;
}


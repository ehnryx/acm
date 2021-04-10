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

	int n, m;
  cin >> n >> m;
  vector a(n, vector<int>(m));
  priority_queue<tuple<int,int,int>> nxt;
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> a[i][j];
      nxt.emplace(a[i][j], i, j);
    }
  }

  ll ans = 0;
  vector vis(n, vector<bool>(m));
  while(!nxt.empty()) {
    auto [h, i, j] = nxt.top();
    nxt.pop();
    if(vis[i][j]) continue;
    vis[i][j] = true;
    ans += abs(a[i][j] - h);
    static const vector<pair<int,int>> dirs = {
      {0, 1}, {0, -1}, {1, 0}, {-1, 0},
    };
    for(auto [di, dj] : dirs) {
      if(i+di < 0 || j+dj < 0 || i+di >= n || j+dj >= m) continue;
      if(vis[i + di][j + dj]) continue;
      nxt.emplace(h-1, i+di, j+dj);
    }
  }
  cout << ans << nl;

	return;
}


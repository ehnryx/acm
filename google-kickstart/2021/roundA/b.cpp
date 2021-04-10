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
  vector len(n, vector(m, vector<int>(4)));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> a[i][j];
      if(a[i][j]) {
        fill(len[i][j].begin(), len[i][j].end(), 1);
      }
    }
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      if(!a[i][j]) continue;
      if(i > 0) {
        len[i][j][0] = len[i-1][j][0] + 1;
      }
      if(j > 0) {
        len[i][j][1] = len[i][j-1][1] + 1;
      }
    }
  }

  for(int i=n-1; i>=0; i--) {
    for(int j=m-1; j>=0; j--) {
      if(!a[i][j]) continue;
      if(i+1 < n) {
        len[i][j][2] = len[i+1][j][2] + 1;
      }
      if(j+1 < m) {
        len[i][j][3] = len[i][j+1][3] + 1;
      }
    }
  }

  function<int(int,int)> get = [](int x, int y) -> int {
    return max(0, min(x, y/2) - 1);
  };

  ll ans = 0;
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      for(int k=0; k<4; k++) {
        int nk = (k+1) % 4;
        int pk = (k+3) % 4;
        ans += get(len[i][j][k], len[i][j][nk]);
        ans += get(len[i][j][k], len[i][j][pk]);
      }
    }
  }
  cout << ans << nl;

	return;
}


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

const int N = 1e5 + 1;
int d[N], a[N], b[N];

pair<int,int> solve(int l, int r) {
	if(l > r) return make_pair(0, 0);
	int m = (l+r) / 2;

	pair<int,int> lres = solve(l, m-1);
	pair<int,int> rres = solve(m+1, r);
	int best = max(lres.first, rres.first);
	int cnt = 0;
	if(lres.first == best) cnt += lres.second;
	if(rres.first == best) cnt += rres.second;

	vector<pair<int,int>> cands;
	cands.push_back(make_pair(d[m] - b[m], d[m] + a[m]));
	for(int i=m-1; i>=l; i--) {
		if(d[i] - b[i] != d[m] - b[m]) {
			cands.push_back(make_pair(d[m] - b[m], d[i] + a[i]));
			break;
		}
	}
	for(int i=m-1; i>=l; i--) {
		if(d[i] + a[i] != d[m] + a[m]) {
			cands.push_back(make_pair(d[i] - b[i], d[m] + a[m]));
			break;
		}
	}
	for(int i=m+1; i<=r; i++) {
		if(d[i] - b[i] != d[m] - b[m]) {
			cands.push_back(make_pair(d[m] - b[m], d[i] + a[i]));
			break;
		}
	}
	for(int i=m+1; i<=r; i++) {
		if(d[i] + a[i] != d[m] + a[m]) {
			cands.push_back(make_pair(d[i] - b[i], d[m] + a[m]));
			break;
		}
	}

	cands.resize(distance(cands.begin(), unique(cands.begin(), cands.end())));
	set<pair<int,int>> have;
	for(const auto& it : cands) {
		int left, right;
		tie(left, right) = it;
		int lb = m;
		int rb = m;
		for(int i=m-1; i>=l; i--) {
			if(d[i] - b[i] == left || d[i] + a[i] == right) {
				lb = i;
			} else {
				break;
			}
		}
		for(int i=m+1; i<=r; i++) {
			if(d[i] - b[i] == left || d[i] + a[i] == right) {
				rb = i;
			} else {
				break;
			}
		}
		if(have.count(make_pair(lb, rb))) continue;
		have.insert(make_pair(lb, rb));
		int cur = rb - lb + 1;
		if(cur > best) {
			best = cur;
			cnt = 0;
		}
		cnt += (cur == best);
	}

	return make_pair(best, cnt);
}

void casesolve() {

	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> d[i] >> a[i] >> b[i];
	}
	int ans, cnt;
	tie(ans, cnt) = solve(0, n-1);
	cout << ans << " " << cnt << nl;

	return;
}


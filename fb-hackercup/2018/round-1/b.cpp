#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef mt19937 RNG;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	return os << '(' << v.first << ',' << v.second << ')';
}
template <class T> 
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}
template <class T> 
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) os << it << " "; 
	return os << '}';
}
template <class T, class U> 
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ "; for (const pair<T,U>& it : v) os << it << " ";
	return os << '}';
}

////////////////////////////////////////////////////////////////////////

void solve();
void init() {
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	init();

	int T;
	cin >> T;
	for (int cc = 1; cc <= T; cc++) {
		cout << "Case #" << cc << ": ";
		solve();
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////

const int N = 2e3+2;

pii adj[N];
bool ischild[N];
vector<int> pre, post;
int ans[N];

int root[N];
int find(int i) {
	if (root[i] == -1) return i;
	return root[i] = find(root[i]);
}
void link(int i, int j) {
	if (find(i) != find(j)) root[find(i)] = find(j);
}

void traverse(int cur) {
	if (cur == 0) return;
	pre.push_back(cur);
	traverse(adj[cur].first);
	traverse(adj[cur].second);
	post.push_back(cur);
}

void caseinit() {
	memset(root, -1, sizeof root);
	memset(ischild, 0, sizeof ischild);
	pre.clear();
	post.clear();
}

void solve() {
	caseinit();

	int n, k;
	cin >> n >> k;

	for (int i = 1; i <= n; i++) {
		cin >> adj[i].first >> adj[i].second;
		ischild[adj[i].first] = ischild[adj[i].second] = true;
	}

	for (int i = 1; i <= n; i++) {
		if (!ischild[i]) traverse(i);
	}
	assert(pre.size() == n && post.size() == n);

	for (int i = 0; i < n; i++) {
		link(pre[i], post[i]);
	}

	int groups = 0;
	for (int i = 1; i <= n; i++) {
		if (find(i) == i) {
			groups = min(k, groups+1);
			ans[i] = groups;
		}
	}

	if (groups < k) {
		cout << "Impossible" << nl;
	}
	else {
		for (int i = 1; i <= n; i++) {
			assert(0 < ans[find(i)] && ans[find(i)] <= k);
			cout << ans[find(i)] << " ";
		}
		cout << nl;
	}

	return;
}


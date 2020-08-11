#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Move {
	pii s, t;
	Move(){}
	Move(pii s, pii t): s(s), t(t) {}
	friend ostream& operator << (ostream& os, const Move& v) {
		return os << v.s.first << " " << v.s.second << " " << v.t.first << " " << v.t.second;
	}
};

int n, m;
vector<Move> ans, memo;

int get(int i, int j) {
	return i*(n+1) + j;
}

pii ret(int x) {
	return pii(x/(n+1), x%(n+1));
}

const int N = 52;

int vis[N*N];
bool bfs(pii t, pii s, const bitset<N*N>& sources) {
	memset(vis, -1, sizeof vis);
	int S = get(s.first, s.second);
	int T = get(t.first, t.second);

	queue<pii> q;
	q.push(pii(S,0));
	while (!q.empty()) {
		pii cur = q.front();
		q.pop();

		if (vis[cur.first] == -1) {
			vis[cur.first] = cur.second;
			if (cur.first == T) break;

			int x, y;
			tie(x,y) = ret(cur.first);
			if (x > 1 && !sources[get(x-1,y)]) q.push(pii(get(x-1,y), cur.first));
			if (y > 1 && !sources[get(x,y-1)]) q.push(pii(get(x,y-1), cur.first));
			if (x < n && !sources[get(x+1,y)]) q.push(pii(get(x+1,y), cur.first));
			if (y < n && !sources[get(x,y+1)]) q.push(pii(get(x,y+1), cur.first));
		}
	}

	if (vis[T] == -1) {
		return false;
	}

	int i = T;
	int j = vis[i];
	while (j != 0) {
		ans.push_back(Move(ret(i),ret(j)));
		j = vis[j];
		i = vis[i];
	}
	return true;
}

bool solve(vector<pii> s, vector<pii> t, vector<pii> mid, vector<pii> extra, bitset<N*N> sources, vector<int> perm) {
	ans.clear();
	shuffle(mid.begin(), mid.end(), rng);
	for (const pii& it : extra) mid.push_back(it);

	vector<bool> done(m);
	for (const pii& it : mid) {
		for (int i = 0; i < m; i++) {
			if (done[i]) continue;
			sources[get(s[i].first, s[i].second)] = false;
			if (bfs(s[i], it, sources)) {
				done[i] = true;
				s[i] = it;
				sources[get(s[i].first, s[i].second)] = true;
				break;
			} else {
				sources[get(s[i].first, s[i].second)] = true;
			}
		}
	}

	memo = ans;
	bitset<N*N> memo_sources = sources;
	for (int cnt = 0; cnt < 7; cnt++) {
		shuffle(perm.begin(), perm.end(), rng);
		bool bad = false;
		for (int i : perm) {
			sources[get(s[i].first, s[i].second)] = false;
			if (!bfs(s[i], t[i], sources)) {
				bad = true;
				break;
			}
			sources[get(t[i].first, t[i].second)] = true;
		}

		if (bad) {
			ans = memo;
			sources = memo_sources;
		} else {
			return true;
		}
	}

	return false;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	vector<pii> s, t, mid, extra;
	bitset<N*N> sources, sinks;

	int a, b;
	cin >> n >> m;

	vector<int> perm;
	for (int i = 0; i < m; i++) {
		perm.push_back(i);
	}


	if (n == 1) {
		cout << 0 << nl;
		return 0;
	}

	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		s.push_back(pii(a,b));
		sources[get(a,b)] = true;
	}
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		t.push_back(pii(a,b));
		sinks[get(a,b)] = true;
	}

	for (int i = 2; i < n; i++) {
		for (int j = 2; j < n; j++) {
			if (!sinks[get(i,j)]) mid.push_back(pii(i,j));
		}
		if (!sinks[get(i,1)]) mid.push_back(pii(i,1));
		if (!sinks[get(i,n)]) mid.push_back(pii(i,n));
		if (!sinks[get(1,i)]) mid.push_back(pii(1,i));
		if (!sinks[get(n,i)]) mid.push_back(pii(n,i));
	}

	if (!sinks[get(1,1)]) extra.push_back(pii(1,1));
	if (!sinks[get(1,n)]) extra.push_back(pii(1,n));
	if (!sinks[get(n,1)]) extra.push_back(pii(n,1));
	if (!sinks[get(n,n)]) extra.push_back(pii(n,n));

	while (!solve(s, t, mid, extra, sources, perm));

	cout << ans.size() << nl;
	for (const Move& mv : ans) {
		cout << mv << nl;
	}

	return 0;
}

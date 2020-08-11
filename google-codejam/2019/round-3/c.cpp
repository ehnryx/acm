#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

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

int n, m;
int get(int i, int j) {
	return i*m + j;
}

const int N = 100+1;
string grid[N];
char ans[N][N];

int cnt[N*N];
int root[N*N];
int find(int i) {
	if (root[i] == -1) return i;
	return root[i] = find(root[i]);
}
bool link(int i, int j) {
	i=find(i); j=find(j);
	if (i==j) return false;
	root[i] = j;
	return true;
}

struct Edge {
	int a, b, i;
	bool operator < (const Edge& o) const {
		char A = grid[a/m][a%m];
		char B = grid[o.a/m][o.a%m];
		if (A != B) return A < B;
		else return cnt[i] < cnt[o.i];
	}
};

void caseinit() {
	memset(root, -1, sizeof root);
	memset(cnt, 0, sizeof cnt);
	fill(&ans[0][0], &ans[0][0]+N*N, '.');
}

void solve() {
	caseinit();

	//int n, m;
	cin >> n >> m;
	int g = n*m;

	vector<Edge> edges;
	For(i,n) {
		cin >> grid[i];
		For(j,m) {
			if (j > 0 && grid[i][j] == grid[i][j-1]) {
				g -= link(get(i,j), get(i,j-1));
			}
			if (i > 0 && grid[i][j] == grid[i-1][j]) {
				g -= link(get(i,j), get(i-1,j));
			}
			if (i > 0 && j > 0 && grid[i][j] == grid[i-1][j-1]) {
				edges.push_back({get(i,j), get(i-1,j-1), get(i-1,j-1)});
				cnt[get(i-1,j-1)]++;
			}
			if (i > 0 && j+1 < m && grid[i][j] == grid[i-1][j+1]) {
				edges.push_back({get(i,j), get(i-1,j+1), get(i-1,j)});
				cnt[get(i-1,j)]++;
			}
		}
	}
	sort(edges.begin(), edges.end());

	for (const Edge& e : edges) {
		if (find(e.a) != find(e.b) && cnt[e.i]) {
			g -= link(e.a, e.b);
			cnt[e.i] = 0;
			if (e.b%m < e.a%m) {
				ans[e.i/m][e.i%m] = '\\';
			} else {
				ans[e.i/m][e.i%m] = '/';
			}
		}
	}
	assert(g >= 2);

	if (g == 2) {
		cout << "POSSIBLE" << nl;
		For(i,n-1) {
			For(j,m-1) {
				cout << ans[i][j];
			}
			cout << nl;
		}
		return;
	}

	cout << "IMPOSSIBLE" << nl;

	return;
}


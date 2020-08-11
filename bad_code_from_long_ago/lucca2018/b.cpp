#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ ";
	for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
	os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

const int N = 1e5;
vector<int> graph[N+1];
int degree[N+1];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;

	memset(degree, 0, sizeof degree);
	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		degree[b]++;
	}

	priority_queue<int, vector<int>, greater<int>> next;
	for (int i = 0; i < n; i++) {
		if (degree[i] == 0) {
			next.push(i);
		}
	}

	vector<int> ans;
	while (!next.empty()) {
		int cur = next.top();
		next.pop();
		ans.push_back(cur);
		for (int x : graph[cur]) {
			degree[x]--;
			if (degree[x] == 0)
				next.push(x);
		}
	}

	if (ans.size() < n) {
		cout << "*" << nl;
	} else {
		for (int it : ans) {
			cout << it << nl;
		}
	}

	return 0;
}

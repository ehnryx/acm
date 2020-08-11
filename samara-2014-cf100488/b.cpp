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

const int N = 100+1;
unordered_set<int> vals[N];

void update(int a, int b, const unordered_set<int>& cur) {
	for (int i = a; i <= b; i++) {
		for (auto it = vals[i].begin(); it != vals[i].end(); ) {
			if (!cur.count(*it)) it = vals[i].erase(it);
			else it++;
		}
	}
}

void query(int a, int b, int n) {
	cout << "Q " << a << " " << b << endl;

	unordered_set<int> cur;
	unordered_set<int> other;
	for (int i = 1; i <= n; i++) {
		other.insert(i);
	}

	int in;
	for (int i = a; i <= b; i++) {
		cin >> in;
		cur.insert(in);
		other.erase(in);
	}

	update(a, b, cur);
	update(1, a-1, other);
	update(b+1, n, other);
}

void answer(int n) {
	cout << "A ";
	for (int i = 1; i <= n; i++) {
		assert(vals[i].size() == 1);
		cout << *vals[i].begin() << " ";
	}
	cout << endl;
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

	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			vals[i].insert(j);
		}
	}

	int lim = (n % 2 == 0 ? n : n+1);
	int lg = 32 - __builtin_clz(n-1);
	query(1, 1<<(lg-1), n);
	for (int h = 0; h < lg; h++) {
		int i;
		for (i = 1<<(h+1); i+(1<<h) < lim; i += 1<<(h+2)) {
			query(i-(1<<h)+1, i+(1<<h), n);
		}
		if (i < lim) {
			int r = h;
			while (i+(1<<r) >= lim) { r--; }
			query(i-(1<<h)+1, i+(1<<r), n);
		}
	}
	answer(n);

	return 0;
}

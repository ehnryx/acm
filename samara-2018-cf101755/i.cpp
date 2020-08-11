#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	return os << '(' << v.first << ',' << v.second << ')';
}

int height(int n) { return 31 - __builtin_clz(n); }

const int N = 1024;
int parent[N];

pii init(int n) {
	int h = height(n);
	set<pii> guessed;

	int res, a, b;
	res = a = b = -1;
	while (res != 2*h) {
		a = 1+rng()%n;
		b = 1+rng()%n;
		if (b < a) swap(a,b);
		if (a == b || guessed.count(pii(a,b))) continue;
		guessed.insert(pii(a,b));
		cout << "? " << a << " " << b << endl;
		cin >> res;
	}
	return pii(a,b);
}

int solve(int n, vector<int> id, int left, int right) {
	if (n == 1) return id[0];
	int h = height(n);
	int root = -1;

	vector<int> lchild, rchild;
	int ldist, rdist, lleaf, rleaf;
	lleaf = rleaf = -1;
	for (int i : id) {
		if (i == left || i == right) continue;
		cout << "? " << left << " " << i << endl;
		cin >> ldist;
		cout << "? " << right << " " << i << endl;
		cin >> rdist;

		if (ldist == rdist) {
			root = i;
		}
		else if (ldist < rdist) {
			lchild.push_back(i);
			if (ldist == 2*(h-1)) lleaf = i;
		}
		else {
			rchild.push_back(i);
			if (rdist == 2*(h-1)) rleaf = i;
		}
	}
	lchild.push_back(left);
	rchild.push_back(right);

	lleaf = solve(n/2, lchild, left, lleaf);
	rleaf = solve(n/2, rchild, right, rleaf);
	parent[lleaf] = root;
	parent[rleaf] = root;
	return root;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;

	if (n == 1) {
		cout << "! 0" << nl;
		return 0;
	}

	pii leaves = init(n);

	vector<int> id;
	for (int i = 1; i <= n; i++) {
		id.push_back(i);
	}
	int root = solve(n, id, leaves.first, leaves.second);
	parent[root] = 0;

	cout << "! ";
	for (int i = 1; i <= n; i++) {
		cout << parent[i] << " ";
	}
	cout << nl;

	return 0;
}

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

struct Target {
	virtual int hit(int i, int j) const = 0;
};

struct Circle : Target {
	int x, y, r;
	Circle(int x, int y, int r): x(x), y(y), r(r) {}
	int hit(int i, int j) const override {
		return ((x-i)*(x-i)+(y-j)*(y-j) <= r*r);
	}
};

struct Rectangle : Target {
	int x, y, a, b;
	Rectangle(int x, int y, int a, int b): x(x), y(y), a(a), b(b) {}
	int hit(int i, int j) const override {
		return x<=i && i<=a && y<=j && j<=b;
	}
};

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
	vector<unique_ptr<Target>> targets;
	for (int i=0; i<n; i++) {
		string s;
		cin >> s;
		if (s == "circle") {
			int x, y, r;
			cin >> x >> y >> r;
			targets.push_back(unique_ptr<Target>(new Circle(x,y,r)));
		} else {
			int x, y, a, b;
			cin >> x >> y >> a >> b;
			targets.push_back(unique_ptr<Target>(new Rectangle(x,y,a,b)));
		}
	}

	int m;
	cin >> m;
	for (int i=0; i<m; i++) {
		int x, y;
		cin >> x >> y;
		int ans = 0;
		for (const unique_ptr<Target>& it : targets) {
			ans += it.get()->hit(x,y);
		}
		cout << ans << nl;
	}

	return 0;
}

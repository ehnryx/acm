#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "fygon"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int value[26], _;
struct Block {
	vector<Block*> v;
	int add;
	char var, lim;
	Block(char x=0, char n=0): add(0), var(x), lim(n) {}
	void add_lag() { add++; }
	void add_block(Block* x) { v.push_back(x); }
	int eval() {
		int n = (lim ? (isalpha(lim) ? value[lim-'a'] : lim-'0') : 1);
		int& i = (var ? value[var-'a'] : _);
		int res = add*n;
		for(i=0; i<n; i++) {
			for(Block* it : v) {
				res += it->eval();
			}
		}
		return res;
	}
};

struct Frac {
	ll n, d;
	Frac(ll a=0, ll b=1) {
		ll g = __gcd(a,b);
		n = a/g; d = b/g;
		if(d<0) {
			n = -n;
			d = -d;
		}
	}
	Frac operator + (const Frac& o) const { return Frac(n*o.d + d*o.n, d*o.d); }
	Frac operator - (const Frac& o) const { return Frac(n*o.d - d*o.n, d*o.d); }
	Frac operator * (const Frac& o) const { return Frac(n*o.n, d*o.d); }
	Frac operator / (const Frac& o) const { return Frac(n*o.d, d*o.n); }
	void operator += (const Frac& o) { *this = *this + o; }
	void operator -= (const Frac& o) { *this = *this - o; }
};

ostream& operator << (ostream& os, const Frac& v) {
	return os << v.n << "/" << v.d;
}

vector<Frac> interpolate(vector<Frac> x, vector<Frac> y) {
	int n = x.size();
	vector<Frac> res(n), temp(n);
  for (int k = 0; k < n-1; k++) for (int i = k+1; i < n; i++)
		y[i] = (y[i] - y[k]) / (x[i] - x[k]);
	Frac last = 0; temp[0] = 1;
  for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) {
		res[i] += y[k] * temp[i];
		swap(last, temp[i]);
		temp[i] -= last * x[k];
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	if(fopen(FILENAME ".in", "r")) {
		freopen(FILENAME ".in", "r", stdin);
		freopen(FILENAME ".out", "w", stdout);
	}

	int pre = 0;
	Block* base = new Block;
	stack<Block*> stk;
	stk.push(base);

	for(string s; getline(cin, s); ) {
		istringstream ss(s);
		vector<string> line;
		for(string t; ss >> t; ) {
			line.push_back(t);
		}

		int indent = 0;
		for(char c:s) {
			if(isspace(c)) {
				indent++;
			} else {
				break;
			}
		}
		while(indent < pre) {
			pre -= 4;
			stk.pop();
		}

		if(line.size() == 1) {
			stk.top()->add_lag();
			pre = indent;
		} else {
			pre = indent + 4;
			Block* cur = new Block(line[1][0], line[3][6]);
			stk.top()->add_block(cur);
			stk.push(cur);
		}
	}

	vector<Frac> x, y;
	for(int i=0; i<7; i++) {
		memset(value, 0, sizeof value);
		value['n'-'a'] = i;
		y.push_back(base->eval());
		x.push_back(i);
	}

	vector<Frac> f = interpolate(x, y);
	for(int i=0; i<f.size(); i++) {
		if(i>0) cout << " + ";
		cout << f[i];
		for(int j=0; j<i; j++) {
			cout << "*n";
		}
	}
	cout << nl;

	return 0;
}

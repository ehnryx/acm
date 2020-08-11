//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

pair<int,int> read_nums(const string& s, int& x) {
	int left = x;
	while(left > 0 && (s[left-1] == '-' || isdigit(s[left-1]))) {
		left--;
	}
	string coeff = s.substr(left, x-left);
	if(coeff == "-") coeff = "-1";
	else if(coeff == "") coeff = "1";

	int right = x;
	while(right+1 < s.size() && isdigit(s[right+1])) {
		right++;
	}
	int id = stoi(s.substr(x+1, right-x)) - 1;

	x = right + 1;
	return make_pair(stoi(coeff), id);
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

#ifdef ONLINE_JUDGE
	freopen("dual.in", "r", stdin);
	freopen("dual.out", "w", stdout);
#endif

	int n, m;
	cin >> n >> m;
	string line;
	getline(cin, line);

	vector<int> b(m), c(n);
	getline(cin, line);
	istringstream in(line);
	string type, obj;
	in >> type >> obj;
	if(type == "min") type = "max";
	else type = "min";
	obj.push_back('.');
	for(int x=obj.find('x'); x!=-1; x=obj.find('x')) {
		auto [coeff, id] = read_nums(obj, x);
		c[id] = coeff;
		obj = obj.substr(x);
	}

	getline(cin, line);

	vector<string> op(n);
	for(int i=0; i<n; i++) {
		getline(cin, line);
		if(line.find('>') != -1) {
			op[i] = (type == "max" ? "<=" : ">=");
		} else if(line.find('<') != -1) {
			op[i] = (type == "max" ? ">=" : "<=");
		} else {
			op[i] = "=";
		}
	}

	getline(cin, line);

	vector<string> var(m);
	vector<vector<int>> mat(m, vector<int>(n));
	for(int i=0; i<m; i++) {
		getline(cin, line);
		for(int x=line.find('x'); x!=-1; x=line.find('x')) {
			auto [coeff, id] = read_nums(line, x);
			mat[i][id] = coeff;
			line = line.substr(x);
		}
		if(line.find('<') != -1) {
			var[i] = (type == "max" ? "<=0" : ">=0");
		} else if(line.find('>') != -1) {
			var[i] = (type == "max" ? ">=0" : "<=0");
		} else {
			var[i] = " arbitary"; // arbitrary
		}
		b[i] = stoi(line.substr(line.find('=') + 1));
	}

	//cerr<<"b = "; for(int it : b) cerr<<it<<" "; cerr<<nl;
	//cerr<<"c = "; for(int it : c) cerr<<it<<" "; cerr<<nl;
	//cerr<<"mat = "<<nl; for(vector<int> row : mat) { for(int it : row) cerr<<it<<" "; cerr<<nl; }
	//cerr<<nl;

	bool s = 0;
	cout << m << " " << n << nl;
	cout << type << " ";
	for(int i=0; i<m; i++) {
		if(!b[i]) continue;
		if(b[i] < 0) cout << '-';
		else if(s) cout << '+';
		if(abs(b[i]) > 1) cout << abs(b[i]);
		cout << 'y' << i+1;
		s = true;
	}
	if(!s) cout << '0';
	cout << nl;

	cout << "with" << nl;
	for(int i=0; i<m; i++) {
		cout << 'y' << i+1 << var[i] << nl;
	}

	cout << "under" << nl;
	for(int i=0; i<n; i++) {
		s = 0;
		for(int j=0; j<m; j++) {
			if(!mat[j][i]) continue;
			if(mat[j][i] < 0) cout << '-';
			else if(s) cout << '+';
			if(abs(mat[j][i]) > 1) cout << abs(mat[j][i]);
			cout << 'y' << j+1;
			s = true;
		}
		if(!s) cout << '0';
		cout << op[i] << c[i] << nl;
	}

	return 0;
}

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



//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	const int n = 8;
	string grid[n];
	for (int i=0; i<n; i++) {
		cin >> grid[i];
	}

	auto valid = [&] (const complex<int>& pos) {
		if (pos.real()<0||pos.imag()<0||pos.real()>7||pos.imag()>7) return false;
		return grid[pos.real()][pos.imag()]!='C'&&grid[pos.real()][pos.imag()]!='I';
	};
	auto shoot = [&] (const complex<int>& pos) {
		if (pos.real()<0||pos.imag()<0||pos.real()>7||pos.imag()>7) return false;
		return grid[pos.real()][pos.imag()]=='I';
	};

	string s;
	cin >> s;

	complex<int> dir(0,1);
	complex<int> pos(7,0);
	for (char c : s) {
		switch (c) {
			case 'F':
				if (valid(pos+dir)) pos += dir;
				else goto bug;
				break;
			case 'R':
				dir *= complex<int>(0,-1);
				break;
			case 'L':
				dir *= complex<int>(0,1);
				break;
			case 'X':
				if (shoot(pos+dir)) grid[(pos+dir).real()][(pos+dir).imag()] = '.';
				else goto bug;
				break;
			default:
				assert(false);
				break;
		}
	}

	if (grid[pos.real()][pos.imag()] == 'D') {
		cout << "Diamond!" << nl;
		return 0;
	}

bug:
	cout << "Bug!" << nl;

	return 0;
}

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

	int n;
	cin >> n;

	int top[n], bot[n];
	unordered_set<int> seen;
	for (int i=0; i<n; i++) {
		cin >> top[i];
		if (seen.count(top[i])) seen.erase(top[i]);
		else seen.insert(top[i]);
	}
	for (int i=0; i<n; i++) {
		cin >> bot[i];
	}

	int topsz = 0;
	int botsz = 0;
	for (int i=0; i<n; i++) {
		if (!seen.count(bot[i])) bot[botsz++] = bot[i];
		if (!seen.count(top[i])) top[topsz++] = top[i];
	}

	auto valid = [&] (int ub) {
		int pre = -1;
		for (int i=0; i<topsz; i++) {
			if (top[i]<=ub) continue;
			if (pre==-1) pre = top[i];
			else if (pre != top[i]) return false;
			else pre = -1;
		}
		if (pre != -1) return false;
		for (int i=0; i<botsz; i++) {
			if (bot[i]<=ub) continue;
			if (pre == -1) pre = bot[i];
			else if (pre != bot[i]) return false;
			else pre = -1;
		}
		if (pre != -1) return false;
		return true;
	};

	int minv = 0;
	for (int it : seen) {
		minv = max(minv, it);
	}

	int left = minv;
	int right = 1e9;
	while (left < right) {
		int mid = (left+right)/2;
		if (valid(mid)) {
			right = mid;
		} else {
			left = mid+1;
		}
	}
	cout << left << nl;

	return 0;
}

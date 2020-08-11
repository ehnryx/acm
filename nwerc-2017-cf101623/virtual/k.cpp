#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

namespace std {
	template<> struct hash<pii> {
		size_t operator () (const pii& v) const {
			return v.first<<15 ^ v.second;
		}
	};
}

const int N = 4200;
ll val[N];

unordered_map<pii,unordered_map<int,ld>> memo;

ld solve(int goal, int left, int right, int bottom) {
	if (left == right) return 1;
	pii node(left,right);
	if (memo[node].count(goal)) return memo[node][goal];

	int diff = right-left+1;
	if (bottom == 0) assert(diff == 2);
	int half = (bottom ? max(bottom, diff-2*bottom) : 1);
	if (goal < left+half) {
		ld res = solve(goal, left, left+half-1, bottom/2);
		ld win = 0;
		for (int g=left+half; g<=right; g++) {
			win += solve(g, left+half, right, bottom/2) * val[goal] / (val[goal]+val[g]);
		}
		//cerr << "solve " << goal << " " << left << " " << right << " -> " << res*win << nl;
		return memo[node][goal] = res*win;
	} else {
		ld res = solve(goal, left+half, right, bottom/2);
		ld win = 0;
		for (int g=left; g<left+half; g++) {
			win += solve(g, left, left+half-1, bottom/2) * val[goal] / (val[goal]+val[g]);
		}
		//cerr << "other " << goal << " " << left << " " << right << " -> " << res*win << nl;
		return memo[node][goal] = res*win;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;

	for (int i=0; i<n; i++) {
		cin >> val[i];
	}
	sort(val+1, val+n);

	int bottom = 1<<(30-__builtin_clz(n));
	//cerr << "bottom: " << bottom << nl;
	cout << solve(0, 0, n-1, bottom) << nl;

	return 0;
}

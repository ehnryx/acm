#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int INF = 0x3f3f3f3f;
const char nl = '\n';

int dist(const vector<int>& a, const vector<int>& b) {
	if (a.size() != b.size()) return INF;
	int ans = 0;
	for (int i = 0; i < a.size(); i++) {
		ans += abs(a[i] - b[i]);
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m; cin >> n >> m;
	vector<int> ones;
	for (int i = 0; i < n; i++) {
		int k; cin >> k;
		if (k) ones.push_back(i);
	}
	vector<int> code(m);
	for (int& i : code) cin >> i;
	int ans = INF;
	vector<int> target;
	{
		int cur = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < code[i]; j++) {
				if (i%2) target.push_back(cur);
				cur++;
			}
		}
	}
	ans = min(ans, dist(ones, target));
	target.clear();
	{
		int cur = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < code[i]; j++) {
				if (!(i%2)) target.push_back(cur);
				cur++;
			}
		}
	}
	ans = min(ans, dist(ones, target));
	cout << ans << nl;
	return 0;
}

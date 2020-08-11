#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

int n, V;
int c[5];
unordered_map<string, int> dp;
unordered_map<string, bool> vis;
int solve(const string &s) {
/*
	   for (char c : s)
	   cout << (int) c << " ";
	   cout << endl;
*/
	if (s[0] == V)
		return dp[s] = 0;
	if (dp.count(s))
		return dp[s];
	if (vis[s])
		return INF;
	vis[s] = 1;
	string s2 = s;
	int ans = INF;
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < s.size(); j++) {
			if (i == j) continue;
			// pour i into j
			int pour = min((int) s2[i], c[j] - s2[j]);
			if (pour) {
				s2[i] -= pour, s2[j] += pour;
				ans = min(ans, solve(s2) + pour);
				s2[i] += pour, s2[j] -= pour;
			}
		}
	}
	return dp[s] = ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	string in;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> c[i];
	in.resize(n);
	in[0] = c[0];
	cin >> V;
	priority_queue<pair<int, string>> pq;
	pq.push({0, in});
	while (!pq.empty()) {
		int d; string s; tie(d, s) = pq.top(); pq.pop();
		if (vis.count(s)) continue;
		if (s[0] == V) {
			cout << -d << endl;
			return 0;
		}
		vis[s] = 1;
		for (int i = 0; i < s.size(); i++) {
			for (int j = 0; j < s.size(); j++) {
				if (i == j) continue;
				int pour = min((int) s[i], c[j] - s[j]);
				if (pour) {
					s[i] -= pour, s[j] += pour;
					if (!vis.count(s))
						pq.push({d - pour, s});
					s[i] += pour, s[j] -= pour;
				}
			}
		}
	}
	puts("impossible");

	return 0;
}

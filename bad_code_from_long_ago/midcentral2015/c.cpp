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

int check(const vector<int>& perm, const vector<vector<int>>& diff) {
	int res = 0;
	for (int i = 1; i < perm.size(); i++) {
		res += diff[perm[i-1]][perm[i]];
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;
	string dance[n];
	vector<int> perm;
	vector<vector<int>> diff(n);
	for (int i = 0; i < n; i++) {
		perm.push_back(i);
		cin >> dance[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			diff[i].push_back(0);
			for (int k = 0; k < dance[i].size(); k++) {
				for (int l = 0; l < dance[j].size(); l++) {
					if (dance[i][k] == dance[j][l]) {
						diff[i][j]++;
						break;
					}
				}
			}
		}
	}
	int ans = INF;
	do {
		ans = min(ans, check(perm, diff));
	} while (next_permutation(perm.begin(), perm.end()));
	cout << ans << nl;

	return 0;
}

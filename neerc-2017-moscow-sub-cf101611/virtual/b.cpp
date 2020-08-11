#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

const int N = 5001;
ll ans[N][N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	string s;
	cin >> s;
	int n = s.size();

	int right = s[0] == '>');
	ans[0][0] = 1;
	for (int i=1; i<n; i++) {
		if (s[i] == '>') {
			for (int j=0; j<i; j++) {
				ans[i][j] = 0;
				if (s[j] == '>') {
					ans[i][i] += ans[i-1][j];
				}
			}
		}
		else {
			for (int j=0; j<i; j++) {
				ans[i][j] = ans[i-1][j];
			}
		}
	}

	return 0;
}

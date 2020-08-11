#include <bits/stdc++.h>
using namespace std;

#define debug

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
const ll MOD = 1e9+7;
const int INF = 0x7f7f7f7f;
const ll INFLL = 0x7f7f7f7f7f7f7f7f;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int cmax;
	int score[10];
	int count[10];
	ll a, b, n, y;
	int T;
	cin >> T;
	while (T--) {
		memset(score, 0, sizeof(score));
		cin >> a >> b >> n;
		for (ll x = 1; ; x++) {
			y = a*x*x + b*x;
			if (y > n) break;
			memset(count, 0, sizeof(count));
			while (y) {
				count[y%10]++;
				y/=10;
			}
			cmax = 0;
			for (int i = 0; i < 10; i++) 
				cmax = max(cmax, count[i]);
			for (int i = 0; i < 10; i++)
				if (cmax == count[i])
					score[i]++;
		}
		cmax = 0;
		for (int i = 0; i < 10; i++)
			cmax = max(cmax, score[i]);
		if (cmax == 0) cout << -1 << endl;
		else { 
			for (int i = 0; i < 10; i++) {
				if (score[i] == cmax) {
					cout << i << endl;
					break;
				}
			}
		}
	}

	return 0;
}

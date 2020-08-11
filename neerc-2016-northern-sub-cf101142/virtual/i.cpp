#include <bits/stdc++.h>
using namespace std;
#define problem_name "integral"

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

const int MAXN = 2e5+10;

int x[MAXN], y[MAXN], n;

int cnt[2][2][2]; //parity + counts

int ox[MAXN], oy[MAXN];

map<pair<ll,ll>, ll> slope;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifdef ONLINE_JUDGE
	freopen(problem_name ".in", "r", stdin);
	freopen(problem_name ".out", "w", stdout);
#endif

	cin >> n;
	for(int i = 0;i<n;i++) {
		cin >> ox[i] >> oy[i];
		x[i]=abs(ox[i])%2;
		y[i]=abs(oy[i])%2;
	}
	for(int j=n-1,i=0;i<n;j=i++) {
		ll dx = ox[i]-ox[j];
		ll dy = oy[i]-oy[j];
		ll g = abs(__gcd(dx, dy));
		dx/=g;
		dy/=g;
		slope[make_pair(dx,dy)]++;
	}
	int sum = 0;
	for(int i=0;i<n;i++) {
		int j = (i+1)%n;
		int area = (x[i]*y[j] - x[j]*y[i]+2)%2;
		sum = (sum+area)%2;
		cnt[sum][x[j]][y[j]]++;
	}
	if (sum!=0) {
		cout << 0 <<endl;
		return 0;
	}
	ll ans = 0;
	bool parity = 0;
	for(int i=0;i<n;i++) {
		for(int j=0;j<2;j++) {
			for(int k=0;k<2;k++) {
				int area = (x[i]*k+y[i]*j)%2;
				ans += cnt[parity^area][j][k];
			}
		}
		//cerr << ans <<endl;
		int j = (i+1)%n;
		int area = (x[i]*y[j] - x[j]*y[i]+2)%2;
		parity^=area;
	}


	for(auto &v: slope) {
		ans -= v.second*(v.second+1);
	}
	ans -= n;
	assert(ans%2==0);
	cout << ans/2 <<endl;

	return 0;
}

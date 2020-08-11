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

	int n=8;
	string a[n];
	for(int i=0;i<n;i++)cin>>a[i];
	int cnt=0;
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(a[i][j]=='*'){
		cnt++;
		for(int k=0;k<n;k++){
			if(k!=j&&a[i][k]=='*')goto bad;
			if(k!=i&&a[k][j]=='*')goto bad;
			if(k!=i&&j+k-i>=0&&j+k-i<8&&a[k][j+k-i]=='*')goto bad;
			if(k!=i&&j-k+i>=0&&j-k+i<8&&a[k][j-k+i]=='*')goto bad;
		}
	}
	if (cnt==8) {
		cout << "valid" << nl;
	} else {
bad:
		cout << "invalid" << nl;
	}

	return 0;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';


const int MAXN = 101;
const ll INF = 0x3f3f3f3f3f3f3f3fLL;

ll m1[MAXN][MAXN*MAXN];
ll m2[MAXN][MAXN*MAXN];

ll a[MAXN], b[MAXN], c[MAXN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int t; cin >> t;
	while(t--) {
		int n; cin >> n;
		for(int i=0;i<n;i++) {
			cin >> a[i] >> b[i] >> c[i];
		}
		fill(&m1[0][0], &m1[0][0]+MAXN*MAXN*MAXN, -INF);
		fill(&m2[0][0], &m2[0][0]+MAXN*MAXN*MAXN, -INF);
		m1[0][0] = 0;
		int nj, nk;
		for(int i=n-1;i>=0;i--) { // consider the ith element
			// state is number of attacks, then number of cum distances
			for(int j=0;j<=n;j++) {
				for(int k=0;k<=n*n; k++){ 
					if (m1[j][k]==-INF) continue;
					//cerr << j << " " << k <<endl;
					// attack, increment k, no benefits
					nj = j+1;
					nk = k+j+1;
					//cerr << "going to " << nj << " " << nk <<endl;
					m2[nj][nk] = max(m2[nj][nk], m1[j][k]+a[i]);
					// else nj and nk are known
				  nj = j;
					nk = k+j;
					// take b
					m2[nj][nk] = max(m2[nj][nk], m1[j][k]+b[i]*k);
					// take c
					m2[nj][nk] = max(m2[nj][nk], m1[j][k]+c[i]*j);
				}
			}
			swap(m1,m2);
			fill(&m2[0][0], &m2[0][0]+MAXN*MAXN*MAXN, -INF);
		}
		ll ans = 0;
		for(int j=0;j<=n;j++) {
			for(int k=0;k<=n*n;k++) {
				ans = max(ans, m1[j][k]);
			}
		}
		cout << ans << endl;
	}


	return 0;
}

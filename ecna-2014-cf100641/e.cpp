#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const char nl = '\n';
const int INF = 0x3f3f3f3f;

const int N = 1e2;
const int maxv = 1e4;

int w[N][N], ml[N], mr[N], lbl[N], lbr[N], s[N], slack[N], par[N];
int wmatch(int n, int m) {
	int i, j, k, done, al, nxt, out=0;
	for (i=0; i<n; i++) for (j=0,lbl[i]=0,ml[i]=-1; j<m; j++) lbl[i]=max(lbl[i],w[i][j]);
	for (i=0; i<m; i++) lbr[i]=0, mr[i]=-1;
	for (i=0; i<n; i++) for (j=0; j<m; j++) if (w[i][j] == lbl[i] && mr[j] == -1)
		{ ml[i] = j, mr[j] = i; break; }
	for (i=0; i<n; i++) if (ml[i] == -1) {
		for (j=0; j<m; j++) s[j]=(j==i), slack[j] = (lbl[i]+lbr[j]-w[i][j]), par[j] = -1;
		for (done=0; !done; ) {
			for (j=0, al=INF; j<m; j++) if (par[j]==-1) al = min(al, slack[j]);
			for (j=0, lbl[j] -= s[j]*al; j<m; ++j, lbl[j]-=s[j]*al)
				if (par[j] != -1) lbr[j] += al; else slack[j] -= al;
			for (j=0; j<m; j++) if (!slack[j] && par[j] == -1) {
				for (k=0; k<n; k++) if (s[k]&&(lbl[k]+lbr[j]==w[k][j])) { par[j]=k; break; }
				if (mr[j] == -1) { done = 1;
					do { nxt=ml[par[j]], mr[j]=par[j], ml[par[j]]=j, j=nxt; } while (j != -1);
				} else for (k=0, s[mr[j]]=1; k<m; k++) 
					slack[k] = min(slack[k], lbl[mr[j]] + lbr[k] - w[mr[j]][k]); break;
			}
		}
	}
	for (i=0; i<n; i++) out += w[i][ml[i]]; return out;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int T;
	cin >> T;
	for (int cs=1; cs<=T; cs++) {
		int n, v;
		cin >> n;

		memset(w, 0, sizeof 0);
		memset(lbl, 0, sizeof lbl);
		memset(lbr, 0, sizeof lbr);
		for (int i=0; i<n; i++) {
			for (int j=i+1; j<n; j++) {
				cin >> v;
				w[i][j] = w[j][i] = maxv - v;
			}
		}

		cout << "Case " << cs << ": " << n*maxv - wmatch(n,n) << nl;
	}

	return 0;
}

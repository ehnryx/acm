#include <bits/stdc++.h>
using namespace std;
#define FILENAME "concatenation"

typedef long long ll;
typedef long double ld;
const char nl = '\n';

typedef vector<int> vi;
typedef pair<int,int> pii;
struct suff_array {
	const int L; int skip, lvl;
	vector<vi> P; vector<pair<pii,int>> M;
	suff_array(const string& s) : L(s.size()), P(1, vi(L,0)), M(L) {
		for(int i=0; i<L-(L==1); i++) P[0][i] = int(s[i]);
		for(skip=1, lvl=1; skip<L; skip*=2, lvl++) {
			P.push_back(vi(L, 0));
			for(int i=0; i<L; i++) {
				M[i] = {{P[lvl-1][i], i+skip<L ? P[lvl-1][i+skip] : -1000}, i};
			}
			sort(M.begin(), M.end());
			for(int i=0; i<L; i++) {
				P[lvl][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ?
					P[lvl][M[i-1].second] : i;
			}
		}
	}
	const vi& get_sarray() { return P.back(); }
	int lcp(int i, int j) const {
		int len=0; if(i==j) return L-i;
		for(int k=P.size()-1; k>=0 && i<L && j<L; k--) {
			if(P[k][i] == P[k][j]) { i+=1<<k; j+=1<<k; len+=1<<k; }
		}
		return len;
	}
};

const int N = 2e5+7;
int psum[N], idx[N], rev[N];

int find_left(const suff_array& sa, int x) {
	int l = 0;
	int r = x;
	while(l<r) {
		int m = (l+r+1)/2;
		if(m>0 && sa.lcp(rev[m-1], rev[x]) == 0) {
			l = m;
		} else {
			r = m-1;
		}
	}
	if(r == 0) return 0;
	else return psum[r-1];
}

int find_right(const suff_array& sa, int x, int n) {
	int l = x+1;
	int r = n;
	while(l<r) {
		int m = (l+r)/2;
		if(m<n && sa.lcp(rev[m], rev[x]) == 0) {
			r = m;
		} else {
			l = m+1;
		}
	}
	if(r == n) return 0;
	else return psum[n-1] - psum[r-1];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);

	char _;
	cin >> _;
	string s, t;
	if(!(cin >> s >> t)) {
		assert(!s.empty() && t.empty());
		swap(s, t);
	}
	t.pop_back();

	//cerr<<"got s = "<<s<<nl;
	//cerr<<"got t = "<<t<<nl;

	int a = s.size();
	int b = t.size();
	s += ".";
	s += t;
	s += "?";

	suff_array sa(s);
	int n = s.size();
	for(int i=0; i<n; i++) {
		idx[i] = sa.get_sarray()[i];
		rev[idx[i]] = i;
		if(i>a && i<n) {
			psum[idx[i]] = 1;
		}
	}
	for(int i=1; i<N; i++) {
		psum[i] += psum[i-1];
	}

	ll ans = 0;
	for(int i=0; i<=a; i++) {
		ans += find_left(sa, idx[i]) + find_right(sa, idx[i], n);
	}
	cout << ans << nl;

	return 0;
}

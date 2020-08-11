//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int INF = 0x3f3f3f3f;

const int N = 5e3 + 1;
bool okab[N], okbc[N], okca[N];

void build(const string& s, const string& t, bool res[]) {
	const int n = s.size();
	for(int i=0; i<n; i++) {
		bool ok = true;
		for(int j=0; j<n; j++) {
			if(s[j] == t[(i+j)%n]) {
				ok = false;
				break;
			}
		}
		res[i] = ok;
	}
}

int check(const string& o, const string& s, const string& t, bool A[], bool B[], bool C[]) {
	int n = s.size();
	int res = INF;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(A[i] && B[(j-i+n)%n] && C[(n-j)%n]) {
				res = min(res, min(i,n-i) + min(j,n-j));
			}
		}
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	string a, b, c;
	cin >> a >> b >> c;
	build(a, b, okab);
	build(b, c, okbc);
	build(c, a, okca);

	int ans = INF;
	ans = min(ans, check(a, b, c, okab, okbc, okca));
	ans = min(ans, check(b, c, a, okbc, okca, okab));
	ans = min(ans, check(c, a, b, okca, okab, okbc));
	if(ans < INF) cout << ans << nl;
	else cout << -1 << nl;

	return 0;
}

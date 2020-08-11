#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef pair<int,int> pii;

struct ans {
	int ops;
	int k;
	vector<int> as;
	bool operator<(const ans& o) const {
		if (ops != o.ops) return ops < o.ops;
		if (k != o.k) return k < o.k;
		for (int i = 0; i < as.size(); i++) {
			if (as[i] != o.as[i]) return as[i] > o.as[i];
		}
		return 0;
	}
	friend ostream& operator<<(ostream& out, const ans& a) {
		int mcnt = 0;
		for (int i : a.as) {
			if (i) {
				if (mcnt) {
					out << mcnt << "M ";
					mcnt = 0;
				}
				out << i << "A ";
			}
			mcnt++;
		}
		if (mcnt > 1) cout << mcnt-1 << "M ";
		return out;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	ll a, m, p, q, r, s;
	int tt = 1;
	while (cin >> a >> m >> p >> q >> r >> s) {
		if (!a) break;
		cout << "Case " << tt++ << ": ";
		if (r <= p && q <= s) {
			cout << "empty\n";
			continue;
		}
		if (m == 1) {
			if (q-p > s-r) {
				cout << "impossible\n";
				continue;
			}
			ll numa = (r - p + a - 1) / a;
			if (q + numa * a > s) {
				cout << "impossible\n";
				continue;
			}
			cout << numa << "A\n";
			continue;
		}

		ll mk = 1;
		bool foundans = false;
		ans bestsol;
		for(int k=0;k<100;k++, mk*=m) {
			if (q*mk>s) break;
			ans sol;
			sol.ops = k;
			sol.k = k;
			ll mi = mk, diff = (q-p)*mk, curp = p, testq;
			for(int i=k;i>=0;i--, mi/=m) {
				ll steps = (r+mi-1)/mi;
				ll inc = (steps-curp+a-1)/a;
				ll testp = (curp + inc*a)*mi;
				testq = testp+diff;
				sol.ops+=inc;
				sol.as.push_back(inc);
				//cerr << "trying " << curp << " " << curq <<endl;
				if (testq<= s) {
					//cerr << "FOUND ANS " <<endl;
					while (sol.as.size() < k+1) {
						sol.as.push_back(0);
					}
					if (!foundans) {
						bestsol = sol;
						//cerr << k << " is k and array is:  "; for(int i: sol.as) cerr << i<< " "; cerr <<endl;
						foundans = 1;
					}
					else if (sol < bestsol) bestsol = sol;
					break;
				}
				inc--;
				curp = m*(curp+inc*a);
				sol.as.back()--;
				sol.ops--;
			}
		}
		if (foundans) cout << bestsol << nl;
		else cout << "impossible\n";
	}

	return 0;
}

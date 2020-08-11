#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

struct rat {
	ll nu, de;
	rat(const ll& n = 0, const ll& d = 1) {
		ll g = __gcd(abs(n), abs(d)); nu = n / g; de = d / g;
		if (de < 0) { nu = -nu; de = -de; } }
	rat operator+(const rat& b) const {
		return rat(nu*b.de+de*b.nu, de*b.de); }
	rat operator-(const rat& b) const {
		return rat(nu*b.de-de*b.nu, de*b.de); }
	rat operator-() { return rat(-nu, de); }
	rat operator*(const rat& b) const {
		return rat(nu*b.nu, de*b.de); }
	rat operator/(const rat& b) const {
		return rat(nu*b.de, de*b.nu);
	}
	bool operator == (const rat& b) const {
		return nu * b.de == b.nu * de;
	}
	bool operator<(const rat& b) const {
		return nu * b.de < b.nu * de;
	}
	ll floor() const {
		return nu / de;
	}
};

rat convert(const vector<int>& v) {
	rat ans(v.back());
	for (int i = v.size()-2; i >= 0; i--) {
		ans = rat(1) / ans;
		ans = ans + rat(v[i]);
	}
	return ans;
}
vector<ll> tocf(rat r) {
	vector<ll> ans;
	if (r.de == 1) return { r.nu };
	if (r.nu == 1) return { 0, r.de };
	if (r.nu == 0) return { 0 };
	if (r.nu < 0) {
		ll add = (abs(r.nu)+r.de-1) / r.de;
		ans.push_back(-add);
		r = r + rat(add);
		r = rat(1) / r;
	}
	//cerr << "tocf " << r.nu << " " << r.de << endl;
	while (r.nu > 1) {
		ll v = r.nu/r.de;
		ans.push_back(v);
		r.nu = r.nu-v*r.de;
		swap(r.nu, r.de);
	}
	if (r.de) ans.push_back(r.de);
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n1, n2;
	int tt = 1;
	while (cin >> n1 >> n2) {
		if (!n1 && !n2) break;
		vector<int> r1(n1), r2(n2);
		for (int i = 0; i < n1; i++) {
			cin >> r1[i];
		}
		for (int i = 0; i < n2; i++) {
			cin >> r2[i];
		}
		rat a = convert(r1), b = convert(r2);
		vector<vector<ll>> ans = {tocf(a + b), tocf(a - b), tocf(a * b), tocf(a / b)};
		cout << "Case " << tt++ << ":\n";
		for (const auto& v : ans) {
			for (const ll& i : v) {
				cout << i << " ";
			}
			cout << "\n";
		}
	}


	return 0;
}

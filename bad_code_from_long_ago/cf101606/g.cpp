#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int a, b, c, aa, bb, cc;
	int x, y, z, xx, yy, zz;
	cin >> a >> b >> c >> aa >> bb >> cc;
	cin >> x >> y >> z >> xx >> yy >> zz;

	srand(time(nullptr));

	while (!(a==aa && b==bb && c==cc) || !(x==xx && y==yy && z==zz)) {
		cout << "(" << a << " " << b << " " << c << ")" << " " << "(" << x << " " << y << " " << z << ")" << nl;
		if (a != aa) {
			if (a < aa) {
				a++;
				if (a == x && b == y && c == z) {
					a--; 
					c += rand()%2 ? 1 : -1;
				}
			}
			else {
				a--;
				if (a == x && b == y && c == z) {
					a++;
					c += rand()%2 ? 1 : -1;
				}
			}
		} else if (b != bb) {
			if (b < bb) {
				b++;
				if (a == x && b == y && c == z) {
					b--;
					c += rand()%2 ? 1 : -1;
				}
			}
			else {
				b--;
				if (a == x && b == y && c == z) {
					b++;
					c += rand()%2 ? 1 : -1;
				}
			}
		} else if (c != cc) {
			if (c < cc) {
				c++;
				if (a == x && b == y && c == z) {
					c--;
					a += rand()%2 ? 1 : -1;
				}
			}
			else {
				c--;
				if (a == x && b == y && c == z) {
					c++;
					a += rand()%2 ? 1 : -1;
				}
			}
		}

		if (x != xx) {
			if (x < xx) {
			   	x++;
				if (a == x && b == y && c == z) {
					if (a == aa && b == bb && c == cc) {
						a++;
					}
					else {
						x--;
					}
				}
			}
			else {
				x--;
				if (a == x && b == y && c == z) {
					if (a == aa && b == bb && c == cc) {
						a--;
					}
					else {
						x++;
					}
				}
			}
		} else if (y != yy) {
			if (y < yy) {
				y++;
				if (a == x && b == y && c == z) {
					if (a == aa && b == bb && c == cc) {
						b++;
					}
					else {
						y--;
					}
				}
			}
			else {
				y--;
				if (a == x && b == y && c == z) {
					if (a == aa && b == bb && c == cc) {
						b--;
					}
					else {
						y++;
					}
				}
			}
		} else if (z != zz) {
			if (z < zz) {
				z++;
				if (a == x && b == y && c == z) {
					if (a == aa && b == bb && c == cc) {
						c++;
					}
					else {
						z--;
					}
				}
			}
			else {
				z--;
				if (a == x && b == y && c == z) {
					if (a == aa && b == bb && c == cc) {
						c--;
					}
					else {
						z++;
					}
				}
			}
		}
	}
	cout << "(" << a << " " << b << " " << c << ")" << " " << "(" << x << " " << y << " " << z << ")" << nl;

	return 0;
}

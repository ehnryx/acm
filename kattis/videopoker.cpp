#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_cxx;
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

typedef pair<char,char> pcc;
vector<char> RANK = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
vector<char> SUIT = {'c','d','h','s'};

int s[9];

ld replace(const vector<pcc>& v, const vector<pcc>& p, int bm) {
	ld tot = (ld)47*46*45*44*43/120;
	ld sum = 0;
	for(int a=0;a<47;a++) {
		for(int b=0;b<a;b++) {
			for(int c=0;c<b;c++) {
				for(int d=0;d<c;d++) {
					for(int e=0;e<d;e++) {
					}
				}
			}
		}
	}
	return sum / tot;
}

ld solve(const vector<pcc>& v) {
	vector<pcc> p;
	for(char rank:RANK) {
		for(char suit:SUIT) {
			pcc cur(rank,suit);
			if(v.find(cur)!=-1) {
				p.push_back(cur);
			}
		}
	}

	ld best = 0;
	for(int bm=0;bm<1<<5;bm++) {
		best = max(best, replace(v,p,bm));
	}
	return best;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	for(int i=0;i<9;i++) {
		cin>>s[i];
	}

	int T;
	cin>>T;
	while(T--) {
		vector<pcc> cards;
		for(int i=0;i<5;i++) {
			char rank, suit;
			cin>>rank>>suit;
			cards.push_back(make_pair(rank,suit));
		}
		cout<<solve(cards)<<nl;
	}

	return 0;
}

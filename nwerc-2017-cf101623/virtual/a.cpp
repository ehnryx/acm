#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int MAXN = 1e6+10;
int n, h[MAXN];

vector<int> e[MAXN];
bool don[MAXN];
bool used[MAXN];


int cntarr[MAXN];
int uniq[MAXN];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n;
	set<int> vals;
	for(int i=0;i<n;i++) {
		cin >> h[i];
		vals.insert(h[i]);
	}
	map<int,int> rmap;
	vector<int> st;
	for(int i:vals) {
		rmap[i] = st.size();
		st.push_back(i);
	}
	for(int i=0;i<n;i++) {
		h[i] = rmap[h[i]];
		cntarr[h[i]]++;
	}
	// compressed!
	// now get blocks
	vector<pair<int,int>> blocks;
	int cnt = 1;
	//for(int i=0;i<n;i++) cerr << h[i] << " "; cerr <<endl;
	for(int i=1;i<n;i++) {
		if (h[i]==h[i-1]) cnt++;
		else {
			blocks.emplace_back(h[i-1], cnt);
			cnt = 1;
		}
	}
	blocks.emplace_back(h[n-1], cnt);
	int k = blocks.size();
	int ans = k-1;
	//for(auto &p: blocks) { cerr << p.first << " " << p.second <<endl; }
	// merge things forward that are all the thing
	for(int i=0;i<k-1;i++) {
		//cerr<< st[blocks[i].first] << " " << cntarr[blocks[i].first]  <<endl;
		if (blocks[i].second == cntarr[blocks[i].first] 
			&& blocks[i].first+1 == blocks[i+1].first) { // merge forward always possible
			//cerr << "MERGE " << st[blocks[i].first] << " " << st[blocks[i].first+1] <<endl;
			used[i] = used[i+1] = true;
			ans--;
		}
		else if (used[i]) {
			continue;
		}
		else if (blocks[i+1].second == cntarr[blocks[i+1].first]
				&& blocks[i].first+1 == blocks[i+1].first) { // merge forward to done thing
			//cerr << "MERGE " << st[blocks[i].first] << " " << st[blocks[i].first+1] <<endl;
			used[i] = used[i+1] = 1;
			ans--;
		}
	}
	for(int i=0;i<k;i++) {
		if (blocks[i].second == cntarr[blocks[i].first]) uniq[blocks[i].first] = 1;
	}
	int lasti=0;
	for(int i=0;i<k-1;i++) {
		if (!used[i] && !used[i+1] && blocks[i].first+1 == blocks[i+1].first) { // can merge forward
		}
		else {
			if (lasti!=i) {
				// merge from i to lastint
				//cerr << " merge add "<< blocks[lasti].first << " " << i-lasti <<endl;
				e[blocks[lasti].first].push_back(i-lasti);
			}
			lasti = i+1;
		}
	}
	if (lasti!=k-1) {
		// merge from i to lastint
		//cerr << " merge add "<< blocks[lasti].first << " " << k-1-lasti <<endl;
		e[blocks[lasti].first].push_back(k-lasti-1);
	}
	multiset<int> pqe, pqo;
	for(int i=0;i<(int)st.size();i++) {
		//cerr << "@ " << i <<endl;
		//cerr << st[i] << " " << uniq[i] <<endl;
		for(int val:e[i]) {
			//cerr << "adding " << val+i <<endl;
			if (val%2) pqo.insert(val+i);
			else pqe.insert(val+i);
		}
		while(!pqe.empty() && *pqe.begin()<=i) { pqe.erase(pqe.begin()); }
		while(!pqo.empty() && *pqo.begin()<=i) { pqo.erase(pqo.begin()); }
		if (!pqo.empty()) {
			//cerr << "merge odd " << i <<endl;
			ans--;
			int tt = *pqo.begin();
			pqo.erase(pqo.begin());
			int diff = 2;
			if (uniq[i+1]) diff = 1;
			if (tt-i-diff>0) {
				e[i+diff].push_back(tt-i-diff);
			}
		}
		else if (!pqe.empty()) {
			//cerr << "merge even " << i <<endl;
			ans--;
			int tt = *pqe.rbegin();
			pqe.erase(prev(pqe.end()));
			int diff = 2;
			if (uniq[i+1]) diff = 1;
			if (tt-i-diff>0) {
				e[i+diff].push_back(tt-i-diff);
			}
		}
		pqe.swap(pqo);
	}
	/*
	for(int i=0;i<(int)st.size();i++) { // iterate over numbers
		if (e1[i]) {
			//cerr << "merge " << st[i] << " "<< st[i+1] <<endl;
			ans--;
			e1[i+1]+=e2[i];
		}
		else if (e2[i]) {
			//cerr << "merge " << st[i] << " "<< st[i+1] <<endl;
			ans--;
			e1[i+1]+=e2[i]-1;
		}
	}
	*/
	cout << ans <<endl;


	return 0;
}

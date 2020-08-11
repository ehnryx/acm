#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0);
	while(!cin.eof()) {
		int x, N; 
		cin >> x;
		if(cin.eof()) break;
		cin >> N;
		x *= 1e7;
		map<int, int> m;
		for(int i=0;i<N;++i) {
			int v;
			cin >> v;
			if(!m.count(v)) {
				m[v] = 0;
			}
			++ m[v];
		}
		bool found_ans = false;
		for(auto it = m.begin(); it != m.end() && !found_ans; ++it) {
			if(m.count(x-it->first) && (x-it->first != it->first || it->second > 1)) {
				cout << "yes " << it->first << " " << x-it->first << "\n";
				found_ans=  true;
			}
		}
		if(!found_ans) {
			cout << "danger" << "\n";
		}
	}
	return 0;
}

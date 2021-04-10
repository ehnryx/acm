#include <bits/stdc++.h>
using namespace std;

main() {
  string s, t;
  cin >> s;
  map<int,int> f;
  for(int c : s) f[c]++;
  vector<int> b;
  for(auto [v, c] : f) if(c % 2) b.push_back(v);
  if(size(b) > 1) cout << "NO SOLUTION";
  else {
    for(auto [v, c] : f) if(c % 2 < 1) t += string(c/2, v);
    cout << t << (size(b) ? string(f[b[0]], b[0]) : "") << string(rbegin(t), rend(t));
  }
}

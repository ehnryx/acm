#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> g() {
  if(!n--) return {""};
  vector<string> a,b;
  for(auto s : g()) a.push_back("0"+s), b.push_back("1"+s);
  a.insert(end(a), rbegin(b), rend(b));
  return a;
}

main() {
  cin >> n;
  for(auto s : g()) cout << s << '\n';
}

#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/number/int_base10.h"

constexpr char nl = '\n';
using ll = long long;
using Int = int_base10;

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  //ll n = 200;
  //if (argc > 1) n = atoll(argv[1]);

  set<Int> ans;
  for(Int a=1; a<10'000; a+=1) {
    bool ok = true;
    set<char> cur;
    for(char d : a.str()) ok &= d && cur.insert(d).second;
    if(!ok) continue;
    for(Int b=1; b<10'000 && 2*b.str().size() + 2*a.str().size() <= 10; b+=1) {
      Int c = a * b;
      vector<char> all;
      for(char d : a.str()) all.push_back(d);
      for(char d : b.str()) all.push_back(d);
      for(char d : c.str()) all.push_back(d);
      sort(begin(all), end(all));
      if(all.front() != '0' && all.size() == 9 && unique(begin(all), end(all)) - begin(all) == 9) {
        ans.insert(c);
      }
    }
  }
  cout << ans.size() << nl;
  Int sum = 0;
  for(Int it : ans) {
    sum += it;
  }
  cout << sum << nl;

  return 0;
}

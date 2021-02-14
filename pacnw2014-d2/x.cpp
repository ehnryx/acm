#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';


int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T;
  cin >> T;
  while(T--) {
    string s;
    cin >> s;

    int dot = s.find('.');
    if(dot == -1) {
      cout << stoi(s) << "\"" << nl;
      continue;
    }

    int num = stoi("0" + s.substr(0, dot));
    s = s.substr(dot + 1);
    if(s.empty() || stoi(s) == 0) {
      cout << num << "\"" << nl;
      continue;
    }
    int dec = stoi(s);

    long double tens = pow(10, s.size());
    string ans;
    for(int d=1; d<=7 && ans.empty(); d++) {
      int bot = 1<<d;
      for(int top=1; top<bot; top++) {
        long double approx = tens * top / bot;
        if(round(approx) == dec || floor(approx) == dec || ceil(approx) == dec) {
          ans = to_string(top) + "/" + to_string(bot);
          break;
        }
      }
    }
    assert(!ans.empty());

    if(num) cout << num << " ";
    cout << ans << "\"" << nl;
  }

  return 0;
}

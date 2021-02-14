#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

int to_num(string s) {
  if(s[0] == '-' && s[1] == '0') throw new exception;
  if(s.size() > 1 && s[0] == '0') throw new exception;
  return stoi(s);
}

bool valid(string s, char d) {
  transform(s.begin(), s.end(), s.begin(), [=](char c) {
    return c == '?' ? d : c;
  });
  int eq = s.find('=');
  for(int i=1; i<s.size(); i++) {
    if(!isdigit(s[i])) {
      try {
        int a = to_num(s.substr(0, i));
        int b = to_num(s.substr(i + 1, eq - i - 1));
        int c = to_num(s.substr(eq + 1));
        if(s[i] == '+') return a + b == c;
        if(s[i] == '-') return a - b == c;
        if(s[i] == '*') return (long long) a * b == c;
      } catch(...) {
        return false;
      }
    }
  }
  assert(false);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n;
  cin >> n;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    set<char> have(s.begin(), s.end());
    bool done = false;
    for(int d=0; d<=9 && !done; d++) {
      if(have.count(d + '0')) continue;
      if(valid(s, d + '0')) {
        cout << d << nl;
        done = true;
      }
    }
    if(!done) {
      cout << -1 << nl;
    }
  }

  return 0;
}

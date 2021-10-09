#include <bits/stdc++.h>
using namespace std;

string s;
int n;

int mem[1222][1222];
int nd[1222][1222];

bool dp(int i, int j) {
  if (mem[i][j]!=-1) return mem[i][j];
  if (i==(int)s.size()) return j==0;
  bool ans = false;
  if (s[i] != '?') {
    nd[i][j] = s[i]-'0';
    ans = dp(i+1, (j*10+nd[i][j])%n);
  }
  else {
    for(int d=0;d<10;d++) {
      if (d==0 && i==0) continue; // no leading 0
      if (dp(i+1, (j*10+d)%n)) {
        nd[i][j] = d;
        ans = true;
        break;
      }
    }
  }
  //cerr << i << " " << j << " " << ans << endl;
  return mem[i][j] = ans;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  cin >> s >> n;
  memset(mem,-1,sizeof mem);
  memset(nd,-1,sizeof nd);
  if (!dp(0,0)) cout << "*" <<endl;
  else {
    int curres = 0;
    for(int i=0;i<(int)s.size();i++) {
      cout << nd[i][curres];
      curres = (curres*10+nd[i][curres])%n;
    }
    cout << endl;
  }
  return 0;
}

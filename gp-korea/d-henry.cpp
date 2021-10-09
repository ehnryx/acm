#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using vi = vector<int>;

const char nl = '\n';

const int N = 1e6+1;
int jump[N][26];
int last[26];
string s;

bool valid(int st, int len) {
  int x = st+len-1;
  for(int i=0; i<len; i++) {
    x = jump[x][s[st+i]-'a'];
    if(x == -1) return false;
  }
  return true;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  cin >> s;

  int n = s.size();
  reverse(s.begin(), s.end());

  memset(last, -1, sizeof last);
  for(int i=n-1; i>=0; i--) {
    for(int j=0; j<26; j++) {
      jump[i][j] = last[j];
    }
    last[s[i]-'a'] = i;
  }

  int ans = 0;
  for(int i=0; i<n; ) {
    int r=1;
    while(i+r<=n && valid(i,r)) {
      r *= 2;
    }
    int l = r/2;
    while(l < r) {
      int m = (l+r+1)/2;
      if(i+m<=n && valid(i,m)) {
        l = m;
      } else {
        r = m-1;
      }
    }
    if(r == 0) {
      i++;
    } else {
      i += r;
    }
    ans++;
  }
  cout << ans << nl;

  return 0;
}

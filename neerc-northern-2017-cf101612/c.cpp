#include <bits/stdc++.h>
using namespace std;

#define FILENAME "consonant"

typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int N = 26;
int cnt[N][N];
bool vow[N+128];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  if(fopen(FILENAME ".in", "r")) {
    freopen(FILENAME ".in", "r", stdin);
    freopen(FILENAME ".out", "w", stdout);
  }

  vow['a'] = true;
  vow['e'] = true;
  vow['i'] = true;
  vow['o'] = true;
  vow['u'] = true;
  vow['w'] = true;
  vow['y'] = true;

  map<char,int> id;
  for(int a='a',i=0; a!='z'+1; a++) {
    if(vow[a]) continue;
    id[a] = i++;
  }

  string s;
  cin >> s;
  int n = s.size();
  for(int i=1; i<n; i++) {
    if(!vow[s[i]] && !vow[s[i-1]]) {
      cnt[id[s[i]]][id[s[i-1]]]++;
    }
  }

  int best = -1;
  int ans = -1;
  for(int bm=0; bm<1<<19; bm++) {
    int cur = 0;
    for(int i=0; i<19; i++) {
      for(int j=0; j<19; j++) {
        if((bm>>i&1) ^ (bm>>j&1)) {
          cur += cnt[i][j];
        }
      }
    }
    if(cur > best) {
      best = cur;
      ans = bm;
    }
  }
  assert(ans != -1);

  for(int i=0; i<n; i++) {
    if(ans>>id[s[i]] & 1) {
      cout << (char)toupper(s[i]);
    } else {
      cout << s[i];
    }
  }
  cout << nl;

  return 0;
}

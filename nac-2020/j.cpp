#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;

typedef __int128 lll;
typedef long long ll;
typedef long double ld;
const char nl = '\n';
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int five = 0b11111;
const lll size1 = (lll)1<<(20*5);
const lll ones1 = (lll)1<<(21*5);

int get_size(const lll& v) {
  return v >> (20*5) & five;
}

int get_ones(const lll& v) {
  return v >> (21*5) & five;
}

void push(lll& v, int k) {
  if(k == 1) {
    v += ones1;
  } else {
    v += (lll)k << (get_size(v)*5);
    v += size1;
  }
}

void pop(lll& v, int k) {
  if(k == 1) {
    v -= ones1;
  } else {
    v -= size1;
    v -= (lll)k << (get_size(v)*5);
  }
}

int n, m;
set<lll> cur, nxt;
int opt, part;

lll canonize(const lll& v) {
  vector<char> s;
  int ones = get_ones(v);
  for(int i=0; i<get_size(v); i++) {
    int a = v >> (i*5) & five;
    if(a == 1) {
      ones++;
    } else {
      s.push_back(a);
    }
  }
  sort(s.begin(), s.end());

  lll res = 0;
  res |= ones * ones1;
  res |= s.size() * size1;
  for(int i=0; i<s.size(); i++) {
    res |= (lll)s[i] << (i*5);
  }
  opt = max(opt, ones);
  part = max(part, (int)s.size());
  return res;
}

set<pair<lll,int>> seen;
void split(lll& v, int i, int b, int left) {
  if(b > left) return;
  if(i < 0 || b == 0 || b == left) {
    nxt.insert(canonize(v));
    return;
  }
  if(seen.count(make_pair(v, i|b<<7))) return;
  seen.insert(make_pair(v, i|b<<7));

  int sz = v >> (i*5) & five;
  split(v, i-1, b, left-sz);
  if(b >= sz) split(v, i-1, b-sz, left-sz);
  for(int s=min(sz/2,b); s>=1; s--) {
    v -= (lll)s << (i*5);
    push(v, s);
    split(v, i-1, b-s, left-sz);
    if(sz-s != s && sz-s<=b) split(v, i-1, b-(sz-s), left-sz);
    pop(v, s);
    v += (lll)s << (i*5);
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  cin >> n >> m;

  int val[m];
  int sum = 0;
  for(int i=0; i<m; i++) {
    cin >> val[i];
    sum += min(val[i], n-val[i]);
  }

  cur.insert(n | size1);
  for(int i=0; i<m; i++) {
    //cerr<<"before "<<i<<" -> "<<cur.size()<<nl;
    int a = min(val[i], n-val[i]);
    nxt.clear();
    seen.clear();
    for(lll it : cur) {
      split(it, get_size(it)-1, a, n);
    }
    cur = move(nxt);

    if(opt == n) {
      cout << n << nl;
      return 0;
    }
    for(auto it=cur.begin(); it!=cur.end(); ) {
      int sz = get_size(*it) + get_ones(*it);
      if(sz < part-1) {
        it = cur.erase(it);
      } else {
        it++;
      }
    }
  }

  cout << opt << nl;

  return 0;
}

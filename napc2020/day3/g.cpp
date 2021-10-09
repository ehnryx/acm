#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const int INF = 0x3f3f3f3f;

const int N = 3e5 + 7;
ll init[N], ans[N];
deque<int> block[N];
int idx[N], ins[N];

int dsu[N];
int find(int i) {
  if(dsu[i] == -1) return i;
  return dsu[i] = find(dsu[i]);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  memset(dsu, -1, sizeof dsu);

  int n, m;
  cin >> n >> m;
  init[0] = INFLL;
  init[1] = -INFLL;
  for(int i=0; i<n; i++) {
    cin >> init[2+i];
  }
  init[2+n] = -INFLL;
  init[2+n+1] = INFLL;
  for(int i=0; i<=n+2; i++) {
    ans[i] = init[i+1] - init[i];
  }

  int bid = 0;
  int curval = 0;
  for(int i=0; i<=n+2; i++) {
    if(ans[i] > 0) {
      if(curval >= 0) {
        block[bid].push_back(i);
      } else {
        block[++bid].push_back(i);
      }
      idx[i] = bid;
      curval = ans[i];
    } else if(ans[i] < 0) {
      if(curval <= 0) {
        block[bid].push_back(i);
      } else {
        block[++bid].push_back(i);
      }
      idx[i] = bid;
      curval = ans[i];
    }
  }

  // value -> id
  set<pair<ll,int>> spos, sneg, lpos, lneg, rpos, rneg;
  set<int> sposx, snegx, lposx, lnegx, rposx, rnegx;
  ll sposv, snegv, lposv, lnegv, rposv, rnegv;
  sposv = snegv = lposv = lnegv = rposv = rnegv = 0;
  for(set<int>* it : {&sposx, &snegx, &lposx, &lnegx, &rposx, &rnegx}) {
    it->insert(INF);
    it->insert(-INF);
  }

  // init values
  for(int i=0; i<=bid; i++) {
    int l = block[i].front();
    int r = block[i].back();
    if(l == r) {
      if(ans[r] > 0) {
        spos.insert(make_pair(ans[r], r));
        sposx.insert(r);
      } else {
        sneg.insert(make_pair(ans[r], r));
        snegx.insert(r);
      }
      ins[r] = ans[r];
    } else {
      if(ans[l] > 0) {
        lpos.insert(make_pair(ans[l], l));
        lposx.insert(l);
      } else {
        lneg.insert(make_pair(ans[l], l));
        lnegx.insert(l);
      }
      ins[l] = ans[l];
      if(ans[r] > 0) {
        rpos.insert(make_pair(ans[r], r));
        rposx.insert(r);
      } else {
        rneg.insert(make_pair(ans[r], r));
        rnegx.insert(r);
      }
      ins[r] = ans[r];
    }
  }

  string dir;
  cin >> dir;

  for(int i=0; i<m; i++) {
    snegv++;
    sposv--;

    if(dir[i] == 'A') {
      // from the left
      lnegv++;
      lposv--;

      while(!lneg.empty() && lneg.rbegin()->first + lnegv == 0) {
        int j = lneg.rbegin()->second;
        lneg.erase(prev(lneg.end()));
        lnegx.erase(j);
        idx[j] = find(idx[j]);
        block[idx[j]].pop_front();
        ans[j] = 0;
        int k = block[idx[j]].front();
        if(block[idx[j]].size() == 1) {
          auto it = rneg.find(make_pair(ins[k], k));
          assert(it != rneg.end());
          rneg.erase(it);
          rnegx.erase(k);
          ins[k] = ins[k] + rnegv - snegv;
          sneg.insert(make_pair(ins[k], k));
          snegx.insert(k);
        } else {
          ins[k] = ans[k] - lnegv;
          lneg.insert(make_pair(ins[k], k));
          lnegx.insert(k);
        }
      }

      while(!lpos.empty() && lpos.begin()->first + lposv == 0) {
        int j = lpos.begin()->second;
        lpos.erase(lpos.begin());
        lposx.erase(j);
        idx[j] = find(idx[j]);
        block[idx[j]].pop_front();
        ans[j] = 0;
        int k = block[idx[j]].front();
        if(block[idx[j]].size() == 1) {
          auto it = rpos.find(make_pair(ins[k], k));
          assert(it != rpos.end());
          rpos.erase(it);
          rposx.erase(k);
          ins[k] = ins[k] + rposv - sposv;
          spos.insert(make_pair(ins[k], k));
          sposx.insert(k);
        } else {
          ins[k] = ans[k] - lposv;
          lpos.insert(make_pair(ins[k], k));
          lposx.insert(k);
        }
      }
    }

    else {
      // from the right
      rnegv++;
      rposv--;

      while(!rneg.empty() && rneg.rbegin()->first + rnegv == 0) {
        int j = rneg.rbegin()->second;
        rneg.erase(prev(rneg.end()));
        rnegx.erase(j);
        idx[j] = find(idx[j]);
        block[idx[j]].pop_back();
        ans[j] = 0;
        int k = block[idx[j]].back();
        if(block[idx[j]].size() == 1) {
          auto it = lneg.find(make_pair(ins[k], k));
          assert(it != lneg.end());
          lneg.erase(it);
          lnegx.erase(k);
          ins[k] = ins[k] + lnegv - snegv;
          sneg.insert(make_pair(ins[k], k));
          snegx.insert(k);
        } else {
          ins[k] = ans[k] - rnegv;
          rneg.insert(make_pair(ins[k], k));
          rnegx.insert(k);
        }
      }

      while(!rpos.empty() && rpos.begin()->first + rposv == 0) {
        int j = rpos.begin()->second;
        rpos.erase(rpos.begin());
        rposx.erase(j);
        idx[j] = find(idx[j]);
        block[idx[j]].pop_back();
        ans[j] = 0;
        int k = block[idx[j]].back();
        if(block[idx[j]].size() == 1) {
          auto it = lpos.find(make_pair(ins[k], k));
          assert(it != lpos.end());
          lpos.erase(it);
          lposx.erase(k);
          ins[k] = ins[k] + lposv - sposv;
          spos.insert(make_pair(ins[k], k));
          sposx.insert(k);
        } else {
          ins[k] = ans[k] - rposv;
          rpos.insert(make_pair(ins[k], k));
          rposx.insert(k);
        }
      }
    }

    vector<tuple<int,int,bool>> merges;
    while(!sneg.empty() && sneg.rbegin()->first + snegv == 0) {
      int j = sneg.rbegin()->second;
      sneg.erase(prev(sneg.end()));
      snegx.erase(j);
      idx[j] = find(idx[j]);
      block[idx[j]].pop_back();
      ans[j] = 0;
      int right = min(*lposx.upper_bound(j), *sposx.upper_bound(j));
      int left = max(*prev(rposx.lower_bound(j)), *prev(sposx.lower_bound(j)));
      merges.push_back(make_tuple(left, right, true)); // pos
    }
    while(!spos.empty() && spos.begin()->first + sposv == 0) {
      int j = spos.begin()->second;
      spos.erase(spos.begin());
      sposx.erase(j);
      idx[j] = find(idx[j]);
      block[idx[j]].pop_back();
      ans[j] = 0;
      int right = min(*lnegx.upper_bound(j), *snegx.upper_bound(j));
      int left = max(*prev(rnegx.lower_bound(j)), *prev(snegx.lower_bound(j)));
      merges.push_back(make_tuple(left, right, false)); // neg
    }

    for(const auto& [left, right, pos] : merges) {
      int l = find(idx[left]);
      int r = find(idx[right]);
      if(block[l].empty() || block[r].empty()) continue;
      assert(left == block[l].back());
      assert(right == block[r].front());

      bool addleft = false;
      bool addright = false;
      if(block[l].size() == 1) {
        addleft = true;
        if(pos) {
          ans[left] = ins[left] + sposv;
          auto it = spos.find(make_pair(ins[left], left));
          assert(it != spos.end());
          spos.erase(it);
          sposx.erase(left);
        } else {
          ans[left] = ins[left] + snegv;
          auto it = sneg.find(make_pair(ins[left], left));
          assert(it != sneg.end());
          sneg.erase(it);
          snegx.erase(left);
        }
      } else {
        if(pos) {
          ans[left] = ins[left] + rposv;
          auto it = rpos.find(make_pair(ins[left], left));
          assert(it != rpos.end());
          rpos.erase(it);
          rposx.erase(left);
        } else {
          ans[left] = ins[left] + rnegv;
          auto it = rneg.find(make_pair(ins[left], left));
          assert(it != rneg.end());
          rneg.erase(it);
          rnegx.erase(left);
        }
      }

      if(block[r].size() == 1) {
        addright = true;
        if(pos) {
          ans[right] = ins[right] + sposv;
          auto it = spos.find(make_pair(ins[right], right));
          assert(it != spos.end());
          spos.erase(it);
          sposx.erase(right);
        } else {
          ans[right] = ins[right] + snegv;
          auto it = sneg.find(make_pair(ins[right], right));
          assert(it != sneg.end());
          sneg.erase(it);
          snegx.erase(right);
        }
      } else {
        if(pos) {
          ans[right] = ins[right] + lposv;
          auto it = lpos.find(make_pair(ins[right], right));
          assert(it != lpos.end());
          lpos.erase(it);
          lposx.erase(right);
        } else {
          ans[right] = ins[right] + lnegv;
          auto it = lneg.find(make_pair(ins[right], right));
          assert(it != lneg.end());
          lneg.erase(it);
          lnegx.erase(right);
        }
      }

      // merge left and right
      if(block[l].size() < block[r].size()) {
        while(!block[l].empty()) {
          block[r].push_front(block[l].back());
          block[l].pop_back();
        }
        dsu[l] = r;
      } else {
        while(!block[r].empty()) {
          block[l].push_back(block[r].front());
          block[r].pop_front();
        }
        dsu[r] = l;
      }

      if(addleft) {
        if(pos) {
          ins[left] = ans[left] - lposv;
          lpos.insert(make_pair(ins[left], left));
          lposx.insert(left);
        } else {
          ins[left] = ans[left] - lnegv;
          lneg.insert(make_pair(ins[left], left));
          lnegx.insert(left);
        }
      }

      if(addright) {
        if(pos) {
          ins[right] = ans[right] - rposv;
          rpos.insert(make_pair(ins[right], right));
          rposx.insert(right);
        } else {
          ins[right] = ans[right] - rnegv;
          rneg.insert(make_pair(ins[right], right));
          rnegx.insert(right);
        }
      }
    }
  }

  ll cur = INFLL;
  for(int i=0; i<=n; i++) {
    cur += ans[i];
    if(i>0) {
      cout << cur << " ";
    }
  }
  cout << nl;

  return 0;
}

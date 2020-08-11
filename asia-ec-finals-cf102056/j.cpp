#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

const int ALPHA_SIZE=26; char _A='a', _$=_A+ALPHA_SIZE;
int DIM1=(int)sqrt(ALPHA_SIZE+1), DIM2=ceil((ALPHA_SIZE+1.0)/DIM1);
struct edge { typedef vector<vector<edge*>> vve;
	string& s; unsigned int begin, end; vve child; edge *sfxlink, *parent;
	edge(string& ss, int b=0, int e=0):s(ss){begin=b,end=e,sfxlink=parent=nullptr;}
	inline edge* get_child(char c) { int id=c-_A;
		if (!child.size() || !child[id/DIM2].size()) return nullptr;
		return child[id/DIM2][id%DIM2]; }
	edge* set_child(char c, edge* chld){ int id=c-_A;
		if (!child.size()) child.resize(DIM1);
		if (!child[id/DIM2].size()) child[id/DIM2].resize(DIM2);
		chld->parent=this; return child[id/DIM2][id%DIM2] = chld; }
	~edge() {
		for (auto i=0u; i < child.size(); i++) for (auto j = 0u; j<child[i].size(); j++)
			delete child[i][j];
		child.clear(); } };
void get_suffix(edge *&e, unsigned int &ep) {
	if ((e = e->parent)->sfxlink) e = e->sfxlink, ep += (e->end - e->begin);
	else ep--; }
void walk_down(edge *&e, unsigned int &ep, unsigned int sp) {
	while (ep > e->end - e->begin) {
		ep -= (e->end - e->begin);
		e = e->get_child(e->s[sp - ep]); } }
edge *build_tree(string& s) {
	edge *t = new edge(s), *cur=t->set_child(s[0], new edge(s, 0, 1 << 30));
	for (auto phase=1u, pos=1u, f=1u; phase < s.size(); phase++, pos++) {
		edge **need_sfxlink=nullptr;
		while (true) {
			if (f) get_suffix(cur, pos);
			f = 1; walk_down(cur, pos, phase);
			if (cur->end == (1 << 30) && pos + cur->begin == phase) continue;
			if ((cur->end - cur->begin > pos && s[cur->begin + pos] == s[phase]) ||
				(cur->end - cur->begin == pos && cur->get_child(s[phase]))) {
					if (need_sfxlink) *need_sfxlink = cur, need_sfxlink = nullptr;
					f = 0; break; }
			if (cur->end - cur->begin > pos) {
				edge *parent = cur->parent;
				edge *oedge = new edge(s, cur->begin, cur->begin + pos);
				if (need_sfxlink) *need_sfxlink = oedge, need_sfxlink = nullptr;
				cur->begin = oedge->end;
				oedge->set_child(s[oedge->end], cur);
				need_sfxlink = &oedge->sfxlink;
				parent->set_child(s[oedge->begin], oedge);
				oedge->set_child(s[phase], new edge(s, phase, 1 << 30));
				cur = oedge;
			} else {
				cur->set_child(s[phase], new edge(s, phase, 1 << 30));
				if (need_sfxlink) *need_sfxlink = cur, need_sfxlink = nullptr;
			}
			if (cur->parent == nullptr) { f = 0; break; } } }
	return t; }
edge *get_state(edge *tree, unsigned int &pos, char ch) {
	if (!tree) return nullptr;
	if (pos < tree->end) {
		if (pos < tree->s.size() && ch == tree->s[pos]) pos++;
		else tree = nullptr;
	} else {
		if (tree->get_child(ch))
			tree = tree->get_child(ch), pos = tree->begin + 1;
		else tree = nullptr;
	} return tree; }

int n;
const ld EPS = 1e-11;

ld dfs(edge* node, bool root=0) {
	vector<ld> childs;
	for (int i = _A; i <= _$; i++) {
		if (node->get_child(i)) {
			edge* e = node->get_child(i);
			childs.push_back(dfs(e) + min((int)e->end, n) - (int)e->begin);
		}
	}
	if (childs.empty()) {
		return 0;
	}
	ld wgt = 0;
	for (ld i : childs) {
		if (i < EPS) {
			if (root) continue;
			return 0;
		}
		wgt += 1/i;
	}
	return 1 / wgt;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int T; cin >> T;
	while (T--) {
		string s; cin >> s;
		n = s.size();
		s.push_back(_$);
		edge* tree = build_tree(s);
		cout << fixed << setprecision(10) << dfs(tree, 1) << nl;
	}

	return 0;
}

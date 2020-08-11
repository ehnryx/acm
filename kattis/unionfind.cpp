#include <bits/stdc++.h>
using namespace std;

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int &x) {
	static char c; x = 0;
	for (c = get(); c < '0' || c > '9'; c = get());
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

const int N = 1e6+1;
int root[N];
int find(int i) {
	if(root[i]==-1) return i;
	return root[i]=find(root[i]);
}
void link(int i, int j) {
	if(find(i)!=find(j)) {
		root[find(j)]=find(i);
	}
}

int main() {
	memset(root,-1,sizeof root);

	int n,m;
	read(n);read(m);
	for(int i=0;i<m;i++) {
		char t; int a,b;
		readchar(t);read(a);read(b);
		if(t=='?') {
			if(find(a)==find(b)) { putchar('y');putchar('e');putchar('s'); }
			else { putchar('n');putchar('o'); }
			putchar('\n');
		} else link(a,b);
	}

	return 0;
}

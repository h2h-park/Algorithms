//https://www.acmicpc.net/problem/11438

#include <stdio.h>
#include <vector>
#define MAX 100010

std::vector<int> vec[MAX];
int n;
int dep[MAX], par[MAX][30];

void make_tree(int p, int now, int d) {
	int i, s;
	dep[now] = d;
	par[now][0] = p;
	s = vec[now].size();
	for (i = 0; i < s; i++) {
		int chd = vec[now][i];
		if (chd == p) continue;
		make_tree(now, chd, d + 1);
	}
}

void ancestor(void) {
	int i, j;
	for (j = 1; j <= 20; j++) {
		for (i = 1; i <= n; i++) {
			par[i][j] = par[par[i][j - 1]][j - 1];
		}
	}
}

int lca(int x, int y) {
	int i, j;
	if (dep[x] > dep[y]) x ^= y ^= x ^= y;

	for (i = 20; i >= 0; i--) {
		if (dep[y] - dep[x] >= (1 << i)) y = par[y][i];
	}
	if (x == y) return x;
	for (i = 20; i >= 0; i--) {
		if (par[x][i] != par[y][i]) {
			x = par[x][i], y = par[y][i];
			i++;
		}
	}
	return par[x][0];
}

int main(void) {
	int i, a, b;
	scanf("%d", &n);
	for (i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		vec[a].push_back(b);
		vec[b].push_back(a);
	}
	make_tree(0, 1, 1);
	ancestor();
	int q;
	for (scanf("%d", &q); q; q--) {
		scanf("%d %d", &a, &b);
		printf("%d\n", lca(a, b));
	}
	return false;
}
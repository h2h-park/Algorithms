//https://www.acmicpc.net/problem/11266

#include <stdio.h>
#include <vector>
#include <algorithm>
#define MAX 10010

std::vector<int> vec[MAX];
std::vector<int> cut;
int n, m, cnt;
int num[MAX];

int dfs(int now, int par, int root) {
	bool flag = false;

	num[now] = ++cnt;
	int ret = num[now];
	int tmp = 0;

	for (int chd : vec[now]) {
		if (chd == par) continue;
		int low = num[chd];
		if (low == 0) {
			low = dfs(chd, now, root);
			tmp++;
			if (now != root && low >= num[now]) flag = true;
		}
		ret = (ret > low) ? low : ret;
	}

	if (flag || (now == root && tmp >= 2)) cut.push_back(now);
	return ret;
}

int main(void) {
	int i, a, b;
	scanf("%d %d", &n, &m);
	for (i = 1; i <= m; i++) {
		scanf("%d %d", &a, &b);
		vec[a].push_back(b);
		vec[b].push_back(a);
	}

	for (i = 1; i <= n; i++) {
		if (num[i] == 0) dfs(i, 0, i);
	}
	printf("%d\n", cut.size());
	std::sort(cut.begin(), cut.end());
	for (int c : cut) printf("%d ", c);
	return false;
}
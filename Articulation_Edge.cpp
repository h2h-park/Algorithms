//https://www.acmicpc.net/problem/11400

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <utility>
#define MAX 100010

std::vector<int> vec[MAX];
std::vector<std::pair<int, int> > cut;
int n, m, cnt;
int num[MAX];

int dfs(int now, int par) {
	num[now] = ++cnt;
	int ret = num[now];
	
	for (int chd : vec[now]) {
		if (chd == par) continue;
		int low = num[chd];
		if (low == 0) {
			low = dfs(chd, now);
			if (low > num[now]) {
				if (now < chd) cut.push_back({ now, chd });
				else cut.push_back({ chd, now });
			}
		}
		ret = (ret > low) ? low : ret;
	}
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
		if (num[i] == 0) dfs(i, 0);
	}
	printf("%d\n", cut.size());
	std::sort(cut.begin(), cut.end());
	for (auto c : cut) printf("%d %d\n", c.first, c.second);
	return false;
}
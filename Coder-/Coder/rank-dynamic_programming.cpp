/*
	2019.07.25 16:00 - 16:37
	求：n个人排名，允许并列名次，共有多少种排名结果？
	例如：a和b排名，有3种：a>b b>a a=b和b=a算一种

	动态规划 = 递推 + 备忘录
	dp[n][m] n个人 m种排名：
	m == 1, dp[n][1] = 1;	//全部并列，显然只有1种
	m == n, dp[n][n] = n!;	//没有并列的情况，直接全排列
	1<m<n,  dp[n][m] = m * (dp[n-1][m]) + m * (dp[n-1][m-1]);
	//状态转移方程：当n-1个人排完名次之后加入一个人，有两种情况：
	//1>他和某一个或几个人并列，这种情况下之前就已经有m个排名了，他可能和这m种中的任何一种并列；
	//2>他有一个新的名次，这种情况相当于他在m个空档中选择一个，有m种可能。

	answer = dp[n][m] 对 m 求和。

*/
#include <iostream>
#define A 19			//最多人数-1

using namespace std;

__int64 solve(int number)
{
	__int64 dp[A][A];			//dp[n][m] n个人 m种排名
	__int64 ans[A] = { 0 };		//dp[n] n个人排名结果
	__int64 fact[A];			//fact[n] n的阶乘

	// 阶乘
	for (int n = 1; n < A; n++)
		fact[n] = n == 1 ? 1 : fact[n - 1] * n;

	// 动态规划计算
	for(int n = 1; n < A; n++)
		for (int m = 1; m <= n; m++)
		{
			if (m == 1)
				dp[n][m] = 1;
			else if (m == n)
				dp[n][m] = fact[m];
			else
				dp[n][m] = m * (dp[n - 1][m] + dp[n - 1][m - 1]);
		}

	// 对排名求和
	for (int n = 1; n < A; n++)
		for (int m = 1; m <= n; m++)
			ans[n] += dp[n][m];

	// 返回结果
	return ans[number];
}

int main()
{
	int n;		// n个人
	cin >> n;
	cout << solve(n) << endl;

	system("pause");
	return 0;
}
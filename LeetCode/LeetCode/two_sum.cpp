/*	2018.03.14 8:43
	给定一个整数数列，找出其中和为特定值的那两个数（下标）。
示例：
	给定 nums = [2, 7, 11, 15], target = 9
	因为 nums[0] + nums[1] = 2 + 7 = 9
	所以返回 [0, 1]
*/
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Solution 
{
public:
	static vector<int> twoSum(vector<int>& nums, int target) 
	{
		vector<int> result;
		int i, j;
		for (i = 0; i < nums.size(); i++)
			for (j = i + 1; j < nums.size(); j++)
			{
				if (nums.at(i) + nums.at(j) == target)
				{	//数值 
					//result.insert(result.begin(), nums.at(i));
					//result.insert(result.begin() + 1, nums.at(j));
					//下标
					result.insert(result.begin(), i);
					result.insert(result.begin() + 1, j);
					return result;
				}
			}
		if (i >= nums.size())
		{
			cout << "not found!" << endl;
			return nums;
		}
	}
};

int main(void)
{
	cout << "LeedCode..." << endl; //算法
	vector<int> nums = { 2,4,7 };
	vector<int> result;
	int target = 6;
	result.clear();
	result = Solution::twoSum(nums, target);
	for (int i = 0; i < result.size(); i++)
	{
		cout << result.at(i) << endl;
	}
	system("pause");
	return 0;
}

/*运行结果
=====================================================================================================
LeedCode...
0
1
请按任意键继续. . .
======================================================================================================
*/

#include <iostream>
#include <cmath>
#define N 100
using namespace std;
float data[N]; //= {205.30,204.94,205.63,205.24,206.65,204.97,205.36,205.16,205.71,204.70,204.86,205.35,205.21,205.19,205.21,205.32};
float vi[N];                      //data[N]存放测量数据；vi[N]存放残差。
float ave, sumXi, sumVi2, sigma;  //ave为测量数据算数平均值；sumXi为测量数据总和；
float maxAbsVi;                   //sumVi2为残差平方和；sigma为标准偏差；
int n; //= 16;				      //maxAbsVi为残差vi绝对值的最大值；
int flag;						  //n为测量数据个数；flag=1表示存在系统误差。
								 
void Divation();
void ErrorLine();
void ErrorCycle();
/******************************************************************************
函  数：main()主函数
参  数：
返回值：int
功  能：主系统流程，输入数据，显示测量结果
******************************************************************************/
int main()
{
	int i;
	float c;		//消除系统误差的因子
	cout << "请输入要输入数据的个数：";
	cin >> n;
	cout << "请输入" << n << "个数据：\n";
	for (i = 0; i < n; i++)
		cin >> data[i];
	cout << "\n您输入的" << n << "个数据为：\n";
	for (i = 0; i < n; i++)
		cout << data[i] << endl;
	cout << "\n******剔除坏值并求测量值的算数平均值与标准偏差******" << endl;
	Divation();
	cout << "\n******判断有无线性系统误差**************************" << endl;
	ErrorLine();
	cout << "\n******判断有无周期性系统误差************************" << endl;
	ErrorCycle();
	if (flag)					//flag=1表示存在系统误差
	{
		c = sumVi2 / n;			//消除系统误差
		for (i = 0; i < n; i++)
			data[i] += c;
		cout << "\n====================================================\n";
		cout << "消除系统误差后的数据为：\n";
		for (i = 0; i < n; i++)
			cout << data[i] << endl;
		cout << "c=" << c << endl;
		Divation();
	}
	cout << "\n====================================================\n";
	cout << "算数平均值的标准偏差(估计值)为：" << sigma/sqrt(n) << endl;
	cout << "测量结果表达式为：x=" << ave << "±" << 3 * sigma / sqrt(n) << endl;
	return 0;
}
/******************************************************************************
函  数：Divation()
参  数：
返回值：void
功  能：剔除坏值并求测量值的算数平均值与标准偏差
******************************************************************************/
void Divation()
{
	int i, j, k;
	float absVi[N];         //absVi[N]为对Vi[N]取绝对值
	sumXi = 0.0;			   
	sumVi2 = 0.0;
	for (i = 0; i < n; i++)
		sumXi += data[i];
	ave = sumXi / (float)n;
	for (i = 0; i < n; i++)
	{
		vi[i] = data[i] - ave;
		sumVi2 += vi[i] * vi[i];
	}
	sigma = sqrt(sumVi2 / (float)(n - 1));
	for (i = 0; i < n; i++)
		absVi[i] = fabs(vi[i]);
	maxAbsVi = absVi[0];
	j = 0;
	for (i = 0; i < n; i++)
		if (absVi[i] > maxAbsVi)
		{
			maxAbsVi = absVi[i];
			j = i;
		}
	if (maxAbsVi > 3 * sigma)				        //验证|Vi[N]|>=3σ并剔除
	{
		cout << "第" << ++j << "个数据是坏值，\n";
		cout << "坏值=" << data[j-1] << endl;
		for (k = j; k < n; k++)
			data[k - 1] = data[k];
		n = n - 1;
		Divation();
	}
	else
	{
		cout << "算数平均值为：" << ave << endl;
		cout << "标准偏差为：" << sigma << endl;
	}
}
/******************************************************************************
函  数：ErrorLine()
参  数：
返回值：void
功  能：判断有无线性系统误差
		马林科夫判据：|前一半数据-后一半数据|<|最大残差|，存在线性系差
******************************************************************************/
void ErrorLine()
{
	int i;
	float former = 0.0, latter = 0.0, dValue;
	if (n % 2 == 0)
	{
		for (i = 0; i < n / 2; i++)
			former += vi[i];
		for (i = n / 2; i < n; i++)
			latter += vi[i];
	}
	else
	{
		for (i = 0; i < (n-1) / 2; i++)
			former += vi[i];
		for (i = (n-1) / 2; i < n; i++)
			latter += vi[i];
	}
	dValue = former - latter;
	if (fabs(dValue) < maxAbsVi)
	{
		cout << "存在线性系统误差！！" << endl;
		flag = 1;
	}
	else
		cout << "不存在线性系统误差" << endl;
}
/******************************************************************************
函  数：ErrorCycle()
参  数：
返回值：void
功  能：判断有无周期性系统误差
		阿卑-赫梅特判据：|i=0→n-1的残差v[i]*v[i+1]|≥(残差平方和/根号下(n-1))，存在周期系差
******************************************************************************/
void ErrorCycle()
{
	int i;
	float sum = 0.0;
	for (i = 0; i < n - 1; i++)
		sum += vi[i] * vi[i + 1];
	if (fabs(sum) >= (sumVi2 / sqrt(n - 1)))
	{
		cout << "存在周期性系统误差！！" << endl;
		flag = 1;
	}
	else
		cout << "不存在周期性系统误差" << endl;
}
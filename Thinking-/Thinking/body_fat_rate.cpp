/*
	2018.06.27 15:43
	计算体脂率

	体脂率是指人体内脂肪重量在人体总体重中所占的比例，又称体脂百分数，它反映人体内脂肪含量的多少。
计算公式：
	成年女性：
	参数a=腰围（cm）×0.74
	参数b=体重（kg）×0.082+34.89
	体脂肪重量（kg）=a－b
	体脂率=（身体脂肪总重量÷体重）×100%

	成年男性：
	参数a=腰围（cm）×0.74
	参数b=体重（kg）×0.082+44.74
	体脂肪重量（kg）=a－b
	体脂率=（身体脂肪总重量÷体重）×100%

正常值参考范围：
	成年人的体脂率正常范围分别是女性20%～25%，男性15%～18%，若体脂率过高，体重超过正常值的20%以上就可视为肥胖。
	运动员的体脂率可随运动项目而定。一般男运动员为7%～15%，女运动员为12%—25%。

注意事项：
	同时采取饮食疗法与运动疗法来减肥，减少热量摄取，通过运动增加热量消耗，达到减肥的效果。

*/
#include <iostream>
#include <cstdlib>
using namespace std;

enum Sex { Female = 0, Male = 1 };	// 性别：女性，男性
/* 计算体脂率
sex: Female-女性，Male-男性；
waist: 腰围（cm）:
weight: 体重（kg）
返回值：体脂率 */
double BodyFatRate(enum Sex sex, double waist, double weight)
{
	double para_a, para_b;		//参数a，参数b
	double total_fat_weight;	//身体脂肪总重量
	double body_fat_rate;		//体脂率
	para_a = waist * 0.74;
	switch (sex)
	{
	case Female:
		para_b = weight * 0.082 + 34.89;
		break;
	case Male:
		para_b = weight * 0.082 + 44.74;
		break;
	default:
		break;
	}
	total_fat_weight = para_a - para_b;
	body_fat_rate = (total_fat_weight / weight);
	return body_fat_rate;
}

int main()
{
	int value;
	enum Sex sex;			//性别
	double waist, weitght;	//腰围，体重
	double rate;			//体脂率

	cout << "****** 计算体脂率 ******" << endl;
	cout << "性别（女性-0，男性-1） sex = ";
	cin >> value;
	switch (value)
	{
	case 0:	sex = Female; break;
	case 1: sex = Male; break;
	default: break;
	}
	cout << "腰围(cm) waist = ";
	cin >> waist;
	cout << "体重(kg) weight = ";
	cin >> weitght;

	rate = BodyFatRate(sex, waist, weitght);

	cout << endl;
	cout << "体脂率 body fat rate = " << rate << endl << endl;
	switch (sex)
	{
	case Female:
		if (rate < 0.12)
			cout << "您偏瘦，要注意营养哦~" << endl;
		else if (rate >= 0.12 && rate < 0.20)
			cout << "您具有女运动员的潜质，实属女中豪杰！" << endl;
		else if (rate >= 0.20 && rate <= 0.25)
			cout << "您身体正常，继续保持。" << endl;
		else
			cout << "您有点沉，该减肥啦……" << endl;
		break;
	case Male:
		if (rate < 0.07)
			cout << "您偏瘦，要注意营养，多吃蔬菜。" << endl;
		else if (rate >= 0.07 && rate < 0.15)
			cout << "您具有男运动员的潜质，为国夺金，超越博尔特。" << endl;
		else if (rate >= 0.15 && rate <= 0.18)
			cout << "您身体正常，继续保持，早睡早起。" << endl;
		else
			cout << "您的将军肚，可以适当收敛，少食多餐多运动。" << endl;
		break;
	default:
		break;
	}
	cout << endl;
	system("pause");
	return 0;
}

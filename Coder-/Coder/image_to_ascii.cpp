/*
	2020.06.11 18:30
	图片转ASCII字符串
灰度值：
把白色与黑色之间按对数关系分成若干级，称为“灰度等级”。
范围一般从0到255，白色为255，黑色为0，黑白照片也称为灰度图像。

RGB值和灰度值的换算公式：
Gray=(R*30+G*59+B*11)/100，转换后的颜色就是RGB(Gray,Gray,Gray)

字符画：
由若干个字符组成，每个字符去替换原图的一块区域，
有些字符会更接近白色(比如.)，有些会更接近黑色(比如M)，
根据某一块的平均灰度找到最接近的字符即可。
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<easyx.h>

char GetCh(int data);

char ch[] = {
	' ', '`', '.', '^', ',', ':', '~', '"', '<', '!', 
	'c', 't', '+','{', 'i', '7', '?', 'u', '3', '0',
	'p', 'w', '4', 'A', '8', 'D','X', '%', '#', 'H', 
	'W', 'M'
};

char num[] = { 
	0, 5, 7, 9, 13, 15, 17, 19, 21, 23, 25, 27, 29, 
	31, 33, 35, 37, 39, 41,43, 45, 47, 49, 51, 53, 
	55, 59, 61, 63, 66, 68, 70 
};

int main()
{
	IMAGE img;
	loadimage(&img, L"Images/image_to_ascii.bmp");
	initgraph(img.getwidth(), img.getheight());
	putimage(0, 0, &img);
	FILE *fp = fopen("Images/image_to_ascii.txt", "w");//创建文件
	if (!fp) return 0;

	int gray;	//灰度值
	for (int i = 0; i < img.getheight() / 8; ++i)
	{
		for (int j = 0; j < img.getwidth() / 8; ++j)
		{
			gray = 0;
			for (int x = 0; x < 8; ++x)
			{
				for (int y = 0; y < 8; ++y)
				{
					//统计这个方块中的灰度值 求平均
					gray += GetRValue(RGBtoGRAY(getpixel(j * 8 + x, i * 8 + y)));
				}
			}
			gray /= 8 * 8;	//取平均值
			//将灰度值  转换成0~70之间的值  匹配数组中的数字  找到对应字符
			fputc(GetCh(70 - gray * 70 / 255), fp);//0~255之间  --->0~70之间的数字	
		}
		fputc('\n', fp);//每一行加个换行符号
	}
	fclose(fp);
	getchar();
	closegraph();
	return 0;
}

char GetCh(int data)
{
	//快速查找
	int left = 0, right = 31, index;	//num的最大元素下标是31
	while (left < right)
	{
		index = (left + right) / 2;
		if (num[index] == data) return ch[index];		//找到数字 直接返回对应的字符
		else if (num[index] > data) right = index - 1;	//往左找
		else left = index + 1;
	}
	//退出的条件  left>=right
	return ch[left];	//return ch[right]也可以			
}

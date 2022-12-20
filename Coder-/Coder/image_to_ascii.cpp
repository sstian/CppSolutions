/*
	2020.06.11 18:30
	ͼƬתASCII�ַ���
�Ҷ�ֵ��
�Ѱ�ɫ���ɫ֮�䰴������ϵ�ֳ����ɼ�����Ϊ���Ҷȵȼ�����
��Χһ���0��255����ɫΪ255����ɫΪ0���ڰ���ƬҲ��Ϊ�Ҷ�ͼ��

RGBֵ�ͻҶ�ֵ�Ļ��㹫ʽ��
Gray=(R*30+G*59+B*11)/100��ת�������ɫ����RGB(Gray,Gray,Gray)

�ַ�����
�����ɸ��ַ���ɣ�ÿ���ַ�ȥ�滻ԭͼ��һ������
��Щ�ַ�����ӽ���ɫ(����.)����Щ����ӽ���ɫ(����M)��
����ĳһ���ƽ���Ҷ��ҵ���ӽ����ַ����ɡ�
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
	FILE *fp = fopen("Images/image_to_ascii.txt", "w");//�����ļ�
	if (!fp) return 0;

	int gray;	//�Ҷ�ֵ
	for (int i = 0; i < img.getheight() / 8; ++i)
	{
		for (int j = 0; j < img.getwidth() / 8; ++j)
		{
			gray = 0;
			for (int x = 0; x < 8; ++x)
			{
				for (int y = 0; y < 8; ++y)
				{
					//ͳ����������еĻҶ�ֵ ��ƽ��
					gray += GetRValue(RGBtoGRAY(getpixel(j * 8 + x, i * 8 + y)));
				}
			}
			gray /= 8 * 8;	//ȡƽ��ֵ
			//���Ҷ�ֵ  ת����0~70֮���ֵ  ƥ�������е�����  �ҵ���Ӧ�ַ�
			fputc(GetCh(70 - gray * 70 / 255), fp);//0~255֮��  --->0~70֮�������	
		}
		fputc('\n', fp);//ÿһ�мӸ����з���
	}
	fclose(fp);
	getchar();
	closegraph();
	return 0;
}

char GetCh(int data)
{
	//���ٲ���
	int left = 0, right = 31, index;	//num�����Ԫ���±���31
	while (left < right)
	{
		index = (left + right) / 2;
		if (num[index] == data) return ch[index];		//�ҵ����� ֱ�ӷ��ض�Ӧ���ַ�
		else if (num[index] > data) right = index - 1;	//������
		else left = index + 1;
	}
	//�˳�������  left>=right
	return ch[left];	//return ch[right]Ҳ����			
}

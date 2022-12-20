/*  2017.3.22 15:57
	��Ӿ�ؼ�������-�������ĳ������˼��
	��һԲ����Ӿ�أ���������Χ��һ���ι�������Χ��դ����
��Ӿ�ذ뾶�ɼ������룬�������Ϊ3�ף�
�������Ϊ20Ԫ/ƽ���ף�դ���۸�Ϊ35Ԫ/ƽ���ס�
�󣺹�����դ���ļ۸�
*/
#include <iostream>
using namespace std;

const double PI = 3.141592653;  //Բ���ʳ���
const double CorridorPrice = 20.0;  //�����۸�������λ��Ԫ/ƽ����
const double CorridorWidth = 3.0;  //������ȳ�������λ����
const double FencePrice = 35.0;  //դ���۸�������λ��Ԫ/ƽ����

class Circle  //Բ��
{
public:
	Circle(double r = 0.0):radius(r) {}  //��һ��Ĭ�ϲ������캯��
	Circle(const Circle& rcircle) { this->radius = rcircle.radius; }  //���ƹ��캯��
	double getRadius() const { return radius; }  //��ȡ�뾶
	void setRadius(double newRadius) { radius = newRadius; }  //���ð뾶
	double area() const { return PI * radius * radius; }  //Բ���
	double circumference() const { return 2 * PI * radius; }  //Բ�ܳ�
	virtual ~Circle() {}  //����������
private:
	double radius;  //�뾶
};

int main(void)
{
	Circle pool, poolfence;  //���� ��Ӿ�ء���Ӿ��+���� ��Բ����
	double radius;
	cout << "******** Swimming Pool ********" << endl;
	cout << "Please input the radius of swimming pool:\nradius = ";
	cin >> radius;
	pool.setRadius(radius);
	poolfence.setRadius(radius + CorridorWidth);
	//����������
	cout << "Corridor's price is ��" << CorridorPrice * (poolfence.area() - pool.area())<< endl;  
	//���դ�����
	cout << "Fence's circumference is ��" << FencePrice * poolfence.circumference()<< endl;
	system("pause");
	return 0;
}
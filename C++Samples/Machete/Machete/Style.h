//Style.h  ��ʽ ͷ�ļ�����ư�ť�Ƚ�����Ԫ�ķ��
#pragma once

//����������֧��
#ifndef IDC_HAND
#define IDC_HAND MAKEINTRESOURCE(32649)
#endif

/* �ṹ����� */
extern void MainMenu();						//���˵�����
extern void ExitProgram(int status = 0);	//�˳�����
extern void StarBloom();					//���������

//ͼ��͸������ 
//������Ϣ����ʣ�easyx�ٶ����ɣ�http://tieba.baidu.com/p/2578675430?pn=1
extern void transp_image(int dstX, int dstY, IMAGE *pimg, int avoid_color, int deviation, int tp);
extern int calc_abs(int value);						//���������ľ���ֵ
extern void copy_image(IMAGE* img1, IMAGE* img2);	//copy img2 to img1


/******************************************************************************************************/
/* ��������˼�� */
class Button	//��ťButton��
{	
public:  //�мǣ��˴��ķ������η�����˵��������Ĭ��Ϊ˽�еģ������಻�ɷ��ʣ�
	//���캯��
	Button() {}
	Button(int left, int top, int right, int bottom)
		:left_(left), top_(top), right_(right), bottom_(bottom) {}
	Button(const RECT& rect) { 
		left_ = rect.left; top_ = rect.top; right_ = rect.right; bottom_ = rect.bottom; }
	//���ƹ��캯��
	Button(const Button& rButton){
		left_ = rButton.left_; top_ = rButton.top_; right_ = rButton.right_; bottom_ = rButton.bottom_; }
	//����������
	virtual ~Button() {}
	//���ݳ�Ա��get,set����
	int		getLeft()	const			{ return left_; } 				//left_
	void	setLeft(const int left)		{ left_ = left; }
	int		getTop()	const			{ return top_; } 				//top_
	void	setTop(const int top)		{ top_ = top; }
	int		getRight()	const			{ return right_; } 				//right_
	void	setRight(const int right)	{ right_ = right; }
	int		getBottom()	 const			{ return bottom_; } 			//bottom_
	void	setBottom(const int bottom)	{ bottom_ = bottom; }

	void SetRect(const RECT& rect);							//���þ�������RECT����
	void SetRect(int left, int top, int right, int bottom);	//���þ������򣨵�����꣩

	static HWND MouseShape(int shape);						//���������״�����ش��ھ��
private:
	int left_;		//���
	int top_;		//�ϵ�
	int right_;		//�ҵ�
	int bottom_;	//�µ�
};

class MenuButton : public Button		//�˵���ťMenuButton�ࣺ���м̳а�ťButton��
{
public:
	//���캯��
	MenuButton() :Button() {}
	MenuButton(int left, int top, int right, int bottom) :Button(left, top, right, bottom) {}
	MenuButton(const RECT& rect):Button(rect) {}

	//void SetRect(const RECT& rect);							//���þ�������RECT����
	//void SetRect(int left, int top, int right, int bottom);	//���þ������򣨵�����꣩
	bool IsWithin();										//�ж�����Ƿ��ڷ�Χ�ڣ��������߽磩
	static MOUSEMSG& MouseMsg();							//��ȡ�����Ϣ
	void MouseMove(const TCHAR* menutext);					//�������
	void MouseLeave(const TCHAR* menutext);					//����뿪
private: 
	//��̬���ݳ�Աʵ�����������е�ȫ�ֱ���,�䶨�弰��ʼ����Ӧ�ñ�����ͷ�ļ��С�
	//���弰��ʼ��ʱ����private��protected�������ơ�
	//��Ҫ��ͷ�ļ��ж��弰��ʼ����̬���ݳ�Ա���������ظ�����Ĵ���
	//��������ж����������������������ж��󣻡�����������ͻ��๲��һ����̬���ݳ�Ա��
	static MOUSEMSG mouse_;						//�����Ϣ
};

class StarButton : public MenuButton	//����ǵ������ΰ�ť�����м̳в˵���ťMenuButton��
{
public:
	//���캯��
	StarButton() {}
	//StarButton(const POINT* pPoints, int num = 3);	

	//���ݳ�Ա��get set ����
	POINT	getFirst()	const					{ return firstpt_; }		//firstpt_
	void	setFirst(const POINT& rFirstpt)		{ firstpt_ = rFirstpt; }
	POINT	getSecond() const					{ return secondpt_; }		//secondpt_
	void	setSecond(const POINT& rSecondpt)	{ secondpt_ = rSecondpt; }
	POINT	getThird()	const					{ return thirdpt_; }		//thirdpt_
	void	setThird(const POINT& rThirdpt)		{ thirdpt_ = rThirdpt; }

	void SetStar(const POINT* pPoints, int num = 3);	//��������������ΰ�ť
	bool IsWithin(int mode);							//�ж�����Ƿ��ڷ�Χ�ڣ��������߽磩
	void MouseMove(int mode);				//����������������ǣ�
	void MouseLeave(int mode);				//����뿪���������ǣ�

private:
	POINT firstpt_;		//��ʼ������
	POINT secondpt_;	//�м������
	POINT thirdpt_;		//��ֹ������
};

class CardButton;	//���ǰ�����������������۰�~
class Poker		//�˿���Poker��
{
public:
	//���캯��
	Poker() {}
	Poker(LPCTSTR pImgFile, int nWidth = 0, int nHeight = 0);	//����ʱ��ȡͼ��
	//���ƹ��캯��
	Poker(const Poker& rPoker) { 
		point_		= rPoker.point_;
		color_		= rPoker.color_;
		image_		= rPoker.image_;
		//pImageFile_ = rPoker.pImageFile_;
	}
	
	//���ݳ�Ա�� get set ����
	int		getPoint()	const					{ return point_;  }		//point_
	void	setPoint(const int point)			{ point_ = point; }
	int		getColor()	const					{ return color_;  }		//color_
	void	setColor(const int color)			{ color_ = color; }
	IMAGE	getImage()	 const					{ return image_;  }		//image_
	void	setImage(const IMAGE& image)		{ image_ = image; }
	//LPCTSTR getImageFile() const				{ return pImageFile_; }	//pImageFile_
	//void	setImageFile(const LPCTSTR pImgFile){ pImageFile_ = pImgFile; }

	void ObtainCard(LPCTSTR pImgFile, int nWidth = 0, int nHeight = 0);					//��ȡ����
	void PlaceCard(int dstX, int dstY, int dstWidth = 80, int dstHeight = 120);			//���ÿ��ƣ�������꣩
	void PlaceCard(const CardButton& rCbutton, int dstWidth = 80, int dstHeight = 120);	//���ÿ��ƣ�CardButotn����

	//bool operator ==(const Poker& rPoker);		//����==���������أ�ʵ��ͼ��ƥ��	
private:
	int		point_;			//�˿��Ƶ���
	int		color_;			//�˿��ƻ�ɫ
	IMAGE	image_;			//�˿���ͼ��
	//LPCTSTR pImageFile_;	//�˿�����Դ
};

class CardButton : public MenuButton	//����CardButotn�ࣺ���м̳в˵���ťMenuButton��
{
public:
	//���캯��
	CardButton() :MenuButton() {}
	CardButton(int left, int top, int right, int bottom) :MenuButton(left, top, right, bottom) {}
	CardButton(const RECT& rect) :MenuButton(rect) {}

	//���ݳ�Ա�� get set ����
	Poker	getPoker()	const				{ return poker_; }		//poker_
	void	setPoker(const Poker& rPoker)	{ poker_ = rPoker; }
	bool	getDown()	const				{ return down_; }		//down_
	void	setDown(const bool down)		{ down_ = down; }		
	bool	getExit()	const				{ return exit_; }		//exit_
	void	setExit(const bool exit)		{ exit_ = exit; }

	int		GetPoint() const { return poker_.getPoint(); }	//��ȡ����point_
	int		GetColor() const { return poker_.getColor(); }	//��ȡ��ɫcolor_
	IMAGE	GetImage() const { return poker_.getImage(); }	//��ȡͼ��image_

	void MouseMove();		//����������������ǣ�
	void MouseLeave();		//����뿪���������ǣ�
	void LeftDown();		//����������

	void operator =(const Poker& rPoker);		//���ظ�ֵ=�����������ٷ��ÿ���
	void ClearCard();							//���������������

private:
	Poker poker_;			//�˿���
	bool  down_;			//���Ʊ�ѡ�б�־λ false
	bool  exit_;			//���ƴ��ڱ�־λ   true
};

class OutButton : public MenuButton		//����OutButotn�ࣺ���м̳в˵���ťMenuButton��
{
public:
	//���캯��
	OutButton() :MenuButton() {}
	OutButton(int left, int top, int right, int bottom) :MenuButton(left, top, right, bottom) {}
	OutButton(const RECT& rect) :MenuButton(rect) {}

	void MouseMove(const TCHAR* outtext);		//����������������ǣ�
	void MouseLeave(const TCHAR* outtext);		//����뿪���������ǣ�
	void LeftDown(int putout);		//����������
};

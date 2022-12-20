//Style.h  样式 头文件：设计按钮等交互单元的风格
#pragma once

//添加手形鼠标支持
#ifndef IDC_HAND
#define IDC_HAND MAKEINTRESOURCE(32649)
#endif

/* 结构化编程 */
extern void MainMenu();						//主菜单界面
extern void ExitProgram(int status = 0);	//退出程序
extern void StarBloom();					//五角星闪亮

//图像透明处理 
//更多信息请访问，easyx百度贴吧：http://tieba.baidu.com/p/2578675430?pn=1
extern void transp_image(int dstX, int dstY, IMAGE *pimg, int avoid_color, int deviation, int tp);
extern int calc_abs(int value);						//计算整数的绝对值
extern void copy_image(IMAGE* img1, IMAGE* img2);	//copy img2 to img1


/******************************************************************************************************/
/* 面向对象的思想 */
class Button	//按钮Button类
{	
public:  //切记！此处的访问修饰符必须说明，否则默认为私有的，派生类不可访问！
	//构造函数
	Button() {}
	Button(int left, int top, int right, int bottom)
		:left_(left), top_(top), right_(right), bottom_(bottom) {}
	Button(const RECT& rect) { 
		left_ = rect.left; top_ = rect.top; right_ = rect.right; bottom_ = rect.bottom; }
	//复制构造函数
	Button(const Button& rButton){
		left_ = rButton.left_; top_ = rButton.top_; right_ = rButton.right_; bottom_ = rButton.bottom_; }
	//虚析构函数
	virtual ~Button() {}
	//数据成员的get,set方法
	int		getLeft()	const			{ return left_; } 				//left_
	void	setLeft(const int left)		{ left_ = left; }
	int		getTop()	const			{ return top_; } 				//top_
	void	setTop(const int top)		{ top_ = top; }
	int		getRight()	const			{ return right_; } 				//right_
	void	setRight(const int right)	{ right_ = right; }
	int		getBottom()	 const			{ return bottom_; } 			//bottom_
	void	setBottom(const int bottom)	{ bottom_ = bottom; }

	void SetRect(const RECT& rect);							//设置矩形区域（RECT对象）
	void SetRect(int left, int top, int right, int bottom);	//设置矩形区域（点的坐标）

	static HWND MouseShape(int shape);						//设置鼠标形状，返回窗口句柄
private:
	int left_;		//左点
	int top_;		//上点
	int right_;		//右点
	int bottom_;	//下点
};

class MenuButton : public Button		//菜单按钮MenuButton类：公有继承按钮Button类
{
public:
	//构造函数
	MenuButton() :Button() {}
	MenuButton(int left, int top, int right, int bottom) :Button(left, top, right, bottom) {}
	MenuButton(const RECT& rect):Button(rect) {}

	//void SetRect(const RECT& rect);							//设置矩形区域（RECT对象）
	//void SetRect(int left, int top, int right, int bottom);	//设置矩形区域（点的坐标）
	bool IsWithin();										//判断鼠标是否在范围内（不包括边界）
	static MOUSEMSG& MouseMsg();							//获取鼠标消息
	void MouseMove(const TCHAR* menutext);					//鼠标悬浮
	void MouseLeave(const TCHAR* menutext);					//鼠标离开
private: 
	//静态数据成员实际上是类域中的全局变量,其定义及初始化不应该被放在头文件中。
	//定义及初始化时不受private和protected访问限制。
	//不要在头文件中定义及初始化静态数据成员，会引起重复定义的错误。
	//被类的所有对象共享，包括类的派生类的所有对象；——即派生类和基类共享一个静态数据成员。
	static MOUSEMSG mouse_;						//鼠标消息
};

class StarButton : public MenuButton	//五角星的三角形按钮：公有继承菜单按钮MenuButton类
{
public:
	//构造函数
	StarButton() {}
	//StarButton(const POINT* pPoints, int num = 3);	

	//数据成员的get set 方法
	POINT	getFirst()	const					{ return firstpt_; }		//firstpt_
	void	setFirst(const POINT& rFirstpt)		{ firstpt_ = rFirstpt; }
	POINT	getSecond() const					{ return secondpt_; }		//secondpt_
	void	setSecond(const POINT& rSecondpt)	{ secondpt_ = rSecondpt; }
	POINT	getThird()	const					{ return thirdpt_; }		//thirdpt_
	void	setThird(const POINT& rThirdpt)		{ thirdpt_ = rThirdpt; }

	void SetStar(const POINT* pPoints, int num = 3);	//设置五角星三角形按钮
	bool IsWithin(int mode);							//判断鼠标是否在范围内（不包括边界）
	void MouseMove(int mode);				//鼠标悬浮（函数覆盖）
	void MouseLeave(int mode);				//鼠标离开（函数覆盖）

private:
	POINT firstpt_;		//起始点坐标
	POINT secondpt_;	//中间点坐标
	POINT thirdpt_;		//终止点坐标
};

class CardButton;	//类的前行引用声明，就是累啊~
class Poker		//扑克牌Poker类
{
public:
	//构造函数
	Poker() {}
	Poker(LPCTSTR pImgFile, int nWidth = 0, int nHeight = 0);	//构造时获取图像
	//复制构造函数
	Poker(const Poker& rPoker) { 
		point_		= rPoker.point_;
		color_		= rPoker.color_;
		image_		= rPoker.image_;
		//pImageFile_ = rPoker.pImageFile_;
	}
	
	//数据成员的 get set 方法
	int		getPoint()	const					{ return point_;  }		//point_
	void	setPoint(const int point)			{ point_ = point; }
	int		getColor()	const					{ return color_;  }		//color_
	void	setColor(const int color)			{ color_ = color; }
	IMAGE	getImage()	 const					{ return image_;  }		//image_
	void	setImage(const IMAGE& image)		{ image_ = image; }
	//LPCTSTR getImageFile() const				{ return pImageFile_; }	//pImageFile_
	//void	setImageFile(const LPCTSTR pImgFile){ pImageFile_ = pImgFile; }

	void ObtainCard(LPCTSTR pImgFile, int nWidth = 0, int nHeight = 0);					//获取卡牌
	void PlaceCard(int dstX, int dstY, int dstWidth = 80, int dstHeight = 120);			//放置卡牌（点的坐标）
	void PlaceCard(const CardButton& rCbutton, int dstWidth = 80, int dstHeight = 120);	//放置卡牌（CardButotn对象）

	//bool operator ==(const Poker& rPoker);		//等于==操作符重载，实现图像匹配	
private:
	int		point_;			//扑克牌点数
	int		color_;			//扑克牌花色
	IMAGE	image_;			//扑克牌图像
	//LPCTSTR pImageFile_;	//扑克牌资源
};

class CardButton : public MenuButton	//卡牌CardButotn类：公有继承菜单按钮MenuButton类
{
public:
	//构造函数
	CardButton() :MenuButton() {}
	CardButton(int left, int top, int right, int bottom) :MenuButton(left, top, right, bottom) {}
	CardButton(const RECT& rect) :MenuButton(rect) {}

	//数据成员的 get set 方法
	Poker	getPoker()	const				{ return poker_; }		//poker_
	void	setPoker(const Poker& rPoker)	{ poker_ = rPoker; }
	bool	getDown()	const				{ return down_; }		//down_
	void	setDown(const bool down)		{ down_ = down; }		
	bool	getExit()	const				{ return exit_; }		//exit_
	void	setExit(const bool exit)		{ exit_ = exit; }

	int		GetPoint() const { return poker_.getPoint(); }	//获取点数point_
	int		GetColor() const { return poker_.getColor(); }	//获取花色color_
	IMAGE	GetImage() const { return poker_.getImage(); }	//获取图像image_

	void MouseMove();		//鼠标悬浮（函数覆盖）
	void MouseLeave();		//鼠标离开（函数覆盖）
	void LeftDown();		//鼠标左键按下

	void operator =(const Poker& rPoker);		//重载赋值=操作符，快速放置卡牌
	void ClearCard();							//清除卡牌所在区域

private:
	Poker poker_;			//扑克牌
	bool  down_;			//卡牌被选中标志位 false
	bool  exit_;			//卡牌存在标志位   true
};

class OutButton : public MenuButton		//出牌OutButotn类：公有继承菜单按钮MenuButton类
{
public:
	//构造函数
	OutButton() :MenuButton() {}
	OutButton(int left, int top, int right, int bottom) :MenuButton(left, top, right, bottom) {}
	OutButton(const RECT& rect) :MenuButton(rect) {}

	void MouseMove(const TCHAR* outtext);		//鼠标悬浮（函数覆盖）
	void MouseLeave(const TCHAR* outtext);		//鼠标离开（函数覆盖）
	void LeftDown(int putout);		//鼠标左键按下
};

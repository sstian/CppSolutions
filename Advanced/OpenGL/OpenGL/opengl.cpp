#include <GL\glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 
const int N = 1000;							//多边形的边数
const GLfloat R = 0.5f;						//圆的半径
const GLfloat PI = 3.14159265358979323846f;	//圆周率
const GLfloat LEN = 1.0f;	//五角星正五边形的边长
const GLfloat FACTOR = 0.1f;	//正弦函数因子
const GLint RANGE = 8;	//色圆边数范围8

#define RAD(d) (d * PI / 180 )	//角度转弧度

int day = 200; // day的变化

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);	//清除
	/* 默认坐标值 -1到1 */
	//glRectf(-0.1f, -0.1f, -0.5f, -0.5f);	//画矩形

	glBegin(GL_LINE_LOOP);
	///BeginMode：
	///GL_POINTS，GL_LINES，GL_LINE_STRIP，GL_LINE_LOOP，GL_TRIANGLES，GL_TRIANGLE_STRIP，GL_TRIANGLE_FAN。GL_QUADS，GL_QUAD_STRIP，GL_POLYGON
	/* 在这里填上你所希望的模式 */ 
	/* 在这里使用glVertex*系列函数 */ 
	/* 指定你所希望的顶点位置 */ 

	////画点 GL_POINTS
	//glVertex2f(0.0f, 0.0f);	
	//glVertex3f(0.7f, 0.7f, 0.0f);
	//glVertex4f(0.8f, 0.6f, 0.0f, 1.0f);
	//GLfloat veterxArray3[] = { 0.7f, 0.9f, 0.0f };
	//glVertex3fv(veterxArray3);

	////画圆 GL_POLYGON
	//for (int i = 0; i < N; i++)
	//	glVertex2f(R*cos(2 * PI / N*i), R*sin(2 * PI / N*i));

	//画五角星 GL_LINE_LOOP，点集：顺时针A-B-C-D-E
	GLfloat sa = LEN / 2 / sin(RAD(36));	//中心到顶点的距离
	GLfloat bx = sa * cos(RAD(18));
	GLfloat by = sa * sin(RAD(18));
	GLfloat cy = sa * cos(RAD(36));
	GLfloat PointA[2] = { 0, sa };
	GLfloat PointB[2] = { bx, by };
	GLfloat PointC[2] = { LEN / 2, -cy };
	GLfloat PointD[2] = { -LEN / 2, -cy };
	GLfloat PointE[2] = { -bx, by };
	GLfloat* PointStar[] = { PointA, PointC, PointE, PointB, PointD };
	for (int s = 0; s < 5; s++)
		glVertex2fv(PointStar[s]);
	glEnd(); 

	glFlush();						//刷新
}

void myDisplay2()
{
	glClear(GL_COLOR_BUFFER_BIT);
	////画正弦函数图像
	//glBegin(GL_LINES);	//坐标轴
	//glVertex2f(-1.0f, 0.0f);
	//glVertex2f(1.0f, 0.0f);
	//glVertex2f(0.0f, -1.0f);
	//glVertex2f(0.0f, 1.0f);
	//glEnd();

	//glBegin(GL_LINE_STRIP);	//正弦图像
	//for (GLfloat x = -1.0f / FACTOR; x < 1.0f / FACTOR; x += 0.01f)
	//	glVertex2f(x*FACTOR, sin(x)*FACTOR);
	//glEnd();

	//画点划线
	glEnable(GL_LINE_STIPPLE);	//启用虚线模式 void glEnable(GLenum cap); 关闭 void glDisable(GLenum cap);
	glLineStipple(3, 0x0F0F);	//虚线样式 void glLineStipple(GLint factor, GLushort pattern);
	glLineWidth(3.0f);			//更改线宽
	//glPointSize(5.0f);			//更改点的大小，默认1.0f，单位：像素 void glPointSize(GLfloat size);
	glBegin(GL_LINES);
	glVertex2f(-0.9f, -0.9f);
	glVertex2f(0.9f, 0.9f);
	glEnd();
	glFlush(); 
}

void myDisplayPolygon()
{
	glClear(GL_COLOR_BUFFER_BIT);
	/* 三维角度，一个多边形有两个面，绘制方式可不同 */
	glPolygonMode(GL_FRONT, GL_FILL);			//正面填充绘制
	glPolygonMode(GL_BACK, GL_LINE);			//反面线型绘制
	//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);	//两面顶点绘制
	/* 约定顶点以逆时针顺序出现在屏幕上的面为“正面”，另一个面即为“反面”*/
	glFrontFace(GL_CCW);		//设置CCW方向为“正面”，CCW=CounterClockWise 逆时针
	//glFrontFace(GL_CW);	//设置CW方向为“正面”，CW=ClockWise 顺时针
	/* 剔除多边形表面 */
	//glEnable(GL_CULL_FACE);	//启用剔除功能
	//glCullFace(GL_FRONT);	//剔除表面 void glCullFace(GLenum mode); //GL_FRONT, GL_BACK, GL_FRONT_AND_BACK
	glBegin(GL_POLYGON);	//按逆时针绘制正方形，在左下方
	glVertex2f(-0.5f, -0.5f); glVertex2f(0.0f, -0.5f); glVertex2f(0.0f, 0.0f); glVertex2f(-0.5f, 0.0f); //！点的顺序很重要
	glEnd();
	glBegin(GL_POLYGON);	//按顺时针绘制正方形，在右上方
	glVertex2f(0.0f, 0.0f); glVertex2f(0.0f, 0.5f); glVertex2f(0.5f, 0.5f); glVertex2f(0.5f, 0.0f);
	glEnd();
	glFlush();
}

void myDisplayPolygon2()
{
	static GLubyte mask[128];	//储存空间点的数据
	FILE* fp;
	fopen_s(&fp, "mask.bmp", "rb");
	if (!fp)
		exit(-1);
	if (fseek(fp, -(int)sizeof(mask), SEEK_END))
		exit(-1);
	if (!fread(mask, sizeof(mask), 1, fp))
		exit(-1);
	fclose(fp);
	glClear(GL_COLOR_BUFFER_BIT);
	/* 镂空多边形 */
	glEnable(GL_POLYGON_STIPPLE);	//启用镂空功能
	glPolygonStipple(mask);			//镂空 void glPolygonStipple(const GLubyte *mask); 长度为128字节的空间，32*32的矩形
	glRectf(-0.5f, -0.5f, 0.0f, 0.0f);	//在左下方绘制一个有镂空效果的正方形
	glDisable(GL_POLYGON_STIPPLE);
	glRectf(0.0f, 0.0f, 0.5f, 0.5f);	//在右上方绘制一个无镂空效果的正方形
	glFlush();
}

void myDisplayColor()
{
	//glClearColor(0.0f, 1.0f, 0.0f, 0.5f);	//指定清除屏幕的颜色
	//glClear(GL_COLOR_BUFFER_BIT);
	///* 颜色模式：RGBA, 索引颜色（不常用） */
	////RGBA 最大颜色值：f,d->1.0; b->127; ub->255; s->32767; us->65535
	////glColor3f(1.0f, 0.0f, 1.0f);	//void glColor3f(GLfloat red, GLfloat green, GLfloat blue);  
	//								//void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	//glColor4ub(255, 0, 255, 255);
	////void glIndexi (GLint c);
	//glRectf(-0.5f, -0.5f, 0.0f, 0.0f);

	//glShadeModel(GL_SMOOTH);	//颜色填充方式：GL_SMOOTH 平滑，GL_FLAT 单色
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	for (int i = 0; i <= RANGE; i++)
	{
		glColor3f(i & 0x04, i & 0x02, i & 0x01);
		glVertex2f(cos(i*PI / (RANGE / 2)), sin(i*PI / (RANGE / 2)));
	}
	glEnd();
	glFlush();
}

void myDisplayMatrix()
{
	//？“太阳，地球和月亮”系统
	glEnable(GL_DEPTH_TEST); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//清空深度缓冲
	glMatrixMode(GL_PROJECTION);	//投影变换矩阵
	glLoadIdentity();	//设置当前矩阵为单位矩阵
	gluPerspective(75, 1, 1, 4);  //透视投影，设置可视空间
	glMatrixMode(GL_MODELVIEW);		//模型视图矩阵
	glLoadIdentity(); 
	gluLookAt(0, -2, 2, 0, 0, 0, 0, 0, 1);
	// 绘制红色的“太阳” 
	glColor3f(1.0f, 0.0f, 0.0f); 
	glutSolidSphere(0.5, 20, 20);	//绘制球体
	// 绘制蓝色的“地球” 
	glColor3f(0.0f, 0.0f, 1.0f); 
	glRotatef(day/3.0*3.0, 0.0f, 0.0f, -1.0f);	//旋转
	glTranslatef(1.5, 0.0f, 0.0f);				//平移
	glutSolidSphere(0.3, 20, 20);
	// 绘制黄色的“月亮”
	glColor3f(1.0f, 1.0f, 0.0f); 
	glRotatef(day/3.0*3.0 - day/3.0*3.0, 0.0f, 0.0f, -1.0f); 
	glTranslatef(0.7, 0.0f, 0.0f);
	glutSolidSphere(0.2, 20, 20); 
	glFlush();
	glutSwapBuffers();
}
void myIdle()
{
	++day;
	if (day >= 360)
		day = 0;
	myDisplayMatrix();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);							//初始化GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);	//初始化显示模式：双缓冲
	glutInitWindowPosition(300, 300);	//初始化窗口位置
	glutInitWindowSize(400, 400);		//初始化窗口大小
	glutCreateWindow("OpeGL Demo");					//创建窗口
	glutDisplayFunc(myDisplayMatrix);						//设置画图函数
	glutIdleFunc(myIdle);	//CPU空闲时间调用
	glutMainLoop();									//消息循环

	return 0;
}
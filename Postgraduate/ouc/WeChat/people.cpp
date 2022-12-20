#include "people.h"
#include <iostream>
#include <algorithm>
#include <set>

using namespace std ;

struct setcompare
{
    bool operator()(const people&a,const people&b)
    {
        return (a.WechartNum < b.WechartNum) ;
    }
};

set <people,setcompare> setPeople ;
set <string> setPhoneNum ;

people::people(string wecharNum,string passwd,string qqNum,string phoneNum,string email)
{
    WechartNum = wecharNum ;
	Passwd = passwd ;
	QqNum = qqNum ;
	PhoneNum = phoneNum ;
	Email = email ;


	myFriend.insert(wecharNum) ;  //将新建的人加入信息库
	setPhoneNum.insert(PhoneNum) ; //将新建人的手机号码加入号码库

}

people::people(const people &_people)
{
	WechartNum = _people.WechartNum ;
	Passwd     = _people.Passwd ;
	QqNum      = _people.QqNum ;
	PhoneNum   = _people.PhoneNum ;
	Email      = _people.Email ;
	myFriend   = _people.myFriend ;
	joinGroup  = _people.joinGroup ;
	myGroup    = _people.myGroup ;
}

void people::displayAll()
{

	set<string>::iterator it ;
	cout<<"微信号："<<WechartNum<<endl ;
	cout<<"密  码："<<Passwd<<endl ;
	cout<<"QQ  号："<<QqNum<<endl ;
	cout<<"电  话："<<PhoneNum<<endl ;
	cout<<"邮  箱："<<Email<<endl ;
	cout<<"朋  友：" ;
	for(it = myFriend.begin() ; it != myFriend.end() ;it++)
	{
		cout<<"\\"<<*it ;
	}
	cout<<endl ;
	cout<<"创建的群：";
	for(it = myGroup.begin() ; it != myGroup.end() ;it++)
	{
		cout<<"\\"<<*it;
	}
	cout<<endl ;
	cout<<"加入的群：" ;
	for(it = joinGroup.begin() ; it != joinGroup.end() ;it++)
	{
		cout<<"\\"<<*it ;
	}
	cout<<endl ;

}


people::~people()
{
    //dtor
}

//互加朋友
void people::MakeFriend(people &p)  //将p1和p2互相添加作为朋友
{
	if(myFriend.count(p.WechartNum) == 0)
	{
		myFriend.insert(p.WechartNum) ;
		p.myFriend.insert(WechartNum) ;
		cout<<WechartNum<<"添加了朋友"<<p.WechartNum<<endl ;
		setPeople.insert(*this) ;  //将自己的信息更新到库
	}
	else
	{
		cout<<"您和"<<p.WechartNum<<"已经是好友关系了，不需要重复添加"<<endl ;
	}
}


//将p2添加到创建的groupName群里
void people::JoinMyGroup(string groupName,people &p2)
{
	if(myGroup.count(groupName) == 0) //自己还没有建这个群呢
	{
		cout<<"没有这个群！"<<endl ;
	}
	else
	{
		cout<<"《"<<groupName<<"》"<<"群:添加了成员："<<p2.WechartNum<<endl ;
		p2.joinGroup.insert(groupName) ;
		setPeople.insert(*this) ;  //将自己的信息更新到库
	}
}

//创建自己的群
void people::CreatMyGroup(string groupName)
{
	if(myGroup.count(groupName) == 0) //没有创建这个群
	{
		myGroup.insert(groupName) ;
		cout<<WechartNum<<":创建了群："<<groupName<<endl ;
		setPeople.insert(*this) ;  //将自己的信息更新到库
	}
	else
	{
		cout<<"这个群已经存在了！"<<endl ;
	}
}


bool findByPhoneNum(string phone)
{

    set <people,setcompare>::iterator it ;
    for(it = setPeople.begin() ; it != setPeople.end() ; it++)
    {
        if((*it).PhoneNum == phone)
        {
            cout<<"查找到此人信息"<<endl ;
            people *p ;
            p = new people(*it) ;
            set<string>::iterator it ;
            cout<<"显示推荐的朋友"<<endl ;
            for(it = p->myFriend.begin() ;it != p->myFriend.end() ;it++)
            {
                cout<<"\\"<<*it ;

            }
            cout<<endl ;
            //p->displayAll() ;
            delete p ;
            return ture ;
        }
    }
    cout<<"木有此人"<<endl ;
    return false ;
}


bool Login()
{
	string wecharnum ;
	string wecharpasswd ;
	set <people,setcompare>::iterator it ;

    bool flag = 0 ;
    cout<<"请登录账号和密码：（第一个账号是<pzh>,密码是<pzh>）"<<endl ;

    cin>>wecharnum>>wecharpasswd ;

    for(it = setPeople.begin(); it != setPeople.end() ;it++)
    {
        if(it->WechartNum == wecharnum && it->Passwd == wecharpasswd) //密码正确
        {
            flag = 1 ;
            cout<<"密码正确"<<endl ;
            break ;
        }
    }
    if(!flag)
    {
        cout<<"账号或密码错误，退出"<<endl ;
        return false ;
    }
    else
    {
        people *my = new people(*it) ;

        /*添加其他人作为好友*/

        for(it = setPeople.begin(); it != setPeople.end() ;it++)
        {
            people *you = new people(*it) ;
            setPeople.erase(it) ;
            my->MakeFriend(*you ) ;
            setPeople.insert(*you) ;
            delete you ;
        }

        //cout<<setPeople.size()<<endl<<endl ;


        /*创建一个群*/
        my->CreatMyGroup("吉首大学") ;

        /*将其他人加入我建的群*/
        for(it = setPeople.begin() ; it != setPeople.end() ; it++)
        {
            people *you = new people(*it) ;
            setPeople.erase(it) ;
            my->JoinMyGroup("吉首大学",*you ) ;
            setPeople.insert(*you) ;
            delete you ;
        }


        //cout<<setPeople.size()<<endl<<endl ;
        /*创建一个群*/
        my->CreatMyGroup("中国海洋大学") ;

        /*将其他人加入我建的群*/
        for(it = setPeople.begin() ; it != setPeople.end() ; it++)
        {
            people *you = new people(*it) ;
            //setPeople.erase(it) ;
            my->JoinMyGroup("中国海洋大学",*you ) ;
            setPeople.insert(*you) ;
            delete you ;
        }

        cout<<"显示所有人的信息"<<endl ;
        for(it = setPeople.begin() ; it != setPeople.end() ; it++)
        {
            people *you = new people(*it) ;
            you->displayAll() ;
            delete you ;
        }

        findByPhoneNum("13762105499") ;  //查找这个手机号的微信的推荐好友


        cout<<endl<<endl<<endl ;

        return ture ;
    }

}


void peopleInit()
{

    set <people,setcompare>::iterator it ;


    cout<<"建立微信人员信息"<<endl ;
    setPeople.insert(people("pzh","pzh","1603668353","13762105499","12311231@qq.com")) ;
    setPeople.insert(people("bee","bee","13762105498","12312313","12311231@qq.com")) ;
    setPeople.insert(people("me1","me1","13762105497","12312313","12311231@qq.com")) ;
    setPeople.insert(people("me2","loveyou","13762105495","12312313","12311231@qq.com")) ;
    setPeople.insert(people("me3","loveyou","12231231","12312313","12311231@qq.com")) ;
    setPeople.insert(people("me4","loveyou","12231231","12312313","12311231@qq.com")) ;
    setPeople.insert(people("me5","loveyou","12231231","12312313","12311231@qq.com")) ;
    setPeople.insert(people("me6","loveyou","12231231","12312313","12311231@qq.com")) ;
    setPeople.insert(people("me7","loveyou","12231231","12312313","12311231@qq.com")) ;
    setPeople.insert(people("me8","loveyou","12231231","12312313","12311231@qq.com")) ;
    setPeople.insert(people("me9","loveyou","12231231","12312313","12311231@qq.com")) ;

/*
    cout<<"显示所有人的信息"<<endl ;
    for(it = setPeople.begin() ; it != setPeople.end() ; it++)
    {
        people *you = new people(*it) ;
        you->displayAll() ;
        delete you ;
    }

  */
    cout<<endl<<endl ;

}


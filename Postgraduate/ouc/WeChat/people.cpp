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


	myFriend.insert(wecharNum) ;  //���½����˼�����Ϣ��
	setPhoneNum.insert(PhoneNum) ; //���½��˵��ֻ������������

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
	cout<<"΢�źţ�"<<WechartNum<<endl ;
	cout<<"��  �룺"<<Passwd<<endl ;
	cout<<"QQ  �ţ�"<<QqNum<<endl ;
	cout<<"��  ����"<<PhoneNum<<endl ;
	cout<<"��  �䣺"<<Email<<endl ;
	cout<<"��  �ѣ�" ;
	for(it = myFriend.begin() ; it != myFriend.end() ;it++)
	{
		cout<<"\\"<<*it ;
	}
	cout<<endl ;
	cout<<"������Ⱥ��";
	for(it = myGroup.begin() ; it != myGroup.end() ;it++)
	{
		cout<<"\\"<<*it;
	}
	cout<<endl ;
	cout<<"�����Ⱥ��" ;
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

//��������
void people::MakeFriend(people &p)  //��p1��p2���������Ϊ����
{
	if(myFriend.count(p.WechartNum) == 0)
	{
		myFriend.insert(p.WechartNum) ;
		p.myFriend.insert(WechartNum) ;
		cout<<WechartNum<<"���������"<<p.WechartNum<<endl ;
		setPeople.insert(*this) ;  //���Լ�����Ϣ���µ���
	}
	else
	{
		cout<<"����"<<p.WechartNum<<"�Ѿ��Ǻ��ѹ�ϵ�ˣ�����Ҫ�ظ����"<<endl ;
	}
}


//��p2��ӵ�������groupNameȺ��
void people::JoinMyGroup(string groupName,people &p2)
{
	if(myGroup.count(groupName) == 0) //�Լ���û�н����Ⱥ��
	{
		cout<<"û�����Ⱥ��"<<endl ;
	}
	else
	{
		cout<<"��"<<groupName<<"��"<<"Ⱥ:����˳�Ա��"<<p2.WechartNum<<endl ;
		p2.joinGroup.insert(groupName) ;
		setPeople.insert(*this) ;  //���Լ�����Ϣ���µ���
	}
}

//�����Լ���Ⱥ
void people::CreatMyGroup(string groupName)
{
	if(myGroup.count(groupName) == 0) //û�д������Ⱥ
	{
		myGroup.insert(groupName) ;
		cout<<WechartNum<<":������Ⱥ��"<<groupName<<endl ;
		setPeople.insert(*this) ;  //���Լ�����Ϣ���µ���
	}
	else
	{
		cout<<"���Ⱥ�Ѿ������ˣ�"<<endl ;
	}
}


bool findByPhoneNum(string phone)
{

    set <people,setcompare>::iterator it ;
    for(it = setPeople.begin() ; it != setPeople.end() ; it++)
    {
        if((*it).PhoneNum == phone)
        {
            cout<<"���ҵ�������Ϣ"<<endl ;
            people *p ;
            p = new people(*it) ;
            set<string>::iterator it ;
            cout<<"��ʾ�Ƽ�������"<<endl ;
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
    cout<<"ľ�д���"<<endl ;
    return false ;
}


bool Login()
{
	string wecharnum ;
	string wecharpasswd ;
	set <people,setcompare>::iterator it ;

    bool flag = 0 ;
    cout<<"���¼�˺ź����룺����һ���˺���<pzh>,������<pzh>��"<<endl ;

    cin>>wecharnum>>wecharpasswd ;

    for(it = setPeople.begin(); it != setPeople.end() ;it++)
    {
        if(it->WechartNum == wecharnum && it->Passwd == wecharpasswd) //������ȷ
        {
            flag = 1 ;
            cout<<"������ȷ"<<endl ;
            break ;
        }
    }
    if(!flag)
    {
        cout<<"�˺Ż���������˳�"<<endl ;
        return false ;
    }
    else
    {
        people *my = new people(*it) ;

        /*�����������Ϊ����*/

        for(it = setPeople.begin(); it != setPeople.end() ;it++)
        {
            people *you = new people(*it) ;
            setPeople.erase(it) ;
            my->MakeFriend(*you ) ;
            setPeople.insert(*you) ;
            delete you ;
        }

        //cout<<setPeople.size()<<endl<<endl ;


        /*����һ��Ⱥ*/
        my->CreatMyGroup("���״�ѧ") ;

        /*�������˼����ҽ���Ⱥ*/
        for(it = setPeople.begin() ; it != setPeople.end() ; it++)
        {
            people *you = new people(*it) ;
            setPeople.erase(it) ;
            my->JoinMyGroup("���״�ѧ",*you ) ;
            setPeople.insert(*you) ;
            delete you ;
        }


        //cout<<setPeople.size()<<endl<<endl ;
        /*����һ��Ⱥ*/
        my->CreatMyGroup("�й������ѧ") ;

        /*�������˼����ҽ���Ⱥ*/
        for(it = setPeople.begin() ; it != setPeople.end() ; it++)
        {
            people *you = new people(*it) ;
            //setPeople.erase(it) ;
            my->JoinMyGroup("�й������ѧ",*you ) ;
            setPeople.insert(*you) ;
            delete you ;
        }

        cout<<"��ʾ�����˵���Ϣ"<<endl ;
        for(it = setPeople.begin() ; it != setPeople.end() ; it++)
        {
            people *you = new people(*it) ;
            you->displayAll() ;
            delete you ;
        }

        findByPhoneNum("13762105499") ;  //��������ֻ��ŵ�΢�ŵ��Ƽ�����


        cout<<endl<<endl<<endl ;

        return ture ;
    }

}


void peopleInit()
{

    set <people,setcompare>::iterator it ;


    cout<<"����΢����Ա��Ϣ"<<endl ;
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
    cout<<"��ʾ�����˵���Ϣ"<<endl ;
    for(it = setPeople.begin() ; it != setPeople.end() ; it++)
    {
        people *you = new people(*it) ;
        you->displayAll() ;
        delete you ;
    }

  */
    cout<<endl<<endl ;

}


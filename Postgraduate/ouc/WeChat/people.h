#ifndef PEOPLE_H
#define PEOPLE_H

#include <string>
#include <set>

#define ture 1
#define false 0



using namespace std ;

class people
{
    public:
        people(string wecharNum,string passwdstring,string qqNum,string phoneNum,string email);
        people(const people &_people) ;

		void MakeFriend(people &p) ; //将p1和p2互相添加作为朋友
        friend void JoinMyGroup(people &p1,string groupName,people &p2) ;
		void CreatMyGroup(string groupName) ;
		void SaveMymsgToFile(string fileName) ;  //将
        void JoinMyGroup(string groupName,people &p2) ;
		void displayAll() ;

		virtual ~people();
    protected:
    //private:
    public:
        string WechartNum ;  //微信号
		string Passwd ;      //微信密码
        string QqNum  ; //
        string PhoneNum ;
        string Email ;

        set<string>myFriend ;    //我的朋友
        set<string>joinGroup ;  //加入的群
        set<string>myGroup ;    //自己创建的群

		//set<group>allGroup ;

};


bool Login() ;
void peopleInit() ;


#endif // PEOPLE_H

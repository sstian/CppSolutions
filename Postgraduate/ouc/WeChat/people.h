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

		void MakeFriend(people &p) ; //��p1��p2���������Ϊ����
        friend void JoinMyGroup(people &p1,string groupName,people &p2) ;
		void CreatMyGroup(string groupName) ;
		void SaveMymsgToFile(string fileName) ;  //��
        void JoinMyGroup(string groupName,people &p2) ;
		void displayAll() ;

		virtual ~people();
    protected:
    //private:
    public:
        string WechartNum ;  //΢�ź�
		string Passwd ;      //΢������
        string QqNum  ; //
        string PhoneNum ;
        string Email ;

        set<string>myFriend ;    //�ҵ�����
        set<string>joinGroup ;  //�����Ⱥ
        set<string>myGroup ;    //�Լ�������Ⱥ

		//set<group>allGroup ;

};


bool Login() ;
void peopleInit() ;


#endif // PEOPLE_H

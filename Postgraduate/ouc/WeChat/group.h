#ifndef GROUP_H
#define GROUP_H

#include "people.h"
#include <set>
#include <string>
using namespace std ;

class group
{
    public:
        group();
        virtual ~group();
    protected:
    //private:
	public :
        string groupName ;  //Ⱥ������
        set<string> userPeople ;//ȺԱ
};

#endif // GROUP_H

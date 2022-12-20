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
        string groupName ;  //群的名字
        set<string> userPeople ;//群员
};

#endif // GROUP_H

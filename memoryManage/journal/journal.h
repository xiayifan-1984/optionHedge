#ifndef JOURNAL_H
#define JOURNAL_H

#include "../utils/memoryManage_declare.h"

MM_NAMESPACE_START

FORWARD_DECLARE_PTR(Journal);

class Journal
{
private:
	int serviceIdx;
	
public:
	int getIndex();
	Journal() {};
};

MM_NAMESPACE_END
#endif
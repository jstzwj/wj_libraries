#include "ptr.h"


std::list<PtrNode > GcGlobal::allptr;
int GcGlobal::capacity = 0;
int GcGlobal::capacityLimit = 10;


void GcGlobal::addPtr(RawPtr & ptr)
{
	bool isroot = true;
	
	//记录指针
	std::list<PtrNode>::iterator i;
	for (i = allptr.begin(); i != allptr.end();++i)
	{
		if (i->ptr->isMine(ptr.p))
		{
			isroot = false;
			//计入总列表
			allptr.push_back(PtrNode(&ptr,&(*i),nullptr,false,false));
			break;
		}
	}
	
	
	if (isroot == true)
	{
		//计入总列表
		allptr.push_back(PtrNode(&ptr,nullptr,nullptr,false,true));
	}
}

void GcGlobal::gc()
{
	//链表检查
	//遍历
	std::list<PtrNode>::iterator i;
	for (i = allptr.begin(); i != allptr.end(); ++i)
	{
		i->deleteFlag = true;
	}
	for (i = allptr.begin(); i != allptr.end(); ++i)
	{
		if (i->root ==true)
		{
			i->deleteFlag = false;
		}
		if (i->deleteFlag==false)
		{
			std::list<PtrNode>::iterator j;
			for (j = allptr.begin(); j != allptr.end(); ++j)
			{
				if (i->ptr->isMine(j->ptr->p))
				{
					j->deleteFlag = false;
				}
			}
		}
	}
	//删除
	//记录指针
	for (i = allptr.begin(); i != allptr.end(); ++i)
	{
		if (i->deleteFlag==true)
		{
			delete reinterpret_cast<int *>(i->ptr->p);
			allptr.erase(i++);
			continue;
		}
	}
}

void GcGlobal::releaseAll()
{
	for (std::list<PtrNode>::iterator i = allptr.begin(); i != allptr.end();)
	{
			delete reinterpret_cast<int *>(i->ptr->p);
			allptr.erase(i++);
	}
}

#include "ptr.h"


std::list<PtrNode > GcGlobal::allptr;
int GcGlobal::capacity = 0;
int GcGlobal::capacityLimit = 10;


void GcGlobal::addPtr(RawPtr & ptr)
{
	bool isroot = true;
	
	//��¼ָ��
	std::list<PtrNode>::iterator i;
	for (i = allptr.begin(); i != allptr.end();++i)
	{
		if (i->ptr->isMine(ptr.p))
		{
			isroot = false;
			//�������б�
			allptr.push_back(PtrNode(&ptr,&(*i),nullptr,false,false));
			break;
		}
	}
	
	
	if (isroot == true)
	{
		//�������б�
		allptr.push_back(PtrNode(&ptr,nullptr,nullptr,false,true));
	}
}

void GcGlobal::gc()
{
	//������
	//����
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
	//ɾ��
	//��¼ָ��
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

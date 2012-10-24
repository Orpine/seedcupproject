#ifndef _DBFILE_H
#define _DBFILE_H
#include<afx.h>

class dbfile
{
public:
	CFile m_file;

	dbfile();
	~dbfile();
	int allocNewBlock();
	int findEnoughSpace(int offset, int size);
};

#endif
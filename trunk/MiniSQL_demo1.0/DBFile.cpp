#include"DBFile.h"

dbfile::dbfile()
{
	m_file.Open("Date.dat",CFile::modeCreate | CFile::modeNoTruncate| CFile::modeReadWrite);
	if(m_file.GetLength() == 0)
	{	
		int content[4096/4];
		content[0]=3;	
		content[1]=4096-3*8-1;
		content[2] = content[4] = content[6] = 8;
		content[3] = 4096-8;
		content[5] = 4096-16;
		content[7] = 4096-24;
		for(int i = 8; i < 4096/4; i++)
			content[i] = -1;
		m_file.Write((void *)content,4096);
	}
}

dbfile::~dbfile()
{
	m_file.Close();
}

int dbfile::allocNewBlock()
{
	unsigned int num = m_file.GetLength()/4096;
	unsigned int base = num * 4096;
	int content[4096/4];
	content[0]=0;		
	content[1]=4096-1;
	m_file.Seek(base, CFile::begin);
	m_file.Write((void *)content,4096);
	return num;
}

int dbfile::findEnoughSpace(int offset, int size)
{
	unsigned int block_count = m_file.GetLength() / 4096;
	int array[2];
	if(offset == 0)
		offset = 1;

	for(int i = offset; i < block_count; i++)
	{
		m_file.Seek(i*4096,CFile::begin);
		m_file.Read((void *)array,8);
		if(array[1] + 1 - 2*4 - array[0]*8 >= size + 8)
			return i;
	}
	return allocNewBlock();
}



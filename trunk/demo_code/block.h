#ifndef _BLOCK_H
#define _BLOCK_H
#include<afx.h>

class dbfile;
class address;

const int BLOCKSIZE = 4096;

class block
{
public:
	char space[BLOCKSIZE];
	int block_position;
	CTime last_use;
	bool valid;
	bool modified;
	CFile* file;
	
public:
	// ---------------------------- block info function -------------------------
	
	int getRecordNum();
	void setRecordNum(int);
	int getFreeSpaceEnd();
	void setFreeSpaceEnd(int);
	void setDataSize(int,int);
	int getDataSize(int);
	void setDataPoint(int,int);
	int getDataPoint(int);
	char* getHead()
	{
		return space;
	}
	void setBlockPosition(int p)
	{
		block_position = p;
	}
	int getBlockPosition()
	{
		return block_position;
	}
	bool IsValid()
	{
		return valid;
	}
	void setValid(bool sign)
	{
		valid = sign;
	}
	CTime getUseTime()
	{
		return last_use;
	}

	// ---------------------------- block basic function ------------------------
	block();
	~block();

	bool canHoldTheSize(int data_size);
	int addData(char* data, int data_size);
	void getData(int, char*);
	void rmData(int index);
	void saveToDisk();
	void getFromDisk(int, CFile*);

	// ---------------------------- data link function -----------------------------
	void setNextLink(int index, address next);
	void getNextLink(int index, address& next);
	void setRecordNextLink(int index, address next);
	void getRecordNextLink(int index, address& next);
	void setRecordFrontLink(int index, address front);
	void getRecordFrontLink(int index, address& front);
	void setIndexNext(int index, address next);
	void getIndexNext(int index, address next);
};

struct item
{
	int index;
	int size;
	int point;
};
#endif
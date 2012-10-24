#include<afx.h>
#include "BTree.h"

void BTree::InsertValue(void *pValue, int Block, int Index)
{
	if(m_iRoot[0] < 0 || m_iRoot[1] < 0 || m_file == NULL)
		throw new Exception("no root when find value in B+tree");
	if((m_sKeyType != "text" && m_sKeyType != "int" && 
		m_sKeyType != "date" && m_sKeyType != "float") ||
		m_iKeyTypeCount <= 0 )
		throw new Exception("error input for find value in b+");
	if(m_sKeyType == "text") {
		Node<char> tmpNode(m_iKeyTypeCount + 1, this);
		tmpNode.SetFileOrganize(m_file);
		tmpNode.SetSelfPosition(m_iRoot[0], m_iRoot[1]);
		tmpNode.Read();

		int tmpBlock, tmpIndex;
		int FindIndex = 0;
		while(!tmpNode.IsLeaf()) {
			FindIndex = tmpNode.FindGreaterKeyIndex((char*)pValue);
			if(FindIndex == -1)
				FindIndex = tmpNode.GetCount();			
			tmpNode.GetPointer(FindIndex, tmpBlock, tmpIndex);
			tmpNode.SetSelfPosition(tmpBlock, tmpIndex);	
			tmpNode.Read();
		}
		tmpNode.InsertKey((char*)pValue, Block, Index);	
	}
	else if(m_sKeyType == "int") {
		Node<int> tmpNode(m_iKeyTypeCount, this);
		tmpNode.SetFileOrganize(m_file);	
		tmpNode.SetSelfPosition(m_iRoot[0], m_iRoot[1]);
		tmpNode.Read();

		int tmpBlock, tmpIndex;
		int FindIndex = 0;
		while(!tmpNode.IsLeaf()) {
			FindIndex = tmpNode.FindGreaterKeyIndex((int*)pValue);
			if(FindIndex == -1)
				FindIndex = tmpNode.GetCount();
			tmpNode.GetPointer(FindIndex, tmpBlock, tmpIndex);
			tmpNode.SetSelfPosition(tmpBlock, tmpIndex);
			tmpNode.Read();
		}
		tmpNode.InsertKey((int*)pValue, Block, Index);
	}
	else if(m_sKeyType == "float") {
		Node<float> tmpNode(m_iKeyTypeCount, this);
		tmpNode.SetFileOrganize(m_file);	
		tmpNode.SetSelfPosition(m_iRoot[0], m_iRoot[1]);
		tmpNode.Read();

		int tmpBlock, tmpIndex;
		int FindIndex = 0;
		while(!tmpNode.IsLeaf()) {
			FindIndex = tmpNode.FindGreaterKeyIndex((float*)pValue);
			if(FindIndex == -1)
				FindIndex = tmpNode.GetCount();
			tmpNode.GetPointer(FindIndex, tmpBlock, tmpIndex);
			tmpNode.SetSelfPosition(tmpBlock, tmpIndex);
			tmpNode.Read();
		}
		tmpNode.InsertKey((float*)pValue, Block, Index);
	}
	else if(m_sKeyType == "date") {
		Node<int> tmpNode(m_iKeyTypeCount, this);
		tmpNode.SetFileOrganize(m_file);	
		tmpNode.SetSelfPosition(m_iRoot[0], m_iRoot[1]);
		tmpNode.Read();

		int tmpBlock, tmpIndex;
		int FindIndex = 0;
		while(!tmpNode.IsLeaf()) {
			FindIndex = tmpNode.FindGreaterKeyIndex((int*)pValue);
			if(FindIndex == -1)
				FindIndex = tmpNode.GetCount();
			tmpNode.GetPointer(FindIndex, tmpBlock, tmpIndex);
			tmpNode.SetSelfPosition(tmpBlock, tmpIndex);
			tmpNode.Read();
		}
		tmpNode.InsertKey((int*)pValue, Block, Index);
	}
}

void BTree::DeleteValue(void* pValue)
{
	if(m_iRoot[0] < 0 || m_iRoot[1] < 0 || m_file == NULL)
		throw new Exception("no root when find value in B+tree");
	if((m_sKeyType != "text" && m_sKeyType != "int" && 
		m_sKeyType != "date" && m_sKeyType != "float") ||
		m_iKeyTypeCount <= 0 )
		throw new Exception("error input for find value in b+");
	if(m_sKeyType == "text") {
		Node<char> tmpNode(m_iKeyTypeCount + 1, this);
		tmpNode.SetFileOrganize(m_file);
		tmpNode.SetSelfPosition(m_iRoot[0], m_iRoot[1]);
		tmpNode.Read();

		int tmpBlock, tmpIndex;
		int FindIndex = 0;
		while(!tmpNode.IsLeaf()) {			
			FindIndex = tmpNode.FindGreaterKeyIndex((char*)pValue);
			if(FindIndex == -1)										
				FindIndex = tmpNode.GetCount();						
			tmpNode.GetPointer(FindIndex, tmpBlock, tmpIndex);	
			tmpNode.SetSelfPosition(tmpBlock, tmpIndex);		
			tmpNode.Read();
		}
		tmpNode.DeleteKey(tmpNode.FindKeyIndex((char*)pValue));	
	}
	else if(m_sKeyType == "int") {
		Node<int> tmpNode(m_iKeyTypeCount, this);
		tmpNode.SetFileOrganize(m_file);	
		tmpNode.SetSelfPosition(m_iRoot[0], m_iRoot[1]);
		tmpNode.Read();

		int tmpBlock, tmpIndex;
		int FindIndex = 0;
		while(!tmpNode.IsLeaf()) {
			FindIndex = tmpNode.FindGreaterKeyIndex((int*)pValue);
			if(FindIndex == -1)
				FindIndex = tmpNode.GetCount();
			tmpNode.GetPointer(FindIndex, tmpBlock, tmpIndex);
			tmpNode.SetSelfPosition(tmpBlock, tmpIndex);
			tmpNode.Read();
		}
		tmpNode.DeleteKey(tmpNode.FindKeyIndex((int*)pValue));
	}
	else if(m_sKeyType == "float") {
		Node<float> tmpNode(m_iKeyTypeCount, this);
		tmpNode.SetFileOrganize(m_file);	
		tmpNode.SetSelfPosition(m_iRoot[0], m_iRoot[1]);
		tmpNode.Read();

		int tmpBlock, tmpIndex;
		int FindIndex = 0;
		while(!tmpNode.IsLeaf()) {
			FindIndex = tmpNode.FindGreaterKeyIndex((float*)pValue);
			if(FindIndex == -1)
				FindIndex = tmpNode.GetCount();
			tmpNode.GetPointer(FindIndex, tmpBlock, tmpIndex);
			tmpNode.SetSelfPosition(tmpBlock, tmpIndex);
			tmpNode.Read();
		}
		tmpNode.DeleteKey(tmpNode.FindKeyIndex((float*)pValue));

	}
	else if(m_sKeyType == "date") {
		Node<int> tmpNode(m_iKeyTypeCount, this);
		tmpNode.SetFileOrganize(m_file);	
		tmpNode.SetSelfPosition(m_iRoot[0], m_iRoot[1]);
		tmpNode.Read();

		int tmpBlock, tmpIndex;
		int FindIndex = 0;
		while(!tmpNode.IsLeaf()) {
			FindIndex = tmpNode.FindGreaterKeyIndex((int*)pValue);
			if(FindIndex == -1)
				FindIndex = tmpNode.GetCount();
			tmpNode.GetPointer(FindIndex, tmpBlock, tmpIndex);
			tmpNode.SetSelfPosition(tmpBlock, tmpIndex);
			tmpNode.Read();
		}
		tmpNode.DeleteKey(tmpNode.FindKeyIndex((int*)pValue));
	}
}

void BTree::DropNode(int Block, int Index)			
{
	if(m_file == NULL)
		throw new Exception("no root when find value in B+tree");
	if((m_sKeyType != "text" && m_sKeyType != "int" && 
		m_sKeyType != "date" && m_sKeyType != "float") ||
		m_iKeyTypeCount <= 0 )
		throw new Exception("error input for find value in b+");
	if(m_sKeyType == "text") {
		Node<char> tmpNode(m_iKeyTypeCount + 1, this);
		tmpNode.SetFileOrganize(m_file);
		tmpNode.SetSelfPosition(Block, Index);
		tmpNode.Read();

		int tmpBlock, tmpIndex;
		if(tmpNode.IsLeaf())				
			tmpNode.FreeNode();					
		else {												
			for(int i = 0; i < tmpNode.GetCount(); ++i) {
				tmpNode.GetPointer(i, tmpBlock, tmpIndex);
				DropNode(tmpBlock, tmpIndex);
			}
			tmpNode.FreeNode();										
		}
	}
	else if(m_sKeyType == "int") {
		Node<int> tmpNode(m_iKeyTypeCount, this);
		tmpNode.SetFileOrganize(m_file);
		tmpNode.SetSelfPosition(Block, Index);
		tmpNode.Read();

		int tmpBlock, tmpIndex;
		if(tmpNode.IsLeaf())
			tmpNode.FreeNode();
		else {
			for(int i = 0; i < tmpNode.GetCount(); ++i) {
				tmpNode.GetPointer(i, tmpBlock, tmpIndex);
				DropNode(tmpBlock, tmpIndex);
			}
			tmpNode.FreeNode();	
		}
	}
	else if(m_sKeyType == "float") {
		Node<float> tmpNode(m_iKeyTypeCount, this);
		tmpNode.SetFileOrganize(m_file);
		tmpNode.SetSelfPosition(Block, Index);
		tmpNode.Read();

		int tmpBlock, tmpIndex;
		if(tmpNode.IsLeaf())
			tmpNode.FreeNode();
		else {
			for(int i = 0; i < tmpNode.GetCount(); ++i) {
				tmpNode.GetPointer(i, tmpBlock, tmpIndex);
				DropNode(tmpBlock, tmpIndex);
			}
			tmpNode.FreeNode();	
		}
	}
	else if(m_sKeyType == "date") {
		Node<int> tmpNode(m_iKeyTypeCount, this);
		tmpNode.SetFileOrganize(m_file);
		tmpNode.SetSelfPosition(Block, Index);
		tmpNode.Read();

		int tmpBlock, tmpIndex;
		if(tmpNode.IsLeaf())
			tmpNode.FreeNode();
		else {
			for(int i = 0; i < tmpNode.GetCount(); ++i) {
				tmpNode.GetPointer(i, tmpBlock, tmpIndex);
				DropNode(tmpBlock, tmpIndex);
			}
			tmpNode.FreeNode();	
		}
	}
}

void BTree::Drop()								
{
	if(m_iRoot[0] < 0 || m_iRoot[1] < 0 ||
		m_iFirstLeaf[0] < 0 || m_iFirstLeaf[1] < 0
		|| m_file == NULL)
		throw new Exception("error when drop B+");
	DropNode(m_iRoot[0], m_iRoot[1]);						

	m_sKeyType = "";
	m_iKeyTypeCount = 0;

	m_iRoot[0] = -1;
	m_iRoot[1] = -1;
	m_iFirstLeaf[0] = -1;
	m_iFirstLeaf[1] = -1;

	m_iTreePosition[0] = -1;
	m_iTreePosition[1] = -1;
}

void BTree::UpdateBPlusTree()	
{
	int tmpBlock, tmpIndex;
	GetSelfPosition(tmpBlock, tmpIndex);
	int Size = 100;
	m_file->Write(&m_iRoot[0],2*sizeof(int));
	m_file->Write(&m_iRoot[1], 2*sizeof(int));
	m_file->Write(&m_iFirstLeaf[0], 2*sizeof(int));
	m_file->Write(&m_iRoot[0], sizeof(int)*2);
}

BTree::BTree()
{
	m_sKeyType = "";
	m_iKeyTypeCount = 0;

	m_iRoot[0] = -1;
	m_iRoot[1] = -1;
	m_iFirstLeaf[0] = -1;
	m_iFirstLeaf[1] = -1;

	m_iTreePosition[0] = -1;
	m_iTreePosition[1] = -1;
	m_file = NULL;
}

BTree::~BTree(void)	
{
	while(m_aReaders.GetSize() != 0) {
		if(m_aReaders.GetAt(0) == NULL) {
			m_aReaders.RemoveAt(0);
		}
		else {
			delete (BTreeReader*)(m_aReaders.GetAt(0));
			m_aReaders.RemoveAt(0);
		}
	}
}

void BTree::CreateBPlusTree(CString KeyType, int KeyTypeCount)
{
	if(m_file == NULL)
		throw new Exception("init before create b+tree");
	m_sKeyType = KeyType;
	m_iKeyTypeCount = KeyTypeCount;
	if((m_sKeyType != "text" && m_sKeyType != "int" && 
		m_sKeyType != "date" && m_sKeyType != "float") ||
		m_iKeyTypeCount <= 0)
		throw new Exception("error input for create B+ Tree");

	if(m_sKeyType=="text") {							
		Node<char> tmpNode(m_iKeyTypeCount + 1, this);
		tmpNode.SetFileOrganize(m_file);
		tmpNode.SetCount(0);
		tmpNode.SetLeaf(1);
		tmpNode.AddNode();
		tmpNode.GetSelfPosition(m_iRoot[0], m_iRoot[1]);
	}
	else if(m_sKeyType=="int") {
		Node<int> tmpNode(m_iKeyTypeCount, this);
		tmpNode.SetFileOrganize(m_file);
		tmpNode.SetCount(0);
		tmpNode.SetLeaf(1);
		tmpNode.AddNode();
		tmpNode.GetSelfPosition(m_iRoot[0],m_iRoot[1]);
	}
	else if(m_sKeyType=="float") {
		Node<float> tmpNode(m_iKeyTypeCount, this);
		tmpNode.SetFileOrganize(m_file);
		tmpNode.SetCount(0);
		tmpNode.SetLeaf(1);
		tmpNode.AddNode();
		tmpNode.GetSelfPosition(m_iRoot[0],m_iRoot[1]);
	}
	else if(m_sKeyType=="date")	
	{
		Node<int> tmpNode(m_iKeyTypeCount, this);
		tmpNode.SetFileOrganize(m_file);
		tmpNode.SetCount(0);
		tmpNode.SetLeaf(1);
		tmpNode.AddNode();
		tmpNode.GetSelfPosition(m_iRoot[0],m_iRoot[1]);
	}
	
	m_iFirstLeaf[0]=m_iRoot[0];
	m_iFirstLeaf[1]=m_iRoot[1];

	int Size = 0;
	Size = m_sKeyType.GetLength() + 1 + sizeof(int) * 5;
	char* c = new char[Size];
	char* p = c;
	_tcscpy(c, m_sKeyType);
	p += m_sKeyType.GetLength();
	*p = '\0';
	p++;
	*(int*)p = m_iKeyTypeCount;
	p += sizeof(int);
	((int*)p)[0] = m_iRoot[0];
	((int*)p)[1] = m_iRoot[1];
	p += (2*sizeof(int));
	((int*)p)[0] = m_iFirstLeaf[0];
	((int*)p)[1] = m_iFirstLeaf[1];
	m_file->Write(&m_iTreePosition[0], sizeof(int)*2);
	delete[] c;
}

void BTree::Read()
{	
	if(m_file == NULL)
		throw new Exception("error now store in b+tree");
	if(m_iTreePosition[0] < 0 || m_iTreePosition[1] < 0  )
		throw new Exception("no init position before read b+ tree");

	int Size = 0;
	m_file->Write((void *)&m_iTreePosition[0], sizeof(int));
	char* c = new char[Size];
	char* p = c;
	m_file->Write((void *)&m_iTreePosition[0], sizeof(int));	
	m_sKeyType = p;
	p += m_sKeyType.GetLength() + 1;

	m_iKeyTypeCount = *(int*)p;
	p += sizeof(int);
	m_iRoot[0] = ((int*)p)[0];
	m_iRoot[1] = ((int*)p)[1];
	p += 2 * sizeof(int);
	m_iFirstLeaf[0] = ((int*)p)[0];
	m_iFirstLeaf[1] = ((int*)p)[1];
	delete[] c;
}

bool BTree::FindValue(void* pValue, int& Block, int& Index)
{
	if(m_iRoot[0] < 0 || m_iRoot[1] < 0 || m_file == NULL)
		throw new Exception("no root when find value in B+tree");
	if((m_sKeyType != "text" && m_sKeyType != "int" && 
		m_sKeyType != "date" && m_sKeyType != "float") ||
		m_iKeyTypeCount <= 0)
		throw new Exception("error input for find value in b+");
	if(m_sKeyType == "text") {
		Node<char> tmpNode(m_iKeyTypeCount + 1, this);
		tmpNode.SetFileOrganize(m_file);	
		tmpNode.SetSelfPosition(m_iRoot[0],m_iRoot[1]);
		tmpNode.Read();
		int tmpBlock, tmpIndex;
		int FindIndex = 0;
		while(!tmpNode.IsLeaf()) {	
			FindIndex = tmpNode.FindGreaterKeyIndex((char*)pValue);	
			if(FindIndex == -1)									
				FindIndex = tmpNode.GetCount();					
			tmpNode.GetPointer(FindIndex, tmpBlock, tmpIndex);	
			tmpNode.SetSelfPosition(tmpBlock, tmpIndex);
			tmpNode.Read();
		}
		FindIndex = tmpNode.FindKeyIndex((char*)pValue);		
		if(FindIndex < 0)										
			return false;
		tmpNode.GetPointer(FindIndex, Block, Index);			
	}
	else if(m_sKeyType == "int")
	{
		Node<int> tmpNode(m_iKeyTypeCount, this);
		tmpNode.SetFileOrganize(m_file);	
		tmpNode.SetSelfPosition(m_iRoot[0], m_iRoot[1]);
		tmpNode.Read();
		int tmpBlock, tmpIndex;
		int FindIndex = 0;
		while(!tmpNode.IsLeaf()) {
			FindIndex = tmpNode.FindGreaterKeyIndex((int*)pValue);
			if(FindIndex == -1)
				FindIndex = tmpNode.GetCount();
			tmpNode.GetPointer(FindIndex, tmpBlock, tmpIndex);
			tmpNode.SetSelfPosition(tmpBlock, tmpIndex);
			tmpNode.Read();
		}
		FindIndex = tmpNode.FindKeyIndex((int*)pValue);
		if(FindIndex < 0)
			return false;
		tmpNode.GetPointer(FindIndex, Block, Index);
	}

	else if(m_sKeyType == "float")
	{
		Node<float> tmpNode(m_iKeyTypeCount, this);
		tmpNode.SetFileOrganize(m_file);	
		tmpNode.SetSelfPosition(m_iRoot[0], m_iRoot[1]);
		tmpNode.Read();
		int tmpBlock, tmpIndex;
		int FindIndex = 0;
		while(!tmpNode.IsLeaf()) {
			FindIndex = tmpNode.FindGreaterKeyIndex((float*)pValue);
			if(FindIndex == -1)
				FindIndex = tmpNode.GetCount();
			tmpNode.GetPointer(FindIndex, tmpBlock, tmpIndex);
			tmpNode.SetSelfPosition(tmpBlock, tmpIndex);
			tmpNode.Read();
		}
		FindIndex = tmpNode.FindKeyIndex((float*)pValue);
		if(FindIndex < 0)
			return false;
		tmpNode.GetPointer(FindIndex, Block, Index);
	}
	else if(m_sKeyType=="date") {
		Node<int> tmpNode(m_iKeyTypeCount, this);
		tmpNode.SetFileOrganize(m_file);	
		tmpNode.SetSelfPosition(m_iRoot[0], m_iRoot[1]);
		tmpNode.Read();
		int tmpBlock, tmpIndex;
		int FindIndex = 0;
		while(!tmpNode.IsLeaf()) {
			FindIndex = tmpNode.FindGreaterKeyIndex((int*)pValue);
			if(FindIndex == -1)
				FindIndex = tmpNode.GetCount();
			tmpNode.GetPointer(FindIndex, tmpBlock, tmpIndex);
			tmpNode.SetSelfPosition(tmpBlock, tmpIndex);
			tmpNode.Read();
		}
		FindIndex = tmpNode.FindKeyIndex((int*)pValue);
		if(FindIndex < 0)
			return false;
		tmpNode.GetPointer(FindIndex, Block, Index);
	}
	return true;
}

bool BTree::FindValueBigger(void* pValue, record& Record)	
{
	if(m_iRoot[0] < 0 || m_iRoot[1] < 0 || m_file == NULL)
		throw new Exception("no root when find value in B+tree");
	if((m_sKeyType != "text" && m_sKeyType != "int" && 
		m_sKeyType != "date" && m_sKeyType != "float") ||
		m_iKeyTypeCount <= 0)
		throw new Exception("error init for find bigger value in b+");
	int ReadNumber = Record.attribute_count;
	int FindIndex = -1;
	int BFindIndex = -1;
	int tmpBlock, tmpIndex;
	BTreeReader* Reader;
	void* tmpNode;
	int Block, Index;
	if(ReadNumber == -1) {									
		Reader = new BTreeReader;
		ReadNumber = m_aReaders.GetSize();
		Record.position.block_position = Record.position.index_position = 0;
		m_aReaders.Add((CObject*)Reader);
		FindIndex = -1;
		BFindIndex = -1;
		Reader->SetFindIndex(-1);
		Reader->SetBFindIndex(-1);

		if(m_sKeyType == "text") {
			tmpNode = new Node<char>(m_iKeyTypeCount + 1, this);	
			((Node<char>*)tmpNode)->SetFileOrganize(m_file);
			Reader->SetNode((void*)tmpNode);
		}
		else if(m_sKeyType == "int") {
			tmpNode = new Node<int>(m_iKeyTypeCount, this);
			((Node<int>*)tmpNode)->SetFileOrganize(m_file);
			Reader->SetNode((void*)tmpNode);
		}
		else if(m_sKeyType == "float") {
			tmpNode = new Node<float>(m_iKeyTypeCount, this);
			((Node<float>*)tmpNode)->SetFileOrganize(m_file);
			Reader->SetNode((void*)tmpNode);
		}
		else if(m_sKeyType == "date") {
			tmpNode = new Node<int>(m_iKeyTypeCount, this);
			((Node<int>*)tmpNode)->SetFileOrganize(m_file);
			Reader->SetNode((void*)tmpNode);
		}
	}
	else {										
		Reader = (BTreeReader*)(m_aReaders.GetAt(ReadNumber));
		FindIndex = Reader->GetFindIndex();
		BFindIndex = Reader->GetBFindIndex();
		tmpNode = Reader->GetNode();
	}
	if(m_sKeyType == "text") {
		if(FindIndex == -1) {
			((Node<char>*)tmpNode)->SetSelfPosition(m_iRoot[0], m_iRoot[1]);	
			((Node<char>*)tmpNode)->Read();
			while(!((Node<char>*)tmpNode)->IsLeaf()) {		 				
				FindIndex = ((Node<char>*)tmpNode)->FindGreaterKeyIndex((char*)pValue);	
				if(FindIndex == -1)											
					FindIndex = ((Node<char>*)tmpNode)->GetCount();		
				((Node<char>*)tmpNode)->GetPointer(FindIndex, tmpBlock, tmpIndex);
				((Node<char>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
				((Node<char>*)tmpNode)->Read();
			}
			FindIndex = ((Node<char>*)tmpNode)->FindKeyIndex((char*)pValue);	
		}
		if(FindIndex < 0) {														
			Record.position.block_position = Record.position.index_position = -1;
			FindIndex = -1;
			BFindIndex = -1;
			delete (Node<char>*)(Reader->GetNode());						
			delete Reader;
			m_aReaders.SetAt(ReadNumber, NULL);
			while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
				m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
				if(m_aReaders.GetSize() == 0)
					break;
			}
			return false;													
		}
		++FindIndex;															
		if(FindIndex >= ((Node<char>*)tmpNode)->GetCount()) {					
			((Node<char>*)tmpNode)->GetPointer(FANOUT - 1, tmpBlock, tmpIndex);	
			if(tmpBlock < 0 || tmpIndex < 0) {								
				Record.position.block_position = Record.position.index_position = -1;
				FindIndex = -1;
				BFindIndex = -1;
				delete (Node<char>*)(Reader->GetNode());					
				delete Reader;
				m_aReaders.SetAt(ReadNumber,NULL);
				while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
					m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
					if(m_aReaders.GetSize() == 0)
						break;
				}
				return false;												
			}
			((Node<char>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);	
			((Node<char>*)tmpNode)->Read();
			FindIndex = 0;
		}
		((Node<char>*)tmpNode)->GetPointer(FindIndex, Block, Index);	
		Record.position.block_position = Block;
		Record.position.index_position = Index;							
		Reader->SetFindIndex(FindIndex);
		Reader->SetBFindIndex(BFindIndex);
		return true;
	}
	else if(m_sKeyType == "int") {
		if(FindIndex == -1) {
			((Node<int>*)tmpNode)->SetSelfPosition(m_iRoot[0], m_iRoot[1]);
			((Node<int>*)tmpNode)->Read();
			while(!((Node<int>*)tmpNode)->IsLeaf()) {
				FindIndex = ((Node<int>*)tmpNode)->FindGreaterKeyIndex((int*)pValue);
				if(FindIndex == -1)
					FindIndex = ((Node<int>*)tmpNode)->GetCount();
				((Node<int>*)tmpNode)->GetPointer(FindIndex, tmpBlock, tmpIndex);
				((Node<int>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
				((Node<int>*)tmpNode)->Read();
			}
			FindIndex = ((Node<int>*)tmpNode)->FindKeyIndex((int*)pValue);
		}
		if(FindIndex < 0) {
			Record.position.block_position = Record.position.index_position = -1;
			FindIndex = -1;
			BFindIndex = -1;
			delete (Node<int>*)(Reader->GetNode());
			delete Reader;
			m_aReaders.SetAt(ReadNumber, NULL);
			while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
				m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
				if(m_aReaders.GetSize() == 0)
					break;
			}
			return false;
		}
		++FindIndex;
		if(FindIndex >= ((Node<int>*)tmpNode)->GetCount()) {
			((Node<int>*)tmpNode)->GetPointer(FANOUT - 1, tmpBlock, tmpIndex);
			if(tmpBlock < 0 || tmpIndex < 0) {
				Record.position.block_position = Record.position.index_position = -1;
				FindIndex = -1;
				BFindIndex = -1;
				delete (Node<int>*)(Reader->GetNode());
				delete Reader;
				m_aReaders.SetAt(ReadNumber,NULL);
				while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
					m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
					if(m_aReaders.GetSize() == 0)
						break;
				}
				return false;
			}
			((Node<int>*)tmpNode)->SetSelfPosition(tmpBlock,tmpIndex);
			((Node<int>*)tmpNode)->Read();
			FindIndex = 0;
		}
		((Node<int>*)tmpNode)->GetPointer(FindIndex, Block, Index);
		Record.position.block_position = Record.position.index_position = -1;
		Reader->SetFindIndex(FindIndex);
		Reader->SetBFindIndex(BFindIndex);
		return true;
	}
	else if(m_sKeyType == "float") {
		if(FindIndex == -1) {
			((Node<float>*)tmpNode)->SetSelfPosition(m_iRoot[0], m_iRoot[1]);
			((Node<float>*)tmpNode)->Read();
			while(!((Node<float>*)tmpNode)->IsLeaf()) {
				FindIndex = ((Node<float>*)tmpNode)->FindGreaterKeyIndex((float*)pValue);
				if(FindIndex == -1)
					FindIndex=((Node<float>*)tmpNode)->GetCount();
				((Node<float>*)tmpNode)->GetPointer(FindIndex, tmpBlock, tmpIndex);
				((Node<float>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
				((Node<float>*)tmpNode)->Read();
			}
			FindIndex = ((Node<float>*)tmpNode)->FindKeyIndex((float*)pValue);
		}
		if(FindIndex < 0) {
			Record.position.block_position = Record.position.index_position = -1;
			FindIndex = -1;
			BFindIndex = -1;
			delete (Node<float>*)(Reader->GetNode());
			delete Reader;
			m_aReaders.SetAt(ReadNumber, NULL);
			while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
				m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
				if(m_aReaders.GetSize() == 0)
					break;
			}
			return false;
		}
		++FindIndex;
		if(FindIndex >= ((Node<float>*)tmpNode)->GetCount()) {
			((Node<float>*)tmpNode)->GetPointer(FANOUT - 1, tmpBlock, tmpIndex);
			if(tmpBlock < 0 || tmpIndex < 0) {
				Record.position.block_position = Record.position.index_position = -1;
				FindIndex = -1;
				BFindIndex = -1;
				delete (Node<float>*)(Reader->GetNode());
				delete Reader;
				m_aReaders.SetAt(ReadNumber, NULL);
				while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
					m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
					if(m_aReaders.GetSize() == 0)
						break;
				}
				return false;
			}
			((Node<float>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
			((Node<float>*)tmpNode)->Read();
			FindIndex = 0;
		}
		((Node<float>*)tmpNode)->GetPointer(FindIndex, Block, Index);
		Record.position.block_position = Record.position.index_position = -1;
		Reader->SetFindIndex(FindIndex);
		Reader->SetBFindIndex(BFindIndex);
		return true;
	}
	else if(m_sKeyType == "date") {
		if(FindIndex == -1) {
			((Node<int>*)tmpNode)->SetSelfPosition(m_iRoot[0], m_iRoot[1]);
			((Node<int>*)tmpNode)->Read();
			while(!((Node<int>*)tmpNode)->IsLeaf()) {
				FindIndex = ((Node<int>*)tmpNode)->FindGreaterKeyIndex((int*)pValue);
				if(FindIndex == -1)
					FindIndex = ((Node<int>*)tmpNode)->GetCount();
				((Node<int>*)tmpNode)->GetPointer(FindIndex, tmpBlock, tmpIndex);
				((Node<int>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
				((Node<int>*)tmpNode)->Read();
			}
			FindIndex = ((Node<int>*)tmpNode)->FindKeyIndex((int*)pValue);
		}
		if(FindIndex < 0) {
			Record.position.block_position = Record.position.index_position = -1;
			FindIndex = -1;
			BFindIndex = -1;
			delete (Node<int>*)(Reader->GetNode());
			delete Reader;
			m_aReaders.SetAt(ReadNumber, NULL);
			while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
				m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
				if(m_aReaders.GetSize() == 0)
					break;
			}
			return false;
		}
		++FindIndex;
		if(FindIndex >= ((Node<int>*)tmpNode)->GetCount()) {
			((Node<int>*)tmpNode)->GetPointer(FANOUT - 1, tmpBlock, tmpIndex);
			if(tmpBlock < 0 || tmpIndex < 0) {
				Record.position.block_position = Record.position.index_position = -1;
				FindIndex = -1;
				BFindIndex = -1;
				delete (Node<int>*)(Reader->GetNode());
				delete Reader;
				m_aReaders.SetAt(ReadNumber, NULL);
				while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
					m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
					if(m_aReaders.GetSize() == 0)
						break;
				}
				return false;
			}
			((Node<int>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
			((Node<int>*)tmpNode)->Read();
			FindIndex = 0;
		}
		((Node<int>*)tmpNode)->GetPointer(FindIndex, Block, Index);
		Record.position.block_position = Block;
		Record.position.index_position = Index;
		Reader->SetFindIndex(FindIndex);
		Reader->SetBFindIndex(BFindIndex);
		return true;
	}
}

bool BTree::FindValueSmaller(void* pValue, record& Record)	
{
	if(m_iRoot[0] < 0 ||m_iRoot[1] < 0 || m_file == NULL)
		throw new Exception("no root when find value in B+tree");
	if((m_sKeyType != "char" && m_sKeyType != "int" && 
		m_sKeyType != "date" && m_sKeyType != "float") ||
		m_iKeyTypeCount <= 0 )
		throw new Exception("error init for find bigger value in b+");
	int ReadNumber = Record.attribute_count;
	int FindIndex = -1;
	int BFindIndex = -1;
	int tmpBlock, tmpIndex;
	BTreeReader* Reader;
	void* tmpNode;
	int Block, Index;
	if(ReadNumber == -1) {								
		Reader = new BTreeReader;
		ReadNumber = m_aReaders.GetSize();
		Record.attribute_count = ReadNumber;
		m_aReaders.Add((CObject*)Reader);
		FindIndex = -1;
		BFindIndex = -1;
		Reader->SetFindIndex(-1);
		Reader->SetBFindIndex(-1);
		if(m_sKeyType == "text") {
			tmpNode = new Node<char>(m_iKeyTypeCount + 1, this);
			((Node<char>*)tmpNode)->SetFileOrganize(m_file);
			Reader->SetNode((void*)tmpNode);
		}
		else if(m_sKeyType == "int") {
			tmpNode = new Node<int>(m_iKeyTypeCount, this);
			((Node<int>*)tmpNode)->SetFileOrganize(m_file);
			Reader->SetNode((void*)tmpNode);
		}
		else if(m_sKeyType == "float") {
			tmpNode = new Node<float>(m_iKeyTypeCount,this);
			((Node<float>*)tmpNode)->SetFileOrganize(m_file);
			Reader->SetNode((void*)tmpNode);
		}
		else if(m_sKeyType == "date") {
			tmpNode = new Node<int>(m_iKeyTypeCount,this);
			((Node<int>*)tmpNode)->SetFileOrganize(m_file);
			Reader->SetNode((void*)tmpNode);
		}
	}
	else {													
		Reader = (BTreeReader*)(m_aReaders.GetAt(ReadNumber));
		FindIndex = Reader->GetFindIndex();
		BFindIndex = Reader->GetBFindIndex();
		tmpNode = Reader->GetNode();
	}
	if(m_sKeyType == "text") {
		if(FindIndex == -1) {
			((Node<char>*)tmpNode)->SetSelfPosition(m_iFirstLeaf[0], m_iFirstLeaf[1]);
			((Node<char>*)tmpNode)->Read();
			BFindIndex = ((Node<char>*)tmpNode)->FindKeyIndex((char*)pValue);
		}
		if(FindIndex < 0) {					
			Record.position.block_position = Record.position.index_position = -1;
			FindIndex = -1;
			BFindIndex = -1;
			delete (Node<char>*)(Reader->GetNode());
			delete Reader;
			m_aReaders.SetAt(ReadNumber, NULL);
			while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
				m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
				if(m_aReaders.GetSize() == 0)
					break;
			}
			return false;
		}
		if(FindIndex + 1 > BFindIndex && BFindIndex != -1) {					
			Record.position.block_position = Record.position.index_position = -1;
			FindIndex = -1;
			BFindIndex = -1;
			delete (Node<char>*)(Reader->GetNode());
			delete Reader;
			m_aReaders.SetAt(ReadNumber, NULL);
			while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
				m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
				if(m_aReaders.GetSize() == 0)
					break;
			}
			return false;
		}
		((Node<char>*)tmpNode)->GetPointer(FindIndex, Block, Index);	
		Record.position.block_position = Record.position.index_position = -1;
		++FindIndex;
		if(FindIndex >= ((Node<char>*)tmpNode)->GetCount()) {
			((Node<char>*)tmpNode)->GetPointer(FANOUT - 1, tmpBlock, tmpIndex);
			if(tmpBlock < 0 || tmpIndex < 0) {
				FindIndex = -2;
			}
			((Node<char>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
			((Node<char>*)tmpNode)->Read();
			FindIndex = 0;
			BFindIndex = ((Node<char>*)tmpNode)->FindKeyIndex((char*)pValue);
		}
		Reader->SetFindIndex(FindIndex);
		Reader->SetBFindIndex(BFindIndex);
		return true;
	}
	else if(m_sKeyType == "int") {
		if(FindIndex == -1) {
			((Node<int>*)tmpNode)->SetSelfPosition(m_iFirstLeaf[0], m_iFirstLeaf[1]);
			((Node<int>*)tmpNode)->Read();
			BFindIndex = ((Node<int>*)tmpNode)->FindKeyIndex((int*)pValue);
			FindIndex = 0;
		}
		if(FindIndex < 0) {
			Record.position.block_position = Record.position.index_position = -1;
			FindIndex = -1;
			BFindIndex = -1;
			delete (Node<int>*)(Reader->GetNode());
			delete Reader;
			m_aReaders.SetAt(ReadNumber, NULL);
			while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
				m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
				if(m_aReaders.GetSize() == 0)
					break;
			}
			return false;
		}
		if(FindIndex + 1 > BFindIndex && BFindIndex != -1) {
			Record.position.block_position = Record.position.index_position = -1;
			FindIndex = -1;
			BFindIndex = -1;
			delete (Node<int>*)(Reader->GetNode());
			delete Reader;
			m_aReaders.SetAt(ReadNumber, NULL);
			while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
				m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
				if(m_aReaders.GetSize() == 0)
					break;
			}
			return false;
		}
		((Node<int>*)tmpNode)->GetPointer(FindIndex, Block, Index);
		Record.position.block_position = Record.position.index_position = -1;
		++FindIndex;

		if(FindIndex >= ((Node<int>*)tmpNode)->GetCount()) {
			((Node<int>*)tmpNode)->GetPointer(FANOUT - 1, tmpBlock, tmpIndex);
			if(tmpBlock < 0 || tmpIndex < 0) {
				FindIndex = -2;
			}
			((Node<int>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
			((Node<int>*)tmpNode)->Read();
			FindIndex = 0;
			BFindIndex = ((Node<int>*)tmpNode)->FindKeyIndex((int*)pValue);
		}
		Reader->SetFindIndex(FindIndex);
		Reader->SetBFindIndex(BFindIndex);
		return true;
	}
	else if(m_sKeyType == "float") {
		if(FindIndex == -1) {
			((Node<float>*)tmpNode)->SetSelfPosition(m_iFirstLeaf[0], m_iFirstLeaf[1]);
			((Node<float>*)tmpNode)->Read();

			BFindIndex = ((Node<float>*)tmpNode)->FindKeyIndex((float*)pValue);
			FindIndex = 0;
		}
		if(FindIndex < 0) {
			Record.position.block_position = Record.position.index_position = -1;
			FindIndex = -1;
			BFindIndex = -1;
			delete (Node<float>*)(Reader->GetNode());
			delete Reader;
			m_aReaders.SetAt(ReadNumber, NULL);
			while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
				m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
				if(m_aReaders.GetSize() == 0)
					break;
			}
			return false;
		}
		if(FindIndex + 1 > BFindIndex && BFindIndex != -1) {
			Record.position.block_position = Record.position.index_position = -1;
			FindIndex = -1;
			BFindIndex = -1;
			delete (Node<float>*)(Reader->GetNode());
			delete Reader;
			m_aReaders.SetAt(ReadNumber, NULL);
			while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
				m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
				if(m_aReaders.GetSize() == 0)
					break;
			}
			return false;
		}
		((Node<float>*)tmpNode)->GetPointer(FindIndex, Block, Index);
		Record.position.block_position = Block;
		Record.position.index_position = Index;
		++FindIndex;

		if(FindIndex >= ((Node<float>*)tmpNode)->GetCount()) {
			((Node<float>*)tmpNode)->GetPointer(FANOUT - 1, tmpBlock, tmpIndex);
			if(tmpBlock < 0 || tmpIndex < 0) {
				FindIndex = -2;
			}
			((Node<float>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
			((Node<float>*)tmpNode)->Read();
			FindIndex = 0;
			BFindIndex = ((Node<float>*)tmpNode)->FindKeyIndex((float*)pValue);
		}
		Reader->SetFindIndex(FindIndex);
		Reader->SetBFindIndex(BFindIndex);
		return true;
	}
	else if(m_sKeyType == "date") {
		if(FindIndex == -1) {
			((Node<int>*)tmpNode)->SetSelfPosition(m_iFirstLeaf[0], m_iFirstLeaf[1]);
			((Node<int>*)tmpNode)->Read();
			BFindIndex = ((Node<int>*)tmpNode)->FindKeyIndex((int*)pValue);
			FindIndex = 0;
		}
		if(FindIndex < 0) {
			Record.position.block_position = Record.position.index_position = -1;
			FindIndex = -1;
			BFindIndex = -1;
			delete (Node<int>*)(Reader->GetNode());
			delete Reader;
			m_aReaders.SetAt(ReadNumber, NULL);
			while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
				m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
				if(m_aReaders.GetSize() == 0)
					break;
			}
			return false;
		}
		if(FindIndex + 1 > BFindIndex && BFindIndex != -1) {
			Record.position.block_position = Record.position.index_position = -1;
			FindIndex = -1;
			BFindIndex = -1;
			delete (Node<int>*)(Reader->GetNode());
			delete Reader;
			m_aReaders.SetAt(ReadNumber, NULL);
			while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
				m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
				if(m_aReaders.GetSize() == 0)
					break;
			}
			return false;
		}
		((Node<int>*)tmpNode)->GetPointer(FindIndex, Block, Index);
			Record.position.block_position = Block;
			Record.position.index_position = Index;
		++FindIndex;
		if(FindIndex >= ((Node<int>*)tmpNode)->GetCount()) {
			((Node<int>*)tmpNode)->GetPointer(FANOUT - 1, tmpBlock, tmpIndex);
			if(tmpBlock < 0 || tmpIndex < 0) {
				FindIndex = -2;
			}
			((Node<int>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
			((Node<int>*)tmpNode)->Read();
			FindIndex = 0;
			BFindIndex = ((Node<int>*)tmpNode)->FindKeyIndex((int*)pValue);
		}
		Reader->SetFindIndex(FindIndex);
		Reader->SetBFindIndex(BFindIndex);
		return true;
	}
}

bool BTree::FindValueBetween(void* pBValue, void* pSValue, record& Record)
{
	if(m_iRoot[0] < 0 || m_iRoot[1] < 0 || m_file == NULL)
		throw new Exception("no root when find value in B+tree");
	if((m_sKeyType != "text" && m_sKeyType != "int" && 
		m_sKeyType != "date" && m_sKeyType != "float") ||
		m_iKeyTypeCount <= 0 )
		throw new Exception("error init for find bigger value in b+");
	int ReadNumber = Record.attribute_count;
	int FindIndex = -1;
	int BFindIndex = -1;
	int tmpBlock, tmpIndex;
	BTreeReader* Reader;
	void* tmpNode;
	int Block, Index;
	if(ReadNumber == -1) {
		Reader = new BTreeReader;
		ReadNumber = m_aReaders.GetSize();
		Record.attribute_count = ReadNumber;
		m_aReaders.Add((CObject*)Reader);
		FindIndex = -1;
		BFindIndex = -1;
		Reader->SetFindIndex(-1);
		Reader->SetBFindIndex(-1);

		if(m_sKeyType == "text") {
			tmpNode = new Node<char>(m_iKeyTypeCount + 1, this);
			((Node<char>*)tmpNode)->SetFileOrganize(m_file);
			Reader->SetNode((void*)tmpNode);
		}
		else if(m_sKeyType == "int") {
			tmpNode = new Node<int>(m_iKeyTypeCount, this);
			((Node<int>*)tmpNode)->SetFileOrganize(m_file);
			Reader->SetNode((void*)tmpNode);
		}
		else if(m_sKeyType == "float") {
			tmpNode = new Node<float>(m_iKeyTypeCount, this);
			((Node<float>*)tmpNode)->SetFileOrganize(m_file);
			Reader->SetNode((void*)tmpNode);
		}
		else if(m_sKeyType == "date") { 
			tmpNode=new Node<int>(m_iKeyTypeCount, this);
			((Node<int>*)tmpNode)->SetFileOrganize(m_file);
			Reader->SetNode((void*)tmpNode);
		}
	}
	else {
		Reader = (BTreeReader*)(m_aReaders.GetAt(ReadNumber));
		FindIndex = Reader->GetFindIndex();
		BFindIndex = Reader->GetBFindIndex();
		tmpNode = Reader->GetNode();
	}
	if(m_sKeyType == "text") {
		if(FindIndex == -1) {
			while(!((Node<char>*)tmpNode)->IsLeaf()) {
				FindIndex = ((Node<char>*)tmpNode)->FindGreaterKeyIndex((char*)pSValue);
				if(FindIndex == -1)
					FindIndex = ((Node<char>*)tmpNode)->GetCount();
				((Node<char>*)tmpNode)->GetPointer(FindIndex, tmpBlock, tmpIndex);
				((Node<char>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
				((Node<char>*)tmpNode)->Read();
			}
			FindIndex = ((Node<char>*)tmpNode)->FindKeyIndex((char*)pSValue);
			BFindIndex = ((Node<char>*)tmpNode)->FindKeyIndex((char*)pBValue);
		}
		if(FindIndex < 0) {
			Record.position.block_position = Record.position.index_position = -1;
			FindIndex = -1;
			BFindIndex = -1;
			delete (Node<char>*)(Reader->GetNode());
			delete Reader;
			m_aReaders.SetAt(ReadNumber, NULL);
			while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
				m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
				if(m_aReaders.GetSize() == 0)
					break;
			}
			return false;
		}
		++FindIndex;
		if(FindIndex > BFindIndex && BFindIndex != -1) {
			FindIndex = -2;
			Reader->SetFindIndex(-2);
			return false;
		}
		if(FindIndex >= ((Node<char>*)tmpNode)->GetCount()) {
			((Node<char>*)tmpNode)->GetFrontNodePosition(tmpBlock, tmpIndex);
			if(tmpBlock < 0 || tmpIndex < 0) {
				FindIndex = -2;
				Reader->SetFindIndex(-2);
				return false;
			}
			((Node<char>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
			((Node<char>*)tmpNode)->Read();
			BFindIndex=((Node<char>*)tmpNode)->FindKeyIndex((char*)pBValue);
			FindIndex = 0;
		}
		((Node<char>*)tmpNode)->GetPointer(FindIndex, Block, Index);
			Record.position.block_position = Block;
			Record.position.index_position = Index;
		Reader->SetFindIndex(FindIndex);
		Reader->SetBFindIndex(BFindIndex);
		return true;
	}
	else if(m_sKeyType == "int") {
		if(FindIndex == -1) {
			while(!((Node<int>*)tmpNode)->IsLeaf()) {
				FindIndex = ((Node<int>*)tmpNode)->FindGreaterKeyIndex((int*)pSValue);
				if(FindIndex == -1)
					FindIndex = ((Node<int>*)tmpNode)->GetCount();
				((Node<int>*)tmpNode)->GetPointer(FindIndex, tmpBlock, tmpIndex);
				((Node<int>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
				((Node<int>*)tmpNode)->Read();
			}
			FindIndex = ((Node<int>*)tmpNode)->FindKeyIndex((int*)pSValue);
			BFindIndex = ((Node<int>*)tmpNode)->FindKeyIndex((int*)pBValue);
		}
		if(FindIndex < 0) {
			Record.position.block_position = Record.position.index_position = -1;
			FindIndex = -1;
			BFindIndex = -1;
			delete (Node<int>*)(Reader->GetNode());
			delete Reader;
			m_aReaders.SetAt(ReadNumber, NULL);
			while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
				m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
				if(m_aReaders.GetSize() == 0)
					break;
			}
			return false;
		}
		++FindIndex;
		if(FindIndex > BFindIndex && BFindIndex != -1) {
			FindIndex = -2;
			Reader->SetFindIndex(-2);
			return false;
		}
		if(FindIndex >= ((Node<int>*)tmpNode)->GetCount()) {
			((Node<int>*)tmpNode)->GetFrontNodePosition(tmpBlock, tmpIndex);
			if(tmpBlock < 0 || tmpIndex < 0) {
				FindIndex = -2;
				Reader->SetFindIndex(-2);
				return false;
			}
			((Node<int>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
			((Node<int>*)tmpNode)->Read();
			BFindIndex=((Node<int>*)tmpNode)->FindKeyIndex((int*)pBValue);
			FindIndex = 0;
		}
		((Node<int>*)tmpNode)->GetPointer(FindIndex, Block, Index);
		Record.position.block_position = Block;
		Record.position.index_position = Index;
		Reader->SetFindIndex(FindIndex);
		Reader->SetBFindIndex(BFindIndex);
		return true;
	}
	else if(m_sKeyType == "float") {
		if(FindIndex == -1) {
			while(!((Node<float>*)tmpNode)->IsLeaf()) {
				FindIndex = ((Node<float>*)tmpNode)->FindGreaterKeyIndex((float*)pSValue);
				if(FindIndex == -1)
					FindIndex = ((Node<float>*)tmpNode)->GetCount();
				((Node<float>*)tmpNode)->GetPointer(FindIndex, tmpBlock, tmpIndex);
				((Node<float>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
				((Node<float>*)tmpNode)->Read();
			}
			FindIndex = ((Node<float>*)tmpNode)->FindKeyIndex((float*)pSValue);
			BFindIndex = ((Node<float>*)tmpNode)->FindKeyIndex((float*)pBValue);
		}
		if(FindIndex < 0) {
			Record.position.block_position = Record.position.index_position = -1;
			FindIndex = -1;
			BFindIndex = -1;
			delete (Node<float>*)(Reader->GetNode());
			delete Reader;
			m_aReaders.SetAt(ReadNumber, NULL);
			while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
				m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
				if(m_aReaders.GetSize() == 0)
					break;
			}
			return false;
		}
		++FindIndex;
		if(FindIndex > BFindIndex && BFindIndex != -1) {
			FindIndex = -2;
			Reader->SetFindIndex(-2);
			return false;
		}
		if(FindIndex >= ((Node<float>*)tmpNode)->GetCount()) {
			((Node<float>*)tmpNode)->GetFrontNodePosition(tmpBlock, tmpIndex);
			if(tmpBlock < 0 || tmpIndex < 0) {
				FindIndex = -2;
				Reader->SetFindIndex(-2);
				return false;
			}
			((Node<float>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
			((Node<float>*)tmpNode)->Read();
			BFindIndex = ((Node<float>*)tmpNode)->FindKeyIndex((float*)pBValue);
			FindIndex = 0;
		}
		((Node<float>*)tmpNode)->GetPointer(FindIndex, Block, Index);
		Record.position.block_position = Block;
		Record.position.index_position = Index;
		Reader->SetFindIndex(FindIndex);
		Reader->SetBFindIndex(BFindIndex);
		return true;
	}
	else if(m_sKeyType == "date") {
		if(FindIndex == -1) {
			while(!((Node<int>*)tmpNode)->IsLeaf()) {
				FindIndex = ((Node<int>*)tmpNode)->FindGreaterKeyIndex((int*)pSValue);
				if(FindIndex == -1)
					FindIndex = ((Node<int>*)tmpNode)->GetCount();
				((Node<int>*)tmpNode)->GetPointer(FindIndex, tmpBlock, tmpIndex);
				((Node<int>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
				((Node<int>*)tmpNode)->Read();
			}
			FindIndex = ((Node<int>*)tmpNode)->FindKeyIndex((int*)pSValue);
			BFindIndex = ((Node<int>*)tmpNode)->FindKeyIndex((int*)pBValue);
		}
		if(FindIndex < 0) {
			Record.position.block_position = Record.position.index_position = -1;
			FindIndex = -1;
			BFindIndex = -1;
			delete (Node<int>*)(Reader->GetNode());
			delete Reader;
			m_aReaders.SetAt(ReadNumber, NULL);
			while(m_aReaders.GetAt(m_aReaders.GetUpperBound()) == NULL) {
				m_aReaders.RemoveAt(m_aReaders.GetUpperBound());
				if(m_aReaders.GetSize() == 0)
					break;
			}
			return false;
		}
		++FindIndex;
		if(FindIndex > BFindIndex && BFindIndex != -1)
		{
			FindIndex = -2;
			Reader->SetFindIndex(-2);
			return false;
		}
		if(FindIndex >= ((Node<int>*)tmpNode)->GetCount()) {
			((Node<int>*)tmpNode)->GetFrontNodePosition(tmpBlock, tmpIndex);
			if(tmpBlock < 0 || tmpIndex < 0) {
				FindIndex = -2;
				Reader->SetFindIndex(-2);
				return false;
			}
			((Node<int>*)tmpNode)->SetSelfPosition(tmpBlock, tmpIndex);
			((Node<int>*)tmpNode)->Read();
			BFindIndex = ((Node<int>*)tmpNode)->FindKeyIndex((int*)pBValue);
			FindIndex = 0;
		}
		((Node<int>*)tmpNode)->GetPointer(FindIndex, Block, Index);
		Record.position.block_position = Block;
		Record.position.index_position = Index;
		Reader->SetFindIndex(FindIndex);
		Reader->SetBFindIndex(BFindIndex);
		return true;
	}
}
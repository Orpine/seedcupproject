#define NORMALL

#include "Buffer_Manager.h"

CBuffer::CBuffer( ) {
	for ( int i = 0; i < Block_Hold; i++) {
		Buffer[ i ] = NULL;
	}
}

Block_Info* CBuffer::GBlock( ) {
	Block_Info* Tmp;

	Tmp 			  	 = new Block_Info;
	Tmp -> address       = NULL;
	Tmp -> table_name    = '0';
	Tmp -> offset_number = 0;
	Tmp -> is_written    = false;
	Tmp -> being_used    = false;
	Tmp -> is_accessed	 = false;
	
	return Tmp;
} 

bool CBuffer::Init( ) {
	//初始化内存管理列表
    for ( int i = 0; i < Block_Hold; i++ ) {
		Buffer[ i ] = GBlock( );
		if ( Buffer[ i ] == NULL ) {
			return false;
		}
    }

	return true;
}

/**************************************************************************************************************/
// 实现了自己的Malloc函数，用以生成可用的内存空间；
Record_Info* CBuffer::Malloc( int Size ) {
	//std::cout << Size << std::endl;
	return ( Record_Info* )( new char[ Size ] );
}

/**************************************************************************************************************/
// 第一类GetBlock函数，主要是实现Record Manager和Buffer Manager之间的插入操作以及通讯。
// 调用的时候Buffer Manager会向我传递table_name以及要替换块的块首指针Passed;
// 如果执行插入操作，则Passed=NULL，否则，Passed=块首指针；
// 函数返回的值为Block_Info的类型。
Block_Info* CBuffer::GetBlock( string table_name, Block_Info* Passed ) {
	Block_Info *BlockInUse;
	int flag = 65535;
	
	if ( Passed == NULL ) {
		BlockInUse = GBlock( );
		//std::cout << Block_Size << std::endl;
		BlockInUse -> address = Malloc( Block_Size );
		if ( ( BlockInUse -> address ) == NULL ) {
			return NULL;
		}
		BlockInUse -> table_name  = table_name;
		BlockInUse -> is_accessed = true;
		return BlockInUse;
	} else {
		while ( flag > 0 ) {
			if ( Sched( table_name, Passed ) ) {
				BlockInUse = GBlock( );
				BlockInUse -> address = Malloc( Block_Size );
				if ( BlockInUse -> address == NULL ) {
					return NULL;
				}
				BlockInUse -> table_name;
				BlockInUse -> is_accessed = true;
				return BlockInUse;
			}
			
			flag--;
		} 
		
		return NULL;
	}
}

/**************************************************************************************************************/
// 第二类GetBlock函数，主要是用于实现Record Manager和Buffer Manager之间的查询操作以及通讯。
// 查询的时候Buffer Manager会向我传递table_name以及块在文件中的偏移量offset；
// 函数返回值为Block_Info类型。
Block_Info* CBuffer::GetBlock( string table_name, int offset ) {
	int flag = 65535;
	
	for ( int i = 0; i < Block_Hold; i++ ) {
		if ( Buffer[ i ] -> table_name == table_name ) {
			if ( Buffer[ i ] -> offset_number == offset ) {
				Buffer[ i ] -> is_accessed = true;
				return Buffer[ i ];
			}
		}
	}
	
	while ( flag > 0 ) {
		if ( Sched( table_name, offset ) ) {
			for ( int i = 0; i < Block_Hold; i++ ) {
				if ( Buffer[ i ] -> table_name == table_name ) {
					if ( Buffer[ i ] -> offset_number == offset ) {
						Buffer[ i ] -> is_accessed = true;
						return Buffer[ i ];
					}
				}
			}
		} else {
			flag--;
		}
	}
	
	return NULL;
}

/**************************************************************************************************************/
/*
	算法描述：
		设：A：访问位	M：修改位
		I类：	（ A=0，M=0 ）最近既未访问过，又未被修改；
		II类：	（ A=0，M=1 ）最近没有访问过，但是修改过；
		III类：	（ A=1，M=0 ）最近曾经访问过，但未被修改；
		IV类：	（ A=1，M=1 ）最近曾经访问过，也曾经修改；
		
		步骤：
		1.扫描循环队列，找出到一类页面，找到则淘汰该页；
		2.未找到，开始第二轮扫描，找到第二轮则淘汰该页并将所有访问过的页访问位置0；
		3.如果两轮扫描都失败，重复（1）（2）过程；
*/
//第一类的调度函数，主要用于实现非查询的内存调度
bool CBuffer::Sched( string table_name, Block_Info* Block ) {
	Block_Info *BlockInUse;
	int flag = 65535;
	
	while( flag > 0 ) {
		// 第一次扫描Buffer，找到第一类页面
		for ( int i = 0; i < Block_Hold; i++ ) {
			//if ( ( Buffer[ i ] -> table_name ) == table_name ) {
				if ( ( Buffer[ i ] -> is_written ) == false
				  && ( Buffer[ i ] -> is_accessed ) == false ) {
					BlockInUse = Buffer[ i ];
					Buffer[ i ] = Block;
					delete BlockInUse -> address;
					delete BlockInUse;
					return true;
				}
			//}
		}
		
		// 第二次扫描Buffer，找到第二类页面，并置零产生下一次扫描的第一、二类页面
		for ( int t = 0; t < Block_Hold; t++ ) {
			if ( ( Buffer[ t ] -> is_written ) == true
			  && ( Buffer[ t ] -> is_accessed ) == false ) {
				BlockInUse = Buffer[ t ];
				Buffer[ t ] = Block;
				HDExchange( table_name, BlockInUse );
				return true;
			}
			Buffer[ t ] -> is_accessed = false;
		}
		
		flag--;
	}
	
	return false;
}

/**************************************************************************************************************/
// 第二类的调度函数，主要用于实现查询类的内存调度
bool CBuffer::Sched( string table_name, int offset ) {
	Block_Info *BlockInUse;
	int flag = 65535;
	
	while ( flag > 0 ) {
		for ( int i = 0; i < Block_Hold; i++ ) {
			if ( ( Buffer[ i ] -> is_written ) == false 
			  && ( Buffer[ i ] -> is_accessed ) == false ) {
				BlockInUse = Buffer[ i ];
				Buffer[ i ] = HDExchange( table_name, BlockInUse, offset );
				return true;
			}
		}
		
		for ( int q = 0; q < Block_Hold; q++ ) {
			if ( ( Buffer[ q ] -> is_written ) == true
			  && ( Buffer[ q ] -> is_accessed ) == false ) {
				BlockInUse = Buffer[ q ];
				Buffer[ q ] = HDExchange( table_name, BlockInUse, offset );
				return true;
			}
			Buffer[ q ] -> is_accessed = false;
		}
		
		flag--;
	}
	
	return false;
}

/**************************************************************************************************************/
// 删除函数，主要用于删除表的操作，实现可用内存块的释放
bool CBuffer::DropTable( string table_name ) {
	Block_Info *BlockInUse;
	
	for ( int i = 0; i < Block_Hold; i++ ) {
		if ( ( Buffer[ i ] -> table_name ) == table_name ) {
			BlockInUse = Buffer[ i ];
			Buffer[ i ] = GBlock( );
			if ( Buffer[ i ] == NULL ) {
				return false;
			}
			delete BlockInUse -> address;
			delete BlockInUse;
		}
	}
	
	return true;
}

// 本函数是进行磁盘操作的函数，table_name传递的是要进行读操作的文件名；
// Block_Info传递的是被换出的块信息，offset传递的是块在文件中的偏移量。
Block_Info* CBuffer::HDExchange( string table_name, Block_Info* Block, int offset ) {
	FILE *fp;
	
	char FileName[ 256 ];
	int i, limit;
	
	limit = ( Block -> table_name ).size( );
	
	for ( i = 0; i < limit; i++ ) {
		FileName[ i ] = ( Block -> table_name ).at( i );
	}
	FileName[ i++ ] = '\0';
	
	if ( ( fp = fopen( FileName, "rb+" ) ) == NULL ) {
		std::cout << "Writing File Operation Error!" << std::endl;
		exit( 0 );
	}
	
	fseek( fp, ( ( Block -> offset_number ) * Block_Size ), SEEK_SET );
	fwrite( Block -> address, Block_Size, 1, fp );
	
	fclose( fp );
	
	delete Block -> address;
	delete Block;
	
	if ( offset != -1 ) {
		for ( i = 0; i < limit; i++ ) {
			FileName[ i ] = table_name.at( i );
		}
		FileName[ i++ ] = '\0';
		
		if ( ( fp = fopen( FileName, "r" ) ) == NULL ) {
			std::cout << "Reading File Operation Error!" << std::endl;
			exit( 0 );
		}

		Record_Info* Tmp = Malloc( Block_Size );
		Block_Info* BTmp = GBlock( );
		
		fseek( fp, ( offset * Block_Size ), SEEK_SET );
		fread( Tmp, Block_Size, 1, fp );
		
		fclose( fp );
		
		BTmp -> address 	  = Tmp;
		BTmp -> is_accessed   = true;
		BTmp -> table_name    = table_name;
		BTmp -> offset_number = offset;
				
		return BTmp;
	} else {
		return NULL;
	}
}

CBuffer::~CBuffer( ) {
	Block_Info *BlockInUse;
	
	for ( int i = 0; i < Block_Hold; i++ ) {
		BlockInUse = Buffer[ i ];
		if ( Buffer[ i ] != NULL ) {
			if ( ( BlockInUse -> is_written ) == true ) {
				HDExchange( ( BlockInUse -> table_name ), BlockInUse );
			}
			delete BlockInUse -> address;
			delete BlockInUse;
		}
	}
}

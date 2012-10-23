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
	//��ʼ���ڴ�����б�
    for ( int i = 0; i < Block_Hold; i++ ) {
		Buffer[ i ] = GBlock( );
		if ( Buffer[ i ] == NULL ) {
			return false;
		}
    }

	return true;
}

/**************************************************************************************************************/
// ʵ�����Լ���Malloc�������������ɿ��õ��ڴ�ռ䣻
Record_Info* CBuffer::Malloc( int Size ) {
	//std::cout << Size << std::endl;
	return ( Record_Info* )( new char[ Size ] );
}

/**************************************************************************************************************/
// ��һ��GetBlock��������Ҫ��ʵ��Record Manager��Buffer Manager֮��Ĳ�������Լ�ͨѶ��
// ���õ�ʱ��Buffer Manager�����Ҵ���table_name�Լ�Ҫ�滻��Ŀ���ָ��Passed;
// ���ִ�в����������Passed=NULL������Passed=����ָ�룻
// �������ص�ֵΪBlock_Info�����͡�
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
// �ڶ���GetBlock��������Ҫ������ʵ��Record Manager��Buffer Manager֮��Ĳ�ѯ�����Լ�ͨѶ��
// ��ѯ��ʱ��Buffer Manager�����Ҵ���table_name�Լ������ļ��е�ƫ����offset��
// ��������ֵΪBlock_Info���͡�
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
	�㷨������
		�裺A������λ	M���޸�λ
		I�ࣺ	�� A=0��M=0 �������δ���ʹ�����δ���޸ģ�
		II�ࣺ	�� A=0��M=1 �����û�з��ʹ��������޸Ĺ���
		III�ࣺ	�� A=1��M=0 ������������ʹ�����δ���޸ģ�
		IV�ࣺ	�� A=1��M=1 ������������ʹ���Ҳ�����޸ģ�
		
		���裺
		1.ɨ��ѭ�����У��ҳ���һ��ҳ�棬�ҵ�����̭��ҳ��
		2.δ�ҵ�����ʼ�ڶ���ɨ�裬�ҵ��ڶ�������̭��ҳ�������з��ʹ���ҳ����λ��0��
		3.�������ɨ�趼ʧ�ܣ��ظ���1����2�����̣�
*/
//��һ��ĵ��Ⱥ�������Ҫ����ʵ�ַǲ�ѯ���ڴ����
bool CBuffer::Sched( string table_name, Block_Info* Block ) {
	Block_Info *BlockInUse;
	int flag = 65535;
	
	while( flag > 0 ) {
		// ��һ��ɨ��Buffer���ҵ���һ��ҳ��
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
		
		// �ڶ���ɨ��Buffer���ҵ��ڶ���ҳ�棬�����������һ��ɨ��ĵ�һ������ҳ��
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
// �ڶ���ĵ��Ⱥ�������Ҫ����ʵ�ֲ�ѯ����ڴ����
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
// ɾ����������Ҫ����ɾ����Ĳ�����ʵ�ֿ����ڴ����ͷ�
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

// �������ǽ��д��̲����ĺ�����table_name���ݵ���Ҫ���ж��������ļ�����
// Block_Info���ݵ��Ǳ������Ŀ���Ϣ��offset���ݵ��ǿ����ļ��е�ƫ������
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

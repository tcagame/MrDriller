#include "BlockBomb.h"
#include "Board.h"


BlockBomb::BlockBomb( ) :
Block( 0, 16 * 25 ) {
}


BlockBomb::~BlockBomb( ) {
}


void BlockBomb::erase( bool connect_erase, bool destroy ) {
	//����̃u���b�N������
	const int ERASE_BLOCK[ 8 ][ 2 ]{
		{  0, -1 },//��
		{  0,  1 },//��
		{ -1,  0 },//��
		{  1,  0 },//�E
		{ -1, -1 },//����
		{  1, -1 },//�E��
		{ -1,  1 },//����
		{  1,  1 } //�E��
	};

	std::shared_ptr< Board > board = getBoard( );

	int mx = getX( ) / BLOCK_WIDTH;
	int my = getY( ) / BLOCK_HEIGHT;

	Block::erase( false, destroy );

	for ( int i = 0; i < 8; i++ ) {
		int check_mx = mx - ERASE_BLOCK[ i ][ 0 ];
		int check_my = my - ERASE_BLOCK[ i ][ 1 ];
		std::shared_ptr< Block > block = board->getBlockM( check_mx, check_my );
		//block���Ȃ��ꍇ������
		if ( !block ) {
			continue;
		}
		//���łɏ����Ă���ꍇ��
		if ( block->isErase( ) ) {
			continue;
		}
		//�u���b�N������
		block->erase( false, true );
	}
}
//C++�̏�����(���ۂɏ����Ċo����)
//



//[�N���X�̍\��]
class Sample {
public:
	Sample( ); //�R���X�g���N�^�[( �N���X�������ɌĂ΂�� )
	~Sample( ); //�f�X�g���N�^�[( �N���X�j�����ɌĂ΂�� )
public:
//������update��draw������
	void update( ); //�X�V����
	void draw( ); //�`�揈��
public:
//get�n�֐�������( �����o�ϐ��Ȃǂ��擾�������Ƃ� )
 int getNum( );
private:
//�����Ƀ����o�ϐ�( C����̏ꍇ�̓O���[�o���ϐ� )
//�����ł͏��������Ȃ�
	int _num;
}


//�N���X�����̎d��
//�ł����std::sheard_ptr���g��( �����I�ɔj�����Ă����|�C���^ )

#include <memory>//shared_ptr�̂��߂�include

void func( ) {
	//�T���v���N���X�̃|�C���^�𐶐�
	std::shared_ptr< Sample > sample( new Sample );

	//�֐����Ăяo���Ƃ���->���g��
	sample->update( );
	sample->draw( );

	//sample����̒l�̎擾
	int num = sample->getNum( );
}
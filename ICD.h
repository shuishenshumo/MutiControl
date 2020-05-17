#ifndef ICD_H
#define ICD_H

#define TEXT_LEN (64)

/************************************************************************************/

//���㡿
typedef struct Point
{
	int x;
	int y;
	int z;
}Point;

/************************************************************************************/

//���ʷ�������롿
//����������Ȼ���Դ�����зֽ�
//������Ĭ��Ϊ�����ơ���ֱ��͸��
//���أ���ʱʹ�û������Ʒ�ʽ��ָ�㡢���ơ�ƽ�ơ���ת������


//���ʷ���������
typedef struct MorphologyOut
{
	int flag;				//1-ָ�㡢2-���ơ�3-�ı���4-ƽ�ơ�5-��ת��6-����
	char buff[TEXT_LEN];	//��Ŵʷ����һ�������ʽ�����ݣ�����flag���������ݵĸ�ʽ��
	int device;				//1-������2-������3-����
	int timeStamp;			//ʱ�������λms
}MorphologyOut;

/************************************************************************************/

//�ʷ����һ�������ʽ��Ŀǰ���Ϊ���֣�ָ�㡢���ơ��ı���ƽ�ơ���ת������

//��ָ�㡿
typedef struct ActionPoint
{
	Point point;
}ActionPoint;

//��ѡ��
typedef struct ActionSelect
{
	int objectId;
}ActionSelect;

//���ı���
typedef struct ActionText
{
	char content[TEXT_LEN];
}ActionText;

//��ƽ��/�϶���
typedef struct ActionDrag
{
	Point prePoint;
	Point postPoint;
}ActionDrag;

//����ת��
typedef struct ActionRoll
{
	Point prePoint;
	float alpha;
}ActionRoll;

//�����š�
typedef struct ActionZoom
{
	Point prePoint;
	float delta;
}ActionZoom;

#endif
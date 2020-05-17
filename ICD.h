#ifndef ICD_H
#define ICD_H

#define TEXT_LEN (64)

/************************************************************************************/

//【点】
typedef struct Point
{
	int x;
	int y;
	int z;
}Point;

/************************************************************************************/

//【词法层的输入】
//语音：仿自然语言处理进行分解
//按键，默认为“控制”，直接透传
//触控，暂时使用基本控制方式：指点、控制、平移、旋转、缩放


//【词法层的输出】
typedef struct MorphologyOut
{
	int flag;				//1-指点、2-控制、3-文本、4-平移、5-旋转、6-缩放
	char buff[TEXT_LEN];	//存放词法层归一化输出格式的内容（根据flag来决定内容的格式）
	int device;				//1-按键、2-语音、3-触控
	int timeStamp;			//时间戳，单位ms
}MorphologyOut;

/************************************************************************************/

//词法层归一化输出格式，目前设计为六种：指点、控制、文本、平移、旋转、缩放

//【指点】
typedef struct ActionPoint
{
	Point point;
}ActionPoint;

//【选择】
typedef struct ActionSelect
{
	int objectId;
}ActionSelect;

//【文本】
typedef struct ActionText
{
	char content[TEXT_LEN];
}ActionText;

//【平移/拖动】
typedef struct ActionDrag
{
	Point prePoint;
	Point postPoint;
}ActionDrag;

//【旋转】
typedef struct ActionRoll
{
	Point prePoint;
	float alpha;
}ActionRoll;

//【缩放】
typedef struct ActionZoom
{
	Point prePoint;
	float delta;
}ActionZoom;

#endif
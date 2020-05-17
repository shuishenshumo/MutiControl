#include "geometryengine.h"

GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();
}

GeometryEngine::~GeometryEngine()
{

}

void GeometryEngine::setAttribute(QOpenGLShaderProgram *program, VertexCalc *vertexCalc)
{
	// Offset for position
    quintptr offset = 0;

	char vname[128] = {0};
	char fname[128] = {0};
	int vnum = 0;
	int fnum = 0;

	switch(vertexCalc->m_curVertexInfo.type)
	{
	case FOR_LINES:
	case FOR_TEXTURE_COLOR:
		memcpy(vname, "a_position", sizeof("a_position"));
		memcpy(fname, "a_color", sizeof("a_color"));
		vnum = 3;
		fnum = 4;
		break;
	case FOR_TEXTURE_PIC:
		memcpy(vname, "a_position", sizeof("a_position"));
		memcpy(fname, "a_texcoord", sizeof("a_texcoord"));
		vnum = 3;
		fnum = 2;
		break;
	}

	// Tell OpenGL programmable how to locate vertex position data
	int vertexLocation = program->attributeLocation(vname);
	program->enableAttributeArray(vertexLocation);
	program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, vnum, (vnum+fnum)*sizeof(float));

	// Offset for texture coordinate
	offset += vnum*sizeof(float);

	// Tell OpenGL programmable  how to locate vertex texture coordinate data
	int texcoordLocation = program->attributeLocation(fname);
	program->enableAttributeArray(texcoordLocation);
	program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, fnum, (vnum+fnum)*sizeof(float));
}

void GeometryEngine::drawVertexCalc(QOpenGLShaderProgram *program, VertexCalc *vertexCalc)
{
	int curIndex = 0;
	for(int i = 0; i < vertexCalc->m_curVertexInfo.indexSetNum; i++)
	{
		//创建buffer
		arrayBuf.create();
		indexBuf.create();

		//设置数据属性位置
		arrayBuf.bind();
		indexBuf.bind();
		setAttribute(program, vertexCalc);

		//数据绑定
		//arrayBuf.bind();
		arrayBuf.allocate(vertexCalc->m_curVertexInfo.vertexData, 
		vertexCalc->m_curVertexInfo.vertexLen * vertexCalc->m_curVertexInfo.vertexStep * sizeof(float));

		//indexBuf.bind();
		indexBuf.allocate(vertexCalc->m_curVertexInfo.indexData + curIndex
			, vertexCalc->m_curVertexInfo.indexLen[i] * sizeof(unsigned short));
		curIndex += vertexCalc->m_curVertexInfo.indexLen[i];

		//按索画图
		switch(vertexCalc->m_curVertexInfo.type)
		{
		case FOR_LINES:
			glDrawElements(GL_LINES, vertexCalc->m_curVertexInfo.indexLen[i], GL_UNSIGNED_SHORT, 0);
			break;
		case FOR_TEXTURE_COLOR:
		case FOR_TEXTURE_PIC:
			glDrawElements(GL_TRIANGLE_STRIP, vertexCalc->m_curVertexInfo.indexLen[i], GL_UNSIGNED_SHORT, 0);
			break;
		}
		
		//
		arrayBuf.release();
		indexBuf.release();

		//
		arrayBuf.destroy();
		indexBuf.destroy();
	}
}
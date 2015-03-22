#include "Triangle.h"

Triangle::Triangle(GLfloat vertex_01_p[], GLfloat vertex_02_p[], GLfloat vertex_03_p[], GLfloat color_01_p[], GLfloat color_02_p[], GLfloat color_03_p[])
{
	//TODO: make it more beautiful maybe with this->...
	for(int i = 0;i<3; i++)
	{
		vertex_01[i] = vertex_01_p[i];
		vertex_02[i] = vertex_02_p[i];
		vertex_03[i] = vertex_03_p[i];
		color_01[i] = color_01_p[i];
		color_02[i] = color_02_p[i];
		color_03[i] = color_03_p[i];
	}
}

GLfloat Triangle::get_vertex_01(int position)
{
	return vertex_01[position];
}
GLfloat Triangle::get_vertex_02(int position)
{
	return vertex_02[position];	
}
GLfloat Triangle::get_vertex_03(int position)
{
	return vertex_03[position];
}
GLfloat Triangle::get_color_01(int position)
{
	return color_01[position];
}
GLfloat Triangle::get_color_02(int position)
{
	return color_02[position];
}
GLfloat Triangle::get_color_03(int position)
{
	return color_03[position];
}
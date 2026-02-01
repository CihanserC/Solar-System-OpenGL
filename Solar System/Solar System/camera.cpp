#include "camera.h"
#include <cmath>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

#define SQR(x) (x*x)

#define NULL_VECTOR Vector3D(0.0f,0.0f,0.0f)


SF3dVector Vector3D(GLfloat x, GLfloat y, GLfloat z)
{
	SF3dVector tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

GLfloat GetVector3DLength(SF3dVector * v)
{
	return (GLfloat)(sqrt(SQR(v->x) + SQR(v->y) + SQR(v->z)));
}

SF3dVector Normalize3dVector(SF3dVector v)
{
	SF3dVector res;
	float l = GetVector3DLength(&v);
	if (l == 0.0f) return NULL_VECTOR;
	res.x = v.x / l;
	res.y = v.y / l;
	res.z = v.z / l;
	return res;
}

SF3dVector operator+ (SF3dVector v, SF3dVector u)
{
	SF3dVector res;
	res.x = v.x + u.x;
	res.y = v.y + u.y;
	res.z = v.z + u.z;
	return res;
}
SF3dVector operator- (SF3dVector v, SF3dVector u)
{
	SF3dVector res;
	res.x = v.x - u.x;
	res.y = v.y - u.y;
	res.z = v.z - u.z;
	return res;
}


SF3dVector operator* (SF3dVector v, float r)
{
	SF3dVector res;
	res.x = v.x*r;
	res.y = v.y*r;
	res.z = v.z*r;
	return res;
}

SF3dVector CrossProduct(SF3dVector * u, SF3dVector * v)
{
	SF3dVector resVector;
	resVector.x = u->y*v->z - u->z*v->y;
	resVector.y = u->z*v->x - u->x*v->z;
	resVector.z = u->x*v->y - u->y*v->x;

	return resVector;
}
float operator* (SF3dVector v, SF3dVector u)
{
	return v.x*u.x + v.y*u.y + v.z*u.z;
}




CCamera::CCamera()
{
	Position = Vector3D(0.0, 0.0, 0.0);
	ViewDir = Vector3D(0.0, 0.0, -1.0);
	RightVector = Vector3D(1.0, 0.0, 0.0);
	UpVector = Vector3D(0.0, 1.0, 0.0);

	RotatedX = RotatedY = RotatedZ = 0.0;
}

void CCamera::Move(SF3dVector Direction)
{
	Position = Position + Direction;
}

void CCamera::RotateX(GLfloat Angle)
{
	RotatedX += Angle;

	ViewDir = Normalize3dVector(ViewDir*cos(Angle*PIdiv180)
		+ UpVector * sin(Angle*PIdiv180));

	UpVector = CrossProduct(&ViewDir, &RightVector)*-1;


}

void CCamera::RotateY(GLfloat Angle)
{
	RotatedY += Angle;

	ViewDir = Normalize3dVector(ViewDir*cos(Angle*PIdiv180) - RightVector * sin(Angle*PIdiv180));

	RightVector = CrossProduct(&ViewDir, &UpVector);
}

void CCamera::RotateZ(GLfloat Angle)
{
	RotatedZ += Angle;

	RightVector = Normalize3dVector(RightVector*cos(Angle*PIdiv180) + UpVector * sin(Angle*PIdiv180));

	UpVector = CrossProduct(&ViewDir, &RightVector)*-1;
}

void CCamera::Render(void)
{
	SF3dVector ViewPoint = Position + ViewDir;

	gluLookAt(Position.x, Position.y, Position.z,ViewPoint.x, ViewPoint.y, ViewPoint.z,UpVector.x, UpVector.y, UpVector.z);

}

void CCamera::MoveForward(GLfloat Distance)
{
	Position = Position + (ViewDir*-Distance);
}

void CCamera::StrRight(GLfloat Distance)
{
	Position = Position + (RightVector*Distance);
}

void CCamera::MoveUpward(GLfloat Distance)
{
	Position = Position + (UpVector*Distance);
}
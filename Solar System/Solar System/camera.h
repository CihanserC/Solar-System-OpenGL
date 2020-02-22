#include <gl\glut.h>		
#define PI 3.14159265
#define PIdiv180 (PI/180.0)

struct SF3dVector  
{
	GLfloat x, y, z;
};
struct SF2dVector
{
	GLfloat x, y;
};
SF3dVector Vector3D(GLfloat x, GLfloat y, GLfloat z);

class CCamera
{
private:

	SF3dVector ViewDir;
	SF3dVector RightVector;
	SF3dVector UpVector;
	SF3dVector Position;

	GLfloat RotatedX, RotatedY, RotatedZ;

public:
	CCamera();				
	void Render(void);	
							

	void Move(SF3dVector Direction);
	void RotateX(GLfloat Angle);
	void RotateY(GLfloat Angle);
	void RotateZ(GLfloat Angle);

	void MoveForward(GLfloat Distance);
	void MoveUpward(GLfloat Distance);
	void StrRight(GLfloat Distance);


};



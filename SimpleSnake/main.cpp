#include "GameWindow.h"
#include <thread>
using namespace std;

struct Vector3
{
	float x, y, z;

	float Dot(const Vector3& v);
	Vector3 Cross(const Vector3& v);
	void Normalize();
};

float Vector3::Dot(const Vector3& v)
{
	float dot = x * v.x + y * v.y + z * v.z;
	return dot;
}

Vector3 Vector3::Cross(const Vector3& v)
{
	Vector3 newVector;

	newVector.x = y*v.z - z*v.y;
	newVector.y = -(x*v.z - z*v.x);
	newVector.z = x*v.y - y*v.x;

	return newVector;
}


void Vector3::Normalize(const Vector3& v)
{
	float norm = sqrt(x*x + y*y + z*z);
	x = x / norm;
	y = y / norm;
	z = z / norm;
}

int main(int argc, char* args[])
{
	//GameWindow *game = new GameWindow("Snake Window", 640, 640);
	//game->InitWindow();

	//delete game;

	return 0;
}
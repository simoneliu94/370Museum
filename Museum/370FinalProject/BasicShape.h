#pragma once

#define P_PI 3.14159265359
class BasicShape
{
public:
	BasicShape(void);
	~BasicShape(void);
	static GLuint MakeSphere(const float& radius);
	static GLuint MakeCylinder(const float& radius, const float& length);
	static GLuint MakeCube(const float& size);
	static GLuint MakeBox(const float length, const float width, const float height);
	static GLuint MakeOctagon(const float& side, const float& thickness);
	static GLuint MakeFrustumShape(const float& bottom_size, const float& top_size, const float& height);
	static GLuint MakePyramid(const float& size, const float& height);
	static GLuint MakeCone(const float& base_rad, const float& length);
	static GLuint MakeTruncatedCone(const float& base_rad, const float & top_rad, const float& length);
};


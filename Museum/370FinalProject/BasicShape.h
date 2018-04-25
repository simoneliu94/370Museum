#pragma once

class BasicShape
{
public:
	BasicShape(void);
	~BasicShape(void);

	static GLuint MakeCube(const float& size);
	static GLuint MakeGround(const float length, const float width, const float height);
	static GLuint MakeWall(const float& size);
};


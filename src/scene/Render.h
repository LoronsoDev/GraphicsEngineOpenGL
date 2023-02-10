#pragma once

#include <scene/Object.h>

class Render
{
public:
	virtual void Init() = 0;
	virtual void SetupObject(Object* obj) = 0;
	virtual void RemoveObject(Object* obj) = 0;
	virtual void DrawObjects(std::vector<Object*> *objs) = 0;
	int GetWidth();
	int GetHeight();
	inline void SetWidth(int w) { m_Width = w; };
	inline void SetHeight(int h) { m_Height = h; };
	inline bool IsClosed() { return m_IsClosed; }

private:
	int m_Width;
	int m_Height;

	bool m_IsClosed = false;
};


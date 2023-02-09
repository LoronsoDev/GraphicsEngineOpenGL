#pragma once

#include "Object.h"
class Render
{
public:
	virtual void init()=0;
	virtual void setupObject(Object* obj)=0;
	virtual void removeObject(Object* obj)=0;
	virtual void drawObjects(vector<Object*> *objs)=0;
	virtual bool isClosed()=0;
	int getWidth();
	int getHeight();
	void setWidth(int w);
	void setHeight(int h);

private:
	int width;
	int height;
};


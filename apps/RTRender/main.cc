#include <Windows.h>
#include <sstream>

#include "spdlog/spdlog.h"

#include "Window/RTMessageMap.h"
#include "Window/RTWindow.h"

class Vector3D
{
public:
	int x, y, z;
};

class Vertex
{
public:
	Vector3D position;
};

class Triangle
{
public:
	int vertexIndex[3];
};

class PixelColor
{
public:
	union
	{
		int x;
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;

	};
};

void TriangleSample(Vertex& p1, Vertex& p2, Vertex& p3)
{
	float d1y = (p1.position.y - p2.position.y);
	float d1x = (p2.position.x - p1.position.x) / d1y;
	float d2y = (p1.position.y - p3.position.y);
	float d2x = (p3.position.x - p1.position.x) / d2y;
	if (p2.position.x > p3.position.x)
	{
		float tmp;
		tmp = d2x;
		d2x = d1x;
		d1x = tmp;
	}

	int dy = d1y > 0 ? -1 : 1;
	Vector3D m1, m2;// m1 = m2 = p1.position;
	
	//p1代表单独点
	while (m1.y != p2.position.y)
	{
		for (int i = m1.x; i < m2.x; i++)
		{
			//绘制
		}
		m1.y += dy;
		m1.x += d1x;
		m2.x += d2x;
	}
}

void Raterier(Triangle* triangles, Vertex* vertices)
{
	PixelColor frame[1024][648];
	int numOfTriangle = 10;
	Vertex* p;
	for (int i = 0; i < numOfTriangle; i++)
	{
		int ay = vertices[triangles[i].vertexIndex[0]].position.y;
		int ax = vertices[triangles[i].vertexIndex[0]].position.x;
		int by = vertices[triangles[i].vertexIndex[1]].position.y;
		int bx = vertices[triangles[i].vertexIndex[1]].position.x;
		int cy = vertices[triangles[i].vertexIndex[2]].position.y;
		int cx = vertices[triangles[i].vertexIndex[2]].position.x;
		if ((ay - by) * (by - cy) > 0)
		{
			Vertex vertex;
			p = &vertices[triangles[i].vertexIndex[1]];
			vertex.position.x = cx + (ax - cx) * (p->position.y - cy) / (ay - cy);
			vertex.position.y = p->position.y;
			TriangleSample(vertices[triangles[i].vertexIndex[0]], *p, vertex);
			TriangleSample(vertices[triangles[i].vertexIndex[2]], *p, vertex);
		}
		else if ((by - ay) * (ay - cy) > 0)
		{
			Vertex vertex;
			p = &vertices[triangles[i].vertexIndex[0]];
			vertex.position.x = cx + (bx - cx) * (p->position.y - cy) / (by - cy);
			vertex.position.y = p->position.y;
			TriangleSample(vertices[triangles[i].vertexIndex[1]], *p, vertex);
			TriangleSample(vertices[triangles[i].vertexIndex[2]], *p, vertex);
		}
		else if ((ay - cy) * (cy - by) > 0)
		{
			Vertex vertex;
			p = &vertices[triangles[i].vertexIndex[2]];
			vertex.position.x = ax + (bx - ax) * (p->position.y - ay) / (by - ay);
			vertex.position.y = p->position.y;
			TriangleSample(vertices[triangles[i].vertexIndex[0]], *p, vertex);
			TriangleSample(vertices[triangles[i].vertexIndex[1]], *p, vertex);
		}
		else
		{
			if (ay == by)
			{
				TriangleSample(
					vertices[triangles[i].vertexIndex[2]],
					vertices[triangles[i].vertexIndex[1]],
					vertices[triangles[i].vertexIndex[0]]
					);
			}
			else if (ay == cy)
			{
				TriangleSample(
					vertices[triangles[i].vertexIndex[1]],
					vertices[triangles[i].vertexIndex[0]],
					vertices[triangles[i].vertexIndex[2]]
				);
			}
			else if (by == cy)
			{
				TriangleSample(
					vertices[triangles[i].vertexIndex[0]],
					vertices[triangles[i].vertexIndex[1]],
					vertices[triangles[i].vertexIndex[2]]
				);
			}
			else
			{

			}
		}
	}
}



int main()
{
	RTWindow window(800, 500, "RTRender");

	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		/*if (window.kbd.KeyIsPressed(VK_SPACE))
		{
			spdlog::info("space key is pressed");
		}*/
		static int i = 0;
		while (!window.mouse.IsEmpty())
		{
			const auto e = window.mouse.Read();
			switch (e.GetType())
			{
			case RTMouse::Event::Type::Leave:
				spdlog::info("Gone");
				break;
			case RTMouse::Event::Type::Move:
				spdlog::info("mouse position: ({}, {})", e.GetPosX(), e.GetPosY());
				break;
			case RTMouse::Event::Type::WheelUp:
				i++;
				spdlog::info("Up:{}", i);
				break;
			case RTMouse::Event::Type::WheelDown:
				spdlog::info("Down:{}", i);
				break;
			}
		}

	}

	if (gResult == -1)
	{
		return -1;
	}
	
	return msg.wParam;
}
#include "RTMouse.h"

std::pair<int, int> RTMouse::GetPos() const noexcept
{
	return { x, y };
}

int RTMouse::GetPosX() const noexcept
{
	return x;
}

int RTMouse::GetPosY() const noexcept
{
	return y;
}

bool RTMouse::LeftIsPressed() const noexcept
{
	return leftIsPressed;
}

bool RTMouse::RightIsPressed() const noexcept
{
	return rightIsPressed;
}

RTMouse::Event RTMouse::Read() noexcept
{
	if (buffer.size() > 0u)
	{
		RTMouse::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	else
	{
		return RTMouse::Event();
	}
}

void RTMouse::Flush() noexcept
{
	buffer = std::queue<Event>();
}

void RTMouse::OnMouseMove(int newx, int newy) noexcept
{
	x = newx;
	y = newy;
	buffer.push(RTMouse::Event(RTMouse::Event::Type::Move, *this));
	TrimBuffer();
}

void RTMouse::OnLeftPressed(int x, int y) noexcept
{
	leftIsPressed = true;
	buffer.push(RTMouse::Event(RTMouse::Event::Type::LPress, *this));
	TrimBuffer();
}

void RTMouse::OnLeftReleased(int x, int y) noexcept
{
	leftIsPressed = false;
	buffer.push(RTMouse::Event(RTMouse::Event::Type::LRelease, *this));
	TrimBuffer();
}

void RTMouse::OnRightPressed(int x, int y) noexcept
{
	rightIsPressed = true;
	buffer.push(RTMouse::Event(RTMouse::Event::Type::RPress, *this));
	TrimBuffer();
}

void RTMouse::OnRightReleased(int x, int y) noexcept
{
	rightIsPressed = false;
	buffer.push(RTMouse::Event(RTMouse::Event::Type::RRelease, *this));
	TrimBuffer();
}

void RTMouse::OnWheelUp(int x, int y) noexcept
{
	buffer.push(RTMouse::Event(RTMouse::Event::Type::WheelUp, *this));
	TrimBuffer();
}

void RTMouse::OnWheelDown(int x, int y) noexcept
{
	buffer.push(RTMouse::Event(RTMouse::Event::Type::WheelDown, *this));
	TrimBuffer();
}

void RTMouse::TrimBuffer() noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}
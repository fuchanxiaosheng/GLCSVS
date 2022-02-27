#include "RTKeyboard.h"

bool RTKeyboard::KeyIsPressed(unsigned char keycode) const noexcept
{
	return keystates[keycode];
}

RTKeyboard::Event RTKeyboard::ReadKey() noexcept
{
	if (keybuffer.size() > 0u)
	{
		RTKeyboard::Event e = keybuffer.front();
		keybuffer.pop();
		return e;
	}
	else
	{
		return RTKeyboard::Event();
	}
}

bool RTKeyboard::KeyIsEmpty() const noexcept
{
	return keybuffer.empty();
}

char RTKeyboard::ReadChar() noexcept
{
	if (charbuffer.size() > 0u)
	{
		unsigned char charcode = charbuffer.front();
		charbuffer.pop();
		return charcode;
	}
	else
	{
		return 0;
	}
}

bool RTKeyboard::CharIsEmpty() const noexcept
{
	return charbuffer.empty();
}

void RTKeyboard::FlushKey() noexcept
{
	keybuffer = std::queue<Event>();
}

void RTKeyboard::FlushChar() noexcept
{
	charbuffer = std::queue<char>();
}

void RTKeyboard::Flush() noexcept
{
	FlushKey();
	FlushChar();
}

void RTKeyboard::EnableAutorepeat() noexcept
{
	autorepeatEnabled = true;
}

void RTKeyboard::DisableAutorepeat() noexcept
{
	autorepeatEnabled = false;
}

bool RTKeyboard::AutorepeatIsEnabled() const noexcept
{
	return autorepeatEnabled;
}

void RTKeyboard::OnKeyPressed(unsigned char keycode) noexcept
{
	keystates[keycode] = true;
	keybuffer.push(RTKeyboard::Event(RTKeyboard::Event::Type::Press, keycode));
	TrimBuffer(keybuffer);
}

void RTKeyboard::OnKeyReleased(unsigned char keycode) noexcept
{
	keystates[keycode] = false;
	keybuffer.push(RTKeyboard::Event(RTKeyboard::Event::Type::Release, keycode));
	TrimBuffer(keybuffer);
}

void RTKeyboard::OnChar(char character) noexcept
{
	charbuffer.push(character);
	TrimBuffer(charbuffer);
}

void RTKeyboard::ClearState() noexcept
{
	keystates.reset();
}

template<typename T>
void RTKeyboard::TrimBuffer(std::queue<T>& buffer) noexcept
{
	while (buffer.size() > bufferSize)
	{
		buffer.pop();
	}
}
#pragma once

namespace Utils
{

	class NotCopyableAndNotMovable
	{
	public:
		NotCopyableAndNotMovable() = default;
		virtual ~NotCopyableAndNotMovable() = default;
		NotCopyableAndNotMovable(NotCopyableAndNotMovable&&) = delete;
		NotCopyableAndNotMovable& operator=(NotCopyableAndNotMovable&&) = delete;
		NotCopyableAndNotMovable(const NotCopyableAndNotMovable&) = delete;
		NotCopyableAndNotMovable& operator=(const NotCopyableAndNotMovable&) = delete;
	};

}
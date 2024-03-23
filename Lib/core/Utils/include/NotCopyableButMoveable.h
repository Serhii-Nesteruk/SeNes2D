#pragma once

namespace Utils
{
	class NotCopyableButMovable
	{
	public:
		NotCopyableButMovable() = default;
		virtual ~NotCopyableButMovable() = default;
		NotCopyableButMovable(NotCopyableButMovable&&) = default;
		NotCopyableButMovable& operator=(NotCopyableButMovable&&) = default;
		NotCopyableButMovable(const NotCopyableButMovable&) = delete;
		NotCopyableButMovable& operator=(const NotCopyableButMovable&) = delete;
	};

}
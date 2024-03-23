#pragma once

namespace Utils
{

	class CopyableAndMoveable
	{
	public:
		CopyableAndMoveable() = default;
		virtual ~CopyableAndMoveable() = default;
		CopyableAndMoveable(CopyableAndMoveable&&) = default;
		CopyableAndMoveable& operator=(CopyableAndMoveable&&) = default;
		CopyableAndMoveable(const CopyableAndMoveable&) = default;
		CopyableAndMoveable& operator=(const CopyableAndMoveable&) = default;
	};

}

#pragma once

#include "LE/Input.h"

namespace LE
{
	class WindowsInput : public Input
	{
	protected:

		virtual bool IsKeyPressedImpl(int32_t Keycode) const override;
		virtual bool IsMouseButtonPressedImpl(int32_t Button) const override;

		virtual std::pair<float, float> GetMouseXYImpl() const override;
	};
}
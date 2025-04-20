
#pragma once

#include "Event.h"

namespace LE
{
	class LE_API MouseMovedEvent : public Event
	{
	public:

		MouseMovedEvent(float X, float Y)
			: m_MouseX(X), m_MouseY(Y) {}

		inline float GetMouseX() const
		{
			return m_MouseX;
		}

		inline float GetMouseY() const
		{
			return m_MouseY;
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::MouseMoved);
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryInput | EventCategory::EventCategoryMouse);

	private:

		float m_MouseX, m_MouseY;
	};

	class LE_API MouseScrolledEvent : public Event
	{
	public:

		MouseScrolledEvent(float XOffset, float YOffset)
			: m_XOffset(XOffset), m_YOffset(YOffset) {}

		inline float GetMouseXOffset() const
		{
			return m_XOffset;
		}

		inline float GetMouseYOffset() const
		{
			return m_YOffset;
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::MouseScrolled);
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryInput | EventCategory::EventCategoryMouse);

	private:

		float m_XOffset, m_YOffset;
	};

	class LE_API MouseButtonEvent : public Event
	{
	public:

		inline int32_t GetMouseButton() const
		{
			return m_ButtonCode;
		}

		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryInput | EventCategory::EventCategoryMouseButton);

	protected:

		MouseButtonEvent(int32_t ButtonCode)
			: m_ButtonCode(ButtonCode) {}

		int32_t m_ButtonCode;
	};

	class LE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:

		MouseButtonPressedEvent(int32_t ButtonCode)
			: MouseButtonEvent(ButtonCode) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_ButtonCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::MouseButtonPressed);
	};

	class LE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:

		MouseButtonReleasedEvent(int32_t ButtonCode)
			: MouseButtonEvent(ButtonCode) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_ButtonCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::MouseButtonReleased);
	};
}
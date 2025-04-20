
#pragma once

#include "Event.h"

namespace LE
{
	class LE_API KeyEvent : public Event
	{
	public:

		inline int32_t GetKeyCode() const
		{ 
			return m_KeyCode;
		}

		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput);

	protected:

		KeyEvent(int32_t KeyCode)
			: m_KeyCode(KeyCode) {}

		int32_t m_KeyCode;
	};
	
	class LE_API KeyPressedEvent : public KeyEvent
	{
	public:

		KeyPressedEvent(int32_t KeyCode, int32_t RepeatCount)
			: KeyEvent(KeyCode), m_RepeatCount(RepeatCount) {}

		inline int32_t GetRepeatCount() const
		{
			return m_RepeatCount;
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyPressed);

	private:

		int32_t m_RepeatCount;
	};

	class LE_API KeyReleasedEvent : public KeyEvent
	{
	public:

		KeyReleasedEvent(int32_t KeyCode)
			: KeyEvent(KeyCode) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::KeyReleased);
	};
}
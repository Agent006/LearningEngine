
#pragma once

#include "Event.h"

namespace LE
{
	class WindowResizeEvent : public Event
	{
	public:

		WindowResizeEvent(uint32_t Width, uint32_t Height)
			: m_Width(Width), m_Height(Height) {}

		inline uint32_t GetWidth() const
		{
			return m_Width;
		}

		inline uint32_t GetHeight() const
		{
			return m_Height;
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(EventType::WindowResize);
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication);

	private:

		uint32_t m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:

		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(EventType::WindowClose);
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication);
	};

	class AppTickEvent : public Event
	{
	public:

		AppTickEvent() = default;

		EVENT_CLASS_TYPE(EventType::AppTick);
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication);
	};

	class AppUpdateEvent : public Event
	{
	public:

		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(EventType::AppUpdate);
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication);
	};

	class AppRenderEvent : public Event
	{
	public:

		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(EventType::AppRender);
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication);
	};
}

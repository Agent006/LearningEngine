#pragma once

namespace LE
{
	class Timestep
	{
	public:

		Timestep(float Time = 0.f)
			: m_Time(Time)
		{
		}

		inline float GetSeconds() const { return m_Time; }
		inline float GetMilliseconds() const { return m_Time * 1000.f; }

		float operator=(float y) { return m_Time = y; }

		float operator+(float y) { return m_Time += y; }
		float operator-(float y) { return m_Time -= y; }
		float operator*(float y) { return m_Time *= y; }
		float operator/(float y) { return m_Time /= y; }

		bool operator!=(float y) { return m_Time != y; }
		bool operator>(float y) { return m_Time > y; }
		bool operator<(float y) { return m_Time < y; }
		bool operator>=(float y) { return m_Time >= y; }
		bool operator<=(float y) { return m_Time <= y; }

		operator float() const { return GetSeconds(); }

	private:

		float m_Time;
	};
}
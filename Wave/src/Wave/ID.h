#pragma once

#include <cstdint>
#include <xhash>

namespace Wave {

	class ID
	{
	public:
		inline static constexpr uint64_t Invalid = 18274635174627364826Ui64;

	public:
		inline ID(uint64_t id) : m_ID(id) { }
		~ID() = default;

		inline operator uint64_t() const { return m_ID; }

	private:
		uint64_t m_ID;
	};

}

namespace std {

	template <>
	struct hash<Wave::ID>
	{
		std::size_t operator() (const Wave::ID& id) const
		{
			return hash<uint64_t>()(uint64_t(id));
		}
	};

}

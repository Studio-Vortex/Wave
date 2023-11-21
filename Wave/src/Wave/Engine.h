#pragma once

#include "Wave/ID.h"

namespace Wave {

	struct EngineSettings
	{

	};

	class Engine
	{
	public:
		inline Engine(ID id) : m_EngineID(id) { }
		~Engine() = default;

		bool Start();
		bool Stop();

		inline ID GetID() const { return m_EngineID; }

		inline operator ID() const { return m_EngineID; }

	private:
		ID m_EngineID = ID::Invalid;
	};

}

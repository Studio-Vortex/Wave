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

		bool Init(const EngineSettings& settings);
		bool Shutdown();

		void Start();
		void Stop();

		inline ID GetID() const { return m_EngineID; }

	private:
		ID m_EngineID = ID(0);
	};

}

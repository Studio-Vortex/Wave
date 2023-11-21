#include "Engine.h"

#include "Wave/Context.h"
#include "Wave/Assert.h"

#include <miniaudio/miniaudio.h>

#include <format>

namespace Wave {

	bool Engine::Init(const EngineSettings& settings)
	{
		return false;
	}

	bool Engine::Shutdown()
	{
		return false;
	}

	void Engine::Start()
	{
		ma_engine* engine = (ma_engine*)Context::GetEngineInternal(m_EngineID);
		ma_result res = ma_engine_start(engine);
		if (res != MA_SUCCESS)
		{
			std::string err = std::format("Failed to start engine with ID: '{}'", uint64_t(m_EngineID));
			Context::SetErrorMsg(err);
		}
	}

	void Engine::Stop()
	{
	}

}

#include "Engine.h"

#include "Wave/Context.h"
#include "Wave/Assert.h"

#include <miniaudio/miniaudio.h>

#include <format>

namespace Wave {

	bool Engine::Start()
	{
		ma_engine* engine = (ma_engine*)Context::GetEngineInternal(m_EngineID);
		ma_result res = ma_engine_start(engine);
		if (res != MA_SUCCESS)
		{
			std::string err = std::format("Failed to start engine with ID: '{}'", uint64_t(m_EngineID));
			Context::SetErrorMsg(err);
			return false;
		}
		return true;
	}

	bool Engine::Stop()
	{
		ma_engine* engine = (ma_engine*)Context::GetEngineInternal(m_EngineID);
		ma_result res = ma_engine_stop(engine);
		if (res != MA_SUCCESS)
		{
			std::string err = std::format("Failed to stop engine with ID: '{}'", uint64_t(m_EngineID));
			Context::SetErrorMsg(err);
			return false;
		}
		return true;
	}

}

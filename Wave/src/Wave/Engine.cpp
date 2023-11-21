#include "Engine.h"

#include "Wave/Context.h"
#include "Wave/Assert.h"

#include <miniaudio/miniaudio.h>

#include <format>

namespace Wave {

	bool Engine::Start() const
	{
		ma_engine* engine = (ma_engine*)Context::GetEngineInternal(m_EngineID);
		WAVE_ASSERT(engine, "Invalid engine ID: '%zu'", uint64_t(m_EngineID));
		WAVE_ASSERT(!Context::GetEngineInternalData(m_EngineID)->IsRunning, "Engine must be stopped to start it!%s", "");
		
		ma_result res = ma_engine_start(engine);
		
		if (res != MA_SUCCESS)
		{
			std::string err = std::format("Failed to start engine with ID: '{}'", uint64_t(m_EngineID));
			Context::SetErrorMsg(err);
			return false;
		}

		Context::GetEngineInternalData(m_EngineID)->IsRunning = true;
		
		return true;
	}

	bool Engine::Stop() const
	{
		ma_engine* engine = (ma_engine*)Context::GetEngineInternal(m_EngineID);
		WAVE_ASSERT(engine, "Invalid engine ID: '%zu'", uint64_t(m_EngineID));
		WAVE_ASSERT(Context::GetEngineInternalData(m_EngineID)->IsRunning, "Engine must be running to stop it!%s", "");
		
		ma_result res = ma_engine_stop(engine);
		
		if (res != MA_SUCCESS)
		{
			std::string err = std::format("Failed to stop engine with ID: '{}'", uint64_t(m_EngineID));
			Context::SetErrorMsg(err);
			Context::GetEngineInternalData(m_EngineID)->IsRunning = false;
			return false;
		}

		Context::GetEngineInternalData(m_EngineID)->IsRunning = false;
		
		return true;
	}

	bool Engine::IsRunning() const
	{
		ma_engine* engine = (ma_engine*)Context::GetEngineInternal(m_EngineID);
		WAVE_ASSERT(engine, "Invalid engine ID: '%zu'", uint64_t(m_EngineID));
		return Context::GetEngineInternalData(m_EngineID)->IsRunning;
	}

}

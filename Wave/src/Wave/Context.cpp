#include "Context.h"

#include "Wave/Sound.h"
#include "Wave/Engine.h"
#include "Wave/Assert.h"

#include <miniaudio/miniaudio.h>

#include <unordered_map>
#include <format>

namespace Wave {

	struct ContextInternalData
	{
		ma_context Context;
		ma_uint32 PlaybackDeviceCount;
		ma_uint32 CaptureDeviceCount;
		ma_device_info* PlaybackDeviceInfos;
		ma_device_info* CaptureDeviceInfos;
	};

	struct SoundInternalData
	{
		ma_sound Sound;
		SoundData Data;
	};

	struct EngineInternalData
	{
		ma_engine Engine;
		EngineData Data;
	};

	struct ContextPair
	{
		Context* pCtx;
		ContextInternalData Data;
	};

	struct SoundPair
	{
		Sound* pSound;
		SoundInternalData Data;
	};

	struct EnginePair
	{
		Engine* pEngine;
		EngineInternalData Data;
	};

	struct InternalData
	{
		ContextPair CurrentContext;
		std::unordered_map<ID, SoundPair> ActiveSounds;
		std::unordered_map<ID, EnginePair> ActiveEngines;
	};

	static InternalData* s_Data = nullptr;
	static uint64_t s_ContextCount = 0;

	ContextResult Context::Init(const ContextSettings& settings)
	{
		ContextResult result;
		result.Success = false;

		WAVE_ASSERT(s_Data == nullptr, "Trying to initialize Wave multiple times!%s", "");
		s_Data = new InternalData();

		s_Data->CurrentContext.pCtx = this;

		// Initialize Miniaudio
		ma_context_config config = ma_context_config_init();
		config.pUserData = settings.pUserData;

		ma_result res = ma_context_init(nullptr, 0, &config, &s_Data->CurrentContext.Data.Context);
		
		if (res != MA_SUCCESS)
		{
			m_LastErrorMsg = "Failed to initialize miniaudio!";
			return result;
		}

		res = ma_context_get_devices(
			&s_Data->CurrentContext.Data.Context,
			&s_Data->CurrentContext.Data.PlaybackDeviceInfos,
			&s_Data->CurrentContext.Data.PlaybackDeviceCount,
			&s_Data->CurrentContext.Data.CaptureDeviceInfos,
			&s_Data->CurrentContext.Data.CaptureDeviceCount
		);
		
		if (res != MA_SUCCESS)
		{
			m_LastErrorMsg = "Failed to enumerate hardware devices!";
			return result;
		}

		if (settings.EnableDebugLogging)
		{
			ma_log* log = ma_context_get_log(&s_Data->CurrentContext.Data.Context);
			
			ma_log_callback callback;
			callback.onLog = settings.LogCallback;

			res = ma_log_register_callback(log, callback);
			
			if (res != MA_SUCCESS)
			{
				m_LastErrorMsg = "Failed to register log callback";
				return result;
			}
		}

		if (settings.EnumerateDevices)
		{
			DeviceInfo deviceInfo = {};

			for (uint32_t i = 0; i < s_Data->CurrentContext.Data.PlaybackDeviceCount; i++)
			{
				deviceInfo.Name = std::string(s_Data->CurrentContext.Data.PlaybackDeviceInfos[i].name);
				deviceInfo.Type = DeviceType::Playback;
				deviceInfo.IsDefault = (bool)s_Data->CurrentContext.Data.PlaybackDeviceInfos[i].isDefault;
				result.PlaybackDeviceInfos.push_back(deviceInfo);
			}

			for (uint32_t i = 0; i < s_Data->CurrentContext.Data.CaptureDeviceCount; i++)
			{
				deviceInfo.Name = std::string(s_Data->CurrentContext.Data.CaptureDeviceInfos[i].name);
				deviceInfo.Type = DeviceType::Capture;
				deviceInfo.IsDefault = (bool)s_Data->CurrentContext.Data.CaptureDeviceInfos[i].isDefault;
				result.CaptureDeviceInfos.push_back(deviceInfo);
			}
		}

		result.Success = true;
		return result;
	}

	bool Context::Shutdown()
	{
		WAVE_ASSERT(s_Data != nullptr, "Trying to shutdown Wave without initializing!%s", "");

		// Shutdown Miniaudio
		ma_context* context = &s_Data->CurrentContext.Data.Context;
		ma_result res = ma_context_uninit(context);
		
		if (res != MA_SUCCESS)
		{
			m_LastErrorMsg = "Failed to shutdown miniaudio!";
			return false;
		}

		delete s_Data;
		s_Data = nullptr;

		return true;
	}

	Sound Context::CreateSoundFromFile(ID engineID, const std::filesystem::path& path)
	{
		ID soundID = ID(s_Data->ActiveSounds.size());
		Sound sound = Sound(soundID);
		
		WAVE_ASSERT(!s_Data->ActiveSounds.contains(soundID), "Sound with ID: '%zu' already exists!", uint64_t(soundID));
		SoundPair& pair = s_Data->ActiveSounds[soundID];
		pair.pSound = &sound;
		
		ma_sound_config config = ma_sound_config_init();
		std::string filepath = path.string();
		config.pFilePath = filepath.c_str();

		ma_engine* engine = &s_Data->ActiveEngines[engineID].Data.Engine;
		ma_result res = ma_sound_init_ex(engine, &config, &pair.Data.Sound);
		
		if (res != MA_SUCCESS)
		{
			m_LastErrorMsg = std::format("Failed to create sound from: '{}'", filepath);
			return Sound(ID::Invalid);
		}

		res = ma_sound_get_length_in_seconds(&pair.Data.Sound, &pair.Data.Data.Length);

		if (res != MA_SUCCESS)
		{
			m_LastErrorMsg = std::format("Failed to get length of sound with ID: '{}'", uint64_t(soundID));
			return Sound(ID::Invalid);
		}

		return sound;
	}

	Sound Context::CreateSoundFromDataSource(ID engineID, const uint8_t* src, size_t size)
	{
		WAVE_ASSERT(false, "Not implemented yet!%s", "");
		return Sound(ID::Invalid);
	}

	bool Context::DestroySound(ID id)
	{
		ma_sound* sound = (ma_sound*)GetSoundInternal(id);
		
		if (sound == nullptr)
		{
			m_LastErrorMsg = std::format("Failed to destroy sound with ID: '{}'", uint64_t(id));
			return false;
		}
		
		ma_sound_uninit(sound);

		s_Data->ActiveSounds.erase(id);

		return true;
	}

	Engine Context::CreateEngine()
	{
		ID engineID = ID(s_Data->ActiveEngines.size());
		Engine engine = Engine(engineID);

		WAVE_ASSERT(!s_Data->ActiveEngines.contains(engineID), "Engine with ID: '%zu' already exists!", uint64_t(engineID));
		EnginePair& pair = s_Data->ActiveEngines[engineID];
		pair.pEngine = &engine;

		ma_engine_config config = ma_engine_config_init();
		config.noAutoStart = true;
		
		ma_result res = ma_engine_init(&config, &pair.Data.Engine);
		
		if (res != MA_SUCCESS)
		{
			m_LastErrorMsg = "Failed to create engine";
			return Engine(ID::Invalid);
		}

		return engine;
	}

	bool Context::DestroyEngine(ID id)
	{
		ma_engine* engine = (ma_engine*)GetEngineInternal(id);
		
		if (engine == nullptr)
		{
			m_LastErrorMsg = std::format("Failed to destroy engine with ID: '{}'", uint64_t(id));
			return false;
		}
		
		ma_engine_uninit(engine);

		s_Data->ActiveEngines.erase(id);

		return true;
	}

	void Context::SetErrorMsg(const std::string& msg)
	{
		WAVE_ASSERT(s_Data != nullptr && s_Data->CurrentContext.pCtx != nullptr, "Wave not initialized... No active context%s", "");
		
		s_Data->CurrentContext.pCtx->m_LastErrorMsg = msg;
	}

	void* Context::GetSoundInternal(ID id)
	{
		WAVE_ASSERT(s_Data != nullptr, "Wave not initialized!%s", "");
		WAVE_ASSERT(s_Data->ActiveSounds.contains(id), "Invalid sound ID: '%zu'", uint64_t(id));
		
		SoundPair& pair = s_Data->ActiveSounds[id];
		
		return (void*)&pair.Data.Sound;
	}

	SoundData* Context::GetSoundInternalData(ID id)
	{
		WAVE_ASSERT(s_Data != nullptr, "Wave not initialized!%s", "");
		WAVE_ASSERT(s_Data->ActiveSounds.contains(id), "Invalid sound ID: '%zu'", uint64_t(id));
		
		SoundPair& pair = s_Data->ActiveSounds[id];
		
		return &pair.Data.Data;
	}

	void* Context::GetEngineInternal(ID id)
	{
		WAVE_ASSERT(s_Data != nullptr, "Wave not initialized!%s", "");
		WAVE_ASSERT(s_Data->ActiveEngines.contains(id), "Invalid engine ID: '%zu'", uint64_t(id));
		
		EnginePair& pair = s_Data->ActiveEngines[id];
		
		return (void*)&pair.Data.Engine;
	}

	EngineData* Context::GetEngineInternalData(ID id)
	{
		WAVE_ASSERT(s_Data != nullptr, "Wave not initialized!%s", "");
		WAVE_ASSERT(s_Data->ActiveEngines.contains(id), "Invalid engine ID: '%zu'", uint64_t(id));

		EnginePair& pair = s_Data->ActiveEngines[id];
		
		return &pair.Data.Data;
	}

	std::shared_ptr<Context> CreateContext()
	{
		return std::make_unique<Context>();
	}

	void DestroyContext(std::shared_ptr<Context> context)
	{
		context.reset();
	}

}

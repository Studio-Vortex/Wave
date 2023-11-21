#pragma once

#include "Wave/Sound.h"
#include "Wave/Engine.h"
#include "Wave/ID.h"

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <filesystem>

namespace Wave {

	enum class LogLevel : uint32_t
	{
		Info = 0, Warning, Error, Debug,
	};

	typedef void(*WaveLogCallback)(void*, uint32_t, const char*);

	struct ContextSettings
	{
		WaveLogCallback LogCallback = nullptr;
		bool EnumerateDevices = false;
		bool EnableDebugLogging = false;
		void* pUserData = nullptr;
	};

	enum class DeviceType
	{
		Playback = 0, Capture,
	};

	struct DeviceInfo
	{
		std::string Name = "";
		DeviceType Type;
		bool IsDefault = false;
	};

	struct ContextResult
	{
		std::vector<DeviceInfo> PlaybackDeviceInfos;
		std::vector<DeviceInfo> CaptureDeviceInfos;
		bool Success = false;
	};

	class Context
	{
	public:
		Context() = default;
		~Context() = default;

		ContextResult Init(const ContextSettings& settings);
		bool Shutdown();

		Sound CreateSoundFromFile(ID engineID, const std::filesystem::path& path);
		Sound CreateSoundFromDataSource(ID engineID, const uint8_t* src, size_t size);
		bool DestroySound(ID id);

		Engine CreateEngine();
		bool DestroyEngine(ID id);

		inline const std::string& GetLastErrorMsg() const { return m_LastErrorMsg; }

	private:
		static void SetErrorMsg(const std::string& msg);

		static void* GetSoundInternal(ID id);
		static SoundData* GetSoundInternalData(ID id);
		static void* GetEngineInternal(ID id);
		static EngineData* GetEngineInternalData(ID id);

	private:
		std::string m_LastErrorMsg = "";

	private:
		friend class Sound;
		friend class Engine;
	};

	std::shared_ptr<Context> CreateContext();
	void DestroyContext(std::shared_ptr<Context> context);

}

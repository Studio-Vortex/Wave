#include "Sound.h"

#include "Wave/Context.h"
#include "Wave/Assert.h"

#include <miniaudio/miniaudio.h>

#include <format>

namespace Wave {
	
	bool Sound::Init(const SoundSettings& settings)
	{
		return false;
	}
	
	bool Sound::Shutdown()
	{
		return false;
	}

	void Sound::Play()
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		ma_result res = ma_sound_start(sound);
		if (res != MA_SUCCESS)
		{
			std::string err = std::format("Failed to start sound with ID: '{}'", uint64_t(m_SoundID));
			Context::SetErrorMsg(err);
		}
	}

	void Sound::Stop()
	{
	}

}

#include "Sound.h"

#include "Wave/Context.h"
#include "Wave/Assert.h"

#include <miniaudio/miniaudio.h>

#include <format>

namespace Wave {

	bool Sound::Play()
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		ma_result res = ma_sound_start(sound);
		if (res != MA_SUCCESS)
		{
			std::string err = std::format("Failed to start sound with ID: '{}'", uint64_t(m_SoundID));
			Context::SetErrorMsg(err);
			return false;
		}
		return true;
	}

	bool Sound::Stop()
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		ma_result res = ma_sound_stop(sound);
		if (res != MA_SUCCESS)
		{
			std::string err = std::format("Failed to stop sound with ID: '{}'", uint64_t(m_SoundID));
			Context::SetErrorMsg(err);
			return false;
		}
		return true;
	}

}

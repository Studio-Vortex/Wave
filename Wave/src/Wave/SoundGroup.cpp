#include "SoundGroup.h"

#include "Wave/Context.h"
#include "Wave/Assert.h"
#include "Wave/Utils.h"

#include <miniaudio/miniaudio.h>

#include <format>

namespace Wave {

	bool SoundGroup::Play() const
	{
		ma_sound_group* soundGroup = (ma_sound_group*)Context::GetSoundGroupInternal(m_SoundGroupID);
		WAVE_ASSERT(soundGroup, "Invalid sound group ID: '%zu'", uint64_t(m_SoundGroupID));

		ma_result res = ma_sound_start(soundGroup);

		if (res != MA_SUCCESS)
		{
			std::string err = std::format("Failed to start sound group with ID: '{}'", uint64_t(m_SoundGroupID));
			Context::SetErrorMsg(err);
			return false;
		}

		Context::GetSoundGroupInternalData(m_SoundGroupID)->IsPaused = false;

		return true;
	}

	bool SoundGroup::Restart() const
	{
		return false;
	}

	bool SoundGroup::Pause() const
	{
		return false;
	}

	bool SoundGroup::Stop() const
	{
		return false;
	}

}

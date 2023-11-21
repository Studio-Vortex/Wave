#include "Sound.h"

#include "Wave/Context.h"
#include "Wave/Assert.h"
#include "Wave/Utils.h"

#include <miniaudio/miniaudio.h>

#include <format>

namespace Wave {

	bool Sound::Play() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));
		
		ma_result res = ma_sound_start(sound);
		
		if (res != MA_SUCCESS)
		{
			std::string err = std::format("Failed to start sound with ID: '{}'", uint64_t(m_SoundID));
			Context::SetErrorMsg(err);
			return false;
		}

		Context::GetSoundInternalData(m_SoundID)->IsPaused = false;
		
		return true;
	}

	bool Sound::Restart() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_result res = ma_sound_seek_to_pcm_frame(sound, 0);

		if (res != MA_SUCCESS)
		{
			std::string err = std::format("Failed to restart sound with ID: '{}'", uint64_t(m_SoundID));
			Context::SetErrorMsg(err);
			return false;
		}

		return true;
	}

	bool Sound::Pause() const
	{
		if (!IsPaused())
		{
			Context::GetSoundInternalData(m_SoundID)->IsPaused = true;
			return Stop();
		}
		
		return true;
	}

	bool Sound::Stop() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));
		
		ma_result res = ma_sound_stop(sound);

		if (res != MA_SUCCESS)
		{
			std::string err = std::format("Failed to stop sound with ID: '{}'", uint64_t(m_SoundID));
			Context::SetErrorMsg(err);
			return false;
		}
		
		return true;
	}

	float Sound::GetVolume() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return ma_sound_get_volume(sound);
	}

	void Sound::SetVolume(float volume) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_volume(sound, volume);
	}

	float Sound::GetPitch() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return ma_sound_get_pitch(sound);
	}

	void Sound::SetPitch(float pitch) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_pitch(sound, pitch);
	}

	float Sound::GetDopplerFactor() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return ma_sound_get_doppler_factor(sound);
	}

	void Sound::SetDopplerFactor(float dopplerFactor) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_doppler_factor(sound, dopplerFactor);
	}

	Vec3 Sound::GetPosition() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_vec3f position = ma_sound_get_position(sound);

		return Vec3(position.x, position.y, position.z);
	}

	void Sound::SetPosition(const Vec3& position) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_position(sound, position.X, position.Y, position.Z);
	}

	Vec3 Sound::GetDirection() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_vec3f direction = ma_sound_get_direction(sound);

		return Vec3(direction.x, direction.y, direction.z);
	}

	void Sound::SetDirection(const Vec3& direction) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_direction(sound, direction.X, direction.Y, direction.Z);
	}

	Vec3 Sound::GetVelocity() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_vec3f velocity = ma_sound_get_velocity(sound);

		return Vec3(velocity.x, velocity.y, velocity.z);
	}

	void Sound::SetVelocity(const Vec3& velocity) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_velocity(sound, velocity.X, velocity.Y, velocity.Z);
	}

	AudioCone Sound::GetAudioCone() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		AudioCone cone;

		ma_sound_get_cone(sound, &cone.InnerAngle, &cone.OuterAngle, &cone.OuterGain);

		cone.InnerAngle = Utils::RadiansToDegrees(cone.InnerAngle);
		cone.OuterAngle = Utils::RadiansToDegrees(cone.OuterAngle);

		return cone;
	}

	void Sound::SetAudioCone(const AudioCone& cone) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_cone(sound, Utils::DegreesToRadians(cone.InnerAngle), Utils::DegreesToRadians(cone.OuterAngle), cone.OuterGain);
	}

	float Sound::GetMinGain() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return ma_sound_get_min_gain(sound);
	}

	void Sound::SetMinGain(float minGain) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_min_gain(sound, minGain);
	}

	float Sound::GetMaxGain() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return ma_sound_get_max_gain(sound);
	}

	void Sound::SetMaxGain(float maxGain) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_max_gain(sound, maxGain);
	}

	float Sound::GetFalloff() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return ma_sound_get_rolloff(sound);
	}

	void Sound::SetFalloff(float falloff) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_rolloff(sound, falloff);
	}

	float Sound::GetMinDistance() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return ma_sound_get_min_distance(sound);
	}

	void Sound::SetMinDistance(float minDistance) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_min_distance(sound, minDistance);
	}

	float Sound::GetMaxDistance() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return ma_sound_get_max_distance(sound);
	}

	void Sound::SetMaxDistance(float maxDistance) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_max_distance(sound, maxDistance);
	}

	AttenuationModel Sound::GetAttenuationModel() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return (AttenuationModel)ma_sound_get_attenuation_model(sound);
	}

	void Sound::SetAttenuationModel(AttenuationModel model) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_attenuation_model(sound, (ma_attenuation_model)model);
	}

	float Sound::GetSoundCursor() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));
		
		float cursor = 0.0f;
		ma_result res = ma_sound_get_cursor_in_seconds(sound, &cursor);
		
		if (res != MA_SUCCESS)
		{
			std::string err = std::format("Failed to get cursor of sound with ID: '{}'", uint64_t(m_SoundID));
			Context::SetErrorMsg(err);
			return 0.0f;
		}

		return cursor;
	}

	float Sound::GetLength() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));
		
		float length = 0.0f;
		ma_result res = ma_sound_get_length_in_seconds(sound, &length);
		
		if (res != MA_SUCCESS)
		{
			std::string err = std::format("Failed to get length of sound with ID: '{}'", uint64_t(m_SoundID));
			Context::SetErrorMsg(err);
			return 0.0f;
		}

		return length;
	}

	bool Sound::IsPlaying() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return (bool)ma_sound_is_playing(sound);
	}

	bool Sound::IsPaused() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return Context::GetSoundInternalData(m_SoundID)->IsPaused;
	}

	bool Sound::IsLooping() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return (bool)ma_sound_is_looping(sound);
	}

	void Sound::SetLooping(bool loop) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_looping(sound, (ma_bool32)loop);
	}

	bool Sound::IsSpacialized() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return (bool)ma_sound_is_spatialization_enabled(sound);
	}

	void Sound::SetSpacialized(bool spacialized) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_spatialization_enabled(sound, spacialized);
	}

}

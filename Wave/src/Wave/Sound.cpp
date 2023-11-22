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
		Context::GetSoundInternalData(m_SoundID)->IsPlaying = true;
		
		return true;
	}

	bool Sound::Restart() const
	{
		bool result = true;

		if (IsPlaying())
		{
			result = SeekToPCMFrame(0);
		}

		Context::GetSoundInternalData(m_SoundID)->IsPaused = false;
		Context::GetSoundInternalData(m_SoundID)->IsPlaying = true;

		return result;
	}

	bool Sound::Pause() const
	{
		bool result = true;

		if (!IsPaused())
		{
			result = Stop();
		}

		Context::GetSoundInternalData(m_SoundID)->IsPaused = true;
		Context::GetSoundInternalData(m_SoundID)->IsPlaying = false;
		
		return result;
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

		Context::GetSoundInternalData(m_SoundID)->IsPaused = false;
		Context::GetSoundInternalData(m_SoundID)->IsPlaying = false;
		
		return true;
	}

	float Sound::GetVolume() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return Context::GetSoundInternalData(m_SoundID)->Volume;
	}

	void Sound::SetVolume(float volume) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_volume(sound, volume);
		Context::GetSoundInternalData(m_SoundID)->Volume = volume;
	}

	float Sound::GetPitch() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return Context::GetSoundInternalData(m_SoundID)->Pitch;
	}

	void Sound::SetPitch(float pitch) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_pitch(sound, pitch);
		Context::GetSoundInternalData(m_SoundID)->Pitch = pitch;
	}

	float Sound::GetDopplerFactor() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return Context::GetSoundInternalData(m_SoundID)->DopplerFactor;
	}

	void Sound::SetDopplerFactor(float dopplerFactor) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_doppler_factor(sound, dopplerFactor);
		Context::GetSoundInternalData(m_SoundID)->DopplerFactor = dopplerFactor;
	}

	Vec3 Sound::GetPosition() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return Context::GetSoundInternalData(m_SoundID)->Position;
	}

	void Sound::SetPosition(const Vec3& position) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_position(sound, position.X, position.Y, position.Z);
		Context::GetSoundInternalData(m_SoundID)->Position = position;
	}

	Vec3 Sound::GetDirection() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return Context::GetSoundInternalData(m_SoundID)->Direction;
	}

	void Sound::SetDirection(const Vec3& direction) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_direction(sound, direction.X, direction.Y, direction.Z);
		Context::GetSoundInternalData(m_SoundID)->Direction = direction;
	}

	Vec3 Sound::GetVelocity() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return Context::GetSoundInternalData(m_SoundID)->Velocity;
	}

	void Sound::SetVelocity(const Vec3& velocity) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_velocity(sound, velocity.X, velocity.Y, velocity.Z);
		Context::GetSoundInternalData(m_SoundID)->Velocity = velocity;
	}

	AudioCone Sound::GetAudioCone() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return Context::GetSoundInternalData(m_SoundID)->Cone;
	}

	void Sound::SetAudioCone(const AudioCone& cone) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_cone(sound, Utils::DegreesToRadians(cone.InnerAngle), Utils::DegreesToRadians(cone.OuterAngle), cone.OuterGain);
		AudioCone& cone_ = Context::GetSoundInternalData(m_SoundID)->Cone;
		cone_.InnerAngle = Utils::DegreesToRadians(cone.InnerAngle);
		cone_.OuterAngle = Utils::DegreesToRadians(cone.OuterAngle);
		cone_.OuterGain = cone.OuterGain;
	}

	float Sound::GetMinGain() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return Context::GetSoundInternalData(m_SoundID)->MinGain;
	}

	void Sound::SetMinGain(float minGain) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_min_gain(sound, minGain);
		Context::GetSoundInternalData(m_SoundID)->MinGain = minGain;
	}

	float Sound::GetMaxGain() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return Context::GetSoundInternalData(m_SoundID)->MaxGain;
	}

	void Sound::SetMaxGain(float maxGain) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_max_gain(sound, maxGain);
		Context::GetSoundInternalData(m_SoundID)->MaxGain = maxGain;
	}

	float Sound::GetFalloff() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return Context::GetSoundInternalData(m_SoundID)->Falloff;
	}

	void Sound::SetFalloff(float falloff) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_rolloff(sound, falloff);
		Context::GetSoundInternalData(m_SoundID)->Falloff = falloff;
	}

	float Sound::GetMinDistance() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return Context::GetSoundInternalData(m_SoundID)->MinDistance;
	}

	void Sound::SetMinDistance(float minDistance) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_min_distance(sound, minDistance);
		Context::GetSoundInternalData(m_SoundID)->MinDistance = minDistance;
	}

	float Sound::GetMaxDistance() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return Context::GetSoundInternalData(m_SoundID)->MaxDistance;
	}

	void Sound::SetMaxDistance(float maxDistance) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_max_distance(sound, maxDistance);
		Context::GetSoundInternalData(m_SoundID)->MaxDistance = maxDistance;
	}

	AttenuationModel Sound::GetAttenuationModel() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return Context::GetSoundInternalData(m_SoundID)->Model;
	}

	void Sound::SetAttenuationModel(AttenuationModel model) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_attenuation_model(sound, (ma_attenuation_model)model);
		Context::GetSoundInternalData(m_SoundID)->Model = model;
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

		return Context::GetSoundInternalData(m_SoundID)->Length;
	}

	bool Sound::IsPlaying() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return Context::GetSoundInternalData(m_SoundID)->IsPlaying;
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

		return Context::GetSoundInternalData(m_SoundID)->IsLooping;
	}

	void Sound::SetLooping(bool loop) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_looping(sound, (ma_bool32)loop);
		Context::GetSoundInternalData(m_SoundID)->IsLooping = loop;
	}

	bool Sound::IsSpacialized() const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		return Context::GetSoundInternalData(m_SoundID)->Spacialized;
	}

	void Sound::SetSpacialized(bool spacialized) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_sound_set_spatialization_enabled(sound, spacialized);
		Context::GetSoundInternalData(m_SoundID)->Spacialized = spacialized;
	}

	bool Sound::SeekToPCMFrame(uint64_t frameIndex) const
	{
		ma_sound* sound = (ma_sound*)Context::GetSoundInternal(m_SoundID);
		WAVE_ASSERT(sound, "Invalid sound ID: '%zu'", uint64_t(m_SoundID));

		ma_result res = ma_sound_seek_to_pcm_frame(sound, frameIndex);

		if (res != MA_SUCCESS)
		{
			std::string err = std::format("Failed to seek to frame '{}' on sound with ID: '{}'", frameIndex, uint64_t(m_SoundID));
			Context::SetErrorMsg(err);
			return false;
		}

		return true;
	}

}

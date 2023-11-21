#pragma once

#include "Wave/Types.h"
#include "Wave/ID.h"

namespace Wave {

	struct SoundData
	{
		float Volume = 1.0f;
		float Pitch = 1.0f;
		float DopplerFactor = 0.0f;
		float Falloff = 1.0f;

		float MinGain = 1.0f;
		float MaxGain = 1.0f;
		float MinDistance = 1.0f;
		float MaxDistance = 1.0f;

		Vec3 Position = Vec3(0.0f);
		Vec3 Direction = Vec3(0.0f);
		Vec3 Velocity = Vec3(0.0f);

		AudioCone Cone;
		AttenuationModel Model = AttenuationModel::Inverse;

		bool IsPlaying = false;
		bool IsPaused = false;
		bool IsLooping = false;
		bool Spacialized = true;
	};

	class Sound
	{
	public:
		inline Sound(ID id) : m_SoundID(id) { }
		~Sound() = default;

		bool Play() const;
		bool Restart() const;
		bool Pause() const;
		bool Stop() const;

		float GetVolume() const;
		void SetVolume(float volume) const;

		float GetPitch() const;
		void SetPitch(float pitch) const;

		float GetDopplerFactor() const;
		void SetDopplerFactor(float dopplerFactor) const;

		Vec3 GetPosition() const;
		void SetPosition(const Vec3& position) const;

		Vec3 GetDirection() const;
		void SetDirection(const Vec3& direction) const;

		Vec3 GetVelocity() const;
		void SetVelocity(const Vec3& velocity) const;

		AudioCone GetAudioCone() const;
		void SetAudioCone(const AudioCone& cone) const;

		float GetMinGain() const;
		void SetMinGain(float minGain) const;

		float GetMaxGain() const;
		void SetMaxGain(float maxGain) const;

		float GetFalloff() const;
		void SetFalloff(float falloff) const;

		float GetMinDistance() const;
		void SetMinDistance(float minDistance) const;

		float GetMaxDistance() const;
		void SetMaxDistance(float maxDistance) const;

		AttenuationModel GetAttenuationModel() const;
		void SetAttenuationModel(AttenuationModel model) const;

		float GetSoundCursor() const;
		float GetLength() const;

		bool IsPlaying() const;
		bool IsPaused() const;

		bool IsLooping() const;
		void SetLooping(bool loop) const;

		bool IsSpacialized() const;
		void SetSpacialized(bool spacialized) const;

		inline ID GetID() const { return m_SoundID; }

		inline operator ID() const { return m_SoundID; }

	private:
		ID m_SoundID = ID::Invalid;
	};

}

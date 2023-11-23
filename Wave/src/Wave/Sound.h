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

		float DirectionalAttenuationFactor = 1.0f;

		float Pan = 1.0f;
		PanMode PanMode = PanMode::Balance;

		Positioning Positioning_ = Positioning::Absolute;

		float LengthInSeconds = 0.0f;
		uint64_t LengthInPCMFrames = 0;

		Vec3 Position = Vec3(0.0f);
		Vec3 Direction = Vec3(0.0f);
		Vec3 Velocity = Vec3(0.0f);

		AudioCone Cone;
		AttenuationModel Model = AttenuationModel::Inverse;

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

		const Vec3& GetPosition() const;
		void SetPosition(const Vec3& position) const;

		const Vec3& GetDirection() const;
		void SetDirection(const Vec3& direction) const;

		const Vec3& GetVelocity() const;
		void SetVelocity(const Vec3& velocity) const;

		const Vec3& GetDirectionToListener() const;

		const AudioCone& GetAudioCone() const;
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

		float GetDirectionalAttenuationFactor() const;
		void SetDirectionalAttenuationFactor(float factor) const;

		float GetPan() const;
		void SetPan(float pan) const;

		PanMode GetPanMode() const;
		void SetPanMode(PanMode panMode) const;

		Positioning GetPositioning() const;
		void SetPositioning(Positioning positioning) const;

		uint32_t GetListenerIndex() const;
		uint32_t GetPinnedListenerIndex() const;
		void SetPinnedListenerIndex(uint32_t listenerIndex) const;

		float GetCurrentFadeVolume() const;
		float GetCursorInSeconds() const;
		uint64_t GetCursorInPCMFrames() const;

		uint64_t GetTimeInMilliseconds() const;
		uint64_t GetTimeInPCMFrames() const;

		void SetStartTimeInMilliseconds(uint64_t startTimeInMilliseconds);
		void SetStopTimeInMilliseconds(uint64_t stopTimeInMilliseconds);
		void SetStopTimeWithFadeInMilliseconds(uint64_t stopTimeInMilliseconds, uint64_t fadeLengthInMilliseconds);

		void SetStartTimeInPCMFrames(uint64_t startTimeInFrames);
		void SetStopTimeInPCMFrames(uint64_t stopTimeInFrames);
		void SetStopTimeWithFadeInPCMFrames(uint64_t stopTimeInFrames, uint64_t fadeLengthInFrames);

		void SetFadeInMilliseconds(float volumeStart, float volumeEnd, uint64_t	fadeLengthInMilliseconds);
		void SetFadeStartInMilliseconds(float volumeStart, float volumeEnd, uint64_t fadeLengthInMilliseconds, uint64_t absoluteGlobalTimeInMilliseconds);

		void SetFadeInPCMFrames(float volumeStart, float volumeEnd, uint64_t fadeLengthInFrames);
		void SetFadeStartInPCMFrames(float volumeStart, float volumeEnd, uint64_t fadeLengthInFrames, uint64_t absoluteGlobalTimeInFrames);

		float GetLengthInSeconds() const;
		uint64_t GetLengthInPCMFrames() const;

		bool IsPlaying() const;
		bool IsPaused() const;

		bool IsLooping() const;
		void SetLooping(bool loop) const;

		bool IsSpacialized() const;
		void SetSpacialized(bool spacialized) const;

		bool SeekToPCMFrame(uint64_t frameIndex) const;

		inline ID GetID() const { return m_SoundID; }

		inline operator ID() const { return m_SoundID; }

	private:
		ID m_SoundID = ID::Invalid;
	};

}

#pragma once

#include "Wave/ID.h"

namespace Wave {

	struct SoundSettings
	{

	};

	class Sound
	{
	public:
		inline Sound(ID id) : m_SoundID(id) { }
		~Sound() = default;

		bool Init(const SoundSettings& settings);
		bool Shutdown();

		void Play();
		void Stop();

		inline ID GetID() const { return m_SoundID; }

	private:
		ID m_SoundID = ID(0);
	};

}

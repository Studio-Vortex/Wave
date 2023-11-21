#pragma once

#include "Wave/Context.h"
#include "Wave/Engine.h"
#include "Wave/Sound.h"
#include "Wave/Types.h"

namespace Wave {

	class PlaybackDevice
	{
	public:
		PlaybackDevice() = default;
		~PlaybackDevice() = default;

		bool Init(std::shared_ptr<Context> context, const std::filesystem::path& path);
		bool Init(std::shared_ptr<Context> context, const DataSource& src);
		bool Shutdown(std::shared_ptr<Context> context); 

		bool Play() const;
		bool Restart() const;
		bool Pause() const;
		bool Stop() const;

		Engine GetEngine() const { return m_Engine; }
		Sound GetSound() const { return m_Sound; }

	private:
		Engine m_Engine = Engine(ID::Invalid);
		Sound m_Sound = Sound(ID::Invalid);
	};

}

#include "PlaybackDevice.h"

#include "Wave/Assert.h"

namespace Wave {

	bool PlaybackDevice::Init(std::shared_ptr<Context> context, const std::filesystem::path& path)
	{
		m_Engine = context->CreateEngine();
		if (m_Engine.GetID() == ID::Invalid)
		{
			return false;
		}
		
		m_Sound = context->CreateSoundFromFile(m_Engine, path);
		if (m_Sound.GetID() == ID::Invalid)
		{
			return false;
		}

		return true;
	}

	bool PlaybackDevice::Init(std::shared_ptr<Context> context, const DataSource& src)
	{
		WAVE_ASSERT(false, "Not implemented yet!%s", "");
		return false;
	}

	bool PlaybackDevice::Shutdown(std::shared_ptr<Context> context)
	{
		if (m_Sound.IsPlaying())
		{
			m_Sound.Stop();
		}

		if (m_Engine.IsRunning())
		{
			m_Engine.Stop();
		}

		// Destroy the sound before the engine because the sound relies on the engine
		if (!context->DestroySound(m_Sound))
		{
			return false;
		}

		if (!context->DestroyEngine(m_Engine))
		{
			return false;
		}

		m_Engine = Engine(ID::Invalid);
		m_Sound = Sound(ID::Invalid);

		return true;
	}

	bool PlaybackDevice::Play() const
	{
		if (m_Sound.IsPlaying())
		{
			return true;
		}

		if (!m_Engine.IsRunning() && !m_Engine.Start())
		{
			return false;
		}

		if (!m_Sound.Play())
		{
			return false;
		}

		return true;
	}

	bool PlaybackDevice::Restart() const
	{
		if (!m_Sound.IsPlaying())
		{
			return true;
		}

		if (!m_Engine.IsRunning() && !m_Engine.Start())
		{
			return false;
		}

		if (!m_Sound.Restart())
		{
			return false;
		}

		return true;
	}

	bool PlaybackDevice::Pause() const
	{
		if (m_Sound.IsPaused())
		{
			return true;
		}

		if (!m_Sound.Pause())
		{
			return false;
		}

		return true;
	}

	bool PlaybackDevice::Stop() const
	{
		if (!m_Sound.IsPlaying())
		{
			return true;
		}

		if (!m_Sound.Stop())
		{
			return false;
		}

		if (!m_Engine.Stop())
		{
			return false;
		}

		return true;
	}

}

#pragma once

#include "Wave/ID.h"

namespace Wave {
	
	struct SoundGroupData
	{
		bool IsPaused = false;
	};

	class SoundGroup
	{
	public:
		inline SoundGroup(ID soundGroupID, ID parentGroupID = ID::Invalid)
			: m_SoundGroupID(soundGroupID), m_ParentGroupID(parentGroupID) { }
		~SoundGroup() = default;

		bool Play() const;
		bool Restart() const;
		bool Pause() const;
		bool Stop() const;

	private:
		ID m_SoundGroupID = ID::Invalid;
		ID m_ParentGroupID = ID::Invalid;
		std::vector<ID> m_Children;
	};

}

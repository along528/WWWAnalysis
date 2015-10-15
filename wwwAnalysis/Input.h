#ifndef Input_H
#define Input_H

#include <vector>
#include <TVector2.h>
#include "PATCore/TAccept.h"
#include "wwwAnalysis/EventData.h"

namespace wwwAnalysis
{

class Input : public EventData
{
	private:
		Long64_t m_iEntry;
		Long64_t m_iEntries;
	public:
    Input();

		void initialize(TTree * = 0);
		bool nextEvent();
		bool isDone();

    ~Input();
};

} // End: namespace wwwAnalysis

#endif

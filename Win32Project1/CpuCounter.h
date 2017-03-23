#pragma once


/////////////
// LINKING //
/////////////
#pragma comment(lib, "pdh.lib")


//////////////
// INCLUDES //
//////////////
#include <pdh.h>


///////////////////////////////////////////////////////////////////////////////
// Class name: CpuClass
///////////////////////////////////////////////////////////////////////////////

namespace GameEngineProject
{

	class CpuCounter
	{
	public:
		CpuCounter();
		CpuCounter(const CpuCounter&);
		~CpuCounter();

		void Initialize();
		void Shutdown();
		void Update();
		int GetCpuPercentage();

	private:
		bool m_canReadCpu;
		HQUERY m_queryHandle;
		HCOUNTER m_counterHandle;
		unsigned long m_lastSampleTime;
		long m_cpuUsage;
	};
}
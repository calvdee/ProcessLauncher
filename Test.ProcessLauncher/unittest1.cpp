#include <Windows.h>
#include <string>
#include <list>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "cProcessGroup.h"
#include "cLaunchReport.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TestProcessLauncher
{		
	TEST_CLASS( AppTest )
	{
	public:
		
		TEST_METHOD( TestRunProcess )
		{
			wstring cmd = L"c:/windows/system32/notepad.exe";
			wstring cmdLine = L"";
			Process::proc_ptr p = make_shared< Process >( cmd, cmdLine );

			// Process should start up okay and have handles
			Assert::AreEqual( 0, p->RunProcess() );
			Assert::AreNotEqual< HANDLE >( NULL, p->GetProcessHandle() );

			// Terminate the process
			DWORD exitCode = 0;
			BOOL term = TerminateProcess( p->GetProcessHandle(), exitCode );
			
			Assert::IsTrue( term );
		}

		TEST_METHOD( TestRunProcessGroup )
		{
			vector< Process::proc_ptr >  procs;
			
			procs.push_back( make_shared< Process >( L"c:/windows/system32/notepad.exe", L"" ) );
			procs.push_back( make_shared< Process >( L"c:/python27/python.exe", L"" ) );

			ProcessGroup procGroup( 1, procs );

			vector< LaunchReport> reports = procGroup.LaunchProcessGroup();

			// For each 
		}

	};
}
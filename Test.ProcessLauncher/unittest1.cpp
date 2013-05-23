#include "stdafx.h"
#include <Windows.h>
#include <string>
#include <list>
#include <algorithm>
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
		
			Process::proc_ptr p = make_shared< Process >( cmd, L"" );

			// Process should start up okay and have handles
			Assert::AreEqual( 0, p->RunProcess() );
			Assert::AreNotEqual< HANDLE >( NULL, p->GetProcessHandle() );

			// Terminate the process
			DWORD exitCode = 0;
			BOOL term = TerminateProcess( p->GetProcessHandle(), exitCode );
		}

		//TEST_METHOD( TestRunProcess_WithSpace )
		//{
		//	wstring cmd = L"ShellError - Copy";
		//	wstring cmdLine = L"";
		//	Process::proc_ptr p = make_shared< Process >( cmd, cmdLine );

		//	// Process should have returned error condition
		//	Assert::AreNotEqual( 0, p->RunProcess() );
		//	Assert::AreEqual< HANDLE >( NULL, p->GetProcessHandle() );
		//}

		TEST_METHOD( TestRunProcessGroup )
		{
			vector< Process::proc_ptr >  procs;
			DWORD exitCode = 0;

			procs.push_back( make_shared< Process >( L"c:/windows/system32/notepad.exe", L"" ) );
			procs.push_back( make_shared< Process >( L"c:/python27/python.exe", L"" ) );

			// Process should start up okay and have handles and terminate properly
			for( auto p = procs.begin(); p != procs.end(); ++p ) {
				Assert::AreEqual( 0, p->get()->RunProcess() );
				Assert::AreNotEqual< HANDLE >( NULL, p->get()->GetProcessHandle() );
				Assert::IsTrue( TerminateProcess( p->get()->GetProcessHandle(), exitCode ) );
				Assert::AreEqual<DWORD>( 0, exitCode );
			}

			ProcessGroup procGroup( 1, procs );
			vector<LaunchReport> reports = procGroup.LaunchProcessGroup();

			// The bad process should not be in the reports
			size_t reportCount = 2;
			Assert::AreEqual( reportCount, reports.size() );
		}

	};
}
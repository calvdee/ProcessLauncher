#include <Windows.h>
#include <string>
#include "stdafx.h"
#include "CppUnitTest.h"
#include "cProcess.h"

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
			Assert::AreNotEqual< HANDLE >( NULL, p->GetThreadHandle() );

			// Terminate the process
			DWORD exitCode = 0;
			BOOL term = TerminateProcess( p->GetProcessHandle(), exitCode );
			
			Assert::IsTrue( term );
		}

	};
}
// mytestdump.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "client/windows/crash_generation/client_info.h"
#include "client/windows/crash_generation/crash_generation_server.h"
#include "client/windows/common/ipc_protocol.h"
#include "client/windows/tests/crash_generation_app/abstract_class.h"
#include "client/windows/handler/exception_handler.h"

const wchar_t kPipeName[] = L"\\\\.\\pipe\\BreakpadCrashServices\\TestServer";

static google_breakpad::ExceptionHandler* handler = NULL;

bool ShowDumpResults(const wchar_t* dump_path,
	const wchar_t* minidump_id,
	void* context,
	EXCEPTION_POINTERS* exinfo,
	MDRawAssertionInfo* assertion,
	bool succeeded) 
{
		return succeeded;
}

static int kCustomInfoCount = 2;
static google_breakpad::CustomInfoEntry kCustomInfoEntries[] = {
	google_breakpad::CustomInfoEntry(L"prod", L"mytestdump.exe"),
	google_breakpad::CustomInfoEntry(L"ver", L"1.0"),
};

google_breakpad::CustomClientInfo custom_info = {kCustomInfoEntries, kCustomInfoCount};

int _tmain(int argc, _TCHAR* argv[])
{
	handler = new google_breakpad::ExceptionHandler(L"./dumps",
		NULL,
		ShowDumpResults,
		NULL,
		google_breakpad::ExceptionHandler::HANDLER_ALL,
		MiniDumpNormal,
		kPipeName,
		&custom_info);

	int * a = NULL;

	*a = 1;

	system("pause");

	return 0;
}


// Copyright (c) 2015 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include <windows.h>
#include "base/cef_scoped_ptr.h"
#include "include/cef_command_line.h"
#include "include/cef_sandbox_win.h"
#include "Chiika/browser/client_app_browser.h"
#include "Chiika/browser/main_context_impl.h"
#include "Chiika/browser/main_message_loop_multithreaded_win.h"
#include "Chiika/browser/main_message_loop_std.h"
#include "Chiika/browser/root_window_manager.h"
#include "Chiika/browser/test_runner.h"
#include "Chiika/common/client_app_other.h"
#include "Chiika/renderer/client_app_renderer.h"

#include "Common/Required.h"
#include "Root/Root.h"
#include "Database\LocalDataManager.h"


// When generating projects with CMake the CEF_USE_SANDBOX value will be defined
// automatically if using the required compiler version. Pass -DUSE_SANDBOX=OFF
// to the CMake command-line to disable use of the sandbox.
// Uncomment this line to manually enable sandbox support.
// #define CEF_USE_SANDBOX 1

#if defined(CEF_USE_SANDBOX)
// The cef_sandbox.lib static library is currently built with VS2013. It may not
// link successfully with other VS versions.
#pragma comment(lib, "cef_sandbox.lib")
#endif

namespace client {
	namespace {

		int RunMain(HINSTANCE hInstance,int nCmdShow) {
			// Enable High-DPI support on Windows 7 or newer.
			CefEnableHighDPISupport();

			CefMainArgs main_args(hInstance);



			void* sandbox_info = NULL;

#if defined(CEF_USE_SANDBOX)
			// Manage the life span of the sandbox information object. This is necessary
			// for sandbox support on Windows. See cef_sandbox_win.h for complete details.
			CefScopedSandboxInfo scoped_sandbox;
			sandbox_info = scoped_sandbox.sandbox_info();
#endif

			// Parse command-line arguments.
			CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
			command_line->InitFromString(::GetCommandLineW());

			// Create a ClientApp of the correct type.
			CefRefPtr<CefApp> app;
			ClientApp::ProcessType process_type = ClientApp::GetProcessType(command_line);
			if(process_type == ClientApp::BrowserProcess)
				app = new ClientAppBrowser();
			else if(process_type == ClientApp::RendererProcess)
				app = new ClientAppRenderer();
			else if(process_type == ClientApp::OtherProcess)
				app = new ClientAppOther();

			// Execute the secondary process, if any.
			int exit_code = CefExecuteProcess(main_args,app,sandbox_info);
			if(exit_code >= 0)
				return exit_code;

			// Create the main context object.
			scoped_ptr<MainContextImpl> context(new MainContextImpl(command_line,true));

			CefSettings settings;

#if !defined(CEF_USE_SANDBOX)
			settings.no_sandbox = true;
#endif




			// Populate the settings based on command line arguments.
			context->PopulateSettings(&settings);
			settings.multi_threaded_message_loop = true;
			// Create the main message loop object.
			scoped_ptr<MainMessageLoop> message_loop;
			if(settings.multi_threaded_message_loop)
				message_loop.reset(new MainMessageLoopMultithreadedWin);
			else
				message_loop.reset(new MainMessageLoopStd);

			// Initialize CEF.
			context->Initialize(main_args,settings,app,sandbox_info);

			// Register scheme handlers.
			test_runner::RegisterSchemeHandlers();

			char szFileName[MAX_PATH];

			GetModuleFileNameA(hInstance, szFileName, MAX_PATH);

			std::string pathToExecutable = szFileName;
			std::string dir = pathToExecutable.substr(0, pathToExecutable.find_last_of("\\"));

			ChiikaApi::Root r;
			r.Initialize(dir);

			// Create the first window.
			context->GetRootWindowManager()->CreateRootWindow(
				false,             // Show controls.
				false,
				CefRect(),        // Use default system size.
				dir + "/UI/Index.html");   // Use default URL.



			ChiikaApi::UserInfo ui;
			ui.UserName = "arkenthera";
			ui.Pass = "123asd456";
			r.m_pLocalData->SetUserInfo(ui);

			/*GetAnimeListRequest req(NULL);
			req.Initialize();
			req.SetOptions();
			req.Initiate();*/









			// Run the message loop. This will block until Quit() is called by the
			// RootWindowManager after all windows have been destroyed.
			int result = message_loop->Run();

			r.Destroy();
			// Shut down CEF.
			context->Shutdown();

			// Release objects in reverse order of creation.
			message_loop.reset();
			context.reset();

			return result;
		}

	}  // namespace
}  // namespace client


// Program entry point function.
int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	return client::RunMain(hInstance,nCmdShow);
}

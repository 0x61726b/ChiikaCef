//----------------------------------------------------------------------------
//Chiika Cef
//Copyright (C) 2015  Alperen Gezer
//This program is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or
//(at your option) any later version.
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//You should have received a copy of the GNU General Public License along
//with this program; if not, write to the Free Software Foundation, Inc.,
//51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/
//----------------------------------------------------------------------------
#ifndef __Chiika_browser_delegate_h__
#define __Chiika_browser_delegate_h__
//----------------------------------------------------------------------------
#include "Chiika\browser\client_handler.h"
//----------------------------------------------------------------------------
namespace client
{
	namespace Chiika_Browser
	{
		class ChiBrowserDelegate : public ClientHandler::ProcessMessageDelegate
		{
		public:
			ChiBrowserDelegate();

			virtual bool OnProcessMessageReceived(
				CefRefPtr<ClientHandler> handler,
				CefRefPtr<CefBrowser> browser,
				CefProcessId source_process,
				CefRefPtr<CefProcessMessage> message) OVERRIDE;

		private:
			IMPLEMENT_REFCOUNTING(ChiBrowserDelegate);
		};

		void CreateProcessMessageDelegates(ClientHandler::ProcessMessageDelegateSet& delegates);
	}
}

//----------------------------------------------------------------------------
#endif
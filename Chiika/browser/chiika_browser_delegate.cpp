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
#include "chiika_browser_delegate.h"
#include "Chiika\common\chi_js_list.h"

#include "Root\Root.h"
#include "Chiika\common\chi_helper.h"
//----------------------------------------------------------------------------
namespace client
{
	namespace Chiika_Browser
	{
		ChiBrowserDelegate::ChiBrowserDelegate()
			: ProcessMessageDelegate(kNamespace)
		{

		}
		void ChiBrowserDelegate::OnSuccess(ChiikaApi::RequestInterface*)
		{
		}
		void ChiBrowserDelegate::OnError(ChiikaApi::RequestInterface*)
		{
		}
		bool ChiBrowserDelegate::OnProcessMessageReceived(
			CefRefPtr<ClientHandler> handler,
			CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message)
		{
			//Process messages here
			ChiikaApi::Root* r = ChiikaApi::Root::Get();
			ChiikaApi::ChiString str = r->GetHash();

			std::string message_name = message->GetName();


			if(message_name == InNamespace("Testo"))
			{


			}

			if(message_name == InNamespace(kVerifyUser))
			{
				bool status = true;
				if(status)
				{
					//Verify success
					CefRefPtr<CefProcessMessage> browserMessage = CefProcessMessage::Create(CefString(message->GetName()));
					CefRefPtr<CefListValue> message_args = browserMessage->GetArgumentList();

					message_args->SetBool(0,true);

					CefRefPtr<CefListValue> userInfoList = CefListValue::Create();
					userInfoList->SetInt(0,45555);
					userInfoList->SetString(1,"arkenthera");

					
					message_args->SetList(1,userInfoList);
					browser->SendProcessMessage(PID_RENDERER,browserMessage);
				}

				if(!status)
				{
					//Verify failed
					CefRefPtr<CefProcessMessage> browserMessage = CefProcessMessage::Create(CefString(message->GetName()));
					CefRefPtr<CefListValue> message_args = browserMessage->GetArgumentList();

					message_args->SetBool(0,false);

					std::string errorMsg = "Verifying user failed.";
					message_args->SetString(1,(errorMsg));
					browser->SendProcessMessage(PID_RENDERER,browserMessage);

				}
			}
			return true;
		}

		void CreateProcessMessageDelegates(ClientHandler::ProcessMessageDelegateSet& delegates) {
			delegates.insert(new ChiBrowserDelegate);
		}
	}
}
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
#include "Chiika\common\chi_helper.h"

//Chiika API Includes
#include "Root\Root.h"
#include "Request\RequestInterface.h"
#include "Request\RequestList.h"
#include "Database\JsKeys.h"

//Requests
#include "Request\AccountVerify.h"
#include "Request\GetAnimeList.h"


#include "Database\LocalDataManager.h"
#include "Request\MalManager.h"
//----------------------------------------------------------------------------
namespace client
{
	namespace Chiika_Browser
	{
		ChiBrowserDelegate::ChiBrowserDelegate()
			: ProcessMessageDelegate(kNamespace)
		{

		}
		//----------------------------------------------------------------------------

		bool ChiBrowserDelegate::OnProcessMessageReceived(
			CefRefPtr<ClientHandler> handler,
			CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message)
		{
			std::string message_name = message->GetName();

#ifdef OS_WIN
			CefRunnableCurlRequestWin* runnableRequest = new CefRunnableCurlRequestWin(browser,message->Copy());
			CreateThread(NULL,0,&CefRunnableCurlRequestWin::RunOnSeperateThread,runnableRequest,0,NULL);
#elif OS_LINUX
			//Implement pt_thread here		
#endif



			return true;
		}
		//----------------------------------------------------------------------------
		void CefRunnableCurlRequestWin::OnSuccess(ChiikaApi::RequestInterface* request)
		{
			std::string name = request->GetName();

			/// VerifyUser
			//	ChiikaVerifyUser(success,error,dict)
			if(name == ChiikaApi::GetRequest(ChiikaApi::Requests::VerifyUser))
			{
				ChiikaApi::LocalDataManager* ldm = ChiikaApi::LocalDataManager::Get();

				CefRefPtr<CefProcessMessage> browserMessage = CefProcessMessage::Create(CefString(kNamespace + name));
				CefRefPtr<CefListValue> message_args = browserMessage->GetArgumentList();

				message_args->SetBool(0,true);

				CefRefPtr<CefListValue> userInfoList = CefListValue::Create();
				userInfoList->SetInt(0,ldm->GetUserInfo().UserId);
				userInfoList->SetString(1,ldm->GetUserInfo().UserName);


				message_args->SetList(1,userInfoList);
				m_pBrowser->SendProcessMessage(PID_RENDERER,browserMessage);
			}

			/// GetAnimelistRequest
			//	ChiikaGetAnimelistRequest(success,error)
			if(name == ChiikaApi::GetRequest(ChiikaApi::Requests::GetAnimelistRequest))
			{
				CefRefPtr<CefProcessMessage> browserMessage = CefProcessMessage::Create(CefString(kNamespace + name));
				CefRefPtr<CefListValue> message_args = browserMessage->GetArgumentList();
				ChiikaApi::MalManager* malManager = ChiikaApi::MalManager::Get();

				ChiikaApi::UserAnimeList animeList = malManager->GetAnimeList();
				
				CefRefPtr<CefListValue> cefAnimeList = CefListValue::Create();

				std::vector<std::string> animeKeys;
				::GetAnimeKeys(animeKeys);
				
				KeyList userAnimeKeys;
				::GetUserAnimeEntryKeys(userAnimeKeys);

				ChiikaApi::UserAnimeList::iterator It = animeList.begin();
				int index = 0;
				
				for(It; It != animeList.end();It++)
				{
					//This UserAnimeEntry index
					CefRefPtr<CefDictionaryValue> userAnimeDict = CefDictionaryValue::Create();


					//UserAnimeEntry::Anime
					CefRefPtr<CefDictionaryValue> animeDict = CefDictionaryValue::Create();

					for(size_t j = 0; j < animeKeys.size(); j++)
					{
						const std::string& value = It->second.Anime.GetKeyValue(animeKeys.at(j));
						animeDict->SetString(animeKeys.at(j),value);
					}
					userAnimeDict->SetDictionary("anime",animeDict);



					//UserAnimeEntry properties
					for (size_t k = 0; k < userAnimeKeys.size(); k++)
					{
						userAnimeDict->SetString(userAnimeKeys[k],
							It->second.GetKeyValue(userAnimeKeys[k]));
					}



					cefAnimeList->SetDictionary(index,userAnimeDict);
					index++;
				}

				//Include User Info
				KeyList userKeys;
				::GetUserInfoKeys(userKeys);

				ChiikaApi::UserInfo ui = ChiikaApi::LocalDataManager::Get()->GetUserInfo();

				CefRefPtr<CefDictionaryValue> userInfoDict = CefDictionaryValue::Create();
				for(size_t i = 0; i < userKeys.size(); i++)
				{
					userInfoDict->SetString(userKeys[i],
											ui.GetKeyValue(userKeys[i]));
				}

				message_args->SetBool(0,true);
				message_args->SetList(1,cefAnimeList);
				message_args->SetDictionary(2,userInfoDict);
				m_pBrowser->SendProcessMessage(PID_RENDERER,browserMessage);
			}

		}
		//----------------------------------------------------------------------------
		void CefRunnableCurlRequestWin::OnError(ChiikaApi::RequestInterface* request)
		{
			std::string name = request->GetName();

			/// VerifyUser
			//	ChiikaVerifyUser(success,error,dict)
			if(name == ChiikaApi::GetRequest(ChiikaApi::Requests::VerifyUser))
			{

				CefRefPtr<CefProcessMessage> browserMessage = CefProcessMessage::Create(CefString(kNamespace + name));
				CefRefPtr<CefListValue> message_args = browserMessage->GetArgumentList();

				message_args->SetBool(0,false);

				std::string errorMsg = "Verifying user failed.";
				message_args->SetString(1,(errorMsg));
				message_args->SetString(2,request->GetResponse());
				m_pBrowser->SendProcessMessage(PID_RENDERER,browserMessage);
			}
			/// GetAnimelistRequest
			//	ChiikaGetAnimelistRequest(success,error)
			if(name == ChiikaApi::GetRequest(ChiikaApi::Requests::GetAnimelistRequest))
			{
				CefRefPtr<CefProcessMessage> browserMessage = CefProcessMessage::Create(CefString(kNamespace + name));
				CefRefPtr<CefListValue> message_args = browserMessage->GetArgumentList();

				message_args->SetBool(0,false);

				std::string errorMsg = name + " failed.";
				message_args->SetString(1,(errorMsg));
				message_args->SetString(2,request->GetResponse());
				m_pBrowser->SendProcessMessage(PID_RENDERER,browserMessage);
			}
		}
		//----------------------------------------------------------------------------
		DWORD CefRunnableCurlRequestWin::RunOnSeperateThread(LPVOID params)
		{
			CefRunnableCurlRequestWin* instance = reinterpret_cast<CefRunnableCurlRequestWin*>(params);

			DCHECK(instance);

			if(!instance)
				return 0;
			if(instance->m_pMessage)
			{
				std::string message_name = instance->m_pMessage->GetName();

				/// NOTE: First 2 arguments are always success,error callbacks.When iterating through list always start from 2nd index
				/// API functions that require threading will be processed here,such as CURL requests
				//  since they block the UI thread if executed from main thread
				//	JS functions are executed on renderer process.
				//  ChiV8 class sends IPC message to here to process messages on browser process
				//	After the custom network thread is executed we send back another IPC to tell renderer process to execute the appropriate callback
				//	See chiika_v8_handler for callback execution on renderer process
				///
				if(message_name == InNamespace("Testo"))
				{


				}
				/// VerifyUser
				//	ChiikaVerifyUser(success,error,dict)
				//	arg2:{ name: , pass: }
				//  return: { UserID:, UserName: }
				//  Creates MAL request to verify user credentials
				///
				if(message_name == InNamespace(kVerifyUser))
				{
					CefRefPtr<CefListValue> message_args = instance->m_pMessage->GetArgumentList();
					CefRefPtr<CefDictionaryValue> dict = message_args->GetDictionary(2);

					ChiikaApi::AccountVerifyRequest request;
					ChiikaApi::UserInfo ui;
					ui.UserName = dict->GetValue("user")->GetString();
					ui.Pass = dict->GetValue("pass")->GetString();

					request.Initialize();
					request.SetUserInfo(ui);
					request.SetOptions();


					request.AddListener(instance);
					request.Initiate();
				}
				/// GetAnimelistRequest
				//	ChiikaGetAnimelistRequest(success,error)
				//	return: { animeListDict,userInfoDict }
				//  Creates MAL request to get user's animelist
				///
				if(message_name == InNamespace(kGetAnimelistRequest))
				{
					ChiikaApi::GetAnimeListRequest request;
					request.Initialize();
					request.SetOptions();
					request.AddListener(instance);
					request.Initiate();

				}
			}
			return 0;
		}
		//----------------------------------------------------------------------------
		CefRunnableCurlRequestWin::CefRunnableCurlRequestWin(CefRefPtr<CefBrowser> browser,CefRefPtr<CefProcessMessage> message)
		{
			m_pBrowser = browser;
			m_pMessage = message;
		}
		//----------------------------------------------------------------------------
		void CreateProcessMessageDelegates(ClientHandler::ProcessMessageDelegateSet& delegates) {
			delegates.insert(new ChiBrowserDelegate);
		}
		//----------------------------------------------------------------------------
	}
}
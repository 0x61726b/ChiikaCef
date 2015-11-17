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
#include "include\base\cef_bind.h"
#include "include\wrapper\cef_closure_task.h"
#include "Chiika\browser\client_handler.h"
#include "Chiika\renderer\chiika_v8_handler.h"

#include "Chiika\common\chi_helper.h"
#include "Chiika\common\chi_js_list.h"
//----------------------------------------------------------------------------

CallbackMap callback_map_;
namespace
	client
{
	namespace Chiika
	{
		void FillCallbackMap(const std::string& name, const CefRefPtr<CefV8Value>& function)
		{
			auto s = callback_map_.insert(std::make_pair(name, std::make_pair(function, CefV8Context::GetCurrentContext())));
			if (s.second == false)
			{
				callback_map_[name] = std::make_pair(function, CefV8Context::GetCurrentContext());
			}
		}
		ChiV8::ChiV8()
		{
			messageId = 0;
		}

		bool ChiV8::Execute(
			const CefString &name, CefRefPtr<CefV8Value> object,
			const CefV8ValueList &arguments,
			CefRefPtr<CefV8Value> &retval,
			CefString &exception)
		{
			CefRefPtr<CefBrowser> browser = CefV8Context::GetCurrentContext()->GetBrowser();

			if (!browser)
				return false;

			if (arguments.size() > 0 && arguments[0]->IsFunction())
			{

				CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
				callback_map_.insert(CallbackMap::value_type(name,
					std::make_pair(arguments[0],context)));

				CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(name);
				CefRefPtr<CefListValue> message_args = message->GetArgumentList();

				::Chiika::SetListValue(message_args, 0, CefV8Value::CreateInt(messageId));

				for (size_t i = 1; i < arguments.size(); i++)
					::Chiika::SetListValue(message_args, i, arguments[i]);

				browser->SendProcessMessage(PID_BROWSER, message);

				return true;
			}
			return false;
		}
		class ChiRenderDelegate : public ClientAppRenderer::Delegate {
		public:
			ChiRenderDelegate() {
			}

			virtual void OnContextCreated(CefRefPtr<ClientAppRenderer> app,
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				CefRefPtr<CefV8Context> context) override
			{
				CefRefPtr<CefV8Value> object = context->GetGlobal();

				CefRefPtr<CefV8Handler> handler = new ChiV8();

				int functionListSize = jsCpp.size();

				if (functionListSize > 0)
				{
					for (std::map<std::string, enum JsEnum>::iterator iter = jsCpp.begin(); iter != jsCpp.end(); iter++)
					{
						object->SetValue(kNamespace + iter->first,
							CefV8Value::CreateFunction(kNamespace + iter->first, handler),
							V8_PROPERTY_ATTRIBUTE_READONLY);
					}
				}
			}
			virtual bool OnProcessMessageReceived(
				CefRefPtr<ClientAppRenderer> app,
				CefRefPtr<CefBrowser> browser,
				CefProcessId source_process,
				CefRefPtr<CefProcessMessage> message) override
			{
				if (message->GetName() == InNamespace(kTestFunc))
				{
					if (CefCurrentlyOn(TID_RENDERER))
					{
						if (!callback_map_.empty())
						{
							CallbackMap::const_iterator it = callback_map_.find(InNamespace(kTestFunc));
							if (it != callback_map_.end())
							{
								CefRefPtr<CefV8Value> callback = it->second.first;
								CefRefPtr<CefV8Context> context = it->second.second;

								if (context.get() && context->Enter())
								{
									CefRefPtr<CefV8Value> object = CefV8Value::CreateObject(NULL);
									CefV8ValueList args;
									CefRefPtr<CefV8Exception> exception;
									CefRefPtr<CefListValue> list = CefListValue::Create();
									list->SetString(0, "1");
									list->SetString(1, "2");
									list->SetString(2, "3");
									list->SetString(3, "4");
									CefRefPtr<CefV8Value> v8list = CefV8Value::CreateArray(4);
									::Chiika::SetList(list, v8list);
									args.push_back(v8list);
									
									if (callback->ExecuteFunctionWithContext(context, object, args))
									{
										//MessageBox(0,L"ExecuteFunctionWithContext",L"success",0);
										LOG(INFO) << kTestFunc << "ExecuteFunctionWithContext Succeeded";
									}
								}
							}
						}
					}


				}
				return false;
			}


		private:
			IMPLEMENT_REFCOUNTING(ChiRenderDelegate);
		};

		void CreateDelegates(ClientAppRenderer::DelegateSet& delegates) {
			delegates.insert(new ChiRenderDelegate);
		}
	}


}
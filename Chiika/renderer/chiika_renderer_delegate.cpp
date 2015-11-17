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
#include "chiika_renderer_delegate.h"
#include "chiika_v8_handler.h"
#include "Chiika/common/chi_js_list.h"
namespace client
{
	namespace Chiika
	{
		// Handle bindings in the render process.
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
				
			}


		private:
			IMPLEMENT_REFCOUNTING(ChiRenderDelegate);
		};

		void CreateDelegates(ClientAppRenderer::DelegateSet& delegates) {
			delegates.insert(new ChiRenderDelegate);
		}
	}
}
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
#ifndef __Chiika_v8_handler_h__
#define __Chiika_v8_handler_h__
//----------------------------------------------------------------------------
#include "Chiika/renderer/client_app_renderer.h"
//----------------------------------------------------------------------------
typedef std::map< std::string, std::pair< CefRefPtr<CefV8Value>, CefRefPtr<CefV8Context> > > CallbackMap;
extern CallbackMap callback_map_;
namespace client
{
	
	namespace Chiika
	{	
		class ChiV8 : public CefV8Handler
		{
		public:
			ChiV8();

			virtual bool Execute(const CefString& name,
				CefRefPtr<CefV8Value> object,
				const CefV8ValueList& arguments,
				CefRefPtr<CefV8Value>& retval,
				CefString& exception) OVERRIDE;

			int32 messageId;
			IMPLEMENT_REFCOUNTING(ChiV8);
		};
		void CreateDelegates(ClientAppRenderer::DelegateSet& delegates);

	}
}

//----------------------------------------------------------------------------
#endif
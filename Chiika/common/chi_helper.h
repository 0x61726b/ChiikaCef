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
#ifndef __Chi_helper_h__
#define __Chi_helper_h__
//----------------------------------------------------------------------------
#include "include\cef_v8.h"
#include "Common\Required.h"
//----------------------------------------------------------------------------
namespace Chiika
{
	void SetList(CefRefPtr<CefV8Value> source, CefRefPtr<CefListValue> target);
	void SetList(CefRefPtr<CefListValue> source, CefRefPtr<CefV8Value> target);
	void SetListValue(CefRefPtr<CefListValue> list, int index, CefRefPtr<CefV8Value> value);
	void SetListValue(CefRefPtr<CefV8Value> list, int index, CefRefPtr<CefListValue> value);
	CefRefPtr<CefV8Value> ListValueToV8Value(CefRefPtr<CefListValue> value, int index);
	std::string DumpListValue(CefRefPtr<CefListValue> list, int index);
	std::string DumpList(CefRefPtr<CefListValue> list);

	void SetDictionary(CefRefPtr<CefDictionaryValue> source, CefRefPtr<CefV8Value> target);
	void SetDictionaryValue(
		CefRefPtr<CefV8Value> list,
		const CefString& key,
		CefRefPtr<CefDictionaryValue> value);
	void AnimeListToCefList(ChiikaApi::UserAnimeList* source,
							CefRefPtr<CefDictionaryValue> target,
							ChiikaApi::UserAnimeEntry::KeyList,
							ChiikaApi::Anime::KeyList);
}

//----------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------
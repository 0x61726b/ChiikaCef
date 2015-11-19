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

#include "chi_helper.h"
#include "include/cef_parser.h"
#include "include\base\cef_logging.h"

namespace Chiika
{
	void SetListValue(
		CefRefPtr<CefListValue> list,
		int index,
		CefRefPtr<CefV8Value> value)
	{

		if (value->IsArray()) {
			CefRefPtr<CefListValue> new_list = CefListValue::Create();
			SetList(value, new_list);
			list->SetList(index, new_list);
		}
		else if (value->IsString()) {
			list->SetString(index, value->GetStringValue());
		}
		else if (value->IsBool()) {
			list->SetBool(index, value->GetBoolValue());
		}
		else if (value->IsInt()) {
			list->SetInt(index, value->GetIntValue());
		}
		else if (value->IsDouble()) {
			list->SetDouble(index, value->GetDoubleValue());
		}
		else if (value->IsNull()) {
			list->SetNull(index);
		}
		else if (value->IsObject() && !value->IsFunction())
		{
			CefRefPtr<CefDictionaryValue> dictionary = CefDictionaryValue::Create();
			std::vector<CefString> keys;
			value->GetKeys(keys);

			for (size_t i = 0; i < keys.size(); ++i)
			{
				dictionary->SetString(keys[i], value->GetValue(keys[i])->GetStringValue());
			}
			list->SetDictionary(index, dictionary);
		}
		else
		{
			LOG(WARNING) << "Unknown CEF list value type";
		}
	}

	// Transfer a V8 array to a List.
	void SetList(CefRefPtr<CefV8Value> source, CefRefPtr<CefListValue> target)
	{
		CHECK(source->IsArray());

		int arg_length = source->GetArrayLength();
		if (arg_length == 0)
			return;

		// Start with null types in all spaces.
		target->SetSize(arg_length);

		for (int i = 0; i < arg_length; ++i)
			SetListValue(target, i, source->GetValue(i));
	}

	CefRefPtr<CefV8Value> ListValueToV8Value(CefRefPtr<CefListValue> value, int index)
	{
		CefRefPtr<CefV8Value> new_value;

		CefValueType type = value->GetType(index);

		switch (type) {
		case VTYPE_LIST: {
			CefRefPtr<CefListValue> list = value->GetList(index);
			new_value = CefV8Value::CreateArray(list->GetSize());
			SetList(list, new_value);
		} break;
		case VTYPE_BOOL:
			new_value = CefV8Value::CreateBool(value->GetBool(index));
			break;
		case VTYPE_DOUBLE:
			new_value = CefV8Value::CreateDouble(value->GetDouble(index));
			break;
		case VTYPE_INT:
			new_value = CefV8Value::CreateInt(value->GetInt(index));
			break;
		case VTYPE_STRING:
			new_value = CefV8Value::CreateString(value->GetString(index));
			break;
		default:
			new_value = CefV8Value::CreateNull();
			break;
		}

		return new_value;
	}

	// Transfer a List value to a V8 array index.
	void SetListValue(
		CefRefPtr<CefV8Value> list,
		int index,
		CefRefPtr<CefListValue> value)
	{

		CefRefPtr<CefV8Value> new_value;

		CefValueType type = value->GetType(index);
		switch (type) {
		case VTYPE_LIST: {
			CefRefPtr<CefListValue> list = value->GetList(index);
			new_value = CefV8Value::CreateArray(list->GetSize());
			SetList(list, new_value);
		} break;
		case VTYPE_DICTIONARY:
		{
			CefRefPtr<CefDictionaryValue> dict = value->GetDictionary(index);
			new_value = CefV8Value::CreateArray(dict->GetSize());
			SetDictionary(dict, new_value);
		} break;
		case VTYPE_BOOL:
			new_value = CefV8Value::CreateBool(value->GetBool(index));
			break;
		case VTYPE_DOUBLE:
			new_value = CefV8Value::CreateDouble(value->GetDouble(index));
			break;
		case VTYPE_INT:
			new_value = CefV8Value::CreateInt(value->GetInt(index));
			break;
		case VTYPE_STRING:
			new_value = CefV8Value::CreateString(value->GetString(index));
			break;
		case VTYPE_NULL:
			new_value = CefV8Value::CreateNull();
			break;
		default:
			break;
		}

		if (new_value.get()) {
			list->SetValue(index, new_value);
		}
		else {
			list->SetValue(index, CefV8Value::CreateNull());
		}
	}

	//Transfer a dict to a v8 array
	void SetDictionaryValue(
		CefRefPtr<CefV8Value> list,
		const CefString& key,
		CefRefPtr<CefDictionaryValue> value)
	{

		CefRefPtr<CefV8Value> new_value;

		CefValueType type = value->GetType(key);
		switch (type) {
		case VTYPE_LIST: {
			CefRefPtr<CefListValue> list = value->GetList(key);
			new_value = CefV8Value::CreateArray(list->GetSize());
			SetList(list, new_value);
		} break;
		case VTYPE_DICTIONARY:
		{
			CefRefPtr<CefDictionaryValue> dict = value->GetDictionary(key);
			new_value = CefV8Value::CreateArray(dict->GetSize());

		} break;
		case VTYPE_BOOL:
			new_value = CefV8Value::CreateBool(value->GetBool(key));
			break;
		case VTYPE_DOUBLE:
			new_value = CefV8Value::CreateDouble(value->GetDouble(key));
			break;
		case VTYPE_INT:
			new_value = CefV8Value::CreateInt(value->GetInt(key));
			break;
		case VTYPE_STRING:
			new_value = CefV8Value::CreateString(value->GetString(key));
			break;
		case VTYPE_NULL:
			new_value = CefV8Value::CreateNull();
			break;
		default:
			break;
		}

		if (new_value.get()) {
			list->SetValue(key, new_value, CefV8Value::PropertyAttribute::V8_PROPERTY_ATTRIBUTE_READONLY);
		}
		else {
			list->SetValue(key, CefV8Value::CreateNull(), CefV8Value::PropertyAttribute::V8_PROPERTY_ATTRIBUTE_READONLY);
		}
	}

	// Transfer a List to a V8 array.
	void SetList(CefRefPtr<CefListValue> source, CefRefPtr<CefV8Value> target)
	{
		DCHECK(target->IsArray());

		int arg_length = source->GetSize();
		if (arg_length == 0)
			return;

		for (int i = 0; i < arg_length; ++i)
			SetListValue(target, i, source);
	}
	void SetDictionary(CefRefPtr<CefDictionaryValue> source, CefRefPtr<CefV8Value> target)
	{
		DCHECK(target->IsArray());

		std::vector<CefString> keys;
		source->GetKeys(keys);
		int arg_length = keys.size();
		if (arg_length == 0)
			return;


		for (int i = 0; i < arg_length; ++i)
			SetDictionaryValue(target, keys[i],source);

	}
	std::string DumpListValue(CefRefPtr<CefListValue> list, int index)
	{
		std::string result;
		switch (list->GetType(index)) {
		case VTYPE_LIST:
			result += DumpList(list->GetList(index));
			break;
		case VTYPE_BOOL:
			result += (list->GetBool(index) ? "true" : "false");
			break;
		case VTYPE_DOUBLE:
			result += std::to_string(list->GetDouble(index));
			break;
		case VTYPE_INT:
			result += std::to_string(list->GetInt(index));
			break;
		case VTYPE_STRING:
			result += '"';
			result += list->GetString(index);
			result += '"';
			break;
		case VTYPE_NULL:
			result += "null";
			break;
		default:
			result += "unknown";
		}

		return result;
	}

	void AnimeListToCefList(ChiikaApi::UserAnimeList* source,
		CefRefPtr<CefDictionaryValue> target,
		ChiikaApi::UserAnimeEntry::KeyList userAnimeKeys,
		ChiikaApi::Anime::KeyList animeKeys)
	{
		
		ChiikaApi::UserAnimeList::iterator It = source->begin();
		int index = 0;
		for (It; It != source->end();It++)
		{
			//This UserAnimeEntry index
			CefRefPtr<CefDictionaryValue> userAnimeDict = CefDictionaryValue::Create();


			//UserAnimeEntry::Anime
			CefRefPtr<CefDictionaryValue> animeDict = CefDictionaryValue::Create();

			for (size_t j = 0; j < animeKeys.size(); j++)
			{
				const std::string& value = It->second.Anime.GetKeyValue(animeKeys.at(j));
				animeDict->SetString(animeKeys.at(j), value);
			}
			userAnimeDict->SetDictionary("anime", animeDict);


			////UserAnimeEntry properties
			//for (size_t k = 0; k < userAnimeKeys.size(); k++)
			//{
			//	userAnimeDict->SetString(userAnimeKeys[k],
			//		source.at(k).GetKeyValue(userAnimeKeys[k]));
			//}



			target->SetDictionary("Anime", userAnimeDict);
			index++;
		}
	}

	std::string DumpList(CefRefPtr<CefListValue> list)
	{
		int arg_length = list->GetSize();
		if (arg_length == 0)
			return "";

		std::stringstream result;
		result << "(";
		for (int i = 0; i < arg_length; ++i) {
			result << DumpListValue(list, i);
			if (i + 1 < arg_length)
				result << ", ";
		}
		result << ")";
		return result.str();
	}
}
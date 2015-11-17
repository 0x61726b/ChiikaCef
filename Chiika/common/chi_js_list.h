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
#ifndef __Chi_js_list_h__
#define __Chi_js_list_h__
//----------------------------------------------------------------------------
const char kNamespace[] = "Chiika";
const char kErrorCallback[] = "Error";
const char kSuccessCallback[] = "Success";
const char kTestFunc[] = "Testo";
const char kVerifyUser[] = "VerifyUser";

//Usage
//All functions will be called as
//Chiika<FunctionName>(callback,args...)
static enum JsEnum
{
	TestFunc,
	VerifyUser
};
static std::map<std::string,JsEnum> jsCpp = 
{
	std::make_pair("Testo",JsEnum::TestFunc),
	std::make_pair(kVerifyUser,JsEnum::VerifyUser)
};

#define InNamespace(x) std::string(kNamespace) + std::string(x)

//----------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------
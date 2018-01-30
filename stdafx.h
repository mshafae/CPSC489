/** \file   stdafx.h
 *  \brief  Precompiled header and program requirements.
 *  \author Steven F. Emory
 *  \date   01/29/2018
 */
#ifndef __STDAFX_H
#define __STDAFX_H

//
// Windows Version
//
#define WINVER 0x0601
#define _WIN32_WINNT 0x0601

//
// Windows Headers
//

#define NOMINMAX
#define STRSAFE_NO_DEPRECATE
#include<windows.h>
#include<windowsx.h>
#include<commctrl.h>
#include<shellapi.h>
#ifndef RC_INVOKED
#include<shlobj.h>
#include<tchar.h>
#include<strsafe.h>
#include<shlwapi.h>
#include<wincodec.h>
#include<atlbase.h>
#endif
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "windowscodecs.lib")

//
// Standard Headers
//

#ifndef RC_INVOKED
#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<memory>
#include<algorithm>
#include<limits>
#include<string>
#include<vector>
#include<array>
#include<deque>
#include<cmath>
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<set>
#endif

//
// Boost Headers
//

#ifndef RC_INVOKED
#include<boost/algorithm/string.hpp>
#include<boost/algorithm/string/classification.hpp>
#include<boost/algorithm/string/split.hpp>
#include<boost/algorithm/string/trim.hpp>
#include<boost/algorithm/string/trim_all.hpp>
#endif

//
// DirectX Headers
//

/// \headerfile d3d11.h <d3d11.h>
/// \headerfile dxgi.h <dxgi.h>
/// \headerfile DirectXMath.h <DirectXMath.h>
#ifndef RC_INVOKED
#include<d3d11.h>
#include<dxgi.h>
#include<DirectXMath.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#endif

//
// DATA TYPES
//

// built-in types
typedef char sint08;
typedef unsigned char uint08;
typedef short sint16;
typedef unsigned short uint16;
typedef int sint32;
typedef unsigned int uint32;
typedef long long sint64;
typedef unsigned long long uint64;
typedef float real32;
typedef double real64;

// string types
typedef std::basic_string<TCHAR> STDTSTRING;
typedef std::basic_string<CHAR>  STDSTRINGA;
typedef std::basic_string<WCHAR> STDSTRINGW;

// stringstream types
typedef std::basic_stringstream<TCHAR> STDTSTRINGSTREAM;
typedef std::basic_stringstream<CHAR>  STDSTRINGSTREAMA;
typedef std::basic_stringstream<WCHAR> STDSTRINGSTREAMW;

//
// String Functions
//

#ifndef RC_INVOKED

/** \class   WideStringHash
 *  \brief   A string hashing function based on Bob Jenkin's One-at-a-Time algorithm.
 *  \details This string hashing algorithm, which I have used for many years now,
 *           has served me quite well. Useful to prevent textures from being loaded
 *           multiple times (filename -> map -> texture data). If I remember right, I
 *           got the code from http://www.burtleburtle.net/bob/hash/doobs.html.
*/
struct WideStringHash {
 size_t operator ()(const std::wstring& str)const;
};

/** \class   WideStringInsensitiveEqual
 *  \brief   A C++ function object for use with std::sort.
 *  \details Yeah, the C++ STL string classes do not have case-insensitive
 *           string sorting so we have to provide a function object (or lambda)
 *           to do it ourselves.
*/
struct WideStringInsensitiveEqual {
 bool operator ()(const std::wstring& s1, const std::wstring& s2)const {
  return _wcsicmp(s1.c_str(), s2.c_str()) == 0;
 }
};

#endif

#endif

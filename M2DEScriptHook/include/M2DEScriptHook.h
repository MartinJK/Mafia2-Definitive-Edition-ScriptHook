/*
 * Copyright (c) 2010 Barzakh (martinjk 'at' outlook 'dot' com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.

 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.

 * 3. This notice may not be removed or altered from any source
 * distribution.

 * 4. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once

#include <Export.h>
#include <PluginSystem.h>
#include <LuaStateManager.h>
#include <singleton.h>
#include <lua.h>
#include <map>
#include <mutex>
#include <vector>

static const char *BindableKeys[] = {
	"VK_LBUTTON", "VK_RBUTTON", "VK_CANCEL", "VK_MBUTTON", "VK_XBUTTON1",
	"VK_XBUTTON2","-", "VK_BACK", "VK_TAB", "-", "VK_CLEAR", "VK_RETURN", "-",
	"VK_SHIFT", "VK_CONTROL", "VK_MENU", "VK_PAUSE", "VK_CAPITAL", "VK_KANA",
	"VK_HANGUEL", "VK_HANGUL", "-", "VK_JUNJA", "VK_FINAL", "VK_HANJA",
	"VK_KANJI", "-", "VK_ESCAPE", "VK_CONVERT", "VK_NONCONVERT", "VK_ACCEPT",
	"VK_MODECHANGE", "VK_SPACE", "VK_PRIOR", "VK_NEXT", "VK_END", "VK_HOME",
	"VK_LEFT", "VK_UP", "VK_RIGHT", "VK_DOWN", "VK_SELECT", "VK_PRINT",
	"VK_EXECUTE", "VK_SNAPSHOT", "VK_INSERT", "VK_DELETE", "VK_HELP", "0", "1",
	"2", "3", "4", "5", "6", "7", "8", "9","-", "-", "-", "-", "-", "-", "-",
	"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k","l", "m", "n", "o",
	"p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "VK_LWIN",
	"VK_RWIN", "VK_APPS", "-", "VK_SLEEP", "VK_NUMPAD0", "VK_NUMPAD1",
	"VK_NUMPAD2", "VK_NUMPAD3", "VK_NUMPAD4", "VK_NUMPAD5", "VK_NUMPAD6",
	"VK_NUMPAD7", "VK_NUMPAD8", "VK_NUMPAD9", "VK_MULTIPLY", "VK_ADD",
	"VK_SEPARATOR", "VK_SUBTRACT", "VK_DECIMAL", "VK_DIVIDE", "VK_F1",
	"VK_F2", "VK_F3", "VK_F4", "VK_F5", "VK_F6", "VK_F7", "VK_F8", "VK_F9",
	"VK_F10", "VK_F11", "VK_F12", "VK_F13", "VK_F14", "VK_F15", "VK_F16",
	"VK_F17", "VK_F18", "VK_F19", "VK_F20", "VK_F21", "VK_F22", "VK_F23",
	"VK_F24", "-", "-", "-", "-", "-", "-", "-", "-", "VK_NUMLOCK",
	"VK_SCROLL", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-",
	"-", "-", "VK_LSHIFT", "VK_RSHIFT", "VK_LCONTROL", "VK_RCONTROL",
	"VK_LMENU", "VK_RMENU", "VK_BROWSER_BACK", "VK_BROWSER_FORWARD",
	"VK_BROWSER_REFRESH", "VK_BROWSER_STOP", "VK_BROWSER_SEARCH",
	"VK_BROWSER_FAVORITES", "VK_BROWSER_HOME", "VK_VOLUME_MUTE",
	"VK_VOLUME_DOWN", "VK_VOLUME_UP", "VK_MEDIA_NEXT_TRACK",
	"VK_MEDIA_PREV_TRACK", "VK_MEDIA_STOP", "VK_MEDIA_PLAY_PAUSE",
	"VK_LAUNCH_MAIL", "VK_LAUNCH_MEDIA_SELECT", "VK_LAUNCH_APP1",
	"VK_LAUNCH_APP2", "-", "-", "VK_OEM_1", "VK_OEM_PLUS", "VK_OEM_COMMA",
	"VK_OEM_MINUS", "VK_OEM_PERIOD", "VK_OEM_2", "VK_OEM_3", "-", "-", "-",
	"-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-",
	"-", "-", "-", "-", "-", "-", "-", "-", "VK_OEM_4", "VK_OEM_5", "VK_OEM_6",
	"VK_OEM_7", "VK_OEM_8", "-", "-", "VK_OEM_102", "-", "-", "VK_PROCESSKEY",
	"-", "VK_PACKET", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-",
	"-", "-", "VK_ATTN", "VK_CRSEL", "VK_EXSEL", "VK_EREOF", "VK_PLAY", "VK_ZOOM",
	"VK_NONAME", "VK_PA1", "VK_OEM_CLEAR" };

#define SCRIPTMACHINE_MAX 12

class M2DEKeyBind
{
public: 
	M2DEKeyBind() = default;
	M2DEKeyBind(uint8_t a1, std::string a2) :
		key(a1),
		bind(a2) { }
	virtual ~M2DEKeyBind() = default;;

	uint8_t key;
	std::string bind;
};

class M2DEScriptHook : public singleton<M2DEScriptHook>
{
private:
	bool m_bEnded = false;
	//std::vector<M3KeyBind*> keyBinds = {};
	std::map<uint8_t, std::string> keyBinds = {};
	std::recursive_mutex _keyBindMutex;

public:
	M2DEScriptHook();
	virtual ~M2DEScriptHook() = default;

	void Log(std::string message);
	void Log(const char *string, ...);
	void LogToFile(const char *fileName, const char *string, ...);
	void EndThreads();
	void LoadScript(const std::string &file);
	void LoadLuaFile(lua_State *L, const std::string &name);
	bool ExecuteLua(lua_State *L, const std::string &lua);
	static uint32_t WINAPI mainThread(LPVOID);
	void StartThreads();
	bool HasEnded();
	void Shutdown();

	void CreateKeyBind(const char *key, const char *context);
	void DestroyKeyBind(const char *key, const char *context);
	void ProcessKeyBinds();
};

lua_State *GetL();
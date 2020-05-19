set MAFIAPATH=H:\Steam\steamapps\common\Mafia II Definitive Edition\pc
set mypath=C:\Users\Martin\Desktop\Mafia2-Definitive-Edition-ScriptHook
copy /Y /B "%mypath%\build\Release\M2DEScriptHook.dll" "%MAFIAPATH%\M2DEScriptHook.dll" /B 
copy /Y /B "%mypath%\build\Release\plugins\ExampleDLLPlugin.dll" "%MAFIAPATH%\plugins\ExampleDLLPlugin.dll" /B 
copy /Y /B "%mypath%\build\Release\M2DEScriptHookLauncher.exe" "%MAFIAPATH%\M2DEScriptHookLauncher.exe" /B
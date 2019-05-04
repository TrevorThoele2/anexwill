
#include <locale>
#include <codecvt>

#include <Atmos/WindowsEngine.h>

//#include <vld.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ::Atmos::FilePath worldPath;

    // Load the world given
    {
        int argCount;
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

        LPWSTR* szArgList;

        szArgList = CommandLineToArgvW(GetCommandLineW(), &argCount);
        if (szArgList == nullptr || argCount < 2)
        {
            MessageBox(nullptr, L"A world file has not been supplied.", L"Error", MB_OK);
            return 0;
        }
 
        worldPath = std::string(converter.to_bytes(std::wstring(szArgList[1])));

        LocalFree(szArgList);
    }

    ::Atmos::WindowsEngine engine(hInstance, lpCmdLine, nCmdShow, "AnExWill");
    engine.Setup();
    engine.LoadWorld(worldPath.GetValue());
    engine.StartExecution();

    return 0;
}
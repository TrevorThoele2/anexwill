
//#include <vld.h>
#include <locale>
#include <codecvt>

#include <Atmos\GameEnvironment.h>
#include <Atmos\Windows.h>
#include <falcon\engine.h>

#include <Inscription\BinaryScribe.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Atmos::FilePath worldPath;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    int argCount;

    // Load the world given
    {
        LPWSTR *szArgList;

        szArgList = CommandLineToArgvW(GetCommandLineW(), &argCount);
        if (szArgList == nullptr || argCount < 2)
        {
            MessageBox(nullptr, L"A world file has not been supplied.", L"Error", MB_OK);
            return 0;
        }
 
        worldPath = std::string(converter.to_bytes(std::wstring(szArgList[1])));

        LocalFree(szArgList);
    }

    Atmos::GameEnvironment::LoadWorld(worldPath.GetValue());
    Atmos::Environment::Setup<Atmos::Windows>(hInstance, lpCmdLine, nCmdShow, "AnExWill");
    Atmos::Environment::StartExecution();
    return 0;
}
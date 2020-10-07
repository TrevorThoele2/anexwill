#include <locale>
#include <codecvt>

#include <Atmos/WindowsEngine.h>

std::optional<Atmos::File::Path> WorldPath()
{
    int argCount;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    const auto szArgList = CommandLineToArgvW(GetCommandLineW(), &argCount);
    if (szArgList == nullptr || argCount < 2)
        return {};

    auto returnValue = std::string(converter.to_bytes(std::wstring(szArgList[1])));

    LocalFree(szArgList);

    return returnValue;
}

void StartEngineExecution(Atmos::WindowsEngine& engine, const Atmos::File::Path& worldPath)
{
    engine.Setup();
    engine.LoadWorld(worldPath, worldPath);
    engine.StartExecution();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //auto worldPath = WorldPath();
    std::optional<std::filesystem::path> worldPath = std::filesystem::current_path() / "1.atw";

    if (!worldPath)
    {
        MessageBox(nullptr, L"A world file needs to be supplied.", L"Error", MB_OK);
        return 0;
    }

    Atmos::WindowsEngine engine(hInstance, lpCmdLine, nCmdShow, "AnExWill");
    StartEngineExecution(engine, *worldPath);

    return 0;
}
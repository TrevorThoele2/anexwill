#include <locale>
#include <codecvt>

#include <Atmos/WindowsEngine.h>
#include <Atmos/AssetsFileExtension.h>
#include <Atmos/Logger.h>

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
    auto assetsPath = worldPath;
    assetsPath.replace_extension(Atmos::World::Serialization::assetsFileExtension);

    engine.Setup();
    engine.LoadWorld(worldPath, assetsPath);
    engine.StartExecution();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Atmos::Logging::Logger logger(Atmos::Logging::Severity::Verbose);

    try
    {
        auto worldPath = WorldPath();

        if (!worldPath)
        {
            MessageBox(nullptr, L"A world file needs to be supplied.", L"Error", MB_OK);
            return 0;
        }

        Atmos::WindowsEngine engine(hInstance, lpCmdLine, nCmdShow, "AnExWill", logger);
        StartEngineExecution(engine, *worldPath);
    }
    catch (const std::exception & e)
    {
        logger.Log(
            e.what(),
            Atmos::Logging::Severity::Error);
    }
    catch(...)
    {
        logger.Log(
            "Unknown error.",
            Atmos::Logging::Severity::Error);
    }

    return 0;
}
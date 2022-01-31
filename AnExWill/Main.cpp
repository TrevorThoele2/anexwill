#include <optional>

#include <Atmos/SDLEngine.h>
#include <Atmos/AssetsFileExtension.h>
#include <Atmos/Logger.h>
#include <Atmos/FileLoggingSink.h>
#include <SDL.h>

std::optional<Atmos::File::Path> WorldPath(int argc, char* argv[])
{
    if (argc < 2 || argv == nullptr)
        return {};

    return argv[1];
}

void StartEngineExecution(Atmos::SDLEngine& engine, const Atmos::File::Path& worldPath)
{
    auto assetsPath = worldPath;
    assetsPath.replace_extension(Atmos::World::Serialization::assetsFileExtension);

    engine.LoadWorld(worldPath, assetsPath);
    engine.StartExecution();
}

int main(int argc, char* argv[])
{
    Atmos::Logging::Logger logger(Atmos::Logging::Severity::Verbose);
    logger.AddSink<Atmos::Logging::FileSink>();

    try
    {
        auto worldPath = WorldPath(argc, argv);

        if (!worldPath)
        {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "A world file needs to be supplied.", nullptr);
            return -3;
        }

        Atmos::SDLEngine engine(logger);
        StartEngineExecution(engine, *worldPath);
    }
    catch (const std::exception& e)
    {
        logger.Log(
            e.what(),
            Atmos::Logging::Severity::Error);
        return -2;
    }
    catch (...)
    {
        logger.Log(
            "Unknown error.",
            Atmos::Logging::Severity::Error);
        return -1;
    }

    return 0;
}
#include "ConverterJson.h"


#ifdef _WIN32
#include <Windows.h>
#elif defined(__linux__)
#include <unistd.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

std::string ConverterJson::getPath() {
    std::string executablePath;

#ifdef _WIN32
    char path[MAX_PATH];
    GetModuleFileName(nullptr, path, sizeof(path));
    executablePath = path;
#elif defined(__linux__)
    char path[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (count != -1) {
        path[count] = '\0';
        executablePath = path;
    }
#elif defined(__APPLE__)
    char path[PATH_MAX];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0) {
        executablePath = path;
    }
#endif

    size_t lastSlashPos = executablePath.find_last_of("/\\");
    if (lastSlashPos != std::string::npos) {
        executablePath = executablePath.substr(0, lastSlashPos+1);
    }

    return executablePath;
}

    int ConverterJson::GetConfig()
    {
        try {
            nlohmann::json config;
            std::ifstream file(getPath()+"config.json");
            if (!file.is_open())
                throw std::runtime_error("Program cannot run without config.json ");
            file >> config;

            nlohmann::json cfg = config["config"];

            if (cfg.is_null()) {
                throw std::runtime_error("JSON file does not contain 'config' key.");
            }
            for (auto &element: cfg.items()) {
                std::cout << element.key() << " : " << element.value() << std::endl;
            }
            files_paths = config["files"];
        }
        catch (std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            return 0;
        }
        return 0;
    }

    int ConverterJson::GetResponsesLimit()
    {
        try {
            nlohmann::json cfg;
            std::ifstream file(getPath()+"config.json");
            file >> cfg;
            file.close();
            return cfg["config"]["maxVariants"];
        }
        catch (std::exception &e)
        {
            throw std::runtime_error("Program cannot run without config.json ");
        }

    }

    std::vector<std::string> ConverterJson::GetRequests()
    {
        nlohmann::json requests;
        try {
            std::ifstream file(getPath()+"requests.json");
            file >> requests;
        }
        catch (std::exception &e) {
            std::cerr << "First you need to create requests.json " << std::endl;
        }

        int i=0;
        for(auto request : requests["requests"])
        {
            all_requests.push_back(request);
//            std::cout << all_requests[i] << std::endl;
            ++i;
        }
        return all_requests;
    }

std::vector<std::string> ConverterJson::GetDocsText()
{
    try{
        nlohmann::json docs_list;
        std::ifstream cfg (getPath()+"config.json");
        cfg >> docs_list;       // load config.json into json object

        std::vector<std::string> docs;
        for(auto& doc : docs_list["files"])
        {
            std::string id=doc;
            std::ifstream input( getPath()+id );
            if(input.is_open())
            {
                std::stringstream buffer;
                buffer << input.rdbuf();
                input.close();
                docs.push_back(buffer.str());
            }
            else
            {
                std::cout << "Error opening " << doc <<std::endl;
            }
        }
        return docs;
    }
    catch (std::exception &e)
    {
        throw std::runtime_error("Program cannot run without config.json ");
    }

}
#include "ConverterJson.h"

    int ConverterJson::GetConfig()
    {
        try {
            nlohmann::json config;
            std::ifstream file("config.json");
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
            std::ifstream file("config.json");
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
            std::ifstream file("requests.json");
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
        std::ifstream cfg ("config.json");
        cfg >> docs_list;       // load config.json into json object

        std::vector<std::string> docs;
        for(auto& doc : docs_list["files"])
        {
            std::ifstream input(doc);
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
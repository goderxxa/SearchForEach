#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <map>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <cstdlib>
#include <limits.h>

class ConverterJson {

private:
    std::vector<std::string> files_paths;
    std::vector<std::string> all_requests;

public:
    ConverterJson() = default;

    std::string getPath();
    int GetConfig(); //
    int GetResponsesLimit();
    std::vector<std::string> GetRequests();
    std::vector<std::string> GetDocsText();

};

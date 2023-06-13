#include "ConverterJson.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

int main() {

    clock_t start = clock();

    InvertedIndex idx;
    idx.UpdateDocumentBase(ConverterJson().GetDocsText());
    SearchServer srv(idx);
    std::vector<std::vector<RelativeIndex>> result = srv.search(ConverterJson().GetRequests());
    srv.showResults(result);

    std::string inputRequest;
    std::cout << "To exit you must type '-1' " <<std::endl;
    std::cout << "To show dictionary '-2' " <<std::endl;
    std::cout << "To update base documents '-3' " <<std::endl;

    while(true)
    {
        std::cout << "Enter request" <<std::endl;
        std::getline(std::cin, inputRequest);
        if(inputRequest == "-1")
            break;
        if(inputRequest == "-2") {
            idx.showDict();
            continue;
        }
        if(inputRequest == "-3")
        {
            idx.UpdateDocumentBase(ConverterJson().GetDocsText());
            srv = idx;
            std::cout << "Base updated " <<std::endl;
            continue;
        }

        std::vector<std::vector<RelativeIndex>> resultWhile = srv.search({inputRequest});
        srv.showResults(resultWhile);

    }

    clock_t end = clock();
    double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time: " << duration << " sec" << std::endl;

    return 0;
}

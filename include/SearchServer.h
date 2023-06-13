#pragma once

#include "InvertedIndex.h"

struct RelativeIndex
{
    size_t doc_id; float rank;
    bool operator ==(const RelativeIndex& other) const { return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer
{
public:
    SearchServer() = default;

    SearchServer(InvertedIndex& idx);
    std::vector<std::string> splitString(const std::string& input);
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string> &queries_input);
    void showResults(const std::vector<std::vector<RelativeIndex>>& outRelativity);

private:

    InvertedIndex _index;

};

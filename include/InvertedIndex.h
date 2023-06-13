#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <regex>
#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>
#include <mutex>

struct Entry {
    size_t doc_id;
    size_t count;
    bool operator == (const Entry& other) const
    {
        return (doc_id == other.doc_id) && (count == other.count);
    }
};

class InvertedIndex {

private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freq_dictionary;

    nlohmann::json answers;
    int reqID;

public:

	InvertedIndex() = default;
    std::map<std::string, std::vector<Entry>> get_freq_dictionary();
    std::vector<Entry> GetWordCount(const std::string& word);

    std::vector<std::string> getDocs();
    std::map<std::string, std::vector<Entry>> wordsFind(const std::vector<std::string>& docs);
    void threadProcess(const std::vector<std::string>& docs);
    void UpdateDocumentBase(const std::vector<std::string>& input_docs);

    void showDict();

    std::vector<std::vector<Entry>> getEntry(std::vector<std::string> input);

};

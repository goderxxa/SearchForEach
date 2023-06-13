#include "InvertedIndex.h"

std::vector<std::string> text_docs;     // from converterJson getTextDocs()
std::map<std::string, std::vector<Entry>> freq_dictionary;  //dictionary
std::mutex mtx;    //mutex

std::map<std::string, std::vector<Entry>> InvertedIndex::get_freq_dictionary()
{
    return freq_dictionary;
};
std::vector<std::string> InvertedIndex::getDocs()
{
    return docs;
}

std::vector<std::vector<Entry>> InvertedIndex::getEntry(std::vector<std::string> requests)
{
    std::vector<std::vector<Entry>> out;

    for(auto request : requests)
    {
        auto it = freq_dictionary.find(request);
        if(it != freq_dictionary.end())
        {
            out.push_back(it->second);
        }
        else
        {
            out.push_back(std::vector<Entry>());
        }
    }
    return out;
};

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
    std::vector<Entry> outVec;
    auto it = freq_dictionary.find(word);
    if(it != freq_dictionary.end())
    {
        outVec = it->second;
    }
    else
    {
        outVec = std::vector<Entry>();
    }

    return outVec;
}

void InvertedIndex::UpdateDocumentBase (const std::vector<std::string>& inputTextDocs)
{
    text_docs.clear();
    freq_dictionary.clear();
    for(auto doc : inputTextDocs)
    {
        text_docs.push_back(doc);
    }
    threadProcess(text_docs); // using with
//    wordsFind(docs);             // using without
}


void processDoc(const std::string& doc, std::map<std::string, std::vector<Entry>>& freq_dictionary, int docid) {
    std::string word;
    for (const char& c : doc) {
        if (std::isalpha(c))
        {
            word += std::tolower(c);
        }
        else
        {
            if (!word.empty()) {
                std::lock_guard<std::mutex> lock(mtx);
                auto& entries = freq_dictionary[word];
                auto it = std::find_if(entries.begin(), entries.end(), [docid](const Entry& entry) {
                    return entry.doc_id == docid;
                });
                if (it != entries.end()) {
                    // if doc_id, find  ++count
                    it->count++;
                } else {
                    // insert new end because of sorting
                    entries.insert(entries.end(), { static_cast<size_t>(docid), 1 });
                }
                word.clear();
            }
        }
    }
    if (!word.empty()) {
        std::lock_guard<std::mutex> lock(mtx);
        auto& entries = freq_dictionary[word];
        auto it = std::find_if(entries.begin(), entries.end(), [docid](const Entry& entry) {
            return entry.doc_id == docid;   //lambda for finding docid
        });
        if (it != entries.end())
        {
            it->count++;
        } else
        {
            entries.insert(entries.end(), { static_cast<size_t>(docid), 1 });
        }
    }
}

void InvertedIndex::threadProcess(const std::vector<std::string>& text_docs)
{
    freq_dictionary.clear();
    std::vector<std::thread> threads;
    int docid = 0;

    for (const auto& doc : text_docs) {
        threads.emplace_back(processDoc, std::ref(doc), std::ref(freq_dictionary), docid); //making refs
        docid++; // current doc for thread
    }

    for (auto& thread : threads) {
        thread.join();  // end of loop
    }
}

//add to dictionary without threads
std::map<std::string, std::vector<Entry>> InvertedIndex::wordsFind(const std::vector<std::string>& text_docs)
{
    std::map<std::string, std::vector<Entry>> total;
    int id_doc = 0;

    for (const auto& content : docs)
    {
        std::string line = content;

        std::lock_guard<std::mutex> lock(mtx); // mutex lock

        std::smatch match;
        std::regex wordRegex("\\b[a-zA-Z0-9']+[a-zA-Z0-9]?\\b");
        // regular expression to find word find words like (it's, I'm)

        while (std::regex_search(line, match, wordRegex)) {
            std::string word = match.str();

            // to lower registry
            for (char &c: word) {
                c = tolower(c);
            }

            if (!total[word].empty() && total[word].back().doc_id == id_doc) {
                // if last element in vector has same doc_id, ++count
                total[word].back().count++;
            } else {
                // add new item to vector
                total[word].push_back({static_cast<size_t>(id_doc), 1});
            }
            line = match.suffix();

        }
        id_doc++;
    }
    freq_dictionary = total;
    showDict();
    return total;
}

void processDoc1(const std::string& doc, std::map<std::string, std::vector<Entry>>& freq_dictionary, int docid) {

    std::string line = doc;

    std::smatch match;
    std::regex wordRegex("\\b[a-zA-Z0-9']+[a-zA-Z0-9]?\\b");

    while (std::regex_search(line, match, wordRegex)) {
        std::string word = match.str();

        for (char &c: word) {
            c = tolower(c);
        }

        if (!freq_dictionary[word].empty() && freq_dictionary[word].back().doc_id == docid)         {
            std::lock_guard<std::mutex> lock(mtx); // mutex lock
            // if last element in vector has same doc_id, ++count
            freq_dictionary[word].back().count++;
        }
        else
        {
            std::lock_guard<std::mutex> lock(mtx); // mutex lock
            // add new item to vector
            freq_dictionary[word].push_back({static_cast<size_t>(docid), 1});
        }
        line = match.suffix();
    }
}


void InvertedIndex::showDict()
{
    for(auto word : freq_dictionary)
    {
        std::cout <<word.first << std::endl;
        for(auto par : word.second)
        {
            std::cout << "\t count: " << par.count << " | id: " << par.doc_id << std::endl;
        }
    }
}





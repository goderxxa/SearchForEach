#include "SearchServer.h"
#include "ConverterJson.h"

std::vector<std::vector<RelativeIndex>> outRelativity;
nlohmann::json answers;
int reqID;

SearchServer::SearchServer(InvertedIndex& idx)
{
     _index = idx;
};

std::vector<std::string> SearchServer::splitString(const std::string& input) {

    std::regex regex("[^\\w']+");   //regex to split words
    std::vector<std::string> words;
    std::sregex_token_iterator iter(input.begin(), input.end(), regex, -1);
    std::sregex_token_iterator end;
    while (iter != end) {
        words.push_back(*iter);
        ++iter;
    }
    return words;
}

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input)
{
    std::vector<std::vector<RelativeIndex>> output;
    std::map<std::string, std::vector<Entry>> result = _index.get_freq_dictionary();
    std::ofstream out_answers("answers.json");
    answers.clear();    //json dump

    reqID=0;
    for(auto req : queries_input)   // req - request consist of some words
    {
        ++reqID;

        std::vector<std::string> split_requests = splitString(req); // split request to requests
        std::cout << req << std::endl;

            // calculate reqID and Count in file
        std::map<std::string, std::vector<Entry>> wordDocidCount;  // name request and files id's counts

        int match=0;
        for(const auto &request: split_requests)
        {
            auto it = result.find(request); // find request in freq_dictionary
            if(it != result.end())
            {
                ++match;
                wordDocidCount[request] = result[request];  // equal from freq_dict to out new req
            }
        }
        if(match==0)
        {
            answers["answers"]["request"+std::to_string(reqID)]["result"] = false;
            output.push_back({});
            continue;
        }
        else
            answers["answers"]["request"+std::to_string(reqID)]["result"] = true;

        std::map<int,int> totalRel;     // sum of create total docid and count of all files

        for(auto key : wordDocidCount)
        {
            if(totalRel.empty())    // if empty create a new vector of Entries
            {
                for (auto vec : key.second) //vector
                {
                    totalRel[vec.doc_id] = vec.count;
                }
            }
            else
            {
                for (auto vec : key.second) //vector
                {
                    if (totalRel.find(vec.doc_id) != totalRel.end())
                    {
                        totalRel[vec.doc_id] += vec.count;  // add if not empty
                    }
                    else
                        totalRel[vec.doc_id] = vec.count;
                }
            }
        }

//    convert output
        std::multimap<int,int> sorted;

        for(auto it = totalRel.rbegin(); it != totalRel.rend(); ++it)
        {
            sorted.insert(std::make_pair(it->second,it->first));
        }

        auto first = sorted.rbegin();
        std::vector<RelativeIndex> outRelative;
        int TOP = (ConverterJson().GetResponsesLimit());
        for(auto it = sorted.rbegin(); it !=sorted.rend(); ++it )
        {
            TOP--;
            RelativeIndex relativeIndex;
            relativeIndex.doc_id = it->second;
            relativeIndex.rank = it->first/ (float) first->first;

//            answers["answers"]["request" + std::to_string(reqID)] ["id_" + std::to_string(relativeIndex.doc_id)] = relativeIndex.rank;

//            std::cout <<   "Doc_ID: " << relativeIndex.doc_id << " Rank: " <<  relativeIndex.rank <<std::endl;
            outRelative.push_back(relativeIndex);

            if(TOP==0)
                break;
        }
        output.push_back(outRelative);
    }
    out_answers << answers.dump(4);
    out_answers.close();
    return output;
}

void SearchServer::showResults(const std::vector<std::vector<RelativeIndex>>& outRelativity)
{
    std::ofstream out_answers("answers.json");

    int id =0;
    for (const auto first : outRelativity)
    {
        ++id;
        std::cout << "Request"+ std::to_string(id) << std::endl;

        for(const auto second : first)
        {
            answers["answers"]["request" + std::to_string(id)] ["id_" + std::to_string(second.doc_id)] = second.rank;
            std::cout << "\t docId: " << second.doc_id << " rank: " << second.rank <<std::endl;
        }
    }
    out_answers << answers.dump(4);
    out_answers.close();
}
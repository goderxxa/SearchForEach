#include "ConverterJson.h"
#include "gtest/gtest.h"

TEST(ConverterJSON, readConfig) {       // exeption

}

TEST(ConverterJSON, readRequests) {     // exeption
    ConverterJson a;

    std::vector<std::string> vecReq = a.GetRequests();
    std::vector<std::string> expectedVecReq = {"milk", "water", "cappuchino"};

    ASSERT_EQ(vecReq, expectedVecReq);
}

TEST(ConverterJSON, getResponsesLimit) {
    ConverterJson a;

    int curResponses = a.GetResponsesLimit();
    int expected = 5;

    ASSERT_EQ(curResponses, expected);
}

TEST(ConverterJSON, getRequests) {
    ConverterJson a;

    std::vector<std::string> vecReq = a.GetRequests();
    std::vector<std::string> expected = {"milk", "water", "cappuchino"};

    ASSERT_EQ(vecReq, expected);
}

TEST(ConverterJSON, getTextDocs) {
    const std::vector<std::string> expected = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuchino"
    };
    ConverterJson a;

    std::vector<std::string> vecTxt = a.GetDocsText();
    ASSERT_EQ(vecTxt, expected);
}


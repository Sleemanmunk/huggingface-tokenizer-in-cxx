#ifndef BPEENCODER_H
#define BPEENCODER_H

#include <string>
#include <unordered_map>
#include <istream>
#include <vector>
#include <set>
#include "re2/re2.h"
#include "bpe.h"

const std::string BASE_RE = "('s|'t|'re|'ve|'m|'ll|'d| ?\\p{L}+| ?\\p{N}+| "
    "?[^\\s\\p{L}\\p{N}]+|\\s+\\(?!\\S\\)|\\s+)";

class GPT2Tokenizer
{

public:
    GPT2Tokenizer(std::string merge_rules, std::string vocab);
    std::vector<int> encode_text(const std::string &str);
    std::vector<std::string> tokenize_text(const std::string &str);
    std::string decode_text(const std::vector<int> &ids);

private:
    BPERanks bpe_ranks;
    std::unordered_map<uint8_t, wchar_t> b2u;
    std::unordered_map<wchar_t, uint8_t> u2b;    
    std::unordered_map<std::string, int> t2i;
    std::unordered_map<int, std::string> i2t;
    RE2 re{BASE_RE};
};

#endif

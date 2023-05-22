#include "tokenizer.h"
#include <stdexcept>
#include <memory>

GPT2Tokenizer::GPT2Tokenizer(std::string merge_rules, std::string vocab)
{
    BPERanks bpe_ranks;
    std::fstream merges(merge_rules, std::ios::in);
    load_merge_rules(merges, &bpe_ranks);

    std::unordered_map<uint8_t, wchar_t> b2u;
    std::unordered_map<wchar_t, uint8_t> u2b;
    bytes_to_unicode(&b2u, &u2b);

    std::unordered_map<std::string, int> t2i;
    std::unordered_map<int, std::string> i2t;
    std::fstream vocab_txt(vocab, std::ios::in);
    load_vocab(vocab_txt, &t2i, &i2t);
}

std::vector<int> GPT2Tokenizer::encode_text(const std::string &str)
{
    std::vector<int> ids;
    encode(str, re, bpe_ranks, b2u, t2i, &ids);
    return ids;
}

std::vector<std::string> GPT2Tokenizer::tokenize_text(const std::string &str)
{
    std::vector<std::string> result;
    tokenize(str, re, bpe_ranks, b2u, &result);
    return result;
}

std::string GPT2Tokenizer::decode_text(const std::vector<int> &ids)
{
    return decode(ids, u2b, i2t);
}

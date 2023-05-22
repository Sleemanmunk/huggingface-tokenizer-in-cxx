#include "tokenizer.h"
#include <stdexcept>
#include <memory>
#include <cassert>

GPT2Tokenizer::GPT2Tokenizer(std::string merge_rules, std::string vocab)
{
    std::fstream merges(merge_rules, std::ios::in);
    assert (merges.good());
    load_merge_rules(merges, &bpe_ranks);

    bytes_to_unicode(&b2u, &u2b);

    std::fstream vocab_txt(vocab, std::ios::in);
    assert (vocab_txt.good());
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

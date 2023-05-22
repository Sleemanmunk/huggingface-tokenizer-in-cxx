#include "bpe.h"
#include "tokenizer.h"
#include <cassert>
#include <iostream>

using namespace std;

string RESOURCES = "tokenizer/assets/";

auto _print_string_vec = [](std::vector<std::string> &v)
{
  // To be compatible with Python's print(*lst, sep=', ')
  for (int i = 0; i < v.size(); ++i)
  {
    std::cout << v[i];
    if (i < v.size() - 1)
      std::cout << ", ";
  }
  std::cout << std::endl;
};

void test_tokenize()
{
  GPT2Tokenizer tokenizer{RESOURCES + "merges.txt", RESOURCES + "vocab.txt"};
  std::vector<std::string> candidates = {
      "this is <|endoftext|> else<|endoftext|>",
      "<|endoftext|> else<|endoftext|>", "this is <|endoftext|> else",
      "this is <|endoftext|>else", "this is else"};
  for (auto s : candidates)
  {
    std::vector<std::string> result;
    result = tokenizer.tokenize_text(s);
    _print_string_vec(result);
  }
}

void test_encode_decode()
{

  GPT2Tokenizer tokenizer{RESOURCES + "merges.txt", RESOURCES + "vocab.txt"};

  std::vector<std::string> candidates = {
      "this is <|endoftext|> else<|endoftext|>",
      "<|endoftext|> else<|endoftext|>", "this is <|endoftext|> else",
      "this is <|endoftext|>else", "this is else"};
  for (auto s : candidates)
  {
    auto ids = tokenizer.encode_text(s);
    assert(ids.size() > 0);
    assert(tokenizer.decode_text(ids) == s);
  }
}

int main()
{
  test_tokenize();
  test_encode_decode();
  return 0;
}

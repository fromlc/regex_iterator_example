//----------------------------------------------------------------------
// regex.cpp
// 
// Author: https://en.cppreference.com/w/cpp/regex
//----------------------------------------------------------------------
#include <iostream>
#include <iterator>
#include <regex>
#include <string>

//----------------------------------------------------------------------
// entry point
//----------------------------------------------------------------------
int main()
{
    // s is the haystack
    std::string s = "Some people, when confronted with a problem, think "
        "\"I know, I'll use regular expressions.\" "
        "Now they have two problems.";

    //------------------------------------------------------------------
    // set the search pattern (needle) and search options: 
    // use regex flavor ECMAscript, don't match case
    // and search for "REGULAR EXPRESSIONS" in string s
    //------------------------------------------------------------------
    std::regex self_regex("REGULAR EXPRESSIONS",
        std::regex_constants::ECMAScript | std::regex_constants::icase);

    // find the needle in the haystack
    if (std::regex_search(s, self_regex)) {
        std::cout << "Text contains the phrase 'regular expressions'\n";
    }

    //------------------------------------------------------------------
    // set a new needle with default options
    // and search for whole words in string s.
    // a word is a sequence of one or more word characters.
    //------------------------------------------------------------------
    std::regex word_regex("(\\w+)");
    
    //------------------------------------------------------------------
    // searches the entire string s, keep the sequence of matches,
    // and create an iterator that references the first match 
    //------------------------------------------------------------------
    auto words_begin =
        std::sregex_iterator(s.begin(), s.end(), word_regex);
    
    //------------------------------------------------------------------
    // create a default iterator that references end-of-sequence
    //------------------------------------------------------------------
    auto words_end = std::sregex_iterator();

    // the distance between the iterators is the number of matches found
    std::cout << "Found "
        << std::distance(words_begin, words_end)
        << " words\n";

    //------------------------------------------------------------------
    // search s for words with more than N characters
    //------------------------------------------------------------------
    const int N = 6;
    std::cout << "Words longer than " << N << " characters:\n";

    //------------------------------------------------------------------
    // use the previously created iterators to access the saved 
    // sequence of matches and limit the for loop
    //------------------------------------------------------------------
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();

        // screen out words with N or less characters
        if (match_str.size() > N) {
            std::cout << "  " << match_str << '\n';
        }
    }

    //------------------------------------------------------------------
    // this time replace words at least 7 characters long with
    // the same word in [].
    // for instance, characters -> [character].
    // the string new_s will be s with the replacements made.
    //------------------------------------------------------------------
    std::regex long_word_regex("(\\w{7,})");
    std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
    std::cout << new_s << '\n';

    return 0;
}
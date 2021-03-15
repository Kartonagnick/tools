
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_TOKENIZER

#include <tools/features.hpp>
#ifndef dHAS_AGGREGATE_INITIALIZE
    dMESSAGE("[test] tools: disabled -> dHAS_AGGREGATE_INITIALIZE")
#else

#define dTEST_COMPONENT tools, algorithm
#define dTEST_METHOD tokenizer
#define dTEST_TAG new_list_ansi

#include <tools/algorithm/tokenizer.hpp>
#include <cstring>
#include <string>
#include <list>

namespace me = ::tools;
//================================================================================
//================================================================================
namespace 
{
    typedef ::std::string str_t;

} //namespace

//================================================================================
//================================================================================

TEST_COMPONENT(000)
{
    // простейший (и самый частый) случай

    const str_t sepparators = ",;.!: ";

    const str_t text 
        = "aaabbb! cccddd, fffggg, hhhjjj; yyyuuu : oooppp";

    std::list<str_t> words;
    std::list<char> puncts;

    const auto call_words = [&words](const char* p, size_t len)
        { words.emplace_back(p, len); };

    const auto call_punct = [&puncts](const char ch)
        { if(ch!=' ') puncts.emplace_back(ch); };

    const std::list<str_t> 
        etalon_w = { "aaabbb", "cccddd", "fffggg", "hhhjjj", "yyyuuu", "oooppp" };

    const std::list<char>
        etalon_p = { '!', ',', ',', ';', ':' };

    me::tokenize(
        text.cbegin(), 
        text.cend(), 
        sepparators.cbegin(), 
        sepparators.cend(), 
        call_words, 
        call_punct, 
        true
    );

    ASSERT_TRUE(words  == etalon_w);
    ASSERT_TRUE(puncts == etalon_p);
}
TEST_COMPONENT(001)
{
    const char sepparators[] = ",;.!: ";

    const char* text 
        = "aaabbb! cccddd, fffggg, hhhjjj; yyyuuu : : oooppp, ";

    std::list<str_t> words;
    std::list<char> puncts;

    const auto call_words = [&words](const char* p, size_t len)
        { words.emplace_back(p, len); };

    const auto call_puncts = [&puncts](const char ch)
        { if(ch!=' ') puncts.emplace_back(ch); };

    const std::list<str_t> 
        etalon_w = { "aaabbb", "cccddd", "fffggg", "hhhjjj", "yyyuuu", "oooppp" };

    const std::list<char>
        etalon_p = { '!', ',', ',', ';', ':', ':', ',' };

    me::tokenize(
        text, 
        text + std::strlen(text), 
        std::begin(sepparators), 
        std::end(sepparators), 
        call_words, 
        call_puncts, 
        true
    );

    ASSERT_TRUE( words  == etalon_w );
    ASSERT_TRUE( puncts == etalon_p );
}
TEST_COMPONENT(002)
{
    // trim_empty = false
    // в этом режиме,
    // если между двумя символами разделителями ничего нет
    // то считается, что между ними токен 'пустышка'
    // он добавляется в список в виде токена нулевой длины

    const char* sepparators = ",;.!: ";

    const str_t text 
        = "aaabbb! cccddd, fffggg, hhhjjj;,, yyyuuu : oooppp, ";

    std::list<str_t> words;
    std::list<char> puncts;

    const auto call_words = [&words](const char* p, size_t len)
        { words.emplace_back(p, len); };

    const auto call_punct = [&puncts](const char ch)
        { if(ch!=' ') puncts.emplace_back(ch); };

    const std::list<str_t> etalon_w = 
    { 
        "aaabbb", "", "cccddd", ""      , "fffggg", "", "hhhjjj", 
        ""      , "", ""      , "yyyuuu", ""      , "", "oooppp",
        "" 
    };

    const std::list<char>
        etalon_p = { '!', ',', ',', ';', ',', ',', ':', ',' };

    me::tokenize(
        text.cbegin(), 
        text.cend(), 
        sepparators, 
        sepparators + ::std::strlen(sepparators), 
        call_words, 
        call_punct,
        false
    );

    ASSERT_TRUE(words  == etalon_w);
    ASSERT_TRUE(puncts == etalon_p);
}
TEST_COMPONENT(003)
{
    // trim_empty = false
    // в этом режиме,
    // если между двумя символами разделителями ничего нет
    // то считается, что между ними токен 'пустышка'
    // он добавляется в список в виде токена нулевой длины

    const char* sepparators = ",;.!: ";

    const str_t text 
        = "aaabbb! cccddd, fffggg, hhhjjj;,, yyyuuu : : oooppp,, ";

    std::list<str_t> words;
    std::list<char> puncts;

    const auto call_words = [&words](const char* p, size_t len)
        { words.emplace_back(p, len); };

    const auto call_punct = [&puncts](const char ch)
        { if(ch!=' ') puncts.emplace_back(ch); };

    const std::list<str_t> etalon_w = 
    { 
        "aaabbb", ""      , "cccddd", ""      , "fffggg", "", "hhhjjj", 
        ""      , ""      , ""      , "yyyuuu", ""      , "", "",
        ""      , "oooppp", ""      , ""
    };

    const std::list<char>
        etalon_p = { '!', ',', ',', ';', ',', ',', ':', ':', ',', ',' };

    me::tokenize(
        text.cbegin(), 
        text.cend(), 
        sepparators, 
        sepparators + ::std::strlen(sepparators), 
        call_words, 
        call_punct,
        false
    );

    ASSERT_TRUE(words  == etalon_w);
    ASSERT_TRUE(puncts == etalon_p);
}

// --- invalid nullptr
TEST_COMPONENT(004)
{
    const char* nill = nullptr;
    const char* b = "";
    const char* e = "";

    const char sep[] = ",;.!: ";

    const auto words  = [](const char*, size_t){};
    const auto puncts = [](const char){};

    (void) nill;
    (void) b;
    (void) e;
    (void) sep;
    (void) words;
    (void) puncts;

    ASSERT_DEATH_DEBUG(
        me::tokenize(
            nill, e, 
            std::begin(sep), 
            std::end(sep), 
            words,
            puncts, 
            true
        )
    );
    ASSERT_DEATH_DEBUG(
        me::tokenize(
            b, nill, 
            std::begin(sep), 
            std::end(sep), 
            words,
            puncts,
            false
        )
    );
    ASSERT_DEATH_DEBUG(
        me::tokenize(
            nill, nill, 
            std::begin(sep), 
            std::end(sep), 
            words,
            puncts,
            false
        )
    );
}
TEST_COMPONENT(005)
{
    const char* nill = nullptr;
    const str_t text = "text";
    const char sep[] = ",;.!: ";

    const auto words  = [](const char*, size_t){};
    const auto puncts = [](const char){};

    (void) nill;
    (void) text;
    (void) sep;
    (void) words;
    (void) puncts;

    ASSERT_DEATH_DEBUG(
        me::tokenize(
            text.cbegin(),
            text.cend(), 
            nill, 
            std::end(sep), 
            words,
            puncts, 
            true
        )
    );
    ASSERT_DEATH_DEBUG(
        me::tokenize(
            text.cbegin(),
            text.cend(), 
            std::begin(sep),
            nill, 
            words,
            puncts, 
            true
        )
    );
    ASSERT_DEATH_DEBUG(
        me::tokenize(
            text.cbegin(),
            text.cend(), 
            nill,
            nill, 
            words,
            puncts, 
            true
        )
    );
}

// --- stress
TEST_COMPONENT(006)
{
    const str_t sep  = ",;.!: ";
    const str_t text = "";

    std::list<str_t> words;
    std::list<char> puncts;

    const auto call_words = [&words](const char* p, size_t len)
        { words.emplace_back(p, len); };

    const auto call_punct = [&puncts](const char ch)
        { if(ch!=' ') puncts.emplace_back(ch); };

    me::tokenize(
        text.cbegin(), 
        text.cend(), 
        sep.cbegin(), 
        sep.cend(), 
        call_words, 
        call_punct
    );

    ASSERT_TRUE(words.empty());
    ASSERT_TRUE(puncts.empty());
}
TEST_COMPONENT(007)
{
    const str_t sep  = ",;.!: ";
    const str_t text = ";;";

    std::list<str_t> words;
    std::list<char> puncts;

    const auto call_words = [&words](const char* p, size_t len)
        { words.emplace_back(p, len); };

    const auto call_punct = [&puncts](const char ch)
        { if(ch!=' ') puncts.emplace_back(ch); };

    const std::list<char> etalon_p = { ';', ';' };

    me::tokenize(
        text.cbegin(), 
        text.cend(), 
        sep.cbegin(), 
        sep.cend(), 
        call_words, 
        call_punct
    );

    ASSERT_TRUE(words.empty());
    ASSERT_TRUE(puncts == etalon_p);
}
TEST_COMPONENT(008)
{
    const str_t sep  = ",;.!: ";
    const str_t text = "; ;";

    std::list<str_t> words;
    std::list<char> puncts;

    const auto call_words = [&words](const char* p, size_t len)
        { words.emplace_back(p, len); };

    const auto call_punct = [&puncts](const char ch)
        { if(ch!=' ') puncts.emplace_back(ch); };

    const std::list<str_t> etalon_w = { "", "", "" };
    const std::list<char>  etalon_p = { ';', ';'   };

    me::tokenize(
        text.cbegin(), 
        text.cend(), 
        sep.cbegin(), 
        sep.cend(), 
        call_words, 
        call_punct,
        false
    );

    ASSERT_TRUE(words  == etalon_w);
    ASSERT_TRUE(puncts == etalon_p);
}

//================================================================================
//================================================================================
#endif // !dHAS_AGGREGATE_INITIALIZE
#endif // !TEST_TOOLS_TOKENIZER




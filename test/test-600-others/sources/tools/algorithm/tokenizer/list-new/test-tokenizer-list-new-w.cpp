
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
#define dTEST_TAG new_list_wide

#include <tools/algorithm/tokenizer.hpp>
#include <string>
#include <list>

namespace me = ::tools;
//================================================================================
//================================================================================
namespace 
{
    typedef ::std::wstring str_w;

} //namespace
//================================================================================
//================================================================================

TEST_COMPONENT(000)
{
    // простейший (и самый частый) случай

    const str_w sepparators = L",;.!: ";

    const str_w text 
        = L"aaabbb! cccddd, fffggg, hhhjjj; yyyuuu : oooppp";

    std::list<str_w> words;
    std::list<wchar_t> puncts;

    const auto call_words = [&words](const wchar_t* p, size_t len)
        { words.emplace_back(p, len); };

    const auto call_punct = [&puncts](const wchar_t ch)
        { if(ch != L' ') puncts.emplace_back(ch); };

    const std::list<str_w> 
        etalon_w = { L"aaabbb", L"cccddd", L"fffggg", L"hhhjjj", L"yyyuuu", L"oooppp" };

    const std::list<wchar_t>
        etalon_p = { L'!', L',', L',', L';', L':' };

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
    const wchar_t sepparators[] = L",;.!: ";

    const wchar_t* text 
        = L"aaabbb! cccddd, fffggg, hhhjjj; yyyuuu : : oooppp, ";

    std::list<str_w> words;
    std::list<wchar_t> puncts;

    const auto call_words = [&words](const wchar_t* p, size_t len)
        { words.emplace_back(p, len); };

    const auto call_puncts = [&puncts](const wchar_t ch)
        { if(ch != L' ') puncts.emplace_back(ch); };

    const std::list<str_w> 
        etalon_w = { L"aaabbb", L"cccddd", L"fffggg", L"hhhjjj", L"yyyuuu", L"oooppp" };

    const std::list<wchar_t>
        etalon_p = { L'!', L',', L',', L';', L':', L':', L',' };

    me::tokenize(
        text, 
        text + std::wcslen(text), 
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

    const wchar_t* sepparators = L",;.!: ";

    const str_w text 
        = L"aaabbb! cccddd, fffggg, hhhjjj;,, yyyuuu : oooppp, ";

    std::list<str_w> words;
    std::list<wchar_t> puncts;

    const auto call_words = [&words](const wchar_t* p, size_t len)
        { words.emplace_back(p, len); };

    const auto call_punct = [&puncts](const wchar_t ch)
        { if(ch != L' ') puncts.emplace_back(ch); };

    const std::list<str_w> etalon_w = 
    { 
        L"aaabbb", L"", L"cccddd", L""      , L"fffggg", L"", L"hhhjjj", 
        L""      , L"", L""      , L"yyyuuu", L""      , L"", L"oooppp",
        L"" 
    };

    const std::list<wchar_t>
        etalon_p = { L'!', L',', L',', L';', L',', L',', L':', L',' };

    me::tokenize(
        text.cbegin(), 
        text.cend(), 
        sepparators, 
        sepparators + ::std::wcslen(sepparators), 
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

    const wchar_t* sepparators = L",;.!: ";

    const str_w text 
        = L"aaabbb! cccddd, fffggg, hhhjjj;,, yyyuuu : : oooppp,, ";

    std::list<str_w> words;
    std::list<wchar_t> puncts;

    const auto call_words = [&words](const wchar_t* p, size_t len)
        { words.emplace_back(p, len); };

    const auto call_punct = [&puncts](const wchar_t ch)
        { if(ch != L' ') puncts.emplace_back(ch); };

    const std::list<str_w> etalon_w = 
    { 
        L"aaabbb", L""      , L"cccddd", L""      , L"fffggg", L"", L"hhhjjj", 
        L""      , L""      , L""      , L"yyyuuu", L""      , L"", L"",
        L""      , L"oooppp", L""      , L""
    };

    const std::list<wchar_t>
        etalon_p = { L'!', L',', L',', L';', L',', L',', L':', L':', L',', L',' };

    me::tokenize(
        text.cbegin(), 
        text.cend(), 
        sepparators, 
        sepparators + ::std::wcslen(sepparators), 
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
    const wchar_t* nill = nullptr;
    const wchar_t* b = L"";
    const wchar_t* e = L"";

    const wchar_t sep[] = L",;.!: ";

    const auto words  = [](const wchar_t*, size_t){};
    const auto puncts = [](const wchar_t){};

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
    const wchar_t* nill = nullptr;
    const str_w text = L"text";
    const wchar_t sep[] = L",;.!: ";

    const auto words  = [](const wchar_t*, size_t){};
    const auto puncts = [](const wchar_t){};

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
    const str_w sep  = L",;.!: ";
    const str_w text = L"";

    std::list<str_w> words;
    std::list<wchar_t> puncts;

    const auto call_words = [&words](const wchar_t* p, size_t len)
        { words.emplace_back(p, len); };

    const auto call_punct = [&puncts](const wchar_t ch)
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
    const str_w sep  = L",;.!: ";
    const str_w text = L";;";

    std::list<str_w> words;
    std::list<wchar_t> puncts;

    const auto call_words = [&words](const wchar_t* p, size_t len)
        { words.emplace_back(p, len); };

    const auto call_punct = [&puncts](const wchar_t ch)
        { if(ch!=' ') puncts.emplace_back(ch); };

    const std::list<wchar_t> etalon_p = { L';', L';' };

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
    const str_w sep  = L",;.!: ";
    const str_w text = L"; ;";

    std::list<str_w> words;
    std::list<wchar_t> puncts;

    const auto call_words = [&words](const wchar_t* p, size_t len)
        { words.emplace_back(p, len); };

    const auto call_punct = [&puncts](const wchar_t ch)
        { if(ch != L' ') puncts.emplace_back(ch); };

    const std::list<str_w> etalon_w = { L"", L"", L"" };
    const std::list<wchar_t>  etalon_p = { L';', L';'    };

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




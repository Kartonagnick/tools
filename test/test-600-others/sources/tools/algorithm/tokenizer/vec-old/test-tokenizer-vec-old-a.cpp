// [2019y-10m-24d][19:22:08] Idrisov Denis R.
// [2021y-03m-15d][18:52:06] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_TOKENIZER

#define dTEST_COMPONENT tools, algorithm
#define dTEST_METHOD tokenizer
#define dTEST_TAG old_vec_ansi

#include <tools/algorithm/tokenizer.hpp>
#include <cstring>
#include <cassert>
#include <string>
#include <vector>

namespace me = ::tools;
//================================================================================
//================================================================================
namespace 
{
    typedef ::std::string str_t;

    #define dCOUNT(arr) sizeof(arr)/sizeof(arr[0])

    template<class cont>
    void insert(cont& dst, const char* p, size_t len)
    {
        #ifdef dHAS_EMPLACE
            dst.emplace_back(p, len); 
        #else
            dst.push_back(str_t(p, len)); 
        #endif
    }

    template<class cont>
    void insert(cont& dst, const char ch)
    {
        #ifdef dHAS_EMPLACE
            if(ch != ' ') 
                dst.emplace_back(ch);
        #else
            if(ch != ' ') 
                dst.push_back(ch);
        #endif
    }


    struct functor
    {
        functor() dNOEXCEPT
            : words()
            , puncts()
            , etalon_w()
            , etalon_p()
        {}

        void operator()(const char* p, size_t len)
            { insert(this->words, p, len); }

        void operator()(const char ch)
            { insert(this->puncts, ch); }

        template<class t, size_t n>
        void init(const t* (&src_words)[n])
        {
            assert(src_words);
            for (size_t i = 0; i != n; ++i)
            {
                assert(src_words[i]);
                this->etalon_w.push_back(src_words[i]);
            }
        }
        template<class ch, size_t n> 
        void init(const ch (&src_puncts)[n])
        {
            for (size_t i = 0; i != n; ++i)
                this->etalon_p.push_back(src_puncts[i]);
        }

        void check() const
        {
            ASSERT_TRUE(words == etalon_w);
            ASSERT_TRUE(puncts == etalon_p);
        }

        std::vector<str_t> words;
        std::vector<char> puncts;

        std::vector<str_t> etalon_w;
        std::vector<char>  etalon_p;
    };

} //namespace

//================================================================================
//================================================================================

TEST_COMPONENT(000)
{
    // простейший (и самый частый) случай

    const str_t sepparators = ",;.!: ";

    const str_t text
        = "aaabbb! cccddd, fffggg, hhhjjj; yyyuuu : oooppp";

    const char* etalon_w[]
        = { "aaabbb", "cccddd", "fffggg", "hhhjjj", "yyyuuu", "oooppp" };

    const char etalon_p[] = { '!', ',', ',', ';', ':' };

    functor func;
    func.init(etalon_w);
    func.init(etalon_p);

    me::tokenize(
        text.begin(),
        text.end(),
        sepparators.begin(),
        sepparators.end(),
        func,
        func,
        true
    );
    func.check();
}

TEST_COMPONENT(001)
{
    const char sepparators[] = ",;.!: ";

    const char* text 
        = "aaabbb! cccddd, fffggg, hhhjjj; yyyuuu : : oooppp, ";

    const char* etalon_w[]
        = { "aaabbb", "cccddd", "fffggg", "hhhjjj", "yyyuuu", "oooppp" };

    const char etalon_p[] 
        = { '!', ',', ',', ';', ':', ':', ',' };

    functor func;
    func.init(etalon_w);
    func.init(etalon_p);

    me::tokenize(
        text, 
        text + std::strlen(text), 
        sepparators, 
        sepparators + dCOUNT(sepparators), 
        func, 
        func, 
        true
    );
    func.check();
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

    const char* etalon_w[] = 
    { 
        "aaabbb", "", "cccddd", ""      , "fffggg", "", "hhhjjj", 
        ""      , "", ""      , "yyyuuu", ""      , "", "oooppp",
        "" 
    };

    const char etalon_p[] 
        = { '!', ',', ',', ';', ',', ',', ':', ',' };

    functor func;
    func.init(etalon_w);
    func.init(etalon_p);

    me::tokenize(
        text.begin(), 
        text.end(), 
        sepparators, 
        sepparators + ::std::strlen(sepparators), 
        func, func, false
    );

    func.check();
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


    const char* etalon_w[] = 
    { 
        "aaabbb", ""      , "cccddd", ""      , "fffggg", "", "hhhjjj", 
        ""      , ""      , ""      , "yyyuuu", ""      , "", "",
        ""      , "oooppp", ""      , ""
    };

    const char etalon_p[] 
        = { '!', ',', ',', ';', ',', ',', ':', ':', ',', ',' };

    functor func;
    func.init(etalon_w);
    func.init(etalon_p);

    me::tokenize(
        text.begin(), 
        text.end(), 
        sepparators, 
        sepparators + ::std::strlen(sepparators), 
        func, func, false
    );
    func.check();
}

// --- invalid nullptr
TEST_COMPONENT(004)
{
    const char* nill = 0;
    const char* b = "";
    const char* e = "";

    const char sep[] = ",;.!: ";

    functor func;

    (void) nill;
    (void) b;
    (void) e;
    (void) sep;
    (void) func;

    ASSERT_DEATH_DEBUG(
        me::tokenize(
            nill, e, 
            sep, sep + dCOUNT(sep), 
            func, func, true
        )
    );
    ASSERT_DEATH_DEBUG(
        me::tokenize(
            b, nill, 
            sep, sep + dCOUNT(sep), 
            func, func, false
        )
    );
    ASSERT_DEATH_DEBUG(
        me::tokenize(
            nill, nill, 
            sep, sep + dCOUNT(sep), 
            func, func, false
        )
    );
}
TEST_COMPONENT(005)
{
    const char* nill = 0;
    const str_t text = "text";
    const char sep[] = ",;.!: ";

    functor func;

    (void) nill;
    (void) text;
    (void) sep;
    (void) func;

    ASSERT_DEATH_DEBUG(
        me::tokenize(
            text.begin(), text.end(), 
            nill, sep + dCOUNT(sep), 
            func, func, true
        )
    );
    ASSERT_DEATH_DEBUG(
        me::tokenize(
            text.begin(), text.end(), 
            sep, nill, 
            func, func, true
        )
    );
    ASSERT_DEATH_DEBUG(
        me::tokenize(
            text.begin(), text.end(), 
            nill, nill, func, func, true
        )
    );
}

// --- stress
TEST_COMPONENT(006)
{
    const str_t sep  = ",;.!: ";
    const str_t text = "";

    functor func;

    me::tokenize(
        text.begin(), 
        text.end(), 
        sep.begin(), 
        sep.end(), 
        func, func
    );
    func.check();
}
TEST_COMPONENT(007)
{
    const str_t sep  = ",;.!: ";
    const str_t text = ";;";

    const char etalon_p[] = { ';', ';' };

    functor func;
    func.init(etalon_p);

    me::tokenize(
        text.begin(), 
        text.end(), 
        sep.begin(), 
        sep.end(), 
        func, func
    );
    func.check();
}
TEST_COMPONENT(008)
{
    const str_t sep  = ",;.!: ";
    const str_t text = "; ;";

    const char* etalon_w[] = { "", "", "" };
    const char etalon_p[]  = { ';', ';'   };

    functor func;
    func.init(etalon_w);
    func.init(etalon_p);

    me::tokenize(
        text.begin(), 
        text.end(), 
        sep.begin(), 
        sep.end(), 
        func, func, false
    );
    func.check();
}

//================================================================================
//================================================================================
#endif // !TEST_TOOLS_TOKENIZER




// [2021y-03m-04d][01:31:40] Idrisov Denis R.
#include <mygtest/modern.hpp>
//=================================================================================
//=================================================================================

#ifdef TEST_TOOLS_FEATURE_CHRONO

#define dTEST_COMPONENT tools, features
#define dTEST_METHOD test_HAS_CHRONO
#define dTEST_TAG tdd

#include <tools/features.hpp>


#ifdef dHAS_CHRONO
    dMESSAGE("[test] tools: enabled -> dHAS_CHRONO")
    #include <chrono>

    #include <tools/assert.hpp>
    #include <stdexcept>
    #include <iomanip>
    #include <sstream>
    #include <string>
    #include <chrono>
#else
    dMESSAGE("[test] tools: disabled -> dHAS_CHRONO")
#endif

//==============================================================================
//==============================================================================
namespace
{
    #if dHAS_CHRONO

    namespace STD = ::std::chrono;

    typedef STD::system_clock
        clockT;

    typedef clockT::time_point
        pointT;

    ::std::string serializeTimePoint(
        const pointT& time, 
        const char* format = "[%Y/%m/%d][%H:%M:%S]")
    {
        const ::std::time_t posix = clockT::to_time_t(time);

        #ifdef _MSC_VER

            ::std::tm cur;
            const ::errno_t result = ::localtime_s(&cur, &posix);
            dASSERT(result == 0);
            if (result != 0)
                throw ::std::invalid_argument(
                    "serializeTimePoint"
                );
        #else
            ::std::tm* ptr = ::std::localtime(&posix);
            dASSERT(ptr);
            if (!ptr)
                throw ::std::invalid_argument(
                    "serializeTimePoint"
                );
            const ::std::tm& cur = *ptr;
        #endif

        ::std::stringstream ss;
        ss << ::std::put_time(&cur, format);
        return ss.str();
    }
    
    #endif

}//namespace

#if dHAS_CHRONO
TEST_COMPONENT(000) 
{
    pointT cur = clockT::now();
    const std::string stamp = serializeTimePoint(cur);
    dprint(std::cout << stamp << '\n');
    (void) stamp;
}
#endif // !dHAS_CHRONO

//==============================================================================
//==============================================================================
#endif // ! TEST_TOOLS_FEATURE_CHRONO


    #if 0
    std::chrono::system_clock::time_point string_to_time_point(const std::string &str)
    {
        using namespace std;
        using namespace std::chrono;

        int yyyy, mm, dd, HH, MM, SS, fff;

        char scanf_format[] = "%4d.%2d.%2d-%2d.%2d.%2d.%3d";

        sscanf(str.c_str(), scanf_format, &yyyy, &mm, &dd, &HH, &MM, &SS, &fff);

        tm ttm = tm();
        ttm.tm_year = yyyy - 1900; // Year since 1900
        ttm.tm_mon = mm - 1; // Month since January 
        ttm.tm_mday = dd; // Day of the month [1-31]
        ttm.tm_hour = HH; // Hour of the day [00-23]
        ttm.tm_min = MM;
        ttm.tm_sec = SS;

        time_t ttime_t = mktime(&ttm);

        system_clock::time_point time_point_result = std::chrono::system_clock::from_time_t(ttime_t);

        time_point_result += std::chrono::milliseconds(fff);
        return time_point_result;
    }

    std::string time_point_to_string(std::chrono::system_clock::time_point &tp)
    {
        using namespace std;
        using namespace std::chrono;

        auto ttime_t = system_clock::to_time_t(tp);
        auto tp_sec = system_clock::from_time_t(ttime_t);
        milliseconds ms = duration_cast<milliseconds>(tp - tp_sec);

        std::tm * ttm = localtime(&ttime_t);

        char date_time_format[] = "%Y.%m.%d-%H.%M.%S";

        char time_str[] = "yyyy.mm.dd.HH-MM.SS.fff";

        strftime(time_str, strlen(time_str), date_time_format, ttm);

        string result(time_str);
        result.append(".");
        result.append(to_string(ms.count()));

        return result;
    }
    #endif

// [2019y-10m-24d][19:22:08] Idrisov Denis R.
#include <mygtest/test-list.hpp>
//==============================================================================
//==============================================================================

#ifdef TEST_TOOLS_URL

#define TEST_CASE_NAME tools
#define TEST_NUMBER(n) url_##n

#include <tools/url.hpp>
namespace me  = ::TEST_CASE_NAME;
//==============================================================================
//=== TDD ======================================================================
namespace 
{
    typedef ::std::string 
        str_t;

    const str_t etalon = "[{\"result\":\"ok\"}]";

} //namespace
//==============================================================================

TEST_COMPONENT(000)
{
    // "https://24.hazuco.com/actions_open/crm/monitoring_log_write_ext?key=33FD4E4A3F1499A4EBD938E009638DD9&event_type_id=43&text=%27example";

    const char* url =
        "https://24.hazuco.com/actions_open/crm/monitoring_log_write_ext?key=33FD4E4A3F1499A4EBD938E009638DD9&event_type_id=41&text=master%3D1000025%20investor%3D1000017";

    const str_t re = me::url(url);
    dprint(std::cout << re << '\n');
    ASSERT_TRUE(re == etalon);
}

TEST_COMPONENT(001)
{
    const str_t master = "11";
    const str_t invest = "22";
    const str_t key = "43";

    const str_t message
        = "master%3D" + master
        + "%20"
        + "investor%3D" + invest;

    const str_t request = "https://24.hazuco.com/actions_open/crm/monitoring_log_write_ext"
        "?key=33FD4E4A3F1499A4EBD938E009638DD9"
        "&event_type_id=" + key +
        "&text=" + message;

    const str_t re = me::url(request);
    dprint(std::cout << re << '\n');
    ASSERT_TRUE(re == etalon);
}

//==============================================================================
//==============================================================================
#endif // !TEST_TOOLS_URL


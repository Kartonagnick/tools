// [2021y-03m-04d][11:49:12] Idrisov Denis R.


#include <tools/url.hpp>
//==============================================================================
//==============================================================================

#ifdef _MSC_VER
    #pragma comment(lib, "urlmon.lib")
#endif // ! _MSC_VER

#include <urlmon.h>
#include <sstream>

#include <tools/assert.hpp>
#include <tools/features.hpp>

namespace tools
{
    static dCONSTEXPR_CPP11
    ::std::streamsize cast_size(unsigned long v) dNOEXCEPT
    {
        return static_cast<::std::streamsize>(v);
    }

    ::std::string url(const ::std::string& request)
    {
        dSTATIC_ASSERT(
            sizeof(::std::streamsize) >= sizeof(unsigned long),
            ERROR_INVALID_SIZE
        );

        ::IStream* stream = 0;
        //Also works with https URL's - unsure about the extent of SSL support though.
        ::HRESULT result 
            = URLOpenBlockingStreamA(0, request.c_str(), &stream, 0, 0);
        if (result != 0)
            return "error";

        char buffer[100];
        unsigned long bytesRead;
        ::std::stringstream ss;

        try
        {
            stream->Read(buffer, 100, &bytesRead);
            while (bytesRead != 0)
            {
                ss.write(buffer, ::tools::cast_size(bytesRead));
                stream->Read(buffer, 100, &bytesRead);
            }
        }
        catch (const ::std::exception&)
        {
            dASSERT(false && "tools::url(std::exception)");
        }
        catch (...)
        {
            dASSERT(false && "tools::url(seh-exception)");
        }

        stream->Release();
        return ss.str();
    }

} // namespace tools

//==============================================================================
//==============================================================================

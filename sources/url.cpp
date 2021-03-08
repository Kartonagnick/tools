// [2021y-03m-04d][11:49:12] Idrisov Denis R.


#include <tools/url.hpp>
//==============================================================================
//==============================================================================

#ifdef _MSC_VER
    #pragma comment(lib, "urlmon.lib")
#endif // ! _MSC_VER

#include <urlmon.h>
#include <sstream>

#include <tools/features.hpp>

namespace tools
{
    ::std::string url(const ::std::string& url)
    {
        dSTATIC_ASSERT(
            sizeof(::std::streamsize) >= sizeof(unsigned long),
            ERROR_INVALID_SIZE
        );

        ::IStream* stream;
        //Also works with https URL's - unsure about the extent of SSL support though.
        ::HRESULT request 
            = URLOpenBlockingStreamA(0, url.c_str(), &stream, 0, 0);
        if (request != 0)
            return "error";

        char buffer[100];
        unsigned long bytesRead;
        ::std::stringstream ss;



        stream->Read(buffer, 100, &bytesRead);
        while (bytesRead != 0)
        {
            const ::std::streamsize bytes_
                = static_cast<::std::streamsize>(bytesRead);

            ss.write(buffer, bytes_);
            stream->Read(buffer, 100, &bytesRead);
        }
        stream->Release();
        ::std::string result = ss.str();
        return result;
    }

} // namespace tools

//==============================================================================
//==============================================================================

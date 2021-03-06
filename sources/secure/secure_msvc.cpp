// [2020y-09m-22d][14:06:17] Idrisov Denis R.
//================================================================================
//================================================================================

#ifdef _MSC_VER

#include <tools/assert.hpp>
#include <tools/windows.hpp>

#pragma comment(lib, "crypt32.lib")
#include <WTypes.h>
#include <Wincrypt.h>

#include <cstdlib>
#include <sstream>
#include <vector>

#ifndef NDEBUG
    // debug
    #include <climits>
#endif

typedef ::std::string
    str_t;

typedef unsigned char
    byte;

typedef ::std::vector<byte> 
    vecbyte;

//================================================================================
//================================================================================

namespace 
{
    void str2blob(const str_t& src, ::DATA_BLOB& blob)
    {
        dASSERT(!src.empty());
        byte* data  = const_cast<byte*>(
            reinterpret_cast<const byte*>(&src[0])
        );
        const size_t len = src.length() + 1;
        dASSERT(len <= ULONG_MAX);
        blob.cbData = static_cast<::DWORD>(len);
        blob.pbData = data;
    }

    void bytes2blob(const vecbyte& src, ::DATA_BLOB& blob)
    {
        dASSERT(!src.empty());
        byte* data  = const_cast<byte*>(&src[0]);
        const size_t len = src.size() + 1;
        dASSERT(len <= ULONG_MAX);
        blob.cbData = static_cast<::DWORD>(len);
        blob.pbData = data;
    }

    vecbyte strHex2bytes(const str_t& data)
    {
        vecbyte vb(data.size() / 2);
        for(size_t i = 0, e = vb.size(); i != e; ++i)
        {
            const str_t str(
                data.begin() + 2 * i,  
                data.begin() + 2 * i + 2
            );

            char* p;
            const long v = strtol(str.c_str(), &p, 16);
            dASSERT(p);

            dASSERT(v <= UCHAR_MAX);
            const byte i_hex = static_cast<byte>(v);
            vb[i] = i_hex;
        }
        return vb;
    }

    str_t toStrHex(const vecbyte& vb)
    {
        ::std::stringstream buf;
        char buffer[50];
    
        for(size_t i= 0, e = vb.size(); i != e; ++i)
        {
            byte c = vb[i];
            ::_snprintf_s(buffer, sizeof(buffer) - 1, _TRUNCATE, "%02x", c);
            buf << buffer;
        }
        return buf.str();
    }

    str_t toString(::DATA_BLOB& blob)
    {
        const char* data 
            = reinterpret_cast<const char*>(blob.pbData);
        return str_t(data, blob.cbData);
    }

} // namespace

//================================================================================
//================================================================================

namespace tools
{
    str_t encrypt(const str_t& src, const str_t &access)
    {
        if(src.empty() || access.empty())
            return "";

        ::DATA_BLOB data_out  = {0};
        ::DATA_BLOB data_in   = {0};
        ::DATA_BLOB data_pass = {0};

        str2blob(src   , data_in  );
        str2blob(access, data_pass);

        #define dNULLPTR 0

        const bool success = ::CryptProtectData(
            &data_in, 
            dNULLPTR,  
            &data_pass, 
            dNULLPTR, 
            dNULLPTR, 
            CRYPTPROTECT_LOCAL_MACHINE, 
            &data_out
        ) == TRUE;

        if(!success)
            return "";

        vecbyte vb;
        vb.assign(data_out.pbData, data_out.pbData + data_out.cbData);

        const str_t result = toStrHex(vb);
        ::LocalFree(data_out.pbData);
        return result;
    }

    str_t decrypt(const str_t& src, const str_t& access)
    {
        dASSERT(!src.empty());
        dASSERT(!access.empty());

        const vecbyte vb = strHex2bytes(src);

        ::DATA_BLOB data_in   = {};
        ::DATA_BLOB data_pass = {};
        ::DATA_BLOB data_out  = {};

        bytes2blob(vb, data_in);
        str2blob(access, data_pass);

        const bool success = ::CryptUnprotectData(
            &data_in, 
            dNULLPTR, 
            &data_pass, 
            dNULLPTR, 
            dNULLPTR, 
            0, 
            &data_out
        ) == TRUE;

        if(!success)
            return "";

        str_t result = toString(data_out);
        ::LocalFree(data_out.pbData);

        if (!result.empty())
        {
            dASSERT(*result.rbegin() == 0);
            if(*result.rbegin() == 0)
                result.erase(result.length() - 1);
        }
        return result;
    }

} //namespace tools

//================================================================================
//================================================================================
#endif // !_MSC_VER


#if 0
str_t generate_random_sequence_as_hex( const size_t length )
{
    HCRYPTPROV hProvider = 0;
    if (!length || !::CryptAcquireContextW(&hProvider, nullptr, nullptr, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT)) 
        return "";
    

    std::vector<byte> dataProtected(length, 0);
    if (!::CryptGenRandom(hProvider, length, &dataProtected[0])) 
    {
        ::CryptReleaseContext(hProvider, 0);
        return "";
    }
    
    // convert to string
    str_tstream outStream;
    for (size_t i=0; i < dataProtected.size(); ++i)
    {
        outStream << std::hex << std::uppercase << static_cast<unsigned int>(dataProtected[i]);
    }

    if (!::CryptReleaseContext(hProvider, 0)) 
        return "";
    
    return outStream.str().substr(0, length).c_str();
}
#endif


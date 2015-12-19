// -------------------------------------------------------------------------
//    @FileName      :    NFCUrlModule.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2013-07-08
//    @Module           :    NFCUrlModule
//    @Desc             :
// -------------------------------------------------------------------------

#ifndef _NFC_URL_MODULE_H_
#define _NFC_URL_MODULE_H_

#include "curl/curl.h"
#include "NFComm/NFPluginModule/NFIUrlModule.h"

class NFCUrlModule
    : public NFIUrlModule
{
public:
    NFCUrlModule(NFIPluginManager* p)
    {
        pPluginManager = p;
    }

public:
    struct StConnFree
    {
        StConnFree(CURL* conn)
        {
            m_conn = conn;
        }
        ~StConnFree()
        {
            if (m_conn)
            {
                curl_easy_cleanup(m_conn);
                m_conn = NULL;
            }
        }
        CURL* m_conn;
    };

    struct StSlistFree
    {
        StSlistFree(struct curl_slist *list)
        {
            m_list = list;
        }
        ~StSlistFree()
        {
            if (m_list)
            {
                curl_slist_free_all (m_list);
            }
        }
        struct curl_slist *m_list;
    };

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute(const float fLasFrametime, const float fStartedTime);

    virtual bool AfterInit();
    virtual bool BeforeShut();

    virtual int HttpRequest(const std::string& strUrl, const std::map<std::string, std::string>& mxGetParams, const std::map<std::string, std::string>& mxPostParams,const std::map<std::string, std::string>& mxCookies, const float fTimeOutSec, std::string& strRsp);    
    virtual int HttpRequest(const std::string& strUrl, const std::map<std::string, std::string>& mxGetParams, const std::string& strBodyData,const std::map<std::string, std::string>& mxCookies, const float fTimeOutSec, std::string& strRsp);    

    virtual bool Test();

protected:
    static size_t RecvHttpData(void* buffer, size_t size, size_t nmemb, std::string* strRecveData);
    std::string CompositeParam( const std::map<std::string,std::string>& params );
    std::string CompositeCookies( const std::map<std::string,std::string>& params );

protected:
    std::string mstrHost;

};

#endif
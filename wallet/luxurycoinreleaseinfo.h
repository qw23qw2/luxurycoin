#ifndef LUXURYCOINRELEASEINFO_H
#define LUXURYCOINRELEASEINFO_H

#include "json_spirit.h"
#include "luxurycoinversion.h"

#include <string>

class LuxuryCoinReleaseInfo
{
    std::string versionStr;
    LuxuryCoinVersion version;
    std::string htmlURL;
    std::string bodyText;
    bool isPreRelease;

    static std::string GetStrField(const json_spirit::Object& data, const std::string& fieldName);
    static bool GetBoolField(const json_spirit::Object &data, const std::string &fieldName);
    static LuxuryCoinVersion VersionTagStrToObj(std::string VersionStr);
    static LuxuryCoinReleaseInfo ParseSingleReleaseData(const json_spirit::Object& data);

public:
    LuxuryCoinReleaseInfo();

    static std::vector<LuxuryCoinReleaseInfo> ParseAllReleaseDataFromJSON(const std::string& data);
    bool getIsPreRelease() const;
    LuxuryCoinVersion getVersion() const;
    std::string getUpdateDescription() const;
    std::string getDownloadLink() const;
    void clear();
};


#endif // LUXURYCOINRELEASEINFO_H

#ifndef LUXURYCOINUPDATER_H
#define LUXURYCOINUPDATER_H

#include <string>

#include "version.h"
#include "clientversion.h"
#include "luxurycoinversion.h"
#include "luxurycoinreleaseinfo.h"

#include "curltools.h"

class LuxuryCoinUpdater
{

public:
    static const std::string ClientVersionSrcFileLink;
    static const std::string ReleasesInfoURL;
    static const std::string LatestReleaseURL;

    LuxuryCoinUpdater();
    void checkIfUpdateIsAvailable(boost::promise<bool> &updateIsAvailablePromise, LuxuryCoinReleaseInfo &lastRelease);

    static LuxuryCoinVersion ParseVersion(const std::string& versionFile);
    static std::string GetDefineFromCFile(const std::string& fileData, const std::string &fieldName);
    static std::string RemoveCFileComments(const std::string& fileData);
};

struct RemovePreReleaseFunctor
{
    bool operator() (const LuxuryCoinReleaseInfo& r)
    {
        return r.getIsPreRelease();
    }
};

struct LuxuryCoinReleaseVersionGreaterComparator
{
    bool operator() (const LuxuryCoinReleaseInfo& r1, const LuxuryCoinReleaseInfo& r2)
    {
        return r1.getVersion() > r2.getVersion();
    }
};


#endif // LUXURYCOINUPDATER_H

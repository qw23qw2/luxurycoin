#include "luxurycoinupdater.h"
#include "util.h"

#include <iostream>
#include <vector>
#include <boost/regex.hpp>
#include <sstream>
#include <boost/algorithm/string.hpp>

const std::string LuxuryCoinUpdater::ClientVersionSrcFileLink  = "https://raw.githubusercontent.com/qw23qw2/luxurycoin/master/wallet/clientversion.h";
const std::string LuxuryCoinUpdater::ReleasesInfoURL = "https://api.github.com/repos/qw23qw2/luxurycoin/releases";
const std::string LuxuryCoinUpdater::LatestReleaseURL = "https://github.com/qw23qw2/luxurycoin/releases/latest";

LuxuryCoinUpdater::LuxuryCoinUpdater()
{
}

void LuxuryCoinUpdater::checkIfUpdateIsAvailable(boost::promise<bool> &updateIsAvailablePromise, LuxuryCoinReleaseInfo& lastRelease)
{
    LuxuryCoinReleaseInfo remoteRelease;
    LuxuryCoinVersion localVersion;
    std::string releaseData;
    std::vector<LuxuryCoinReleaseInfo> luxurycoinReleases;
    try {
        releaseData = cURLTools::GetFileFromHTTPS(ReleasesInfoURL, 0);
        luxurycoinReleases = LuxuryCoinReleaseInfo::ParseAllReleaseDataFromJSON(releaseData);

        // remove prerelease versions
        luxurycoinReleases.erase(std::remove_if(luxurycoinReleases.begin(), luxurycoinReleases.end(),
                RemovePreReleaseFunctor()), luxurycoinReleases.end());
//        std::for_each(luxurycoinReleases.begin(), luxurycoinReleases.end(), [](const LuxuryCoinReleaseInfo& v) {std::cout<<v.versionStr<<std::endl;});
        // sort in descending order
        std::sort(luxurycoinReleases.begin(), luxurycoinReleases.end(), LuxuryCoinReleaseVersionGreaterComparator());
//        std::for_each(luxurycoinReleases.begin(), luxurycoinReleases.end(), [](const LuxuryCoinReleaseInfo& v) {std::cout<<v.versionStr<<std::endl;});
        if(luxurycoinReleases.size() <= 0) {
            throw std::length_error("The list of releases retrieved is empty.");
        }
    } catch (std::exception& ex) {
        std::string msg("Unable to download update file: " + std::string(ex.what()) + "\n");
        printf("%s", msg.c_str());
        updateIsAvailablePromise.set_exception(boost::current_exception());
        return;
    }

    try {
        remoteRelease = luxurycoinReleases[0]; // get highest version
        localVersion  = LuxuryCoinVersion::GetCurrentLuxuryCoinVersion();
    } catch (std::exception& ex) {
        std::stringstream msg;
        msg << "Unable to parse version data during update check: " << ex.what() << std::endl;
        printf("%s", msg.str().c_str());
        updateIsAvailablePromise.set_exception(boost::current_exception());
        return;
    }
    lastRelease = remoteRelease;
    updateIsAvailablePromise.set_value(remoteRelease.getVersion() > localVersion);
}

LuxuryCoinVersion LuxuryCoinUpdater::ParseVersion(const std::string &versionFile)
{
    int majorVersion    = FromString<int>(GetDefineFromCFile(versionFile, "CLIENT_VERSION_MAJOR"));
    int minorVersion    = FromString<int>(GetDefineFromCFile(versionFile, "CLIENT_VERSION_MINOR"));
    int revisionVersion = FromString<int>(GetDefineFromCFile(versionFile, "CLIENT_VERSION_REVISION"));
    int buildVersion    = FromString<int>(GetDefineFromCFile(versionFile, "CLIENT_VERSION_BUILD"));
    return LuxuryCoinVersion(majorVersion, minorVersion, revisionVersion, buildVersion);
}

std::string LuxuryCoinUpdater::GetDefineFromCFile(const std::string &fileData, const std::string& fieldName)
{
    //regex of define in one or multiple lines
    const std::string regex_str = ".*\\s*#define\\s+" + fieldName + "\\s+[\\s*|(\\n)]+([^\\s]+)\\s*.*";
    boost::regex pieces_regex(regex_str);
    boost::smatch pieces_match;
    std::string piece;
    bool match_found = boost::regex_match(fileData, pieces_match, pieces_regex);
    if (match_found) {
        piece = pieces_match[1];
    } else {
        std::string error = "Unable to find match for " + fieldName + " in the downloaded file.";
        throw std::runtime_error(error.c_str());
    }
    return piece;
}

std::string LuxuryCoinUpdater::RemoveCFileComments(const std::string &fileData)
{
    std::string result = fileData;

    //remove carriage return, as they could hinder detecting new lines
    std::string carriage_return_regex_str("\\r", boost::match_not_dot_newline);
    boost::regex carriage_return_regex(carriage_return_regex_str);
    result = boost::regex_replace(result, carriage_return_regex, "");

    //remove single line comments (//)
    std::string line_comments_regex_str("\\/\\/.*\\n");
    boost::regex line_comments_regex(line_comments_regex_str);
    result = boost::regex_replace(result, line_comments_regex, "", boost::match_not_dot_newline);

    //remove multi-line comments (/* */)
    std::string multiline_comments_regex_str("/\\*(.*?)\\*/"); // The "?" is to turn off greediness
    boost::regex multiline_comments_regex(multiline_comments_regex_str);
    result = boost::regex_replace(result, multiline_comments_regex, "");

    return result;
}

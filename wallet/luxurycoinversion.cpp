#include "luxurycoinversion.h"
#include "util.h"
#include "clientversion.h"

#include <stdexcept>

void LuxuryCoinVersion::checkInitialization()
{
    if(major < 0 || minor < 0 || revision < 0 || build < 0)
        throw std::runtime_error("LuxuryCoinVersion object is not initialized.");
}

LuxuryCoinVersion::LuxuryCoinVersion(int Major, int Minor, int Revision, int Build)
{
    major = Major;
    minor = Minor;
    revision = Revision;
    build = Build;
}

bool LuxuryCoinVersion::operator>(const LuxuryCoinVersion &rhs)
{
    checkInitialization();
    if(this->major > rhs.major)
        return true;
    else if(this->major < rhs.major)
        return false;

    if(this->minor > rhs.minor)
        return true;
    else if(this->minor < rhs.minor)
        return false;

    if(this->revision > rhs.revision)
        return true;
    else if(this->revision < rhs.revision)
        return false;

    if(this->build > rhs.build)
        return true;
    else if(this->build < rhs.build)
        return false;

    return false;
}

bool LuxuryCoinVersion::operator<(const LuxuryCoinVersion &rhs)
{
    return (!(*this > rhs) && !(*this == rhs));
}

bool LuxuryCoinVersion::operator>=(const LuxuryCoinVersion &rhs)
{
    return !(*this < rhs);
}

bool LuxuryCoinVersion::operator<=(const LuxuryCoinVersion &rhs)
{
    return !(*this > rhs);
}

bool LuxuryCoinVersion::operator==(const LuxuryCoinVersion &rhs)
{
    return (major    == rhs.major &&
            minor    == rhs.minor &&
            revision == rhs.revision &&
            build    == rhs.build);
}

bool LuxuryCoinVersion::operator!=(const LuxuryCoinVersion &rhs)
{
    return !(*this == rhs);
}

std::string LuxuryCoinVersion::toString()
{
    return ToString(major)    + "." +
           ToString(minor)    + "." +
           ToString(revision) + "." +
           ToString(build);

}

void LuxuryCoinVersion::clear()
{
    *this = LuxuryCoinVersion();
}

void LuxuryCoinVersion::setMajor(int value)
{
    major = value;
}

void LuxuryCoinVersion::setMinor(int value)
{
    minor = value;
}

void LuxuryCoinVersion::setRevision(int value)
{
    revision = value;
}

void LuxuryCoinVersion::setBuild(int value)
{
    build = value;
}

int LuxuryCoinVersion::getMajor() const
{
    return major;
}

int LuxuryCoinVersion::getMinor() const
{
    return minor;
}

int LuxuryCoinVersion::getRevision() const
{
    return revision;
}

int LuxuryCoinVersion::getBuild() const
{
    return build;
}

LuxuryCoinVersion LuxuryCoinVersion::GetCurrentLuxuryCoinVersion()
{
    return LuxuryCoinVersion(CLIENT_VERSION_MAJOR,
                         CLIENT_VERSION_MINOR,
                         CLIENT_VERSION_REVISION,
                         CLIENT_VERSION_BUILD);
}

#ifndef LUXURYCOINVERSION_H
#define LUXURYCOINVERSION_H

#include <string>

//TODO: Sam: Write unit tests for this class's comparators
class LuxuryCoinVersion
{
    int major;
    int minor;
    int revision;
    int build;
    void checkInitialization();

public:
    LuxuryCoinVersion(int Major = -1, int Minor = -1, int Revision = -1, int Build = -1);
    bool operator>(const LuxuryCoinVersion& rhs);
    bool operator<(const LuxuryCoinVersion& rhs);
    bool operator>=(const LuxuryCoinVersion& rhs);
    bool operator<=(const LuxuryCoinVersion& rhs);
    bool operator==(const LuxuryCoinVersion& rhs);
    bool operator!=(const LuxuryCoinVersion& rhs);
    std::string toString();
    void clear();

    void setMajor(int value);
    void setMinor(int value);
    void setRevision(int value);
    void setBuild(int value);

    int getMajor() const;
    int getMinor() const;
    int getRevision() const;
    int getBuild() const;

    static LuxuryCoinVersion GetCurrentLuxuryCoinVersion();
};

#endif // LUXURYCOINVERSION_H

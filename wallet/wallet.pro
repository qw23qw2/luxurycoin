TEMPLATE = app
TARGET = luxurycoin-qt
VERSION = 1.0.7
INCLUDEPATH += . json qt
DEFINES += QT_GUI BOOST_THREAD_USE_LIB BOOST_SPIRIT_THREADSAFE
CONFIG += no_include_pwd
CONFIG += thread

LUXURYCOIN_ROOT = $${PWD}/../

VPATH += $${LUXURYCOIN_ROOT}/wallet/ $${LUXURYCOIN_ROOT}/wallet/json $${LUXURYCOIN_ROOT}/wallet/qt


# use: qmake "LUXURYCOIN_REST=1"
contains(LUXURYCOIN_REST, 1) {
    DEFINES += LUXURYCOIN_REST
    # restbed
    LIBS += -L"$(CURDIR)/restbed/distribution/library" -lrestbed
    INCLUDEPATH += "$(CURDIR)/restbed/distribution/include/"
    QMAKE_CXXFLAGS += -std=c++11
}

include(wallet.pri)
include(wallet-libs.pri)

RESOURCES += \
    qt/bitcoin.qrc

system($$QMAKE_LRELEASE -silent $$_PRO_FILE_)

DISTFILES +=                                \
    .travis.yml                             \
    ci_scripts/test_linux-daemon.py         \
    ci_scripts/test_linux-gui_wallet.py     \
    ci_scripts/test_win32-gui_wallet.py     \
    ci_scripts/luxurycoin_ci_libs/__init__.py   \
    ci_scripts/luxurycoin_ci_libs/common.py

include(luxurycoin-wallet.pri)

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += wallet

#LUXURYCOIN_CONFIG += Tests

contains( LUXURYCOIN_CONFIG, Tests ) {
    SUBDIRS += wallet/test
}

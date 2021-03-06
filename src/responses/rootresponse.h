#ifndef ROOTRESPONSE_H
#define ROOTRESPONSE_H
#include "response.h"

/**
* Represents root endpoint response.
* @see org.stellar.sdk.Server#root()
*/
class RootResponse : public Response
{
    Q_OBJECT
    Q_PROPERTY(QString horizon_version MEMBER m_horizonVersion)
    Q_PROPERTY(QString core_version MEMBER m_coreVersion)
    Q_PROPERTY(qint32 history_latest_ledger MEMBER m_historyLatestLedger)
    Q_PROPERTY(qint32 history_elder_ledger MEMBER m_historyElderLedger)
    Q_PROPERTY(qint32 core_latest_ledger MEMBER m_coreLatestLedger)
    Q_PROPERTY(QString network_passphrase MEMBER m_networkPassphrase)
    Q_PROPERTY(qint32 protocol_version MEMBER m_protocolVersion)

    QString m_horizonVersion;
    QString m_coreVersion;
    qint32 m_historyLatestLedger;
    qint32 m_historyElderLedger;
    qint32 m_coreLatestLedger;
    QString m_networkPassphrase;
    qint32 m_protocolVersion;
public:
    RootResponse(QNetworkReply *reply=nullptr);
    virtual ~RootResponse();
    QString getHorizonVersion() const;

    QString getStellarCoreVersion() const;

    qint32 getHistoryLatestLedger() const;

    qint32 getHistoryElderLedger() const;

    qint32 getCoreLatestLedger() const;

    QString getNetworkPassphrase() const;

    qint32 getProtocolVersion() const;
};
Q_DECLARE_METATYPE(RootResponse*)
#endif // ROOTRESPONSE_H


#ifndef RESPONSE_H
#define RESPONSE_H
#include <QObject>
#include <QNetworkReply>
#include <QMetaProperty>
#include <QVariantMap>

template<class T>
inline QList<T> convert(QVariantList source)
{
    QList<T> res;
    for(int n = 0;n<source.count();n++){
        T r;
        QVariantMap m = source[n].toMap();
        //for(int i=0;i<T::staticMetaObject.propertyCount();i++)
        for(auto key : m.keys())
        {
            int index = T::staticMetaObject.indexOfProperty(key.toLatin1().data());
            if(index>=T::staticMetaObject.propertyOffset()){
                QMetaProperty p = T::staticMetaObject.property(index);
                p.writeOnGadget(&r,m.value(QString(p.name())));
            }
        }
        res.append(r);

    }
    return res;
}


class Response : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int rateLimitLimit READ getRateLimitLimit NOTIFY ready)
    Q_PROPERTY(int rateLimitRemaining READ getRateLimitRemaining NOTIFY ready)
    Q_PROPERTY(int rateLimitReset READ getRateLimitReset NOTIFY ready)
    Q_PROPERTY(QString type MEMBER m_type NOTIFY ready)
    Q_PROPERTY(QString title MEMBER m_title NOTIFY ready)
    Q_PROPERTY(int status MEMBER m_status NOTIFY ready)
    Q_PROPERTY(QString instance MEMBER m_instance NOTIFY ready)
    Q_PROPERTY(QString detail MEMBER m_detail NOTIFY ready)


    QString m_type;
    QString m_title;
    int m_status;
    QString m_instance;

    QString m_detail;

    QByteArray m_pendingData;
protected:
    QNetworkReply * m_reply;
    int m_rateLimitLimit;
    int m_rateLimitRemaining;
    int m_rateLimitReset;

    void fillObject(const QMetaObject *mo, void *obj, const QJsonObject &jsonObj, bool qobject = false);

    virtual void reset();
    bool isStreamingResponse();
public:
    explicit Response(QNetworkReply* reply=0);

    virtual ~Response();
    void loadFromReply(QNetworkReply *reply);
    virtual void loadFromJson(QByteArray data);
signals:
    void ready();
    void error();
private:
    bool preprocessResponse(QNetworkReply *response);
private slots:
    void processResponse();    
    void processPartialResponse();
    void reconnectStream();
    void reconnectStreamDelayed();
    void clearReply(QObject *obj);
public:
    /**
     * Returns X-RateLimit-Limit header from the response.
     * This number represents the he maximum number of requests that the current client can
     * make in one hour.
     * @see <a href="https://www.stellar.org/developers/horizon/learn/rate-limiting.html" target="_blank">Rate Limiting</a>
     */
    int getRateLimitLimit();

    /**
     * Returns X-RateLimit-Remaining header from the response.
     * The number of remaining requests for the current window.
     * @see <a href="https://www.stellar.org/developers/horizon/learn/rate-limiting.html" target="_blank">Rate Limiting</a>
     */
    int getRateLimitRemaining();

    /**
     * Returns X-RateLimit-Reset header from the response. Seconds until a new window starts.
     * @see <a href="https://www.stellar.org/developers/horizon/learn/rate-limiting.html" target="_blank">Rate Limiting</a>
     */
    int getRateLimitReset();
};
Q_DECLARE_METATYPE(Response*)
#endif // RESPONSE_H

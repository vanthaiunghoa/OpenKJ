#ifndef OKJSONGBOOKAPI_H
#define OKJSONGBOOKAPI_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QUrl>
#include <QDebug>
#include <QTimer>


class OkjsRequest
{
public:
    int requestId;
    QString singer;
    QString artist;
    QString title;
    int key;
    int time;
    bool operator == (const OkjsRequest r) const;
};


typedef QList<OkjsRequest> OkjsRequests;

class OkjsVenue
{
public:
    int venueId;
    QString name;
    QString urlName;
    bool accepting;
    bool operator == (const OkjsVenue& v) const;
};

QDebug operator<<(QDebug dbg, const OkjsVenue &okjsvenue);

typedef QList<OkjsVenue> OkjsVenues;

class OKJSongbookAPI : public QObject
{
    Q_OBJECT
private:
    int serial;
    OkjsVenues venues;
    OkjsRequests requests;
    QNetworkAccessManager *manager;
    QTimer *timer;
    QTimer *alertTimer;
    QTime lastSync;
    bool delayErrorEmitted;
    bool connectionReset;

public:
    explicit OKJSongbookAPI(QObject *parent = 0);
    void getSerial();
    void refreshRequests();
    void removeRequest(int requestId);
    bool getAccepting();
    void setAccepting(bool enabled);
    void refreshVenues(bool blocking = false);
    void clearRequests();
    void updateSongDb();
    bool test();
    void alertCheck();

signals:
    void venuesChanged(OkjsVenues);
    void sslError();
    void remoteSongDbUpdateProgress(int);
    void remoteSongDbUpdateNumDocs(int);
    void remoteSongDbUpdateDone();
    void remoteSongDbUpdateStart();
    void requestsChanged(OkjsRequests);
    void synchronized(QTime);
    void delayError(int);
    void testPassed();
    void testFailed(QString error);
    void testSslError(QString error);
    void alertRecieved(QString title, QString message);


public slots:

private slots:
        void onSslErrors(QNetworkReply * reply, QList<QSslError> errors);
        void onTestSslErrors(QNetworkReply * reply, QList<QSslError> errors);
        void onNetworkReply(QNetworkReply* reply);
        void timerTimeout();
        void alertTimerTimeout();
        void setInterval(int interval);
};

#endif // OKJSONGBOOKAPI_H

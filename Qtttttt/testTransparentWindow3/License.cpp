#include "License.h"

//#include <common/Common.h>
#include <TigerCommon/common/Common.h>
#include <QCryptographicHash>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <utils/CrypteHelper.h>
#include <utils/JsonHelper.h>

License::License():
    m_licenceId(""),
    m_beginDate(""),
    m_endDate(""),
    m_pcCountLimit(0),
    m_deviceCountLimit(0),
    m_signature(""),
    m_permit(false)
{

}

QString License::lisenceId()const
{
    return m_licenceId;
}

int License::maxComputerNum() const
{
    return m_pcCountLimit;
}


QStringList License::usedComputerList() const
{
    return m_pcList;
}

int License::usedPcCount() const
{
    return m_pcList.count();
}

int License::maxDeviceNum() const
{
    return m_deviceCountLimit;
}

QString License::signature() const
{
    return m_signature;
}

QStringList License::usedDeviceList() const
{
    return m_deviceList;
}

int License::usedDeviceCount() const
{
    return m_deviceList.count();
}


bool License::addUsedDevice(const QString &deviceId, QString &errMsg)
{
    if (m_deviceList.contains(deviceId)){
        return true;
    }
    // m_deviceCountLimit == 0 表示不限设备
    if (m_deviceCountLimit == 0 || m_deviceList.size() < m_deviceCountLimit) {
        m_deviceList << deviceId;
        return checkPermit(errMsg);
    }
    errMsg = QString(tr("Available devices reach the upper limit, no more data can be exported"));
    return false;
}

bool License::checkSignature()
{
    bool result = false;
    QString signText = QString("%1%2%3%4%5%6").arg(g_appKey).arg(m_licenceId).arg(m_pcCountLimit)
            .arg(m_deviceCountLimit).arg(m_endDate).arg(g_appSecurity);

    QString signature = QCryptographicHash::hash(QCryptographicHash::hash(signText.toUtf8(), QCryptographicHash::Sha1), QCryptographicHash::Md5).toHex();

    if (signature == m_signature) {
        result = true;
    }
    return result;
}

bool License::checkPermit(QString & errMsg)
{
    if (!checkSignature()) {
        errMsg = QString(tr("Licence Signature verification failed"));
        return false;
    }
    if (m_pcList.size() > m_pcCountLimit) {
        errMsg = QString(tr("Available PC reach the upper limit, no more data can be exported"));
        return false;
    }
    // m_deviceCountLimit = 0 表示不限设备
    if (m_deviceCountLimit != 0 && m_deviceList.size() > m_deviceCountLimit) {
        errMsg = QString(tr("Available devices reach the upper limit, no more data can be exported"));
        return false;
    }
    QDateTime localTime = QDateTime::currentDateTime().toLocalTime();
    QDateTime beginTime = QDateTime::fromString(m_beginDate, "yyyy-MM-dd hh:mm:ss");
    QDateTime endTime = QDateTime::fromString(m_endDate, "yyyy-MM-dd hh:mm:ss");
    auto diff = localTime.secsTo(beginTime);
    if (diff > 86400){  // 生效时间有24小时的容差
        errMsg = QString(tr("The product is not within the validity period"));
        return false;
    }
    if (localTime > endTime) {
        errMsg = QString(tr("The product is not within the validity period"));
        return false;
    }
    return true;
}


QString License::endDate() const
{
    return m_endDate;
}

QString License::subscribe() const
{
    return m_subscribe;
}

QString License::licenceId() const
{
    return m_licenceId;
}

void License::setLicenceId(const QString &newLicenceId)
{
    m_licenceId = newLicenceId;
}

QString License::beginDate() const
{
    return m_beginDate;
}

void License::setBeginDate(const QString &newBeginDate)
{
    m_beginDate = newBeginDate;
}

void License::setEndDate(const QString &newEndDate)
{
    m_endDate = newEndDate;
}

int License::pcCountLimit() const
{
    return m_pcCountLimit;
}

void License::setPcCountLimit(int newPcCountLimit)
{
    m_pcCountLimit = newPcCountLimit;
}

QStringList License::pcList()
{
    return m_pcList;
}

void License::setPcList(const QStringList &newPcList)
{
    m_pcList = newPcList;
}

int License::deviceCountLimit() const
{
    return m_deviceCountLimit;
}

void License::setDeviceCountLimit(int newDeviceCountLimit)
{
    m_deviceCountLimit = newDeviceCountLimit;
}

QStringList License::deviceList()
{
    return m_deviceList;
}

void License::setDeviceList(const QStringList &newDeviceList)
{
    m_deviceList = newDeviceList;
}

void License::setSignature(const QString &newSignature)
{
    m_signature = newSignature;
}

void License::setSubscribe(const QString &newSubscribe)
{
    m_subscribe = newSubscribe;
}

QStringList License::productIdList()
{
    return m_productIdList;
}

void License::setProductIdList(const QStringList &newProductIdList)
{
    m_productIdList = newProductIdList;
}

void License::setPermit(bool newPermit)
{
    m_permit = newPermit;
}

bool License::permit(QString &errMsg)
{
    return checkPermit(errMsg);
}


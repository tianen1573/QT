#ifndef LICENSE_H
#define LICENSE_H

#include <QSharedPointer>

///
/// \brief 软件激活license数据定义
///
class License : public QObject
{
    Q_OBJECT
public:
    License();
    QString lisenceId() const;

    QString validPeriod() const;

    int maxComputerNum() const;

    QStringList usedComputerList() const;

    int usedPcCount() const;

    int maxDeviceNum() const;

    QString signature() const;

    QStringList usedDeviceList() const;

    int usedDeviceCount() const;

    bool permit(QString &errMsg);

    //添加已使用的设备ID
    bool addUsedDevice(const QString &deviceId, QString &errmsg);

    //验证签名
    bool checkSignature();

    //更新许可状态
    bool checkPermit(QString & errMsg);

    QString endDate() const;

    QString subscribe() const;

    QString licenceId() const;
    void setLicenceId(const QString &newLicenceId);

    QString beginDate() const;
    void setBeginDate(const QString &newBeginDate);

    void setEndDate(const QString &newEndDate);
    int pcCountLimit() const;
    void setPcCountLimit(int newPcCountLimit);
    QStringList pcList();
    void setPcList(const QStringList &newPcList);
    int deviceCountLimit() const;
    void setDeviceCountLimit(int newDeviceCountLimit);
    QStringList deviceList();
    void setDeviceList(const QStringList &newDeviceList);
    void setSignature(const QString &newSignature);
    void setSubscribe(const QString &newSubscribe);
    QStringList productIdList();
    void setProductIdList(const QStringList &newProductIdList);
    void setPermit(bool newPermit);

private:
    QString m_licenceId;
    QString m_beginDate;
    QString m_endDate;
    int m_pcCountLimit;
    QStringList m_pcList;
    int m_deviceCountLimit;
    QStringList m_deviceList;
    QString m_signature;
    QString m_subscribe;
    QStringList m_productIdList;
    bool m_permit;
};
typedef QSharedPointer<License> LicensePtr;
#endif // LICENSE_H

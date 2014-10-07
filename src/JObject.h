#ifndef JOBJECT_H
#define JOBJECT_H

#include <QObject>
#include <QVariant>
#include <QVariantList>
#include <QMetaObject>
#include <QString>
#include <QMetaProperty>

// t: type, x: property name
#define PropertyPrivateSet(t, x) private: t _##x;  \
    public: t x() const {return _##x;} \
    private: void x(const t& v){_##x = v;}


// t: type, x: property name
#define PropertyProtectedSet(t, x) private: t _##x;  \
    public: t x() const {return _##x;} \
    protected: void x(const t& v){_##x = v;}

// t: type, x: property name
#define PropertyPublicSet(t, x) private: t _##x;  \
    public: t x() const {return _##x;} \
    void x(const t& v){_##x = v;}


// t: type, x: property name
#define MetaPropertyPrivateSet_List(t, x)  private: Q_PROPERTY(QVariantList x READ x WRITE x) \
    PropertyPrivateSet(QVariantList, x) \
    void append##x(const t& i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.append(v);}} \
    void remove##x(const t& i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.removeAll(v);}} \
    public: \
    int count##x()const {return _##x.length();} \
    t item##x##At(int i) {return _##x.at(i).value<t>();} \
    bool item##t##Exist(const t& i) const {QVariant v = QVariant::fromValue(i); if (v.isValid()) { return _##x.contains(v);} else return false;}


// t: type, x: property name
#define MetaPropertyProtectedSet_List(t, x)  private: Q_PROPERTY(QVariantList x READ x WRITE x) \
    PropertyProtectedSet(QVariantList, x) \
    void append##x(const t& i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.append(v);}} \
    void remove##x(const t& i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.removeAll(v);}} \
    public: \
    int count##x()const {return _##x.length();} \
    t item##x##At(int i) {return _##x.at(i).value<t>();} \
    bool item##t##Exist(const t& i) const {QVariant v = QVariant::fromValue(i); if (v.isValid()) { return _##x.contains(v);} else return false;}


// t: type, x: property name
#define MetaPropertyPublicSet_List(t, x)  private: Q_PROPERTY(QVariantList x READ x WRITE x) \
    PropertyPublicSet(QVariantList, x) \
    public: \
    void append##x(const t& i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.append(v);}} \
    void remove##x(const t& i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.removeAll(v);}} \
    int count##x()const {return _##x.length();} \
    t item##x##At(int i) {return _##x.at(i).value<t>();}

// t: type, x: property name
#define PropertyPrivateSet_Ptr(t, x) private: t* _##x;  \
    public: t* x() {return _##x;} \
    private: void x(t* v){_##x = v;}


// t: type, x: property name
#define PropertyProtectedSet_Ptr(t, x) private: t* _##x;  \
    public: t* x() {return _##x;} \
    protected: void x(t* v){_##x = v;}

// t: type, x: property name
#define PropertyPublicSet_Ptr(t, x) private: t* _##x;  \
    public: t* x() {return _##x;} \
    void x(t* v){_##x = v;}


// t: type, x: property name
#define PropertyPrivateSet_Ptr_O(t, x) private: QObject* _##x;  \
    public: t* x() {return qobject_cast<t*>(_##x);} \
    private: void x(QObject* v){_##x = v;}


// t: type, x: property name
#define PropertyProtectedSet_Ptr_O(t, x) private: QObject* _##x;  \
    public: t* x() {return qobject_cast<t*>(_##x);} \
    protected: void x(QObject* v){_##x = v;}

// t: type, x: property name
#define PropertyPublicSet_Ptr_O(t, x)  private: QObject* _##x;  \
    public: t* x() {return qobject_cast<t*>(_##x);} \
    public: void x(QObject* v){_##x = v;}

// t: type, x: property name
#define MetaPropertyPrivateSet(t, x) private: Q_PROPERTY(t x READ x WRITE x) \
    PropertyPrivateSet(t, x)


// t: type, x: property name
#define MetaPropertyProtectedSet(t, x) private: Q_PROPERTY(t x READ x WRITE x) \
    PropertyProtectedSet(t, x)

// t: type, x: property name
#define MetaPropertyPublicSet(t, x) private: Q_PROPERTY(t x READ x WRITE x) \
    PropertyPublicSet(t, x)

// t: type, x: property name
#define MetaPropertyPrivateSet_Ptr(t, x) private: Q_PROPERTY(QObject* x READ x WRITE x) \
    PropertyPrivateSet_Ptr_O(t, x) \
    public: Q_INVOKABLE void _type##x(const QString& prop){registerPtrProperty(prop, &t::staticMetaObject);}


// t: type, x: property name
#define MetaPropertyProtectedSet_Ptr(t, x) private: Q_PROPERTY(QObject* x READ x WRITE x) \
    PropertyProtectedSet_Ptr_O(t, x) \
    public: Q_INVOKABLE void _type##x(const QString& prop){registerPtrProperty(prop, &t::staticMetaObject);}


// t: type, x: property name
#define MetaPropertyPublicSet_Ptr(t, x) private: Q_PROPERTY(QObject* x READ x WRITE x) \
    PropertyPublicSet_Ptr_O(t, x) \
    public: Q_INVOKABLE void _type##x(const QString& prop){registerPtrProperty(prop, &t::staticMetaObject);}

// t: type, x: property name
#define MetaPropertyPrivateSet_Ptr_List(t, x)  private: Q_PROPERTY(QVariantList x READ x WRITE x) \
    PropertyPrivateSet(QVariantList, x) \
    private: Q_INVOKABLE void _type##x(const QString& prop){registerPtrProperty(prop, &t::staticMetaObject);} \
    void append##t(t* i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.append(v);}} \
    void remove##t(t* i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.removeAll(v);}} \
    public: int count##t()const {return _##x.length();} \
    t* item##t##At(int i) {return _##x.at(i).value<t*>();} \
    bool item##t##Exist(t* i) const {QVariant v = QVariant::fromValue(i); if (v.isValid()) { return _##x.contains(v);} else return false;}


// t: type, x: property name
#define MetaPropertyProtectedSet_Ptr_List(t, x)  private: Q_PROPERTY(QVariantList x READ x WRITE x) \
    PropertyProtectedSet(QVariantList, x) \
    protected: Q_INVOKABLE void _type##x(const QString& prop){registerPtrProperty(prop, &t::staticMetaObject);} \
    void append##t(t* i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.append(v);}} \
    void remove##t(t* i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.removeAll(v);}} \
    public: int count##t()const {return _##x.length();} \
    t* item##t##At(int i) {return _##x.at(i).value<t*>();} \
    bool item##t##Exist(t* i) const {QVariant v = QVariant::fromValue(i); if (v.isValid()) { return _##x.contains(v);} else return false;}


// t: type, x: property name
#define MetaPropertyPublicSet_Ptr_List(t, x)  private: Q_PROPERTY(QVariantList x READ x WRITE x) \
    PropertyPublicSet(QVariantList, x) \
    public: Q_INVOKABLE void _type##x(const QString& prop){registerPtrProperty(prop, &t::staticMetaObject);} \
    void append##t(t* i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.append(v);}} \
    void remove##t(t* i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.removeAll(v);}} \
    int count##t()const {return _##x.length();} \
    t* item##t##At(int i) {return _##x.at(i).value<t*>();} \
    bool item##t##Exist(t* i) const {QVariant v = QVariant::fromValue(i); if (v.isValid()) { return _##x.contains(v);} else return false;}


/**
 *  Base class of classes that should import/export all its properties from/to QVariant via JSON.
 */
class JObject : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit JObject(QObject *parent = 0);
    virtual void initAfterConstruct() {}
    virtual void initAfterImport() {}

    virtual QVariant exportToVariant();
    virtual bool importFromVariant(const QVariant& v);

    QByteArray exportToJson(bool indented = true);
    bool importFromJson(const QByteArray& json);

protected:
    void registerPtrProperty(const QString& prop, const QMetaObject* mo);
    const QMetaObject* metaObjectForProp(const QString& prop);

private:
    Q_DISABLE_COPY(JObject)
    QMap <QString, const QMetaObject* > _ptrPropMap;
};

#endif // JOBJECT_H

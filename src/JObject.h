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
    private: void x(const t& v){_##x = v; notify##x(v);}


// t: type, x: property name
#define PropertyProtectedSet(t, x) private: t _##x;  \
    public: t x() const {return _##x;} \
    protected: void x(const t& v){_##x = v; notify##x(v);}

// t: type, x: property name
#define PropertyPublicSet(t, x) private: t _##x;  \
    public: t x() const {return _##x;} \
    void x(const t& v){_##x = v; notify##x(v);}


// t: type, x: property name
#define MetaPropertyPrivateSet_List(t, x)  Q_SIGNALS: void notify##x(const QVariantList& i); \
    private: Q_PROPERTY(QVariantList x READ x WRITE x NOTIFY notify##x) \
    PropertyPrivateSet(QVariantList, x) \
    void append##x(const t& i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.append(v);}} \
    void insert##t(int ind, const t& i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.insert(ind,v);}} \
    void remove##x(const t& i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.removeAll(v);}} \
    public: \
    int count##x()const {return _##x.length();} \
    t item##x##At(int i) {return _##x.at(i).value<t>();} \
    bool item##t##Exist(const t& i) const {QVariant v = QVariant::fromValue(i); if (v.isValid()) { return _##x.contains(v);} else return false;}


// t: type, x: property name
#define MetaPropertyProtectedSet_List(t, x)  Q_SIGNALS: void notify##x(const QVariantList& i); \
    private: Q_PROPERTY(QVariantList x READ x WRITE x NOTIFY notify##x) \
    PropertyProtectedSet(QVariantList, x) \
    void append##x(const t& i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.append(v);}} \
    void insert##t(int ind, const t& i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.insert(ind,v);}} \
    void remove##x(const t& i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.removeAll(v);}} \
    public: \
    int count##x()const {return _##x.length();} \
    t item##x##At(int i) {return _##x.at(i).value<t>();} \
    bool item##t##Exist(const t& i) const {QVariant v = QVariant::fromValue(i); if (v.isValid()) { return _##x.contains(v);} else return false;}


// t: type, x: property name
#define MetaPropertyPublicSet_List(t, x)  Q_SIGNALS: void notify##x(const QVariantList& i); \
    private: Q_PROPERTY(QVariantList x READ x WRITE x NOTIFY notify##x) \
    PropertyPublicSet(QVariantList, x) \
    public: \
    void append##x(const t& i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.append(v);}} \
    void insert##t(int ind, const t& i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.insert(ind,v);}} \
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
#define MetaPropertyPrivateSet(t, x) Q_SIGNALS: void notify##x(const t& i); \
    private: Q_PROPERTY(t x READ x WRITE x NOTIFY notify##x) \
    PropertyPrivateSet(t, x)


// t: type, x: property name
#define MetaPropertyProtectedSet(t, x) Q_SIGNALS: void notify##x(const t& i); \
    private: Q_PROPERTY(t x READ x WRITE x NOTIFY notify##x) \
    PropertyProtectedSet(t, x)

// t: type, x: property name
#define MetaPropertyPublicSet(t, x) Q_SIGNALS: void notify##x(const t& i); \
    private: Q_PROPERTY(t x READ x WRITE x NOTIFY notify##x) \
    PropertyPublicSet(t, x)

// t: type, x: property name
#define MetaPropertyPrivateSet_Ptr(t, x) Q_SIGNALS: void notify##x(QObject* i); \
    private: Q_PROPERTY(QObject* x READ x WRITE x NOTIFY notify##x) \
    PropertyPrivateSet_Ptr_O(t, x) \
    public: Q_INVOKABLE void _type##x(const QString& prop){registerPtrProperty(prop, &t::staticMetaObject);}


// t: type, x: property name
#define MetaPropertyProtectedSet_Ptr(t, x) Q_SIGNALS: void notify##x(QObject* i); \
    private: Q_PROPERTY(QObject* x READ x WRITE x) \
    PropertyProtectedSet_Ptr_O(t, x) \
    public: Q_INVOKABLE void _type##x(const QString& prop){registerPtrProperty(prop, &t::staticMetaObject);}


// t: type, x: property name
#define MetaPropertyPublicSet_Ptr(t, x) Q_SIGNALS: void notify##x(QObject* i); \
    private: Q_PROPERTY(QObject* x READ x WRITE x) \
    PropertyPublicSet_Ptr_O(t, x) \
    public: Q_INVOKABLE void _type##x(const QString& prop){registerPtrProperty(prop, &t::staticMetaObject);}

// t: type, x: property name
#define MetaPropertyPrivateSet_Ptr_List(t, x)  Q_SIGNALS: void notify##x(const QVariantList& i); \
    private: Q_PROPERTY(QVariantList x READ x WRITE x) \
    PropertyPrivateSet(QVariantList, x) \
    private: Q_INVOKABLE void _type##x(const QString& prop){registerPtrProperty(prop, &t::staticMetaObject);} \
    void append##t(t* i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.append(v);}} \
    void insert##t(int ind, t* i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.insert(ind,v);}} \
    void remove##t(t* i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.removeAll(v);}} \
    t* remove##t##At(int ind){t* i = _##x.at(ind).value<t*>(); QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.removeAll(v);} return i;} \
    Q_INVOKABLE void removeAll##t() {for (int i = _##x.length() - 1; i >= 0; i--) (_##x.at(i).value<t*>())->deleteLater(); _##x.clear();} \
    public: Q_INVOKABLE int count##t()const {return _##x.length();} \
    Q_INVOKABLE t* item##t##At(int i) {return _##x.at(i).value<t*>();} \
    Q_INVOKABLE bool item##t##Exist(t* i) const {QVariant v = QVariant::fromValue(i); if (v.isValid()) { return _##x.contains(v);} else return false;}


// t: type, x: property name
#define MetaPropertyProtectedSet_Ptr_List(t, x)  Q_SIGNALS: void notify##x(const QVariantList& i); \
    private: Q_PROPERTY(QVariantList x READ x WRITE x) \
    PropertyProtectedSet(QVariantList, x) \
    protected: Q_INVOKABLE void _type##x(const QString& prop){registerPtrProperty(prop, &t::staticMetaObject);} \
    void append##t(t* i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.append(v);}} \
    void insert##t(int ind, t* i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.insert(ind,v);}} \
    void remove##t(t* i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.removeAll(v);}} \
    t* remove##t##At(int ind){t* i = _##x.at(ind).value<t*>(); QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.removeAll(v);} return i;} \
    Q_INVOKABLE void removeAll##t() {for (int i = _##x.length() - 1; i >= 0; i--) (_##x.at(i).value<t*>())->deleteLater(); _##x.clear();} \
    public: Q_INVOKABLE int count##t()const {return _##x.length();} \
    Q_INVOKABLE t* item##t##At(int i) {return _##x.at(i).value<t*>();} \
    Q_INVOKABLE bool item##t##Exist(t* i) const {QVariant v = QVariant::fromValue(i); if (v.isValid()) { return _##x.contains(v);} else return false;}


// t: type, x: property name
#define MetaPropertyPublicSet_Ptr_List(t, x)  Q_SIGNALS: void notify##x(const QVariantList& i); \
    private: Q_PROPERTY(QVariantList x READ x WRITE x) \
    PropertyPublicSet(QVariantList, x) \
    public: Q_INVOKABLE void _type##x(const QString& prop){registerPtrProperty(prop, &t::staticMetaObject);} \
    Q_INVOKABLE void append##t(t* i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.append(v);}} \
    Q_INVOKABLE void insert##t(int ind, t* i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.insert(ind,v);}} \
    Q_INVOKABLE void remove##t(t* i){QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.removeAll(v);}} \
    Q_INVOKABLE t* remove##t##At(int ind){t* i = _##x.at(ind).value<t*>(); QVariant v = QVariant::fromValue(i); if (v.isValid()) { _##x.removeAll(v);} return i;} \
    Q_INVOKABLE int count##t()const {return _##x.length();} \
    Q_INVOKABLE void removeAll##t() {for (int i = _##x.length() - 1; i >= 0; i--) (_##x.at(i).value<t*>())->deleteLater(); _##x.clear();} \
    Q_INVOKABLE t* item##t##At(int i) {return _##x.at(i).value<t*>();} \
    Q_INVOKABLE bool item##t##Exist(t* i) const {QVariant v = QVariant::fromValue(i); if (v.isValid()) { return _##x.contains(v);} else return false;}


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

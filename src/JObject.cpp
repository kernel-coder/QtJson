#include "JObject.h"
#include <QJsonDocument>

JObject::JObject(QObject *parent) :
    QObject(parent)
{
}


void JObject::registerPtrProperty(const QString &prop, const QMetaObject *mo)
{
    if (!_ptrPropMap.contains(prop)) {
        _ptrPropMap.insert(prop, mo);
    }
}


const QMetaObject* JObject::metaObjectForProp(const QString &prop)
{
    if (!_ptrPropMap.contains(prop)) {
        QMetaObject::invokeMethod(this, QString(QString("_type") + prop).toStdString().c_str(),
                                  Qt::DirectConnection, Q_ARG(QString, prop));
    }

    return _ptrPropMap.value(prop, 0);
}


QVariant JObject::exportToVariant()
{
    QVariantMap map;
    const QMetaObject* mo = metaObject();
    int count = mo->propertyCount();
    for (int i = 0; i < count; i++) {
        QMetaProperty mp = mo->property(i);
        QString  name(mp.name());
        if (name == "objectName") continue;
        QVariant::Type type = mp.type();
        switch (type) {
            case QMetaType::QObjectStar: {
                JObject* child = property(mp.name()).value<JObject*>();
                if (child) {
                    map.insert(name, child->exportToVariant());
                }}
                break;
            case QVariant::List:{
                QVariantList newList;
                QVariantList list = property(mp.name()).toList();
                foreach (QVariant v, list) {
                    if (v.type() == QMetaType::User) {
                        JObject* child = v.value<JObject*>();
                        if (child) {
                            newList.append(child->exportToVariant());
                        }
                    }
                    else {
                        newList.append(v);
                    }
                }
                map.insert(name, newList);}
                break;
            default:
                {map.insert(name, property(mp.name()));}break;
        }
    }

    QVariant root(QVariant::Map);
    root.setValue(map);
    return root;
}


bool JObject::importFromVariant(const QVariant &v)
{
    if (v.type() != QVariant::Map) return false;

    QVariantMap map = v.toMap();
    const QMetaObject* mo = metaObject();
    int count = mo->propertyCount();

    if ( (count - 1) > map.count()) return false;

    for (int i = 0; i < count; i++) {
        QMetaProperty mp = mo->property(i);
        QString  name(mp.name());
        if (name == "objectName") continue;
        if (!map.contains(name)) return false;
        QVariant value = map[name];
        QVariant::Type type = mp.type();
        switch (type) {
            case QMetaType::QObjectStar: {
                    const QMetaObject* cmo = metaObjectForProp(name);
					if (cmo) {
                        JObject* child = qobject_cast < JObject* > (cmo->newInstance());
                        if (child) {
                            child->setParent(this);child->initAfterConstruct();
                            child->importFromVariant(value);child->initAfterImport();
							setProperty(mp.name(), QVariant::fromValue(child));
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
                }
                break;
            case QVariant::List:
                {QVariantList newList;
                QVariantList list = value.toList();
                const QMetaObject* cmo = metaObjectForProp(name);
                foreach (QVariant v, list) {
                    if (v.type() == QVariant::Map) {
                        JObject* child = cmo == 0? 0 : qobject_cast< JObject* >(cmo->newInstance());
                        if (child) {
                            child->setParent(this);child->initAfterConstruct();
                            child->importFromVariant(v);child->initAfterImport();
                            newList.append(QVariant::fromValue(child));
                        }
                        else {
							return false;
						}
                    }
                    else {
                        newList.append(v);
                    }
                }
                setProperty(mp.name(), newList);}
            break;
            default:
                {setProperty(mp.name(), value);}break;
        }
    }

    return true;
}


QByteArray JObject::exportToJson(bool indented)
{
    return QJsonDocument::fromVariant(exportToVariant()).toJson(indented ? QJsonDocument::Indented : QJsonDocument::Compact); //
}


bool JObject::importFromJson(const QByteArray &json)
{
    return importFromVariant(QJsonDocument::fromJson(json).toVariant());
}


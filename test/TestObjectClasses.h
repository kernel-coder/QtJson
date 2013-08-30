#ifndef TESTOBJECTCLASSES_H
#define TESTOBJECTCLASSES_H
#include "JObject.h"
#include <QStringList>

class Address : public JObject {
    Q_OBJECT
public:
    Q_INVOKABLE explicit Address(QObject* parent = 0) : JObject(parent){}

    MetaPropertyPublicSet(QString, country)
    MetaPropertyPublicSet(QString, city)
    MetaPropertyPublicSet(QString, zip)
};


class Person : public JObject {
    Q_OBJECT
public:
    Q_INVOKABLE explicit Person(QObject* parent = 0) : JObject(parent){}
    MetaPropertyPublicSet(QString, name)
    MetaPropertyPublicSet_Ptr(Address, address)
};


class Student : public Person {
    Q_OBJECT
public:
    Q_INVOKABLE explicit Student(QObject* parent = 0) : Person(parent){}
    MetaPropertyPublicSet(QStringList, courses)
};

class Teacher : public Person {
    Q_OBJECT
public:
    Q_INVOKABLE explicit Teacher(QObject* parent = 0) : Person(parent){}
    MetaPropertyPublicSet(QStringList, speciality)
};


class School : public JObject {
    Q_OBJECT
public:
    Q_INVOKABLE explicit School(QObject* parent = 0) : JObject(parent){}

    MetaPropertyPublicSet(QString, name)
    MetaPropertyPublicSet_Ptr(Address, address)
    MetaPropertyPublicSet_Ptr_List(Teacher, teachers)
    MetaPropertyPublicSet_Ptr_List(Student, students)
};

#endif // TESTOBJECTCLASSES_H

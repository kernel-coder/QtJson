Overview
======

Importing json into your custom class's instance and vice versa!
Json support added in Qt5. However, this utility codebase will let you import json data into you your class's instance and you can also get json from your class instance! Please take a look at the sample!


Dependencies
======
Only to Qt5


How to Use?
======
1) Include the QtJson.pri file into your pro file
2) Create your class inhering the JObject class
3) Your class's default constructor shuold be marked with Q_INVOKABLE
4) Add properties to your class using the 3 macros --  MetaPropertyPublicSet, MetaPropertyPublicSet_Ptr, MetaPropertyPublicSet_Ptr_List -- this way you will see getter/setter with the same name as your property name you said in the MetaPropertyPublicSet* macro.
  i) Use MetaPropertyPublicSet to declare properites of built-in types (QString, int and such, that is, all the types in QMetaType::Type enum)
  ii) Use MetaPropertyPublicSet_Ptr to declare property of your other JObject base custom types.
  iii) Use MetaPropertyPublicSet_Ptr_List to declare property of list type of your other JObject base custom types. You will see a append<PropertyName> method in the class to append an item in the list of that particular type.
See the test project in test directory for a bit more details.


Usage
======
Classes that we'll use for the sample code following ---

	// All the classes that we need for our sample!
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


Improting JSON to your class's instance!
======
    // Importing json into your custom instance
    QByteArray jsonInput = "{\"address\": {"
                "\"city\": \"Rajshahi\","
                "\"country\": \"Bangladesh\","
                "\"zip\": \"6402\"},"
            "\"name\": \"Kernel Coders Lab --- www.kernelcoderslab.com\","
            "\"students\": [{"
                    "\"address\": {"
                        "\"city\": \"Natore\","
                        "\"country\": \"Bangladesh\","
                        "\"zip\": \"6200\"},"
                    "\"courses\": ["
                        "\"C/C++\","
                        "\"Algorithms\"],"
                    "\"name\": \"Shahazan Ali\"}],"
            "\"teachers\": [{"
                    "\"address\": {"
                        "\"city\": \"Dhaka\","
                        "\"country\": \"Bangladesh\","
                        "\"zip\": \"1000\"},"
                    "\"name\": \"Mirza Alam\","
                    "\"speciality\": ["
                        "\"C/C++\","
                        "\"Algorithms\"]}]}";

    School school;
    school.importFromJson(jsonInput);
    qDebug() <<"School name: " << school.name();
    qDebug() <<"School address's city: " << school.address()->city();
    qDebug() <<"Teacer name: " << school.itemTeacherAt(0)->name();
    qDebug() <<"Student name: " << school.itemStudentAt(0)->name();
	

Exporting JSON from your class's instance!
======
    School school;
    school.name("Kernel Coders Lab --- www.kernelcoderslab.com");
    Address* address = new Address(&school);
    address->country("Bangladesh");address->city("Rajshahi");address->zip("6402");
    school.address(address);

    Teacher* teacher = new Teacher(&school);
    teacher->name("Mirza Alam");teacher->speciality(QStringList() << "C/C++" << "Algorithms");
    address = new Address(teacher);
    address->country("Bangladesh");address->city("Dhaka");address->zip("1000");
    teacher->address(address);
    school.appendTeacher(teacher);

    Student* student = new Student(&school);
    student->name("Shahazan Ali");student->courses(QStringList() << "C/C++" << "Algorithms");
    address = new Address(student);
    address->country("Bangladesh");address->city("Natore");address->zip("6200");
    student->address(address);
    school.appendStudent(student);

    QByteArray json = school.exportToJson();
    qDebug() << json;

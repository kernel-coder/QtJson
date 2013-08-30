#include <QCoreApplication>
#include "TestObjectClasses.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    School* school = new School(&a);
    school->name("Kernel Coders Lab --- www.kernelcoderslab.com");
    Address* address = new Address(school);
    address->country("Bangladesh");address->city("Rajshahi");address->zip("6402");
    school->address(address);

    Teacher* teacher = new Teacher(school);
    teacher->name("Mirza Alam");teacher->speciality(QStringList() << "C/C++" << "Algorithms");
    address = new Address(teacher);
    address->country("Bangladesh");address->city("Dhaka");address->zip("1000");
    teacher->address(address);
    school->appendTeacher(teacher);

    Student* student = new Student(school);
    student->name("Shahazan Ali");student->courses(QStringList() << "C/C++" << "Algorithms");
    address = new Address(student);
    address->country("Bangladesh");address->city("Natore");address->zip("6200");
    student->address(address);
    school->appendStudent(student);

    QByteArray json = school->exportToJson();
    qDebug() << json;



    // Importing json into your custom instance
    QByteArray jsonInput = "\"{\"address\": {"
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
                        "\"Algorithms\"]}]}\"";

    School* school = new School(&a);
    school->importFromJson(jsonInput);
    qDebug() <<"School name: " << school->name();
    qDebug() <<"School address's city: " << school->address()->city();

    return a.exec();
}

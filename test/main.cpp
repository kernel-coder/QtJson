#include <QCoreApplication>
#include "TestObjectClasses.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
{
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
}

{
    // Exporting json into your custom instance
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
}

    return a.exec();
}

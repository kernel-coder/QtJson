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
4) Add properties to your class using the macros --  
  i) Use MetaPropertyPublicSet to declare properites of built-in types (QString, int and such, that is, all the types in QMetaType::Type enum)
  ii) Use MetaPropertyPublicSet_Ptr to declare property of your other JObject base custom types.
  iii) Use MetaPropertyPublicSet_Ptr_List to declare property of list type of your other JObject base custom types. You will see a append<PropertyName> method in the class to append an item in the list of that particular type.
See the test project in test directory for a bit more details.
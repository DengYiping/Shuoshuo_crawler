# Shuoshuo_crawler
A crawler for one of the most popular social network. Work correctly on Mac os with Xcode.
It has trouble on Ubuntu to compile right now, if someone could help me to compile on Ubuntu 12.04 or 14.04, it will be great. Contact info: qq#: 649899819
#Disclaimer
This project's master branch will remains dormant untill the new MongoDB driver comes out. I personally spend too much time on the Mongo C++ Driver, yet it has a lot of issues. I will still continue update the progress in MySQL.

#Dependency
libjsoncpp: a fast json parser

libmongoclient: mongo-cxx-driver legacy version. Clone it from github and follow the instruction to compile it

libcurl

#MongoDB
MongoDB is used to store shuoshuos. It is stored in dbs.qq collections. Make sure you have this collections before start the program.

#Skey
Skey can be find in Chrome Console when you log in. It is start with "@"

#Usage
1.First enter the qq number as a seed for crawling.

2.Then enter your qq number.

3.Finally enter your current skey.

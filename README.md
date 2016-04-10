Shuoshuo_crawler
----------------
----------------
A new scala version has been released: https://github.com/DengYiping/shuoshuo_scala This version uses elasticsearch, and it is more easy to use, and more features will come later. I will still maintain this repo, but I will not add any new features to this free software. 


A crawler for one of the most popular social network. Work correctly on Mac os with Xcode. The troble is been solved and is stable under Mac OS X and Ubuntu. If you need data, you can contact me. If you are using this crawler, you should know that I am not resposible for your usage, even if I create this software for academic analysis. Crawling may increase the pressure on Tencent server, please be gentle. Contact info: qq#: 649899819

Disclaimer
----------
This project's master branch will no longer updated and remains dormant untill the new MongoDB driver comes out. This branch is stable under Mac OS X and Ubuntu.  I personally spend too much time on the Mongo C++ Driver, yet it has a lot of issues.(Looking forward to new driver's release). I will still continue update the progress in MySQL. MongoDB version is currently stable for Mac and linux user.

Dependency
----------
-libjsoncpp: a fast json parser

-libmongoclient: mongo-cxx-driver legacy version. Clone it from github and follow the instruction to compile it

-boost: the dependency of libmongoclient(that's why it has compile issue on Ubuntu). boost::regex is used as an alternative for std::regex, which is unstable under libc++.

-libcurl

MongoDB
--------
MongoDB is used to store shuoshuos. It is stored in dbs.qq collections. Make sure you have this collections before start the program.

Skey
----
Skey can be find in Chrome Console when you log in. It is start with "@"

Usage
------
1.First, enter the qq number as a seed for crawling.

2.Then, enter your qq number.

3.Third, enter your current skey. (please Baidu or Google "qq skey")

4.Last, enter the number of thread you want to create. If your machine is powerful enough, it should hold 50 thread easily. However, the larger the number, the more the pressure you will exert on the server. Please be careful.

My blog: www.geekinguniverse.com


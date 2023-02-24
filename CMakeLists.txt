cmake_minimum_required(VERSION 3.23)
project(VirtualSoc)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH  "/home/alex/Qt/6.4.1/gcc_64/lib/cmake")
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
find_package(SQLite3 REQUIRED)

add_executable(Server main.cpp DOB/sqlite3.c Users/User.cpp Users/User.h DOB/DOB.cpp DOB/DOB.h)
add_executable(Client client.cpp Interface/chatwindow.cpp Interface/chatwindow.h Interface/chatwindow.ui
        Interface/createpost.cpp Interface/createpost.h Interface/createpost.ui
        Interface/friendlist.cpp Interface/friendlist.h Interface/friendlist.ui
        Interface/loginwindow.cpp Interface/loginwindow.h Interface/loginwindow.ui
        Interface/mainwindow.cpp Interface/mainwindow.h Interface/mainwindow.ui
        Interface/window.cpp Interface/window.h)

target_link_libraries(Client
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

target_link_libraries(Server SQLite::SQLite3)
find_package(Threads REQUIRED)
target_link_libraries(Server Threads::Threads )
target_link_libraries(Server ${CMAKE_DL_LIBS})
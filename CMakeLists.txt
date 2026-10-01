cmake_minimum_required(VERSION 3.16)

project(Projet_Interface_Graphique_2025 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        acceuil.cpp
        acceuil.h
        acceuil.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Projet_Interface_Graphique_2025
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        avion.h avion.cpp avion.ui
        compagnie.h compagnie.cpp compagnie.ui
        passager.h passager.cpp passager.ui
        reservation.h reservation.cpp reservation.ui
        vol.h vol.cpp vol.ui
        connexion.h connexion.cpp
        admin.h admin.cpp admin.ui
        ressources/icons.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Projet_Interface_Graphique_2025 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Projet_Interface_Graphique_2025 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Projet_Interface_Graphique_2025
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Projet_Interface_Graphique_2025 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Projet_Interface_Graphique_2025 PRIVATE Qt${QT_VERSION_MAJOR}::Sql) 

# Extrait à ajouter dans CMakeLists.txt

# Copier la DLL MySQL dans le dossier de l'exécutable après la compilation
add_custom_command(TARGET Projet_Interface_Graphique_2025 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/dependencies/mysql/libmysql.dll"
    "$<TARGET_FILE_DIR:Projet_Interface_Graphique_2025>"
)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Projet_Interface_Graphique_2025)
endif()
set_target_properties(Projet_Interface_Graphique_2025 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Projet_Interface_Graphique_2025
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Projet_Interface_Graphique_2025)
endif()

cmake_minimum_required(VERSION 3.19)
project(CMEditor3D LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Core
    Widgets
    OpenGL
    OpenGLWidgets
    3DCore
    3DExtras
    3DRender
    3DInput
)

qt_standard_project_setup()

qt_add_executable(CMEditor3D
    WIN32 MACOSX_BUNDLE
    main.cpp
    CMeditor.cpp
    CMeditor.h
    CMeditor.ui
    glwidget.cpp
    glwidget.h
)

target_link_libraries(CMEditor3D
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::OpenGL
        Qt::OpenGLWidgets
        Qt::3DCore
        Qt::3DExtras
        Qt::3DRender
        Qt::3DInput
)

include(GNUInstallDirs)

install(TARGETS CMEditor3D
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET CMEditor3D
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

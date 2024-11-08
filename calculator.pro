QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FSM/executerpn.cpp \
    FSM/infixtorpn.cpp \
    FSM/tokenizer.cpp \
    Token/Operation/divide.cpp \
    Token/Operation/minus.cpp \
    Token/Operation/multiply.cpp \
    Token/Operation/operation.cpp \
    Token/Operation/plus.cpp \
    Token/Operation/power.cpp \
    Token/closeparenthesis.cpp \
    Token/factories.cpp \
    Token/itoken.cpp \
    Token/number.cpp \
    Token/openparenthesis.cpp \
    calculator.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    FSM/executerpn.h \
    FSM/infixtorpn.h \
    FSM/tokenizer.h \
    Token/Operation/divide.h \
    Token/Operation/minus.h \
    Token/Operation/multiply.h \
    Token/Operation/operation.h \
    Token/Operation/plus.h \
    Token/Operation/power.h \
    Token/closeparenthesis.h \
    Token/factories.h \
    Token/itoken.h \
    Token/number.h \
    Token/openparenthesis.h \
    calculator.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

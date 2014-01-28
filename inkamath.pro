TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    pmath.cpp

HEADERS += \
    best_promotion.hpp \
    expression.hpp \
    expression_dict.hpp \
    expression_visitor.hpp \
    interpreter.hpp \
    mapstack.hpp \
    matrix.hpp \
    numeric_interface.hpp \
    pmath.hpp \
    reference.hpp \
    sequence.hpp \
    stdworkspace.hpp \
    token.hpp \
    workspace.hpp \
    workspace_manager.hpp

TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    diffusion_eq_solvers.cpp \
    solve_tridiagonal_matrix_eq.cpp \
    output_data.cpp

LIBS += -larmadillo -lblas -llapack

HEADERS += \
    solve_tridiagonal_matrix_eq.h \
    diffusion_eq_solvers.h \
    output_data.h

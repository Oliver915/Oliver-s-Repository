TEMPLATE = subdirs

SUBDIRS += \
    src/protobuf \
    src/gui \
    src/app

app.depends = gui


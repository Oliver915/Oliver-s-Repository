TEMPLATE = subdirs

SUBDIRS += \
    src/protobuf \
    src/gui \
    src/app

gui.depends = protobuf
app.depends = gui protobuf

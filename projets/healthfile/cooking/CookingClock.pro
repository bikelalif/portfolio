#-------------------------------------------------
#
# Project created by QtCreator 2013-06-06T18:40:02
#
#-------------------------------------------------

QT       += core gui

mac {
    # for unified toolbar
	lessThan(QT_MAJOR_VERSION, 6): QT += macextras
	# Don't freak out when system upgrades
	CONFIG+=sdk_no_version_check
}
# includes for QT5: widgets and multimedia (for QSoundEffect)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = CookingClock
TEMPLATE = app

# no debug output in release mode: qDebug(...) will be ignored
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

# MODULES: Classes or Modules (.h/.cpp)
MODULES = QCountDown \
    QLCDMouseListener \
	QAppSettings \
	QEditableValue \
	MainWindow

for(f, MODULES){
    HEADERS += $${f}.h
	SOURCES += $${f}.cpp
	ALLSOURCES += $${f}.h $${f}.cpp
}

# Mains: main program (.cpp)
MAINS = main

for(f, MAINS){
    SOURCES += $${f}.cpp
	ALLSOURCES += $${f}.cpp
}

# GUIs
FORMS    += MainWindow.ui \
    QEditableValue.ui

# Resource files
RESOURCES += \
    CookingResources.qrc

# Translation files for "lupdate" (see translate.target)
TRANSLATIONS += \
    CookingResources_fr.ts \
	CookingResources_en.ts

# Compiled Translation files for "lrelease" (see compile_translation.target)
TRANSLATIONS_RES += \
    CookingResources_fr.qm \
	CookingResources_en.qm

# Other files to be included in archive
OTHER_FILES += $${TARGET}.icns \
    $${TARGET}.ico \
	$${TARGET}.rc \
	icons/audio_file-32.png \
	icons/cancel-32.png \
	icons/dashboard-32.png \
	icons/down-32.png \
	icons/mute-32.png \
	icons/pause-32.png \
	icons/play-32.png \
	icons/repeat-32.png \
	icons/stop-32.png \
	icons/synchronize-32.png \
	icons/up-32.png \
	icons/volume_up-32.png \
	icons/info-32.png \
	icons/clock-512.png \
	sounds/Glass.wav \
	sounds/Tink.wav \
	Doxyfile
# -----------------------------------------------------------------------------
# Platform specific options
# -----------------------------------------------------------------------------

mac {
    # icon for mac os
	ICON = $${TARGET}.icns
}

win32 {
    # icon for windows
	RC_FILE = $${TARGET}.rc
}

# There is no specific icons for Linux platform (except in your desktop config
# files), but you can still setup the mainwindow icon with :
# void setWindowIcon(const QIcon &icon);
# which will then be used in any "about" dialog box.

# -----------------------------------------------------------------------------
# Extra tools
# -----------------------------------------------------------------------------

# Listing tools
A2PS = a2ps-utf8 -2 --file-align=fill --line-numbers=1 --font-size=10 \
--chars-per-line=100 --tabsize=4 --pretty-print --highlight-level=heavy \
--prologue="gray"

PS2PDF = ps2pdf -dPDFX=true -sPAPERSIZE=a4
# Documentation tool
DOCTOOL = doxygen
# Year-month-day Date
unix {
    DATE = $$system(date +%Y-%m-%d)
}
win32 {
    DATE = $$system("for /F \"usebackq tokens=1,2,3 delims=/ \" %a in \
	(`date /t`) do @echo %c-%b-%a")
}

# Archive format
ARCHIVER = zip
ARCHOPT =
ARCHEXT = zip


# directories for listings and archives
LISTDIR = listings
ARCHDIR = archives

# -----------------------------------------------------------------------------
# Extra targets for generated makefile
# -----------------------------------------------------------------------------

# Generate translation files --------------------------------------------------
translate.target = translate
translate.depends = $${ALLSOURCES}
translate.commands = lupdate $${TARGET}.pro

compile_translation.target = compile_translation
compile_translation.depends = $${TRANSLATIONS}
compile_translation.commands = lrelease $${TARGET}.pro

# Generate documentation from sources -----------------------------------------
doc.target = doc
doc.depends = $${ALLSOURCES}
doc.commands = (cat Doxyfile; echo "INPUT = $?") | $${DOCTOOL} -

# linking .h to .hpp for correct printing highlight needed by a2ps ------------
for(f, HEADERS){
    LINK_ACTION+="ln -fs $${f} $${f}pp; "
	CPPHEADERS+="$${f}pp "
}
links.target = links
links.commands = $$LINK_ACTION
links.depends = $$HEADERS

# unlinking .hpp --------------------------------------------------------------
for(f, HEADERS){
    UNLINK_ACTION+="rm -f $${f}pp; "
}
unlinks.target = unlinks
unlinks.commands = $$UNLINK_ACTION

# Postscript listing generation with A2PS -------------------------------------
listings.target = listings
listings.commands = mkdir $$LISTDIR

for(f, MODULES){
    PRINTSOURCES+= $${f}.hpp $${f}.cpp
}
for(f, EXTRAHEADERS){
    PRINTSOURCES+= $${f}.hpp
}
for(f, MAINS){
    PRINTSOURCES+= $${f}.cpp
}
ps.target = ps
ps.commands = $$A2PS --output $${LISTDIR}/$${TARGET}.ps $${PRINTSOURCES}
ps.depends = links listings

# PDF listing generation from Postscript --------------------------------------
pdf.target = pdf
pdf.commands = $$PS2PDF $${LISTDIR}/$${TARGET}.ps $${LISTDIR}/$${TARGET}.pdf
pdf.depends = ps

# Timestamped archive generation ----------------------------------------------
archives.target = archives
archives.commands = mkdir $$ARCHDIR

archive.target = archive
archive.commands = $$ARCHIVER $$ARCHOPT $${ARCHDIR}/$${TARGET}-$${DATE}.$${ARCHEXT} \
$${ALLSOURCES} $${TARGET}.pro $${FORMS} $${RESOURCES} \
$${OTHER_FILES} $${TRANSLATIONS} $${TRANSLATIONS_RES}
archive.depends = archives

# Cleaning doc, listing and archives ------------------------------------------
myclean.target = myclean
myclean.commands = rm -rf $${LISTDIR}/*~ $${LISTDIR}/$${TARGET}.ps \
$${LISTDIR}/$${TARGET}.pdf doc
myclean.depends = unlinks

# Adding extra clean to regular clean -----------------------------------------
# adding clean as extra targets when there is already a clean target generated
# by QT just adds a second clean target which is also executed when invoking
# make clean
clean.depends = myclean

# Extra targets to be added in the makefile -----------------------------------
QMAKE_EXTRA_TARGETS += doc listings ps pdf archives archive myclean links \
unlinks clean translate compile_translation

# -----------------------------------------------------------------------------
# QT Information (comment if not needed)
# -----------------------------------------------------------------------------
message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(Qt resources can be found in the following locations:)
message(Documentation: $$[QT_INSTALL_DOCS])
message(Header files: $$[QT_INSTALL_HEADERS])
message(Libraries: $$[QT_INSTALL_LIBS])
message(Binary files (executables): $$[QT_INSTALL_BINS])
message(Plugins: $$[QT_INSTALL_PLUGINS])
message(Data files: $$[QT_INSTALL_DATA])
message(Translation files: $$[QT_INSTALL_TRANSLATIONS])
message(Settings: $$[QT_INSTALL_SETTINGS])
message(Examples: $$[QT_INSTALL_EXAMPLES])
message(Demonstrations: $$[QT_INSTALL_DEMOS])

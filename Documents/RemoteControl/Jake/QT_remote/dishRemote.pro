QT       += core gui
QT       += serialport
QT += core
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
 else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourses.qrc
# Libssh:
#LIBS += -L$$PWD/'../../../../../Program Files (x86)/libssh/lib/' -lssh.dll
INCLUDEPATH += $$PWD/../../../../QtOs/6.5.0/
#DEPENDPATH += $$PWD/'../../../../../Program Files (x86)/libssh/include'

#win32: LIBS += -L$$PWD/../../../../src/vcpkg/vcpkg/installed/x64-windows/lib/ -llibssl

INCLUDEPATH += $$PWD/../../../../src/vcpkg/vcpkg/installed/x64-windows/include
DEPENDPATH += $$PWD/../../../../src/vcpkg/vcpkg/installed/x64-windows/include
INCLUDEPATH += C:/Users/jacob.montgomery/AppData/Local/Programs/Python/Python310/include
LIBS += C:/Users/jacob.montgomery/AppData/Local/Programs/Python/Python310/libs/python3.lib
#LIBS += C:/QtOs/6.5.0/msvc2019_64/lib/Qt6Widgets.lib
#LIBS += C:/QtOs/6.5.0/mingw_64/lib/*


DISTFILES += \
    SSH/IP_only/.git/COMMIT_EDITMSG \
    SSH/IP_only/.git/FETCH_HEAD \
    SSH/IP_only/.git/HEAD \
    SSH/IP_only/.git/ORIG_HEAD \
    SSH/IP_only/.git/config \
    SSH/IP_only/.git/description \
    SSH/IP_only/.git/hooks/applypatch-msg.sample \
    SSH/IP_only/.git/hooks/commit-msg.sample \
    SSH/IP_only/.git/hooks/post-update.sample \
    SSH/IP_only/.git/hooks/pre-applypatch.sample \
    SSH/IP_only/.git/hooks/pre-commit.sample \
    SSH/IP_only/.git/hooks/pre-push.sample \
    SSH/IP_only/.git/hooks/pre-rebase.sample \
    SSH/IP_only/.git/hooks/prepare-commit-msg.sample \
    SSH/IP_only/.git/hooks/update.sample \
    SSH/IP_only/.git/index \
    SSH/IP_only/.git/info/exclude \
    SSH/IP_only/.git/logs/HEAD \
    SSH/IP_only/.git/logs/refs/remotes/origin/HEAD \
    SSH/IP_only/.git/logs/refs/remotes/origin/master \
    SSH/IP_only/.git/objects/03/997997685f76e65f6cc968ba48949c07c1f24f \
    SSH/IP_only/.git/objects/0c/f2b8632bd200257286d28b277650a93b1921f8 \
    SSH/IP_only/.git/objects/14/1c0d93db1f90d046de842ffdfd7d2114cbbf11 \
    SSH/IP_only/.git/objects/18/772a05ad8727916e7992733151c565b5f11c2c \
    SSH/IP_only/.git/objects/19/34b580e4826c017e8436c02e6511f741063098 \
    SSH/IP_only/.git/objects/2c/54ee2d3cec95e45c53e33ee79602d799b784bb \
    SSH/IP_only/.git/objects/2d/fdd3757716dd05032f951a4c9e3d203e79893e \
    SSH/IP_only/.git/objects/38/e0700be06a972817f83468f2a7c90df983addd \
    SSH/IP_only/.git/objects/3a/ad076c4d262e1b924b8ac4862b3d0b02dc94ed \
    SSH/IP_only/.git/objects/3e/bebc5c56a9f3297a7eac44d6ad95c71793c980 \
    SSH/IP_only/.git/objects/49/e253100a4a7d9d406028ef0fec936c3a349cc5 \
    SSH/IP_only/.git/objects/51/156038ac3f2d0545570c7fc36da5deea36b1a7 \
    SSH/IP_only/.git/objects/51/9810029668669978974d936b91477abae57ea2 \
    SSH/IP_only/.git/objects/53/0f6c9c6a5fdc370dc7214638e573db1d04c0f8 \
    SSH/IP_only/.git/objects/53/2d5531fd8681cf3dd58e2a44a541fdb63d1496 \
    SSH/IP_only/.git/objects/53/d449ae50d43ada436b972d4bb5dadb08738595 \
    SSH/IP_only/.git/objects/56/f31444036716f4d5b6e6b332c0ecc4d5ceb1fd \
    SSH/IP_only/.git/objects/5b/a7c68bff806c512d959fb05b08b95e0236ae08 \
    SSH/IP_only/.git/objects/6d/5841eb1f85dbd5f6969de3d6d6dcc05f574bda \
    SSH/IP_only/.git/objects/72/c5c814647dcad100f08b55f2b3b10092e12edb \
    SSH/IP_only/.git/objects/86/59072118d1afd5eb3dedd19e15a82eeb0cccb2 \
    SSH/IP_only/.git/objects/87/5a4db8f129fc271e6fd3e5dd92da8e9358a644 \
    SSH/IP_only/.git/objects/8c/72b3029c0131585a18568a5882941689d7111e \
    SSH/IP_only/.git/objects/8d/571fea1267e88f2c23cebce862d27842b7ff46 \
    SSH/IP_only/.git/objects/ad/f59350ed70b048ff25da93fccfdcb80723ddc5 \
    SSH/IP_only/.git/objects/b4/0642c007b370527bbd7b87d412477619bb002d \
    SSH/IP_only/.git/objects/bb/0a179fb39e4520cb9a90ae5bcd218ec811e8ab \
    SSH/IP_only/.git/objects/c0/fa30a05bdf7c6c5a8ede13f7b6bcbffdd0b034 \
    SSH/IP_only/.git/objects/c7/334987ed7379dd50fe1741b944f5c64588cee6 \
    SSH/IP_only/.git/objects/cc/3f30080c385e416e572f9ea85cb01c2a81ad1c \
    SSH/IP_only/.git/objects/db/9a1b40f33ec07f9a629cebf123fb12b1c84b78 \
    SSH/IP_only/.git/objects/de/6b134aa65b05ddf01c551ebe9b7ed5d2f6ab59 \
    SSH/IP_only/.git/objects/e5/06d2dd3ab7865c11f9cec9aee00b3de7c4efdc \
    SSH/IP_only/.git/objects/e5/24676b0983fdc8dead18fb3694f5fc64695407 \
    SSH/IP_only/.git/objects/ee/87b9ead5935d2c3f7d254959f51d3bcd6537b2 \
    SSH/IP_only/.git/objects/f5/8791294f7f23843dee7df156054697c9e3f67e \
    SSH/IP_only/.git/objects/fe/a88a28f9a3846fc7974c5b31cb66c69194c8e7 \
    SSH/IP_only/.git/objects/pack/pack-8edffeea37a419acaa417c789acdf9ea1f765fe6.idx \
    SSH/IP_only/.git/objects/pack/pack-8edffeea37a419acaa417c789acdf9ea1f765fe6.pack \
    SSH/IP_only/.git/packed-refs \
    SSH/IP_only/.git/refs/remotes/origin/HEAD \
    SSH/IP_only/.git/refs/remotes/origin/master \
    SSH/IP_only/.gitignore \
    SSH/IP_only/README \
    SSH/IP_only/__pycache__/sgs_lib.cpython-310.pyc \
    SSH/IP_only/__pycache__/sgs_lib.cpython-34.pyc \
    SSH/IP_only/base.txt \
    SSH/IP_only/cert.pem \
    SSH/IP_only/command.txt \
    SSH/IP_only/dhcp_restart.sh \
    SSH/IP_only/duo_remote.sh \
    SSH/IP_only/edit_cs.sh \
    SSH/IP_only/get_auto_suggestion.py \
    SSH/IP_only/get_img.sh \
    SSH/IP_only/get_mdu_mode.py \
    SSH/IP_only/get_multicasts.py \
    SSH/IP_only/get_stb_information.py \
    SSH/IP_only/get_tuner_usage_v2.py \
    SSH/IP_only/get_whole_home_devices_info.py \
    SSH/IP_only/hopper_remote.sh \
    SSH/IP_only/key.pem \
    SSH/IP_only/log_cec \
    SSH/IP_only/log_cec_full \
    SSH/IP_only/remote_ip_only.sh \
    SSH/IP_only/remote_prod.sh \
    SSH/IP_only/services_list_xip.py \
    SSH/IP_only/settops_prod.csv \
    SSH/IP_only/sgs.py \
    SSH/IP_only/sgs_ae.py \
    SSH/IP_only/sgs_lib.py \
    SSH/IP_only/sgs_lib.py2 \
    SSH/IP_only/sgs_pair.py \
    SSH/IP_only/sgs_pair_simple.py \
    SSH/IP_only/sgs_remote.py \
    SSH/IP_only/sgs_remote_simple.py \
    SSH/IP_only/sgs_simple.py \
    SSH/IP_only/sgs_simple/README \
    SSH/IP_only/sgs_simple/cert.pem \
    SSH/IP_only/sgs_simple/get_stb_information.py \
    SSH/IP_only/sgs_simple/key.pem \
    SSH/IP_only/sgs_simple/sgs_pair_simple.py \
    SSH/IP_only/sgs_simple/sgs_remote_simple.py \
    SSH/IP_only/stb.txt \
    SSH/IP_only/stb_getlogs \
    SSH/IP_only/stb_grep \
    SSH/IP_only/stb_mount \
    SSH/IP_only/stb_search.py \
    SSH/IP_only/stb_update \
    SSH/IP_only/stop_stb \
    SSH/IP_only/tnet_nfs \
    SSH/IP_only/wally_remote.sh

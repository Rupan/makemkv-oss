cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(makemkv VERSION 1.14.3)

list(APPEND CMAKE_PREFIX_PATH "$ENV{HOME}/matroska/lib/cmake")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)
find_package(EXPAT REQUIRED)
find_package(EBML REQUIRED)
find_package(Matroska REQUIRED)

find_library(RT_LIBRARY rt)


set(libdriveio_SOURCES
	libdriveio/src/infolist.cpp
	libdriveio/src/scsihlp.cpp
	libdriveio/src/srlist.cpp
	libdriveio/src/stdquery.cpp
	libdriveio/src/tipclient.cpp
	libdriveio/src/tipcommon.cpp
	libdriveio/src/tipserver.cpp
	libdriveio/src/drives/pioneer.cpp
	libdriveio/src/drives/xboxhddvd.cpp
)

set(libdriveio_PUBLIC_HEADERS
	libdriveio/inc/driveio/driveio.h
	libdriveio/inc/driveio/scsicmd.h
	libdriveio/inc/driveio/scsihlp.h
)

set(libdriveio_PRIVATE_HEADERS
	libdriveio/inc/lgpl/tcpip.h
)

add_library(driveio SHARED ${libdriveio_SOURCES} ${libdriveio_PUBLIC_HEADERS} ${libdriveio_PRIVATE_HEADERS})
target_include_directories(driveio PUBLIC libdriveio/inc)
set_target_properties(driveio PROPERTIES VERSION "${PROJECT_VERSION}" SOVERSION 0)
target_link_options(driveio PRIVATE LINKER:-z,defs)


add_library(mmbd SHARED
	libmmbd/src/marmmbd.cpp
	libmmbd/src/nstring.cpp
	libmmbd/src/mmbd.cpp
	libmmbd/src/mmconn.cpp
	libmmbd/src/mmbdipc.cpp
	libmmbd/src/utf8.cpp
	libmmbd/src/aacs.cpp
	libmmbd/src/bdplus.cpp
	libmmbd/src/crypto_ossl.cpp
	makemkvgui/src/client.cpp
	makemkvgui/src/marshall.cpp
	makemkvgui/src/api_posix.cpp
	makemkvgui/src/api_linux.cpp
	makemkvgui/src/sem_posix.cpp
	makemkvgui/src/spawn_posix.cpp
	sstring/src/sstring.cpp
	libdriveio/src/srlist.cpp
	makemkvgui/inc/lgpl/aproxy.h
	libmmbd/inc/libmmbd/mmbd.h
	libdriveio/inc/driveio/driveio.h
)
target_include_directories(mmbd PRIVATE
	makemkvgui/inc
	libmmbd/inc
	libdriveio/inc
	libmakemkv/inc
	sstring/inc
	libabi/inc
)

set_target_properties(mmbd PROPERTIES VERSION "${PROJECT_VERSION}" SOVERSION 0)

# TODO: --enable-noec  use private ECDSA code
# TODO: add --version-script=libmmbd/src/libmmbd.vers
target_link_libraries(mmbd ${RT_LIBRARY} Threads::Threads OpenSSL::Crypto)
target_link_options(mmbd PRIVATE LINKER:-z,defs)


# Need to install libebml-dev libmatroska-dev then link with ebml and matroska
add_library(makemkv SHARED
	libabi/src/httplinux.cpp
	libabi/src/libm.c
	libabi/src/ossl_aes.c
	libabi/src/ossl_ec.c
	libabi/src/ossl_sha.c
	libabi/src/sys_linux.c
	libabi/src/xpat.c
	libabi/src/zlib.c
	libffabi/src/audio_convert.c
	libffabi/src/audio_mix.c
	libffabi/src/audio_mix_matrix.c
	libffabi/src/ffabi.c
	libffabi/src/log.c
	libffabi/src/mlp.c
	libmakemkv/src/ebmlwrite.cpp
	libmakemkv/src/libmkv.cpp
	libmakemkv/src/stdstring.cpp
	libmakemkv/src/version.cpp
	libmakemkv/src/world.cpp
	makemkvgui/src/api_linux.cpp
	makemkvgui/src/spawn_posix.cpp
	sstring/src/sstring.cpp
	# headers...
	libabi/inc/lgpl/httpabi.h
)
target_include_directories(makemkv PRIVATE
	libmakemkv/inc
	sstring/inc
	makemkvgui/inc
	libabi/inc
	libffabi/inc
)

set_target_properties(makemkv PROPERTIES VERSION "${PROJECT_VERSION}" SOVERSION 1)
target_link_libraries(makemkv OpenSSL::Crypto ZLIB::ZLIB EXPAT::EXPAT EBML::ebml Matroska::matroska avcodec avutil)
target_link_options(makemkv PRIVATE LINKER:-z,defs)
target_compile_definitions(makemkv PRIVATE -D_linux_ -D_GNU_SOURCE -D_REENTRANT)


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
# find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5DBus CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)

add_custom_command(OUTPUT image_data.o
	COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && ld -m elf_x86_64 -r -b binary -z noexecstack -o ${CMAKE_CURRENT_BINARY_DIR}/image_data.o makemkvgui/bin/image_data.bin
)

add_executable(makemkv_bin
	makemkvgui/src/aboutbox.cpp
	makemkvgui/src/client.cpp
	makemkvgui/src/dirselectbox.cpp
	makemkvgui/src/logic.cpp
	makemkvgui/src/logtext.cpp
	makemkvgui/src/main.cpp
	makemkvgui/src/nativefiledialog.cpp
	makemkvgui/src/mainwnd.cpp
	makemkvgui/src/marshall.cpp
	makemkvgui/src/progress.cpp
	makemkvgui/src/scsiinfo.cpp
	makemkvgui/src/settingdlg.cpp
	makemkvgui/src/uisync.cpp
	makemkvgui/src/viteminfo.cpp
	makemkvgui/src/margui.cpp
	makemkvgui/src/backupdlg.cpp
	makemkvgui/src/lstring.cpp
	makemkvgui/src/notify.cpp
	makemkvgui/src/str/en_utf16.cpp
	makemkvgui/src/image.cpp
	makemkvgui/src/abutton.cpp
	makemkvgui/src/lineeditk.cpp
	makemkvgui/src/dvdbox.cpp
	makemkvgui/src/drivebox.cpp
	# Linux stuff...
	makemkvgui/src/api_posix.cpp
	makemkvgui/src/api_linux.cpp
	makemkvgui/src/sem_posix.cpp
	makemkvgui/src/spawn_posix.cpp
	makemkvgui/src/logic_posix.cpp
	makemkvgui/src/notify_linux.cpp
	makemkvgui/src/image_linux.cpp
	# extras
	sstring/src/sstring.cpp
	libdriveio/src/srlist.cpp
	image_data.o
)

target_include_directories(makemkv_bin PRIVATE
	libmakemkv/inc
	makemkvgui/inc
	sstring/inc
	libdriveio/inc
	libabi/inc
)

# /usr/bin/ld -m elf_x86_64 -r -b binary -z noexecstack -o tmp/image_data.o makemkvgui/bin/image_data.bin
target_compile_definitions(makemkv_bin PRIVATE -D_linux_ -D_GNU_SOURCE -D_REENTRANT)
target_link_libraries(makemkv_bin Qt5::Widgets Qt5::Gui Qt5::DBus Qt5::Core Threads::Threads ZLIB::ZLIB ${RT_LIBRARY})
target_link_options(makemkv_bin PRIVATE LINKER:-z,defs)

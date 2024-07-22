#
# This file is the testapp recipe.
#

SUMMARY = "Simple testapp application"
SECTION = "PETALINUX/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS += "dpkg"
SRC_URI = "file://testapp.c \
	   file://ddr.c \
	   file://ddr.h \
	   file://testapp.h \
	   file://i2c.c \
	   file://i2c.h \
	   file://spi.h \
	   file://spi.c \
	   file://uart.h \
	   file://uart.c \
	   file://ethernet.c \
	   file://ethernet.h \
	   file://registers.h \
	   file://registers.c \
	   file://AFDX_registers.c \
	   file://AFDX_registers.h \
	   file://core_configuration.h \
	   file://core_configuration.c \
	   file://crc_core.h \
	   file://crc_core.c \
	   file://can_registers.c \
	   file://can_registers.h \
	   file://Makefile \
		  "

S = "${WORKDIR}"

do_compile() {
	     oe_runmake
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 testapp ${D}${bindir}
}


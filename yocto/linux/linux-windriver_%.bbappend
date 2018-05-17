# Copyright (C) 2018 Node Graph Systems, Inc

DESCRIPTION_append += "apply kernel patches and modify kernel configurations."

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

PR_append = "ngs2"

SRC_URI[0001-onlyreboot_NOshutdown.patch.md5sum] = "b23b97bb1d5798d9b81e242ed0c14f70"
SRC_URI[0001-custom_kernel_fragment.cfg.md5sum] = "d13defd44d1720749e995f25a0fb35cb"

# Adding patch to prevent halt state "shutdown -h".  embedded system requires to reboot always
SRC_URI += " file://0001-onlyreboot_NOshutdown.patch"

# bitbake linux-yocto -c menuconfig  then bitbake linux-yocto -c diffconfig  generated file fragment.cfg
# Creating Custom kernel menu configuration change for enabling i2c_support
SRC_URI += " file://0001-custom_kernel_fragment.cfg"

# Copyright (C) 2018 Node Graph systems, Inc

DESCRIPTION_append += "Applying network connectivity patches and configuration files."

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

PR_append = "+ngs1"

SRC_URI[0001-Permissions_DNS_rndc.key.patch.md5sum] = "b5996b903245c0e901ae503a03dcce8d"

# Adding patch to prevent DNS fail at boot time.
SRC_URI += " file://0001-Permissions_DNS_rndc.key.patch"

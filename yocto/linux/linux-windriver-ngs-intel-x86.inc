TARGET_SUPPORTED_KTYPES_ngs-networkplane-intel-x86-32 = "standard preempt-rt tiny cgl secure"
KBRANCH_DEFAULT_standard_ngs-networkplane-intel-x86-32 = "standard/${KMACHINE}"

#add the depends of cdrtools-native to make sure it is
#always built to support the usb-image & iso-image UEFI 
#booting by default  without explicitly add the configure 
#option of "--enable-bootimage=iso"

DEPENDS_append_ngs-networkplane-intel-x86-32 = " cdrtools-native"

# A method to install/update for bzImage on a deployed target
KERNELLOADEREXTENSION_append_ngs-networkplane-intel-x86-32 = " kernel-grub"

do_install_append_ngs-networkplane-intel-x86() {
	rm -rf ${D}/lib/modules/${KERNEL_VERSION}/kernel/drivers/crypto
}

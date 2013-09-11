Qualcomm USB Host Driver version 2.0.5.3 for Windows 2000/XP/Server 2003/Vista

This readme covers important information regarding Qualcomm USB Host Driver
version 2.0.5.3 for Windows 2000, Windows XP, Windows Server 2003 and Windows
Vista.

Table of Contents

1. Installation Notes
2. Major Features
3. What's New in This Release
4. Known issues
5. Build Information

----------------------------------------------------------------------

1. INSTALLATION NOTES

Please refer to Qualcomm document 80-V4609-1 Rev J for detailed instructions on
driver installation. The aforesaid document is encloded in the driver package.

----------------------------------------------------------------------

2. MAJOR FEATURES

1) Major bug fixes for operations under Windows XP, backward compatible with
   Windows 2000. Support 64-bit Windows.

2) Introduced new solution to the Windows open handle issue. The solution makes
   the USB virtual/PNP COM port's behavior similar to that of a physical COM port
   when device is reset or disconnected.

3) The driver is re-designed to be reentrant, which may allow multiple device
   connections on Windows XP over a single USB hub. Please note, multiple connections
   on Windows 2000 or through multiple USB hubs on Windows XP may cause system
   crash unless the devices completely remove their USB serial number string
   from the USB descriptor.
 
4) Vitually eliminated use of global cancel spin lock. This not only boosts the
   performance of the whole system but also makes the current driver much faster
   from one USB transfer to another, thus makes short packet handling more efficient. 

5) The driver is designed to be running safe with Intel Hyper-Threading processor
   and multi-processor systems with Windows XP, and multi-processor systems with
   Windows 2000.

6) Added true resident mode to the driver. Users can configure the driver to be a
   true resident driver instead of a PNP driver at run-time via registry settings.
   This feature itend to provide the ultimate solution to all the issues caused by
   device reset/disconnection. Under the true-resident mode, the driver will maintain
   its virtual(PNP) COM port(s) at all times and thus try to make the virtual(PNP)
   COM port behave as same as a traditional/physical COM port when the device is
   disconnected or reset. For details, please refer to section 9.4.2 in Qualcomm
   document 80-V4609-1 Rev J. By default, the driver operates under PNP mode.

----------------------------------------------------------------------

3. What's New in This Release

1) Fixed a possible race condition during IRP completion. (2.0.5.1)

2) Removed registry setting for USB remote wakeup. (2.0.5.1)

3) Corrected the implementation of HS-USB byte padding to work around the HW bug.
   (2.0.5.1)

4) Added support for PID F005. (2.0.5.2)

5) Changed the port device type from FILE_DEVICE_UNKNOWN to FILE_DEVICE_SERIAL_PORT
   for better compatibility. (2.0.5.2)

6) Refined error handling for USB control transfer. (2.0.5.2)

7) Added support for PID 9012, 9013, 9016 and 9017. (2.0.5.3)

8) Added support for 1.8Mbps baudrate(2.0.5.3)
----------------------------------------------------------------------

4. KNOWN ISSUES:

   It's been observed that the Qualcomm USB driver could trigger bugs in older
   versions of McAfee mini-firewall driver mvstd5x.sys. McAfee has suggested
   that users obtain McAfee VirusScan patch 14 or later patches for bug fixes.

   Compilation flag QCSER_TARGET_XP should NOT be defined with this version due to
   unsolved issues with XP-specific function calls.

   Rarely, when the modem connection is up but the device is reset or disconnected/
   re-connected, modem application may not be able to talk to modem port. A workaround
   is to perform a second reset or re-connection of the device. It's also recommended
   that users obtain Mirosoft hotfix Q822112 to reduce the possibility of this problem.
   This problem is fixed in Windows XP SP2.

----------------------------------------------------------------------

5. BUILD INFORMATION:

   The following compilation flags are defined for customers to build the driver
   to debug various issues related to host and device, they are not recommended
   for other purposes.
      ENABLE_LOGGING
      QCSER_ENABLE_LOG_REC
      QCSER_DBGPRINT
      QCSER_DBGPRINT2
      QCSER_TARGET_XP

   IMPORTANT!!! To achieve best security and performance, all of the above features
   should be turned off for commercial distributions. The free build binaries are
   recommended for commercial distributions.

----------------------------------------------------------------------
Copyright (c) 2003-2008 QUALCOMM Incorporated
All rights reserved.

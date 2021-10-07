SYMANTEC LOCALISATION GROUP IRELAND

README.TXT--
Copyright 1994 Symantec Corp. All Rights Reserved.

NORTON COMMANDER
Version 4.5

Welcome to Norton Commander Version 4.5 !
------------------------------------------
Please read this document carefully, it contains important information not 
included in the documentation.

     Topics covered in this document include:

     * Files that come with Norton Commander 4.5
     * Compressing files from the Tree Panel
     * Internal Editor & Viewer
     * Password protected Compressed files
     * Cloning using SHARE.EXE
     * Filters
     * Viewers
     * Special Characters
     * Norton Commander Environment Variables
     * Limitations in Changing Drives
     * Datex.p File

Files that come with Norton Commander 4.5
-----------------------------------------

The following files are shipped on the diskettes for Norton Commander 
Version 4.5 :

Diskette 1 : Program Diskette
	install.exe	Install program
	4372ansi.set	Conversion table from CP437 to ANSI
	8502ansi.set	Conversion table from CP850 to ANSI
	ansi2437.set	Conversion table from ANSI to 437
	ansi2850.set	Conversion table from ANSI to 850
	nc.cfg		Configuration file for Filters and Viewers
	nc.exe		Norton Commander V4.5 Loader
	nc.hlp		Norton Commander 4.50 Help File
	nc.ico		Norton Commander 4.50 Icon
	ncedit.exe	Norton Commander 4.50 Editor
	ncmain.exe	Norton Commander 4.50 File Manager
	nczip.exe	Norton Commander 4.50 Compressor
	packer.exe	Norton Commander 4.50 Compressor Interpreter
	packer.set	Program file for PACKER.EXE
	readme.txt	Useful information not included in manual
	term90.exe	Terminal Emulation Program
	term90.hlp	Terminal Emulation Help
	term90.res	Terminal Emulation Resource File
	testmdm.scx	Script File for Terminal Emulation 
	cmpsrv.scx	Script File for Terminal Emulation 
	genie.scx	Script File for Terminal Emulation 
	datex.p		Telephone number log file

Diskette 2 : Utilities Diskette
	nc_arc.exe	Compressed file containing Norton Commander 
			V4.5 Viewers


Compressing files from the Tree Panel
-------------------------------------
A powerful feature was added to Norton Commander Version 4.5 that is not 
documented in the User's Guide. This is the ability to select a directory 
from the Tree Panel and then compress is using Commander Compression or any 
other packer defined in PACKER.SET.

Internal Editor & Viewer
------------------------
There is no internal editor built into NCMAIN.EXE in Commander Version 4.5. The
Commander Editor is now in the file NCEDIT.EXE.  However a simple Internal 
Viewer is still functional in the NCMAIN.EXE file. Use ALT+F3 to invoke this.

Password protected Compressed files
------------------------------------
As in any password protected file system, if you have protected your
compressed file with a password, you cannot uncompress it without specifying
it correctly. If you forget your password you will not be able to uncompress
the file correctly.

Cloning using SHARE.EXE
------------------------
A problem exists when you are trying to clone to a COM port on a machine that
has SHARE.EXE installed. A conflict exists between the Clone software opening 
the device COMX and SHARE granting exclusive rights to this port to the Clone 
Bootstrap loader. This results in sharing violation errors occuring during a
cloning session. To get around this problem use the CTTY AUX command 
instead of CTTY COM1:.

Filters
-------
The definition of the Filters for Norton Commander Version 4.5 are defined
in the file NC.CFG. The Filters dialog box can be changed by modifying this 
file. One good example of using this file is to create a filter for Program 
Files. (ie Files with extensions such as CXX, HPP, C and H ). To create a 
filter like this simply enter the following data into the NC.CFG file in the 
filter section :-

		!Program Files
		;DevFiles
		:*.c??
		:*.h??

The text following the ! will appear in the Filter Selection Dialog box. The 
text following the ; is the text that will appear in the Title Bar of the panel. 
This is displayed when this filter is operational. The file specifications 
following the : are the types of files that are to be associated with this 
filter. All valid DOS wildcards are allowable. 

Viewers
--------
All viewers that are supported by Norton Commander 4.5  are defined in the file 
NC.CFG. You can modify this list of files that are associated with viewers. For 
example, if your word processor documents have a special file extension such 
as .DCC, then you can change the list of files that the wpview.exe file handles 
by simply adding this file specification to the list of files that are defined 
underneath WPVIEW.EXE.

Special Characters
------------------
To enter special European characters, it is sometimes neccessary to use the
CRTL+Q key first followed by the character you wish to enter. For example, to
enter the German paragraph character, type CRTL+Q followed by SHIFT+3. 

Norton Commander Environment Variables
---------------------------------------
Norton Commander searches your environment for the following three 
environment variables in order to determine where to locate and store 
temporary work files :- TEMP, TMP, NC

Limitations in Compressed Files
-------------------------------
If the current panel contains an open compressed file, then it is not possible 
to change the drive of that panel. This compressed file should be closed first 
and then the drive selected in the normal manner.

Due to the wide range of different compression utilities on the market today 
and the major differences in behaviour, you may find some features of Norton
Commander impossible to implement using your compression utility. This is
especially true of some compression utilities that do not support the
decompressing of files into a destination location other than the current
directory. In addition to this not all compression utilities support the 
storing of full pathnames and directories.

Datex.p File
------------
The file DATEX.P contains a list of telephone numbers that can be used
when running the script file CMPSRV.SCX. This file is used by the Terminal
Emulation Program. The format of this file is a follows :-

Position      1	        2	  3	    4	      5		6
1             5	        5	  5	    5	      5		5
<City Name   ><Prefix  ><300     ><1200/75 ><1200    ><2400    ><9600    >

The telephone numbers that are stored in this file correspond to the numbers 
that are used to connect to the CompuServe Bulletin Board System. The numbers
specified after position 25 are the different numbers to be used depending on 
the baud rate that you wish to connect at. You can add in you own telephone
numbers easily by modifying this file using the Commander Editor.




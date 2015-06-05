@echo off
"C:\Qt\4.7.3\bin\moc.exe"  "f:\Git\LabExe-UserPlugins\SoftwarePlugins\LabNotesLoggerPlugin\LabNotesLoggerPlugin.h" -o ".\GeneratedFiles\Release\moc_LabNotesLoggerPlugin.cpp"  -DUNICODE -DWIN32 -DQT_LARGEFILE_SUPPORT -DQT_NO_DEBUG -DNDEBUG -DQT_CORE_LIB -DQT_GUI_LIB -DLabNotesLoggerPlugin_LIB -D_WINDLL -D_MBCS  "-I.\..\..\include" "-I.\..\..\..\LabExe\src" "-I.\..\..\..\LabExe\include" "-I.\GeneratedFiles" "-IC:\Qt\4.7.3\include" "-I.\GeneratedFiles\Release\." "-IC:\Qt\4.7.3\include\qtmain" "-IC:\Qt\4.7.3\include\QtCore" "-IC:\Qt\4.7.3\include\QtGui" "-I."

if errorlevel 1 goto VCReportError
goto VCEnd
:VCReportError
echo Project : error PRJ0019: A tool returned an error code from "Moc'ing LabNotesLoggerPlugin.h..."
exit 1
:VCEnd
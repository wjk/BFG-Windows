# Required variables checks
!IF "[$(OutDir)]" == "[]"
!ERROR OutDir must be specified
!ENDIF

!IF "[$(IntDir)]" == "[]"
!ERROR IntDir must be specified
!ENDIF

.PHONY : all
all : build

.PHONY : build
build : 
	powershell -executionpolicy bypass -command .\Download.ps1 -URI "'http://repo1.maven.org/maven2/com/madgag/bfg/1.12.5/bfg-1.12.5.jar'" -OutputFile "'$(OutDir)\bfg-1.12.5.jar'" -SkipIfPresent

.PHONY : clean
clean : 
	del "$(OutDir)\bfg-1.12.5.jar"

.PHONY : rebuild
rebuild : clean build

#!python
import subprocess
import os

SConscript('color_SConscript')
Import( 'env' )

ROOTCFLAGS    	= subprocess.check_output( ['root-config',  '--cflags'] ).rstrip().split( " " )
ROOTLDFLAGS    	= subprocess.check_output( ["root-config",  "--ldflags"] )
ROOTLIBS      	= subprocess.check_output( ["root-config",  "--libs"] )
ROOTGLIBS     	= subprocess.check_output( ["root-config",  "--glibs"] )
ROOTLIBPATH 	= subprocess.check_output( ["root-config", "--libdir" ] )
ROOT_SYS 		= os.environ[ "ROOTSYS" ]
JDB_LIB			= os.environ[ "JDB_LIB" ]
JDB_LIB_NAME 	= 'libRooBarb.a'

cppDefines 		= {}
cppFlags 		= ['-Wall' ]#, '-Werror']
cxxFlags 		= ['-std=c++11' ]
cxxFlags.extend( ROOTCFLAGS )

paths 			= [ '.', 			# dont really like this but ended up needing for root dict to work ok
					'include', 
					JDB_LIB + "/include", 
					ROOT_SYS + "/include"
					]
# uncomment this if you put includes in sub-dirs
# paths.extend( Glob( "include/*" ) )

########################## Project Target #####################################
common_env = env.Clone()
# if you dont like the color_SConstruct
# common_env =  Environment()

common_env.Append(CPPDEFINES 	= cppDefines)
common_env.Append(CPPFLAGS 		= cppFlags)
common_env.Append(CXXFLAGS 		= cxxFlags)
common_env.Append(LINKFLAGS 	= cxxFlags )
common_env.Append(CPPPATH		= paths)
# link to RooBarb
common_env.Append(LIBS 			= [ "libRooBarbCore.a", "libRooBarbConfig.a", "libRooBarbTasks.a", "libRooBarbRootAna.a", "libRooBarbUnitTest.a", "libRooBarbExtra.a" ] )
common_env.Append(LIBPATH 		= [ JDB_LIB + "/lib/", "/Users/jdb/bnl/local/work/muonAna/vendor/" ] )

common_env[ "_LIBFLAGS" ] = common_env[ "_LIBFLAGS" ] + " " + ROOTLIBS + " "

jdb_log_level = ARGUMENTS.get( "ll", 60 )
common_env.Append(CXXFLAGS 		= "-DJDB_LOG_LEVEL=" + str(jdb_log_level) )

target = common_env.Program( target='bin/boiler.app', source=[Glob( "src/*.cpp" ), Glob( "src/*/*.cpp" )] )


Depends( target, Glob( JDB_LIB + "/include/jdb/*" ) )

# set as the default target
Default( target )



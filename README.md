# V8.Net
.NET wrapper for Google V8 JavaScript engine.

The project is based on the Javascript.Net project and is intended to improve on the previous project's shortcomings.

#Getting Started
The project is supposed to be more or less self contained. However you may choose to which V8 engine version you want to use. The default value is the current stable branch given at http://omahaproxy.appspot.com/ .
It is strongly suggested that when you build and consume the library, you should use the latest stable window branch from the chromiom projects.

##Requirements
	- Visual Studio >= 2010
	- Powershell (Set-ExecutionPolicy RemoteSigned)

#Building from Source
Observer that everything that is indicated with [optional] is a script argument that is not needed. Furtermore, it is recommended that the latest stable version in the chromiom project is used
when building V8. Check out the site: http://omahaproxy.appspot.com/ .
The visual studio version argument that you may use is the following (requires that you have that version installed!)

	*2010
	*2012
	*2013
	*2015
	
The visual studio path is optional and is not required unless you have installed Visual Studio in a non-default location.
The depot tools url is coded in the script and is normally not necessary in case you don't want to use the default location.
The supported build types are:

	*Release
	*Debug
	
The supported architectures are:

	*ia32
	*x64

Furthermore, since we cannot dynamically link the c runtime when combining it with the CLR, you need to manually add the following shared libraries into
the /build for the unit tests to pass (for each architecture and build configuration):

	*msvcp[version].dll[d]
	*msvcr[version].dll[d]
	*vccorlib[version].dll[d]
	*[architecture]/msvcp[version].dll[d]
	*[architecture]/msvcr[version].dll[d]
	*[architecture]/vccorlib[version].dll[d]
	

### Get and build everything

	- Launch a powershell session and got to /build
	- Type.\get_build_everything.ps1 <VS version[xxxx]> <V8 version[optional]> <VS path[optional]> <depot_tools url[optional]>
	
### Build all v8 for all platforms

	- Requires that you already have installed depot_tools
	- Launch a powershell session and got to /build
	- Type.\build_all_platforms.ps1 <VS version[xxxx]> <VS path[optional]>
	
### Only build a specific configuration

	- Requires that you already have installed depot_tools
	- Launch a powershell session and got to /build
	- Type.\build_v8.ps1 <Build type[Release, Debug]> <Architecture [ia32, x64]> <VS version[xxxx]> <VS path[optional]>
	
### Only get depot_tools and v8

	- Launch a powershell session and got to /build
	- Type .\get_v8 <V8 version[optional]> <depot_tools url[optional]>

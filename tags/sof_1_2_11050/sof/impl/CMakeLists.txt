PROJECT (SOF)

SET (SOF_SOURCES 
	src/sof/config/BundleConfiguration.cpp
	src/sof/config/ConfigFileReader.cpp
	src/sof/config/ConfigurationException.cpp

	src/sof/framework/BundleInfo.cpp
    src/sof/framework/BundleInfoBase.cpp
	src/sof/framework/IBundleContextImpl.cpp
	src/sof/framework/IServiceRegistrationImpl.cpp
	src/sof/framework/Properties.cpp
	src/sof/framework/ServiceEvent.cpp
	src/sof/framework/ServiceInfo.cpp
	src/sof/framework/ServiceListenerInfo.cpp
	src/sof/framework/ServiceReference.cpp
	src/sof/framework/ServiceTracker.cpp
    src/sof/framework/SOFException.cpp

	src/sof/instantiation/ObjectCreationException.cpp

	src/sof/services/admin/AdministrationActivator.cpp
	src/sof/services/admin/DumpAllBundlesCmd.cpp
	src/sof/services/admin/DumpBundleInfoCmd.cpp
	src/sof/services/admin/IAdministrationServiceImpl.cpp
	src/sof/services/admin/StartBundleCmd.cpp
	src/sof/services/admin/StartBundleFromDLLCmd.cpp
	src/sof/services/admin/StartBundlesFromFileCmd.cpp
	src/sof/services/admin/StopAllBundlesCmd.cpp
	src/sof/services/admin/StopBundleCmd.cpp

	src/sof/util/helper/StringTokenizer.cpp

	src/sof/util/logging/LoggerFactory.cpp
	src/sof/util/logging/LoggerImpl.cpp )


ADD_LIBRARY( sof STATIC ${SOF_SOURCES} )
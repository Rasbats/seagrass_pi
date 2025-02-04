# ~~~
# Summary:      Local, non-generic plugin setup
# Copyright (c) 2020-2021 Mike Rossiter
# License:      GPLv3+
# ~~~

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.


# -------- Options ----------

set(OCPN_TEST_REPO
    "opencpn/dr-alpha"
    CACHE STRING "Default repository for untagged builds"
)
set(OCPN_BETA_REPO
    "opencpn/dr-beta"
    CACHE STRING
    "Default repository for tagged builds matching 'beta'"
)
set(OCPN_RELEASE_REPO
    "opencpn/dr-prod"
    CACHE STRING
    "Default repository for tagged builds not matching 'beta'"
)

option(seagrass_USE_SVG "Use SVG graphics" ON)

#
#
# -------  Plugin setup --------
#
set(PKG_NAME seagrass_pi)
set(PKG_VERSION  5.0.3)
set(PKG_PRERELEASE "")  # Empty, or a tag like 'beta'

set(DISPLAY_NAME seagrass)    # Dialogs, installer artifacts, ...
set(PLUGIN_API_NAME seagrass) # As of GetCommonName() in plugin API
set(PKG_SUMMARY "make GPX files for dead reckoning positions")
set(PKG_DESCRIPTION [=[
Create GPX files for dead reckoning positions using existing GPX route files
]=])

set(PKG_AUTHOR "Mike Rossiter")
set(PKG_IS_OPEN_SOURCE "yes")
set(PKG_HOMEPAGE https://github.com/Rasbats/seagrass_pi)
set(PKG_INFO_URL https://opencpn.org/OpenCPN/plugins/dreckoning.html)

set(SRC
    src/seagrass_pi.h
    src/seagrass_pi.cpp
    src/icons.h
    src/icons.cpp
    src/seagrassgui.h
    src/seagrassgui.cpp
    src/seagrassgui_impl.cpp
    src/seagrassgui_impl.h
    src/NavFunc.cpp
    src/NavFunc.h
)

set(PKG_API_LIB api-16)  #  A directory in libs/ e. g., api-17 or api-16

macro(late_init)
  # Perform initialization after the PACKAGE_NAME library, compilers
  # and ocpn::api is available.
  if (seagrass_USE_SVG)
    target_compile_definitions(${PACKAGE_NAME} PUBLIC seagrass_USE_SVG)
  endif ()

  add_definitions("-DHAVE_WX_GESTURE_EVENTS")

endmacro ()

macro(add_plugin_libraries)
  # Add libraries required by this plugin
  add_subdirectory("libs/tinyxml")
  target_link_libraries(${PACKAGE_NAME} ocpn::tinyxml)

  add_subdirectory("${CMAKE_SOURCE_DIR}/opencpn-libs/plugingl")
  target_link_libraries(${PACKAGE_NAME} ocpn::plugingl)

  add_subdirectory("${CMAKE_SOURCE_DIR}/opencpn-libs/nmea0183")
  target_link_libraries(${PACKAGE_NAME} ocpn::nmea0183)

endmacro ()

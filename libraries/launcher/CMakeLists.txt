cmake_minimum_required(VERSION 3.9.4)
project(launcher Java)
find_package(Java 1.8 REQUIRED COMPONENTS Development)

include(UseJava)
set(CMAKE_JAVA_JAR_ENTRY_POINT net.extremelauncher.EntryPoint)
set(CMAKE_JAVA_COMPILE_FLAGS -target 8 -source 8)

set(SRC
    net/extremelauncher/EntryPoint.java
    net/extremelauncher/launcher/Launcher.java
    net/extremelauncher/launcher/impl/AbstractLauncher.java
    net/extremelauncher/launcher/impl/StandardLauncher.java
    net/extremelauncher/exception/ParameterNotFoundException.java
    net/extremelauncher/exception/ParseException.java
    net/extremelauncher/utils/Parameters.java
    net/extremelauncher/utils/ReflectionUtils.java
    net/extremelauncher/utils/logging/Level.java
    net/extremelauncher/utils/logging/Log.java
    net/extremelauncher/legacy/LegacyProxy.java
)

set(LEGACY_SRC
    legacy/net/extremelauncher/legacy/LegacyFrame.java
    legacy/net/extremelauncher/legacy/LegacyLauncher.java
    legacy/net/extremelauncher/legacy/fix/online/Handler.java
    legacy/net/extremelauncher/legacy/fix/online/OnlineFixes.java
    legacy/net/extremelauncher/legacy/fix/online/OnlineModeFix.java
    legacy/net/extremelauncher/legacy/fix/online/SkinFix.java
    legacy/net/extremelauncher/legacy/utils/Base64.java
    legacy/net/extremelauncher/legacy/utils/api/MojangApi.java
    legacy/net/extremelauncher/legacy/utils/api/Texture.java
    legacy/net/extremelauncher/legacy/utils/json/JsonParseException.java
    legacy/net/extremelauncher/legacy/utils/json/JsonParser.java
    legacy/net/extremelauncher/legacy/utils/url/ByteArrayUrlConnection.java
    legacy/net/extremelauncher/legacy/utils/url/UrlUtils.java
    legacy/net/minecraft/Launcher.java
    legacy/net/extremelauncher/legacy/LegacyProxy.java
)

add_jar(NewLaunch ${SRC})
add_jar(NewLaunchLegacy ${LEGACY_SRC} INCLUDE_JARS NewLaunch)
install_jar(NewLaunch "${JARS_DEST_DIR}")
install_jar(NewLaunchLegacy "${JARS_DEST_DIR}")

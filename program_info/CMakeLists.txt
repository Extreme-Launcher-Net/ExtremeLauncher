if(UNIX)
    find_package(PkgConfig)
    if(PkgConfig_FOUND)
        pkg_search_module(SCDOC scdoc)
        if(SCDOC_FOUND)
            pkg_get_variable(SCDOC_SCDOC scdoc scdoc)
        endif()
    endif()
endif()

set(Launcher_CommonName "ExtremeLauncher")
set(Launcher_DisplayName "Extreme Launcher")

set(Launcher_Name "${Launcher_CommonName}" PARENT_SCOPE)
set(Launcher_DisplayName "${Launcher_DisplayName}" PARENT_SCOPE)

set(Launcher_Copyright "© 2024 Extreme Launcher Contributors\\n© 2022-2024 Prism Launcher Contributors\\n© 2021-2022 PolyMC Contributors\\n© 2012-2021 MultiMC Contributors")
set(Launcher_Copyright_Mac "© 2024 Extreme Launcher Contributors, © 2022-2024 Prism Launcher Contributors, © 2021-2022 PolyMC Contributors and © 2012-2021 MultiMC Contributors" PARENT_SCOPE)
set(Launcher_Copyright "${Launcher_Copyright}" PARENT_SCOPE)
set(Launcher_Domain "extremelauncher.net" PARENT_SCOPE)
set(Launcher_UserAgent "${Launcher_CommonName}/${Launcher_VERSION_NAME}" PARENT_SCOPE)
set(Launcher_ConfigFile "extremelauncher.cfg" PARENT_SCOPE)
set(Launcher_Git "https://github.com/ExtremeLauncherTeam/ExtremeLauncher" PARENT_SCOPE)
set(Launcher_DesktopFileName "net.extremelauncher.ExtremeLauncher.desktop" PARENT_SCOPE)
set(Launcher_SVGFileName "net.extremelauncher.ExtremeLauncher.svg" PARENT_SCOPE)

set(Launcher_Desktop "program_info/net.extremelauncher.ExtremeLauncher.desktop" PARENT_SCOPE)
set(Launcher_mrpack_MIMEInfo "program_info/modrinth-mrpack-mime.xml" PARENT_SCOPE)
set(Launcher_MetaInfo "program_info/net.extremelauncher.ExtremeLauncher.metainfo.xml" PARENT_SCOPE)
set(Launcher_SVG "program_info/net.extremelauncher.ExtremeLauncher.svg" PARENT_SCOPE)
set(Launcher_Branding_ICNS "program_info/extremelauncher.icns" PARENT_SCOPE)
set(Launcher_Branding_ICO "program_info/extremelauncher.ico")
set(Launcher_Branding_ICO "${Launcher_Branding_ICO}" PARENT_SCOPE)
set(Launcher_Branding_WindowsRC "program_info/extremelauncher.rc" PARENT_SCOPE)
set(Launcher_Branding_LogoQRC "program_info/extremelauncher.qrc" PARENT_SCOPE)

set(Launcher_Portable_File "program_info/portable.txt" PARENT_SCOPE)

configure_file(net.extremelauncher.ExtremeLauncher.desktop.in net.extremelauncher.ExtremeLauncher.desktop)
configure_file(net.extremelauncher.ExtremeLauncher.metainfo.xml.in net.extremelauncher.ExtremeLauncher.metainfo.xml)
configure_file(extremelauncher.rc.in extremelauncher.rc @ONLY)
configure_file(extremelauncher.manifest.in extremelauncher.manifest @ONLY)
configure_file(extremelauncher.ico extremelauncher.ico COPYONLY)

if(MSVC)
    set(Launcher_MSVC_Redist_NSIS_Section [=[
!ifdef haveNScurl
Section "Visual Studio Runtime"
    Var /GLOBAL vc_redist_exe
    ${If} ${IsNativeARM64}
        StrCpy $vc_redist_exe "vc_redist.arm64.exe"
    ${Else}
        StrCpy $vc_redist_exe "vc_redist.x64.exe"
    ${EndIf}
    DetailPrint 'Downloading Microsoft Visual C++ Redistributable...'
    NScurl::http GET "https://aka.ms/vs/17/release/$vc_redist_exe" "$INSTDIR\vc_redist\$vc_redist_exe" /INSIST /CANCEL /Zone.Identifier /END
    Pop $0
    ${If} $0 == "OK"
        DetailPrint "Download successful"
        ExecWait "$INSTDIR\vc_redist\$vc_redist_exe /install /passive /norestart"
    ${Else}
        DetailPrint "Download failed with error $0"
    ${EndIf}
SectionEnd
!endif
]=])
endif()

configure_file(win_install.nsi.in win_install.nsi @ONLY)

if(SCDOC_FOUND)
    set(in_scd "${CMAKE_CURRENT_SOURCE_DIR}/extremelauncher.6.scd")
    set(out_man "${CMAKE_CURRENT_BINARY_DIR}/extremelauncher.6")
    add_custom_command(
        DEPENDS "${in_scd}"
        OUTPUT "${out_man}"
        COMMAND ${SCDOC_SCDOC} < "${in_scd}" > "${out_man}"
    )
    add_custom_target(man ALL DEPENDS ${out_man})
    set(Launcher_ManPage "program_info/extremelauncher.6" PARENT_SCOPE)
endif()

TEMPLATE = subdirs

THE_SRYBEXE_HARD_PLUGINS = []

win32 {
    THE_SRYBEXE_HARD_PLUGINS += PluginCameraUEye
    THE_SRYBEXE_HARD_PLUGINS += MenloDDS120Plugin
    THE_SRYBEXE_HARD_PLUGINS += Novatech409BPlugin
    THE_SRYBEXE_HARD_PLUGINS += Novatech425APlugin
    #THE_SRYBEXE_HARD_PLUGINS += PluginPhidgets
    #THE_SRYBEXE_HARD_PLUGINS += ThorlabsTSP01Plugin
    #THE_SRYBEXE_HARD_PLUGINS += PluginWavelengthHighFinesse
    #THE_SRYBEXE_HARD_PLUGINS += PluginPxiSystem
}


for(plugproj, THE_SRYBEXE_HARD_PLUGINS) {
    exists($$plugproj) {
        SUBDIRS += $$plugproj
    }
}



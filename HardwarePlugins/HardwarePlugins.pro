TEMPLATE = subdirs

THE_SRYBEXE_HARD_PLUGINS = \
PluginCameraUEye \
#PluginPhidgets \
#ThorlabsTSP01Plugin \
MenloDDS120Plugin \
Novatech409BPlugin \
Novatech425APlugin \
#PluginWavelengthHighFinesse \
#PluginPxiSystem


for(plugproj, THE_SRYBEXE_HARD_PLUGINS) {
    exists($$plugproj) {
        SUBDIRS += $$plugproj
    }
}



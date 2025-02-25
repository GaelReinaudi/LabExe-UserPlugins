TEMPLATE = subdirs

THE_SRYBEXE_PLUGINS = \
Scroller2DPlugin \
StepperPlugin \
LowPassFilterPlugin \
RollingStatsPlugin \
LockingSlapperPlugin \
Scroller2DPlugin \
RandomNumberGeneratorPlugin \
NumericalExpressionPlugin \
MemorySwitcherPlugin \
ParamSupplierPlugin \
TimerPlugin \
TextLoaderPlugin \
LabNotesLoggerPlugin \
\
Plot1DPlugin \
PlotYPlugin \
PlotXYPlugin \
\
Fitter2DGaussianPlugin \
ImagePixelAdderPlugin \
ImageSaverPlugin \
ImageAbsorptionPlugin \
BetterAbsorptionImagePlugin \
ImageStackerPlugin \
\
LinearCombinationPlugin \
\
PlainTextLoggerPlugin \
# SRSControllerPlugin \
#SerialComPortPlugin \
#Pupin632MonitorPlugin \
\
#\
#ParamPlotterPlugin \
#SerialComPortPlugin \
#DropObserverPlugin \
#YoutubePlugin \
#TCO13Round1Plugin
#MonteCarloLogNormalPricerPlugin \

for(plugproj, THE_SRYBEXE_PLUGINS) {
	exists($$plugproj) {
        SUBDIRS += $$plugproj
	}
}





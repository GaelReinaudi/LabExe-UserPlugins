TEMPLATE = subdirs

THE_SRYBEXE_PLUGINS = \
MonteCarloLogNormalPricerPlugin \
Scroller2DPlugin \
StepperPlugin \
LowPassFilterPlugin \
RollingStatsPlugin \
LockingSlapperPlugin \
Scroller2DPlugin \
RandomNumberPlugin \
NumericalExpressionPlugin \
MemorySwitcherPlugin \
ParamSupplierPlugin \
TimerPlugin \
TextLoaderPlugin \
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
#SRSControllerPlugin \
Pupin632MonitorPlugin \
\
ImagePixelAdderPlugin \
ImagePixelAdderPlugin \
ImagePixelAdderPlugin \
 \
#\
#ParamPlotterPlugin \
#SerialComPortPlugin \
#DropObserverPlugin \
YoutubePlugin \


for(plugproj, THE_SRYBEXE_PLUGINS) {
	exists($$plugproj) {
	SUBDIRS += $$plugproj
	}
}





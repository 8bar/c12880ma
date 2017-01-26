# c12880ma
This is a modification of GroupGets C12880MA Arduino and Processing example. It's been tested on an Arduino Uno.

Changelog:

1/26/17

Added variable integration time. While Processing is running and the plot is the active window, press ']' to double the integration time and '[' to halve it. (As before, press 't' to toggle cumulative averaging of the signal and press 'c' to reset the cumulative averaging.)

Modified the clock cycle counts to (hopefully) capture all of the VID signals.

Adjusted the ST signal so as not to include the serial communication in the integration period.

Please note that the clock timing in this code does not conform to the datasheet requirements. On an Uno, the CLK signal runs at about 125 kHZ with a roughly 50% duty cycle during the integration period, but during reading of the VID signal, it slows way down to about 8 kHZ with a duty cycle of only a couple percent! Nevertheless, it seems to work OK. See file 593.png for scope traces.

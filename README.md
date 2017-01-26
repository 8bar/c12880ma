# c12880ma
This is a modification of GroupGets C12880MA Arduino and Processing example. It's been tested on an Arduino Uno.

Changelog:

1/26/17

Added variable integration time. While Processing is running and the plot is the active window, press ']' to double the integration time and '[' to halve it. (As before, press 't' to toggle cumulative averaging of the signal and press 'c' to reset the cumulative averaging.)

Modified the clock cycle counts to (hopefully) capture all of the VID signals.

Adjusted the ST signal so as not to include the serial communication in the integration period.

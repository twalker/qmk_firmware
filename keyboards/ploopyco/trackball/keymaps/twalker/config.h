/* DPI_CONFIG macro that will cycle through an array of options for the DPI. 
 * This is set to 1200, 1600, and 2400, but can be changed. 
 * 1600 is also set to the default.
 * To configure/set your own array, there are two defines to use, 
 * PLOOPY_DPI_OPTIONS to set the array, and PLOOPY_DPI_DEFAULT.
 */

// #define PLOOPY_DPI_DEFAULT 800
// Trackball PSI on Tractyl Manuform: 900 for Mac, 350 for Linux
#define PLOOPY_DPI_OPTIONS \
    { 350, 600, 900 }

// Makes the key into a momentary key, rather than a toggle.
#define PLOOPY_DRAGSCROLL_MOMENTARY
// Sets the DPI multiplier to use when drag scroll is enabled.
// #define PLOOPY_DRAGSCROLL_MULTIPLIER 0.3

// Normally, when activating Drag Scroll, it uses a fraction of the current DPI. 
// You can define this to use a specific, set DPI rather than a fraction of the current DPI.
#define PLOOPY_DRAGSCROLL_FIXED

// When the fixed DPI option is enabled, this sets the DPI to be used for Drag Scroll.
#define PLOOPY_DRAGSCROLL_DPI 100

// This reverses the direction that the scroll is performed.
//#define PLOOPY_DRAGSCROLL_INVERT  

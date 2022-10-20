// The Arduino Pro Micro is a general development board.
// The following provides a sample of user-customized code to USBemani.

// All code should start by including the main "usbemani.h" file. This provides access to system functions
#include "usbemani.h"

/*** PLEASE READ THE FOLLOWING:
  USBemani provides a number of callback functions that are invoked by the system.
  A number of these callbacks are available for the user to override and insert their own custom functionality.
  The following will provide examples on how to use these callbacks and the available APIs.
*/

/*** Definitions ***/
// We can define our own variables for use by our code.
// For our example controller, we'll define a variable to hold a rainbow effect that we'll draw around our turntable.
// Additionally, we'll only draw this RGB ring for _fallback_ lighting, when no USB HID lighting data is available.
// If this data is available, we'll draw that instead.

// We'll make a new Effect_Rainbow_t for our rainbow effect. This takes in the following parameters, as defined in common/effect.h:
//  * The RGB channel we'll draw to. We only have one RGB channel, so this will be 0.
//  * The first LED to draw to. LEDs are 0-indexed.
//    * Our example controller has 11 RGB LEDs for buttons, followed by our turntable. So, our first LED will be index 11.
//    * We can get this with our user defines we setup earlier: (BUTTONS_ACTIVE * RGB_LEDS_PER_KEY).
//  * The number of LEDs to draw.
//    * We defined that earlier as well, as RGB_LEDS_PER_TURNTABLE.
//  * The direction to draw our LEDs in. `false` draws LEDs from left-to-right, whereas `true` draws LEDs from right-to-left.
static Effect_Rainbow_t rainbow = New_EffectRainbow(
  0,                                    // Our channel
  (BUTTONS_ACTIVE * RGB_LEDS_PER_KEY),  // Our first LED to draw to
  (RGB_LEDS_PER_TURNTABLE),             // The number of LEDs to draw
  false                                 // The direction we'll draw our LEDs in
);

/*** RGB Lighting ***/
// For our example, we'll use this along with the input of our controller to calculate a brightness value.
// Any time there's motion, we'll make the right bright.
// When there's no motion, we'll wait 2 seconds before dimming.
// Since we're going to track brightness, let's define some variables.
// Our dimmest brightness will be 64, and our brightest will be 128.
static const uint8_t dim    = 64;
static const uint8_t bright = 128;
// We'll keep track of the current brightness here, starting at our dim value
static uint8_t brightness = dim;

// This function is called once every frame, and it'll be used to help keep track of our brightness.
void CALLBACK_RGBCalculateNextFrame() {
  // We'll create a counter to keep track of whether we've received motion.
  static uint8_t counter = 0;

  // First, we'll check for movement.
  // Our encoder provides a way to get directional movement, so we'll use this.
  // Note that this is subject to our hold timeout.
  // If we have directional movement, we'll set our timer to 2 * our FPS = 2 seconds
  if (Encoder_Direction(0)) {
    counter = (RGB_FRAMERATE_TARGET * 2);
  // If we don't have directional movement, we'll check if our counter has a value stored. If it does, we'll decrement it.
  } else if (counter) {
    counter--;
  }

  // As long as we have a counter value, we should increase our brightness to our brightest point.
  if (counter) {
    if (brightness < bright) brightness++;
  // If we don't have a counter value, our timer expired, and we should decrease to our dimmest point.
  } else {
    if (brightness > dim) brightness--;
  }
}

// This function is called any time we can draw lighting, but only when no USB HID lighting data is available.
// This will be used to draw the lighting for our keys and turntable.
void CALLBACK_OnRGBDrawFallback() {
  // We'll draw three different colors of buttons:
  // * White, for keys 1, 3, 5, and 7
  // * Blue, for keys 2, 4, and 6
  // * Red, for buttons E1 - E4
  // We can define RGB colors for these:
  const RGB_Color_t white = { .r = 128, .g = 128, .b = 128 };
  const RGB_Color_t red   = { .r = 255, .g =   0, .b =   0 };
  const RGB_Color_t blue  = { .r =   0, .g =   0, .b = 255 };

  // We'll draw these buttons if the button is pressed, starting with our keys.
  // We only need to fetch button data once, so we'll grab it now.
  const uint16_t buttons = Button_GetAll();

  // Before we draw any RGB data, let's clear our channel.
  RGB_Clear(0);

  // We'll draw our buttons first. These are one LED each.
  for (uint8_t i = 0; i < 7; i++) {
    // If our button isn't pressed, move to the next one.
    if (!(buttons & (1 << i))) continue;

    // If we have an even number, we'll draw blue. Otherwise, white.
    // We'll use RGB_Set to set a specific LED on a specific channel.
    if (i & 1) {
      RGB_Set(0, i, blue);
    } else {
      RGB_Set(0, i, white);
    }
  }

  // Next, we'll draw our red E1-E4 buttons
  for (uint8_t i = 0; i < 4; i++) {
    // Our button lookup and draws will both be offset by 7 (the number of keys we drew).
    const uint8_t index = 7 + i;
    // If our button isn't pressed, move to the next one.
    if (!(buttons & (1 << index))) continue;
    // Otherwise, we'll draw it red
    RGB_Set(0, i, red);
  }

  // Last, we'll draw our turntable effect. Our rainbow effect comes with its own draw command, EffectRainbow_Draw.
  // We can call this, passing two things to it:
  // * The effect itself, as a pointer
  // * A hue to start the rainbow effect with
  // This effect can have its brightness and saturation adjusted with Effect_SetValue and Effect_SetSaturation.
  // First, we'll make sure we draw this at full saturation.
  Effect_SetSaturation(255);
  // Recall that we also want to draw this at a specific brightness, which is in our brightness variable.
  // We simply reference that variable here, and our effect update will make sure the brightness is adjusted automatically.
  Effect_SetValue(brightness);
  // Now we perform our draw. For the starting hue, we'll make our rainbow ring start with a hue based on our turntable's position.
  // This will make the ring "follow" the turntable as it's rotated.
  EffectRainbow_Draw(&rainbow, Encoder_PhysicalPercent(0));
  // NOTE: Depending on how the LED strip is installed, this may appear to rotate the _opposite_ direction.
  // If this is the case, we can invert the turntable position before drawing like so:
  //   EffectRainbow_Draw(&rainbow, Encoder_PhysicalPercent(0) ^ 0xFF);
}

// This function is called any time we can draw lighting, but only when USB HID lighting data is available.
// This will be used to draw the lighting for our keys and turntable.
void CALLBACK_OnRGBDrawUSB(USB_OutputReport_t *output) {
  // Just like before, we'll start by clearing our RGB channel.
  RGB_Clear(0);

  // Our output variable will contain two types of data: traditional lights (if available), and RGB data.
  // We can take this RGB data and directly draw it.
  // We'll start with our buttons first, as they each are one LED in size.
  for (uint8_t i = 0; i < BUTTONS_ACTIVE; i++) {
    RGB_Set(0, i, output->rgb[i]);
  }

  // Our turntable will be drawn last, which covers a range of LEDs.
  // We won't draw the rainbow effect here; instead, we'll draw the RGB data we receive over USB.
  // We'll use RGB_SetRange to perform this draw, to draw multiple LEDs the same color.
  // We'll use the same defines that we used to setup our rainbow effect.
  RGB_SetRange(
    0,
    (BUTTONS_ACTIVE * RGB_LEDS_PER_KEY),  // Our starting LED
    (RGB_LEDS_PER_TURNTABLE),             // How many LEDs to draw
    output->rgb[11]                       // What color to draw
  );
}
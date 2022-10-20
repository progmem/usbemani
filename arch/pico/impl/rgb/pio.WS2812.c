#pragma once

static const uint _rgb_counts[RGB_CHANNELS_ACTIVE] = { RGB_LEDS_PER_CHANNEL };
uint _rgb_ws2812_pio_dma[RGB_CHANNELS_ACTIVE];

void _impl_rgb_init(void) {
  static const _pin_t pins[RGB_CHANNELS_AVAILABLE] = { RGB_PINS };
  static const uint   pidx[RGB_CHANNELS_ACTIVE] = { RGB_CHANNELS };

  uint leds = 0;

  // Configure PIO for transferring WS2812 data
  static const PIO pio = RGB_PIO;
  uint offset = pio_add_program(pio, &ws2812_pio_program);

  for (int sm = 0; sm < RGB_CHANNELS_ACTIVE; sm++) {
    ws2812_pio_program_init(pio, sm, offset, pins[pidx[sm]], 800000);

    // Configure DMA to push data to PIO state machine
    _rgb_ws2812_pio_dma[sm] = dma_claim_unused_channel(true);
    dma_channel_config dma_config = dma_channel_get_default_config(_rgb_ws2812_pio_dma[sm]);

    channel_config_set_transfer_data_size(&dma_config, DMA_SIZE_8);
    channel_config_set_read_increment(&dma_config, true);
    channel_config_set_write_increment(&dma_config, false);
    channel_config_set_dreq(&dma_config, pio_get_dreq(pio, sm, true));

    dma_channel_configure(
      _rgb_ws2812_pio_dma[sm],
      &dma_config,
      &pio->txf[sm],                        // Write to state machine
      &_rgb[leds],                          // Read from the correct framebuffer segment
      _rgb_counts[sm] * sizeof(RGB_LED_t),  // Reads the LEDs for a given channel
      false                                 // Do not auto-start
    );

    leds += _rgb_counts[sm];
  }
}

bool _impl_rgb_ready(void) {
  bool busy = false;
  for (uint sm = 0; sm < RGB_CHANNELS_ACTIVE; sm++) {
    if (dma_channel_is_claimed(_rgb_ws2812_pio_dma[sm]))
      busy = busy || dma_channel_is_busy(_rgb_ws2812_pio_dma[sm]);
  }

  return !(busy);
}

void _impl_rgb_render(void) {
  uint leds = 0;

  // Reset the address each DMA channel should read from
  for (uint sm = 0; sm < RGB_CHANNELS_ACTIVE; sm++) {
    if (dma_channel_is_claimed(_rgb_ws2812_pio_dma[sm])) {
      if (!dma_channel_is_busy(_rgb_ws2812_pio_dma[sm]))
        dma_channel_set_read_addr(_rgb_ws2812_pio_dma[sm], &_rgb[leds], true);
    }
    leds += _rgb_counts[sm];
  }
}
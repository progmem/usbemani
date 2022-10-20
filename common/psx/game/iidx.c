WEAK void CALLBACK_OnPlaystationInputRequest(PSX_Input_t *input) {
  const PSX_Button_t button_mapping[] = {
    PSX_Square,
    PSX_L1,
    PSX_Cross,
    PSX_R1,
    PSX_Circle,
    PSX_L2,
    PSX_DPad_Left,
    PSX_Start,
    PSX_Select
  };

  for (uint8_t i = 0; i < 9; i++)
    if (Button_Get(i)) input->buttons |= button_mapping[i];

  if (Encoder_Direction(0) == ENCODER_CCW)
    input->buttons |= PSX_DPad_Down;

  if (Encoder_Direction(0) == ENCODER_CW)
    input->buttons |= PSX_DPad_Up;
}
typedef enum
{
    NoneClk,
    McgPllFllClk,
    OscerClk,
    McgIrcClk
} pwm_clock_source_e;

typedef enum
{
	NoOutput,
	Edge,
	Center,
	EdgeInverted
} pwm_alignment_e;

typedef enum
{
	Prescaler1,
	Prescaler2,
	Prescaler4,
	Prescaler8,
	Prescaler16,
	Prescaler32,
	Prescaler64,
	Prescaler128
} pwm_prescaler_e;

typedef struct
{
	pwm_clock_source_e eClock_source;
	pwm_prescaler_e ePrescaler_value;
	uint16_t uiPeriod_ms;
	uint32_t uiXtal_frequency;
} tpm_config_t;

typedef struct
{
	pwm_alignment_e eAlignment;
	uint16_t uiPulse_width_ms;
	uint8_t uiInterrupt_enable;
	uint8_t uiChannel;
} channel_config_t;

int pwm_initPWM(TPM_Type * tTimer, tpm_config_t tTpmConfig);

int pwm_channelInit (TPM_Type * tTimer, tpm_config tTpmConfig, channel_config_t tChannelConfig);

int pwm_changeChannelPeriod(TPM_Type * tTimer, tpm_config_t tTpmConfig, uint16_t uiPeriod_ms);

int pwm_changeModulePeriod(TPM_Type * tTimer, tpm_config_t tTpmConfig);

void pwm_disablePwm(TPM_Type * tTimer);

void pwm_enablePwm(TPM_Type * tTimer);

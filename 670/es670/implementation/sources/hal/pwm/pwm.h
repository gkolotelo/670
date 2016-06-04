

typedef enum
{
    NoneClk,
    McgPllFllClk,
    OscerClk,
    McgIrcClk
} pwm_clock_source_e;

typedef enum
{
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
	pwm_clock_source_e clock_source;
	pwm_prescaler_e prescaler_value;
	uint16_t period_ms;
	uint32_t xtal_frequency;
} tpm_config;

typedef struct
{
	pwm_alignment_e alignment;
	uint16_t pulse_width_ms;
	char interrupt_enable;
	uint8_t channel;
} channel_config;

void pwm_initPWM(TPM_Type * timer, tpm_config tpmConfig);

void pwm_channelInit (TPM_Type * timer, tpm_config tpmConfig, channel_config channelConfig);

void pwm_setPortPinPwm(PORT_Type * port, GPIO_Type * gpio, char pinNo);

/*
 * После подачи питания на DHT11 необходимо:
 * 1. подождать 1с;
 * 2. низкий уровень > 18 мс
 * 3. считывать (80 мкс низкий уровень, 80 мкс высокий уровень)
 * 4. Прием 40 битов
 * "0" - 50 мкс низкий, 26-28 мкс высокий
 * "1" 50 мкс низкий, 70 мкс высокий
 * 5. Окончание сигнала - 50 мкс низкий уровень
 *
 * Порядок выполнения функций:
 * 1. Инициализация
 * 2. Считывание
 */
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "DHT11.h"
/*
 * Определение пина как выход
 * arg:
 * GPIO_TypeDef  *GPIOx				- порт, пин которого нужно переопределить
 * uint8_t pinNumber				- номер пина, который нужно переопределить
 * ret:								успешное выполнение функции
 */
uint8_t GPIO_InitOutput(GPIO_TypeDef  *GPIOx, uint8_t pinNumber)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(*GPIOx, pinNumber, GPIO_PIN_SET);

	GPIO_InitStruct.Pin = pinNumber;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(*GPIOx, &GPIO_InitStruct);
}
/*
 * Определение пина как вход
 * arg:
 * GPIO_TypeDef  *GPIOx				- порт, пин которого нужно переопределить
 * uint8_t pinNumber				- номер пина, который нужно переопределить
 * ret:								успешное выполнение функции
 */
uint8_t GPIO_InitInput(void)
{
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };
	TIM_IC_InitTypeDef sConfigIC = { 0 };

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 8 - 1;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 65535;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_IC_Init(&htim2) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK) {
		Error_Handler();
	}
	sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
	sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
	sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
	sConfigIC.ICFilter = 0;
	if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK) {
		Error_Handler();
	}
}

/*
 * Запуск датчика DHT11
 * arg:
 * GPIO_TypeDef  *GPIOx				- порт, к пину которого подключен датчик
 * uint8_t pinNumber				- номер пина, к которому подключен датчик
 * ret:								успешное выполнение инициализации
 */
uint8_t DHT11_Init (GPIO_TypeDef  *GPIOx, uint8_t pinNumber)
{
	HAL_Delay(1000);
	GPIO_InitOutput(*GPIOx, pinNumber);

	HAL_GPIO_WritePin(*GPIOx, pinNumber, 0);
	HAL_Delay(20);
	HAL_GPIO_WritePin(*GPIOx, pinNumber, 1);

	GPIO_InitInput();
}

__weak void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 8-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

__weak void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}



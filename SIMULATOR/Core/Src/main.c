/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "led.h"
#include "vehicle.h"
#include "ignition.h"
#include "ecu.h"
#include "ssd1306.h"
#include "gpio.h"
#include "uart.h"
#include "display.h"
#include <string.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

/* Definitions for IgnitionTask */
osThreadId_t IgnitionTaskHandle;
const osThreadAttr_t IgnitionTask_attributes = {
  .name = "IgnitionTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for EcuTask */
osThreadId_t EcuTaskHandle;
const osThreadAttr_t EcuTask_attributes = {
  .name = "EcuTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for SensorTask */
osThreadId_t SensorTaskHandle;
const osThreadAttr_t SensorTask_attributes = {
  .name = "SensorTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for DisplayTask */
osThreadId_t DisplayTaskHandle;
const osThreadAttr_t DisplayTask_attributes = {
  .name = "DisplayTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for LedTask */
osThreadId_t LedTaskHandle;
const osThreadAttr_t LedTask_attributes = {
  .name = "LedTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for UartTask */
osThreadId_t UartTaskHandle;
const osThreadAttr_t UartTask_attributes = {
  .name = "UartTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_ADC1_Init(void);
void StartIgnitionTask(void *argument);
void StartEcuTask(void *argument);
void StartSensorTask(void *argument);
void StartDisplayTask(void *argument);
void StartLedTask(void *argument);
void StartUartTask(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
ECU_Fault_t Fault;

char uartBuffer[200];

static IgnitionState_t PrevIgnition = IGNITION_OFF;

uint8_t ignitionStartup = 0;

uint32_t ADC_ReadChannel(uint32_t channel)
{
    ADC_ChannelConfTypeDef sConfig = {0};

    sConfig.Channel = channel;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

    uint32_t adc_value = HAL_ADC_GetValue(&hadc1);

    HAL_ADC_Stop(&hadc1);

    return adc_value;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  SSD1306_Init();
  Display_IgnitionOff();

  UART_Init(UART2);      // USART2 -> PC Serial Monitor
  UART_Init(UART1);      // USART1 -> ESP8266
 // UART_SendString(UART1, "Hello ESP32\r\n");

  LED_Init();

  BUTTON_Init();

  Ignition_Init();
  SSD1306_UpdateScreen();


  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of IgnitionTask */
  IgnitionTaskHandle = osThreadNew(StartIgnitionTask, NULL, &IgnitionTask_attributes);

  /* creation of EcuTask */
  EcuTaskHandle = osThreadNew(StartEcuTask, NULL, &EcuTask_attributes);

  /* creation of SensorTask */
  SensorTaskHandle = osThreadNew(StartSensorTask, NULL, &SensorTask_attributes);

  /* creation of DisplayTask */
  DisplayTaskHandle = osThreadNew(StartDisplayTask, NULL, &DisplayTask_attributes);

  /* creation of LedTask */
  LedTaskHandle = osThreadNew(StartLedTask, NULL, &LedTask_attributes);

  /* creation of UartTask */
  UartTaskHandle = osThreadNew(StartUartTask, NULL, &UartTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	    /* USER CODE END WHILE */

	    /* USER CODE BEGIN 3 */

  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartIgnitionTask */
/**
  * @brief  Function implementing the IgnitionTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartIgnitionTask */
void StartIgnitionTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
	    Ignition_Update();

	    if(Ignition_GetState() != PrevIgnition)
	    {
	        if(Ignition_GetState() == IGNITION_ON)
	        {
	        	UART_SendString(UART2, "\r\nIGNITION ON\r\n");
	        	UART_SendString(UART1, "\r\nIGNITION ON\r\n");

	            ignitionStartup = 0;

	            Display_IgnitionOn();

	            LED_SetColor(LED_WHITE);

	            osDelay(1000);

	            ignitionStartup = 1;
	        }
	        else
	        {
	        	UART_SendString(UART2, "\r\nIGNITION OFF\r\n");
	        	UART_SendString(UART1, "\r\nIGNITION OFF\r\n");

	            Display_IgnitionOff();

	            LED_SetColor(LED_OFF);

	            ignitionStartup = 0;
	        }

	        PrevIgnition = Ignition_GetState();
	    }

	    osDelay(20);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartEcuTask */
/**
* @brief Function implementing the EcuTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartEcuTask */
void StartEcuTask(void *argument)
{
  /* USER CODE BEGIN StartEcuTask */
  /* Infinite loop */
  for(;;)
  {
      if(Ignition_GetState() == IGNITION_ON)
      {
          ECU_CheckFaults();
      }

      osDelay(100);
  }
  /* USER CODE END StartEcuTask */
}

/* USER CODE BEGIN Header_StartSensorTask */
/**
* @brief Function implementing the SensorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSensorTask */
void StartSensorTask(void *argument)
{
  /* USER CODE BEGIN StartSensorTask */
  /* Infinite loop */
  for(;;)
  {
	    if(Ignition_GetState() == IGNITION_ON)
	    {
	        /* Read ADC */

	        VehicleData.tempADC =
	                ADC_ReadChannel(ADC_CHANNEL_0);

	        VehicleData.speedADC =
	                ADC_ReadChannel(ADC_CHANNEL_4);

	        VehicleData.rpmADC =
	                ADC_ReadChannel(ADC_CHANNEL_8);

	        /* Convert */

	        VehicleData.temperature =
	                Vehicle_GetTemperature(VehicleData.tempADC);

	        VehicleData.speed =
	                Vehicle_GetSpeed(VehicleData.speedADC);

	        VehicleData.rpm =
	                Vehicle_GetRPM(VehicleData.rpmADC);

	        VehicleData.fuel =
	                Vehicle_GetFuel(VehicleData.speed);
	    }

	    osDelay(100);
  }
  /* USER CODE END StartSensorTask */
}

/* USER CODE BEGIN Header_StartDisplayTask */
/**
* @brief Function implementing the DisplayTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDisplayTask */
void StartDisplayTask(void *argument)
{
  /* USER CODE BEGIN StartDisplayTask */
  /* Infinite loop */

    for(;;)
    {
        if(Ignition_GetState() == IGNITION_ON)
        {
            if(ignitionStartup)
            {
                ECU_Fault_t fault = ECU_GetFaultStatus();
                Display_Update(&VehicleData,&fault);
            }
        }
        else
        {
            Display_IgnitionOff();
        }

        osDelay(200);
    }
  /* USER CODE END StartDisplayTask */
}

/* USER CODE BEGIN Header_StartLedTask */
/**
* @brief Function implementing the LedTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLedTask */
void StartLedTask(void *argument)
{
  /* USER CODE BEGIN StartLedTask */
  /* Infinite loop */
    ECU_Fault_t fault;

    for(;;)
    {
        if(Ignition_GetState() == IGNITION_ON)
        {
            /* Wait until startup indication is over */
            if(ignitionStartup)
            {
                fault = ECU_GetFaultStatus();

                LED_Update(fault);
            }
        }
        else
        {
            LED_SetColor(LED_OFF);
        }

        osDelay(100);
  }
  /* USER CODE END StartLedTask */
}

/* USER CODE BEGIN Header_StartUartTask */
/**
* @brief Function implementing the UartTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartUartTask */
void StartUartTask(void *argument)
{
  /* USER CODE BEGIN StartUartTask */
  /* Infinite loop */
    ECU_Fault_t fault;

    char buff[200];        // PC Serial Monitor (UART2)
    char espBuffer[100];   // ESP32 (UART1)

    char faultString[20];

    uint8_t faultCount;

    for(;;)
    {
        if(Ignition_GetState() == IGNITION_ON)
        {
            fault = ECU_GetFaultStatus();

            /*==============================
             * UART2 -> PC Serial Monitor
             *=============================*/

            sprintf(buff,
                    "Temperature : %3d C   %s\r\n"
                    "Fuel        : %3d %%   %s\r\n"
                    "Speed       : %3d km/h %s\r\n"
                    "RPM         : %4d     %s\r\n"
                    "---------------------------\r\n",

                    VehicleData.temperature,
                    fault.overTemperature ? "FAULT" : "OK",

                    VehicleData.fuel,
                    fault.lowFuel ? "FAULT" : "OK",

                    VehicleData.speed,
                    fault.overSpeed ? "FAULT" : "OK",

                    VehicleData.rpm,
                    fault.overRPM ? "FAULT" : "OK");

            UART_SendString(UART2, buff);


            /*==============================
             * Build Fault String
             *=============================*/

            faultCount = 0;

            faultCount += fault.overTemperature;
            faultCount += fault.overSpeed;
            faultCount += fault.overRPM;
            faultCount += fault.lowFuel;

            if(faultCount == 0)
            {
                strcpy(faultString, "OK");
            }
            else if(faultCount == 1)
            {
                if(fault.overTemperature)
                    strcpy(faultString, "OVERHEATING");

                else if(fault.overSpeed)
                    strcpy(faultString, "HIGH SPEED");

                else if(fault.overRPM)
                    strcpy(faultString, "HIGH RPM");

                else if(fault.lowFuel)
                    strcpy(faultString, "LOW FUEL");
            }
            else
            {
                faultString[0] = '\0';

                if(fault.overTemperature)
                    strcat(faultString, "T");

                if(fault.overSpeed)
                {
                    if(strlen(faultString))
                        strcat(faultString, "+");

                    strcat(faultString, "S");
                }

                if(fault.overRPM)
                {
                    if(strlen(faultString))
                        strcat(faultString, "+");

                    strcat(faultString, "R");
                }

                if(fault.lowFuel)
                {
                    if(strlen(faultString))
                        strcat(faultString, "+");

                    strcat(faultString, "L");
                }
            }


            /*==============================
             * UART1 -> ESP32
             *=============================*/

            sprintf(espBuffer,
                    "T=%d,S=%d,R=%d,F=%d,ST=%s,E=%s\r\n",

                    VehicleData.temperature,
                    VehicleData.speed,
                    VehicleData.rpm,
                    VehicleData.fuel,

                    faultString,

                    (Ignition_GetState()==IGNITION_ON) ? "ON" : "OFF");

            UART_SendString(UART1, espBuffer);
        }

        osDelay(1000);
    }
  /* USER CODE END StartUartTask */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

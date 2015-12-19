################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
drivers/buttons.obj: C:/EK-TM4C129/examples/boards/ek-tm4c1294xl/drivers/buttons.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/CCSV6/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -Ooff --opt_for_speed=2 --include_path="C:/EK-TM4C129/exosite" --include_path="C:/CCSV6/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/include" --include_path="C:/Tiva_Connected_Launchpad_CCS6_workspace/wlan_station_exosite_write_read" --include_path="C:/EK-TM4C129" --include_path="C:/EK-TM4C129/examples/boards/ek-tm4c1294xl" --include_path="C:/ti/CC3100SDK_1.1.0/cc3100-sdk/examples/common" --include_path="C:/ti/CC3100SDK_1.1.0/cc3100-sdk/simplelink/include" --include_path="C:/ti/CC3100SDK_1.1.0/cc3100-sdk/simplelink/source" --include_path="C:/ti/CC3100SDK_1.1.0/cc3100-sdk/platform/tiva-c-connected-launchpad" -g --gcc --define=TARGET_IS_TM4C129_RA0 --define=PART_TM4C1294NCPDT --define=ccs="ccs" --define=UART_BUFFERED --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="drivers/buttons.pp" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/pinout.obj: C:/EK-TM4C129/examples/boards/ek-tm4c1294xl/drivers/pinout.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/CCSV6/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -Ooff --opt_for_speed=2 --include_path="C:/EK-TM4C129/exosite" --include_path="C:/CCSV6/ccsv6/tools/compiler/ti-cgt-arm_5.2.2/include" --include_path="C:/Tiva_Connected_Launchpad_CCS6_workspace/wlan_station_exosite_write_read" --include_path="C:/EK-TM4C129" --include_path="C:/EK-TM4C129/examples/boards/ek-tm4c1294xl" --include_path="C:/ti/CC3100SDK_1.1.0/cc3100-sdk/examples/common" --include_path="C:/ti/CC3100SDK_1.1.0/cc3100-sdk/simplelink/include" --include_path="C:/ti/CC3100SDK_1.1.0/cc3100-sdk/simplelink/source" --include_path="C:/ti/CC3100SDK_1.1.0/cc3100-sdk/platform/tiva-c-connected-launchpad" -g --gcc --define=TARGET_IS_TM4C129_RA0 --define=PART_TM4C1294NCPDT --define=ccs="ccs" --define=UART_BUFFERED --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="drivers/pinout.pp" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '



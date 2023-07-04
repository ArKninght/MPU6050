################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"E:/CSS/CSS11.2.0/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="E:/CSS/CSS11.2.0/ccs/ccs_base/arm/include" --include_path="E:/CSS/CSS11.2.0/ccs/ccs_base/arm/include/CMSIS" --include_path="E:/CSS/SDK/simplelink_msp432p4_sdk_3_40_01_02/source" --include_path="E:/CSS/CSS11.2.0/WorkSpace/MPU6050" --include_path="E:/CSS/CSS11.2.0/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



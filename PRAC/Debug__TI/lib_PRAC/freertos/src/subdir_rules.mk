################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
lib_PRAC/freertos/src/croutine.obj: C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/src/croutine.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"F:/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/ccs/ccs/ccs_base/arm/include" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/cortex-m4" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/inc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/src" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/inc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/msp432" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/uoc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/screen" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/graphics" --include_path="F:/ccs/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Shake/Desktop/2019-1-prac/PRAC" --include_path="F:/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="lib_PRAC/freertos/src/$(basename $(<F)).d_raw" --obj_directory="lib_PRAC/freertos/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

lib_PRAC/freertos/src/event_groups.obj: C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/src/event_groups.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"F:/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/ccs/ccs/ccs_base/arm/include" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/cortex-m4" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/inc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/src" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/inc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/msp432" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/uoc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/screen" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/graphics" --include_path="F:/ccs/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Shake/Desktop/2019-1-prac/PRAC" --include_path="F:/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="lib_PRAC/freertos/src/$(basename $(<F)).d_raw" --obj_directory="lib_PRAC/freertos/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

lib_PRAC/freertos/src/heap_1.obj: C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/src/heap_1.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"F:/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/ccs/ccs/ccs_base/arm/include" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/cortex-m4" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/inc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/src" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/inc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/msp432" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/uoc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/screen" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/graphics" --include_path="F:/ccs/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Shake/Desktop/2019-1-prac/PRAC" --include_path="F:/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="lib_PRAC/freertos/src/$(basename $(<F)).d_raw" --obj_directory="lib_PRAC/freertos/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

lib_PRAC/freertos/src/list.obj: C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/src/list.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"F:/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/ccs/ccs/ccs_base/arm/include" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/cortex-m4" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/inc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/src" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/inc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/msp432" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/uoc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/screen" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/graphics" --include_path="F:/ccs/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Shake/Desktop/2019-1-prac/PRAC" --include_path="F:/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="lib_PRAC/freertos/src/$(basename $(<F)).d_raw" --obj_directory="lib_PRAC/freertos/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

lib_PRAC/freertos/src/queue.obj: C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/src/queue.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"F:/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/ccs/ccs/ccs_base/arm/include" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/cortex-m4" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/inc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/src" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/inc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/msp432" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/uoc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/screen" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/graphics" --include_path="F:/ccs/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Shake/Desktop/2019-1-prac/PRAC" --include_path="F:/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="lib_PRAC/freertos/src/$(basename $(<F)).d_raw" --obj_directory="lib_PRAC/freertos/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

lib_PRAC/freertos/src/tasks.obj: C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/src/tasks.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"F:/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/ccs/ccs/ccs_base/arm/include" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/cortex-m4" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/inc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/src" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/inc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/msp432" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/uoc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/screen" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/graphics" --include_path="F:/ccs/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Shake/Desktop/2019-1-prac/PRAC" --include_path="F:/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="lib_PRAC/freertos/src/$(basename $(<F)).d_raw" --obj_directory="lib_PRAC/freertos/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

lib_PRAC/freertos/src/timers.obj: C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/src/timers.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"F:/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/ccs/ccs/ccs_base/arm/include" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/cortex-m4" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/inc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/freertos/src" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/inc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/msp432" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/uoc" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/screen" --include_path="C:/Users/Shake/Desktop/2019-1-prac/lib_PRAC/graphics" --include_path="F:/ccs/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Shake/Desktop/2019-1-prac/PRAC" --include_path="F:/ccs/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="lib_PRAC/freertos/src/$(basename $(<F)).d_raw" --obj_directory="lib_PRAC/freertos/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



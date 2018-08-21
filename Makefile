mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += \
	DetectionManager.o \
	GrayDetection.o \
	DistanceDetection.o \
	ImpactDetection.o \
	StepDetecion.o \
	SensorManager.o \
	ColorSensor.o \
	GyroSensor.o \
	BatterySensor.o\
	MotorRaSensor.o \
	Motor.o \
	PidController.o\
	PwmVoltageCorr.o\
	LineTraceController.o\
	BalanceController.o\
	TailContoroller.o\
	RobotController.o\
	SectionManager.o\
	SectionInfo.o\
	SectionLineTracer.o\
	SectionSenarioTracer.o\
	BalancerCpp.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
#今回は既存のハードウェアクラスを用いないためコメントアウト
#include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile
include $(EV3RT_SDK_LIB_DIR)/../Makefile.slib

endif

APPL_DIR += $(mkfile_path)Detection $(mkfile_path)Hardware \
						$(mkfile_path)RobotControl $(mkfile_path)Scenario

INCLUDES += \
	-I$(mkfile_path)Detection \
	-I$(mkfile_path)Hardware \
	-I$(mkfile_path)RobotControl \
	-I$(mkfile_path)Scenario

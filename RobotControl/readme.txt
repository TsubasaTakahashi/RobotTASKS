PID制御->PidController
PWM電圧補正->PwmVoltageCorr
ライントレース制御->LineTraceController
姿勢制御->BalanceController
尻尾制御->TailController
走行制御->RobotController


//PWM左右モータ個体差補正->PwmMotorIdCorr
//(Pwm MotorIndividual difference Correction)
//削除
//理由1　個体差補正をする場合、周期ハンドラの4msの時間間隔で補正してもあまり
//意味がない
//理由2　姿勢制御をする場合、左右の個体差が出ずらい
//理由3　走行体を姿勢制御を切った状態で走行させるタイミングがない

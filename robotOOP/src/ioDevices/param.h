#include "Arduino.h"
#include  <ArduinoJson.h>
#include "signalConst.h"

#ifndef param_h
#define param_h

    const int PARAMETER_VALUE = 0;
    const int PARAMETER_LOW_RANGE = 1;
    const int PARAMETER_HIGH_RANGE = 2;
    const int PARAMETER_LOW_LIMIT = 3;
    const int PARAMETER_HIGH_LIMIT = 4;
    const int PARAMETER_ALFA_EMA = 5;
    const int PARAMETER_INCREMENT = 6;
    const int PARAMETER_ALARM = 7;
    const int PARAMETER_OPERATION_MODE = 8;
    const float DELTA_INCREMENT = 0.5;

    //commSer header code
    const int DATA_OPERATION = 0;
    const int DATA_PARAMETER = 1;
    const int REMOTE_PARAMETER = 2;
    const int REMOTE_OPERATION = 3;

    typedef struct param{
        String unit;//unit
        float value;
        float highRange;
        float lowRange;
        float highLimit;//for alarm high
        float lowLimit;//for alarm low
        float alfaEma;//alfa for EMA Filter (0 - 100) in percentage
        float increment;
        int alarm;
        int operationMode;
    }param;

    class AccessParam{
    
    public:
        AccessParam(String);
        void init(String, param);
        JsonObject getJson();
        JsonObject getOperation();
        void setOperationJson(JsonObject);
        param getParam();
        void setParamJson(JsonObject);
        void setParam(param);
        void setParam(int, float);
        boolean isChangeAble(int);
        void setAlarm(int);
        String toString();
        String getId();
        void info();

    private:
        String    _id;
        param _dataParam;

    };//end of class
#endif
#ifndef OBJECT_ADAPTER_HPP
#define OBJECT_ADAPTER_HPP

// Уже существующий класс температурного датчика окружающей среды
class FahrenheitSensor {
public:
    // Получить показания температуры в градусах Фаренгейта
    float getFahrenheitTemp() { 
        float t = 32.0;
    // ... какой то код 
        return t;
    } 
};
class Sensor {
public:
    virtual ~Sensor() {}
    virtual float getTemperature() = 0;
};

class Adapter : public Sensor {
public:
    Adapter( FahrenheitSensor* p ) : p_fsensor(p) { }
    ~Adapter() {
    delete p_fsensor;
    }
    float getTemperature() {
    return (p_fsensor->getFahrenheitTemp()-32.0)*5.0/9.0; 
    }
private:
    FahrenheitSensor* p_fsensor;
};

#endif // OBJECT_ADAPTER_HPP

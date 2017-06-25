#include <iostream>
using namespace std;
class Car
{
private:
	int gasolineGauge;
public:
	Car()
	{}
	Car(int inputgasoline): gasolineGauge(inputgasoline)
	{
	}
	int GetGasGauge()
	{
		return gasolineGauge;
	}
};


class HybridCar : public Car
{
private:
	int electricgauge;
public:
	HybridCar()
	{}
	HybridCar(int inputelectricgauge) : electricgauge(inputelectricgauge)
	{}
	HybridCar(int inputgasoline ,int inputelectricgauge) : Car(inputgasoline), electricgauge(inputelectricgauge)
	{}

	int GetElecGauge()
	{
		return electricgauge;
	}
};


class HybridWaterCar : public HybridCar
{
private:
	int waterGauge;
public:
	HybridWaterCar()
	{}
	HybridWaterCar(int inputwater) : waterGauge(inputwater)
	{}
	HybridWaterCar(int inputgasoline, int inputelectricgauge, int inputwater) : HybridCar(inputgasoline,inputelectricgauge), waterGauge(inputwater)
	{

	}
	void ShowCurrentGauge()
	{
		cout << "ÀÜ¿© °¡¼Ö¸°: " << GetGasGauge() << endl;
		cout << "ÀÜ¿© Àü±â·®: " << GetElecGauge() << endl;
		cout << "ÀÜ¿© ¿öÅÍ·®: " << waterGauge<< endl;
	}
};

int main()
{
	HybridWaterCar ionic(1000,50,100);
	ionic.ShowCurrentGauge();
	return 0;
}
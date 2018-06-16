#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Manager.h"

namespace I2c
{
Bme280Manager::Bme280Manager(I2cClient *i2c)
	: m_bme280{i2c},
	  m_compensator{nullptr}
{}

// TODO(bozkurtus): close bme280
Bme280Manager::~Bme280Manager() {}

void Bme280Manager::p_Init()
{
		// TODO(bozkurtus): how do we know when it comes up?
		m_bme280.PowerOnReset();
}
} // namespace I2c

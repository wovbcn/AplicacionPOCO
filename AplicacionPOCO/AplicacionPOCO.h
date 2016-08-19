#pragma once
class AplicacionPOCO: public Poco::Util::Application
{
public:
	AplicacionPOCO();
	virtual ~AplicacionPOCO();

protected:
	void initialize(Application& self);
	void uninitialize();
	void reinitialize(Application& self);
	virtual void defineOptions(Poco::Util::OptionSet& options);
	virtual void handleOption(const std::string& name, const std::string& value);
	virtual int main(const std::vector<std::string>& args);
	void gestinaPeticionDeAyuda(const std::string& name, const std::string& value);

protected:
	bool hanPedidoAyuda;
	int  puertoDeEscucha;
};


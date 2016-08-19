#include "Poco/Util/Application.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/IntValidator.h"
#include <iostream>
#include <sstream>
#include "AplicacionPOCO.h"


POCO_APP_MAIN(AplicacionPOCO)

AplicacionPOCO::AplicacionPOCO():hanPedidoAyuda(false), puertoDeEscucha(8085)
{
}

AplicacionPOCO::~AplicacionPOCO()
{
}

void AplicacionPOCO::initialize(Application & self)
{
	logger().information("Cargando configuración");
	loadConfiguration();
	logger().information("Inicializando aplicación");
	Poco::Util::Application::initialize(self);
}

void AplicacionPOCO::uninitialize()
{
	logger().information("Cerrando aplicación");
	Poco::Util::Application::uninitialize();
}

void AplicacionPOCO::reinitialize(Application & self)
{
	logger().information("Reiniciando aplicación");
	Poco::Util::Application::reinitialize(self);
}

void AplicacionPOCO::defineOptions(Poco::Util::OptionSet & options)
{
	logger().information("Procesando argumentos");
	Poco::Util::Application::defineOptions(options);
	
	options.addOption(
		Poco::Util::Option("puerto", "p", "Permite definir el puerto de escuicha del servidor")
		.required(true)
		.repeatable(false)
		.argument("value")
		.binding("puerto") );

	options.addOption(
		Poco::Util::Option("ayuda", "a", "Muestra la descripción para la llamada desde la línea de comandos")
		.required(false)
		.repeatable(false)
		.callback(Poco::Util::OptionCallback<AplicacionPOCO>(this, &AplicacionPOCO::gestinaPeticionDeAyuda)));

}

void AplicacionPOCO::handleOption(const std::string & name, const std::string & value)
{
	Poco::Util::Application::handleOption(name, value);
}

int AplicacionPOCO::main(const std::vector<std::string>& args)
{
	if (hanPedidoAyuda) {
		logger().information("No hacemos nada mas que mostrar la ayuda");
	}
	else {
		std::ostringstream ostr;
		bool               tenemosPuerto =  config().has("puerto");
		
		if(tenemosPuerto)
			this->puertoDeEscucha = config().getInt("puerto");
		
		ostr << "Creamos el servidor escuchando en el puerto " << puertoDeEscucha;

		logger().information( ostr.str() );
	}
	return ExitCode::EXIT_OK;
}

void AplicacionPOCO::gestinaPeticionDeAyuda(const std::string& name, const std::string& value)
{
	Poco::Util::HelpFormatter helpFormatter(options());
	
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("[/puerto=value] [/ayuda] \n");
	
	std::cout << std::endl;

	helpFormatter.setHeader("La AplicacionPOCO dispone de las siguientes opciones");

	helpFormatter.format(std::cout);

	std::cout << std::endl;

	hanPedidoAyuda = true;

	stopOptionsProcessing();
}

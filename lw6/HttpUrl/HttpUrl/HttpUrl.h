#pragma once
#include <iostream>
#include <cassert>
#include <string>
#include "UrlParsingError.h"

const unsigned short DEFAULT_HTTP_PORT = 80;
const unsigned short DEFAULT_HTTPS_PORT = 443;

enum class Protocol
{
	HTTP,
	HTTPS
};

class CHttpUrl
{
public:
	// выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
	// выбрасыват исключение CUrlParsingError, содержащее текстовое описание ошибки
	CHttpUrl(std::string const& url);

	/* инициализирует URL на основе переданных параметров.
		ѕри недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP
	);

	/* инициализирует URL на основе переданных параметров.
		ѕри недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port
	);

	// возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
	// выбранного протокола (80 дл€ http и 443 дл€ https) в эту строку
	// не должен включатьс€
	std::string GetURL() const;

	// возвращает доменное им€
	std::string GetDomain() const;

	/*
		¬озвращает им€ документа. ѕримеры:
			/
			/index.html
			/images/photo.jpg
	*/
	std::string GetDocument() const;

	// возвращает тип протокола
	Protocol GetProtocol() const;

	// возвращает номер порта
	unsigned short GetPort() const;
private:
	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	unsigned short m_port;

	Protocol ParseProtocol(std::string const& strProtocol);
	unsigned short ParsePort(std::string const& strPort);
	std::string ParseDomain(std::string const& domain);
	std::string ParseDocument(std::string const& document);
	std::string ProtocolToString(Protocol const& protocol) const;
	unsigned short ProtocolToDefaultPort(Protocol const& protocol) const;
};

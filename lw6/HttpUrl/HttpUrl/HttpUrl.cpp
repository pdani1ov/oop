#include <regex>
#include "HttpUrl.h"

using namespace std::string_literals;

const std::string URL_REGEX_EXPRESSION = R"(^(https|http)://([\w-]{1,63}(?:\.[\w-]{1,63})*)(?:(?::)(\d{1,5}))?(?:(?:/)([^\s]*))*$)";
const std::string DOMAIN_REGULAR_EXPRESSION = R"(^([\w-]{1,63}(?:\.[\w-]{1,63})*)$)";
const std::string DOCUMENT_REGULAR_EXPRESSION = R"(^(((?:/)*([^\s]*))*)$)";
const std::regex HTTP_URL_REG(URL_REGEX_EXPRESSION, std::regex_constants::icase);
const std::regex DOMAIN_REG(DOMAIN_REGULAR_EXPRESSION, std::regex_constants::icase);
const std::regex DOCUMENT_REG(DOCUMENT_REGULAR_EXPRESSION, std::regex_constants::icase);

CHttpUrl::CHttpUrl(std::string const& url)
{	
	std::smatch matches;

	std::regex_search(url, matches, HTTP_URL_REG);

	if (matches.size() != 5)
	{
		throw CUrlParsingError("invalid url");
	}

	m_protocol = ParseProtocol(matches[1]);
	m_port = ParsePort(matches[3]);
	m_domain = matches[2];
	m_document = "/" + matches[4].str();
};

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
	m_protocol = protocol;
	try
	{
		m_domain = ParseDomain(domain);
		m_document  = ParseDocument(document);
		m_port = ProtocolToDefaultPort(protocol);
	}
	catch (CUrlParsingError const& error)
	{
		throw error;
	}
};

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
{
	m_protocol = protocol;
	m_port = port;
	try
	{
		m_domain = ParseDomain(domain);
		m_document = ParseDocument(document);
	}
	catch (CUrlParsingError const& error)
	{
		throw error;
	}
};

std::string CHttpUrl::GetURL() const
{
	std::string url = ProtocolToString(m_protocol) + "://" + m_domain;

	if ((m_protocol == Protocol::HTTP && m_port != DEFAULT_HTTP_PORT) || (m_protocol == Protocol::HTTPS && m_port != DEFAULT_HTTPS_PORT))
	{
		url += ":" + std::to_string(m_port);
	}

	url += m_document;

	return url;
};

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
};

std::string CHttpUrl::GetDocument() const
{
	return m_document;
};

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
};

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
};

std::string CHttpUrl::ProtocolToString(Protocol const& protocol) const
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return "http";
		break;
	case Protocol::HTTPS:
		return "https";
		break;
	default:
		assert(false);
		return "";
		break;
	}
};

unsigned short CHttpUrl::ProtocolToDefaultPort(Protocol const& protocol) const
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return DEFAULT_HTTP_PORT;
		break;
	case Protocol::HTTPS:
		return DEFAULT_HTTPS_PORT;
		break;
	default:
		assert(false);
		return 0;
		break;
	}
};

Protocol CHttpUrl::ParseProtocol(std::string const& strProtocol)
{
	if (strProtocol == "http")
	{
		return Protocol::HTTP;
	}
	else if (strProtocol == "https")
	{
		return Protocol::HTTPS;
	}
	else
	{
		throw CUrlParsingError("invalid protocol");
	}
};

unsigned short CHttpUrl::ParsePort(std::string const& strPort)
{
	if (strPort.length() == 0)
	{
		return ProtocolToDefaultPort(m_protocol);
	}

	try
	{
		int port = std::stoi(strPort);

		if (port >= 0 && port <= 65535)
		{
			return static_cast<unsigned short>(port);
		}
		else
		{
			throw CUrlParsingError("error parsing port");
		}
	}
	catch (const std::exception&)
	{
		throw CUrlParsingError("error parsing port");
	}
};

std::string CHttpUrl::ParseDomain(std::string const& domain)
{
	std::smatch matches;

	if (!regex_search(domain, matches, DOMAIN_REG))
	{
		throw CUrlParsingError("invalid domain");
	}

	return matches[1];
};

std::string CHttpUrl::ParseDocument(std::string const& document)
{
	std::smatch matches;

	if (!regex_search(document, matches, DOCUMENT_REG))
	{
		throw CUrlParsingError("invalid document");
	}

	std::string parsedDocument = matches[1];

	if (parsedDocument[0] != '/')
	{
		parsedDocument = '/' + parsedDocument;
	}

	return parsedDocument;
};
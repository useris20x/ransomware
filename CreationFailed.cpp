#include"MyException.h"

namespace Inferno{

CreationFailed::CreationFailed(const std::string& cause)
	: MyExceptionBase_RuntimeError("")
{
	m_message = cause + "�̍쐬�Ɏ��s���܂����B";
}

CreationFailed::CreationFailed(const char* cause)
	: MyExceptionBase_RuntimeError("")
{
	m_message = std::string(cause) + "�̍쐬�Ɏ��s���܂����B";
}

CreationFailed::CreationFailed(const std::wstring& cause)
	: MyExceptionBase_RuntimeError("")
{
	m_message_w = cause + L"�̍쐬�Ɏ��s���܂����B";
}

CreationFailed::CreationFailed(const wchar_t* cause)
	: MyExceptionBase_RuntimeError("")
{
	m_message_w = std::wstring(cause) + L"�̍쐬�Ɏ��s���܂����B";
}

const char* CreationFailed::what() const
{
	return m_message.c_str();
}

const wchar_t* CreationFailed::what_w() const
{
	return m_message_w.c_str();
}

CreationFailed::~CreationFailed() {}

}
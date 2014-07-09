#pragma once
/*
�������g����O�N���X���܂Ƃ߂��w�b�_�[
�Ȃ�����ȉ���c++�W���݂̂ŏ����Ă���
*/
#include<exception>
#include<string>

namespace Inferno{
#define THROW_EXCEPTION(EXCEPTION_TYPE, message) \
  throw EXCEPTION_TYPE(message, __FILE__, __func__, __LINE__)  

class MyExceptionBase_RuntimeError: public std::runtime_error{
public:
	//�p�������R���X�g���N�^
	MyExceptionBase_RuntimeError(const std::string& what_arg)
		:runtime_error(what_arg){};
	MyExceptionBase_RuntimeError(const char* what_arg)
		:runtime_error(what_arg){};
	//�g�������R���X�g���N�^
	MyExceptionBase_RuntimeError(const std::wstring& what_arg);
	MyExceptionBase_RuntimeError(const wchar_t* what_arg);

	virtual ~MyExceptionBase_RuntimeError();
    
    virtual const char* what() const;
	//���C�h������Ԃ������g���֐�
	virtual const wchar_t* what_w() const;

protected:
	std::string m_message;
	std::wstring m_message_w;
};

class FileNotFound : public MyExceptionBase_RuntimeError{
public:
	FileNotFound(const std::string& filename);
	FileNotFound(const char* filename);
	FileNotFound(const std::wstring& filename);
	FileNotFound(const wchar_t* filename);
	~FileNotFound();

	//���{��ŃG���[���b�Z�[�W���̂��̂�Ԃ�
	virtual const char* what() const;
	virtual const wchar_t* what_w() const;
};

class CreationFailed : public MyExceptionBase_RuntimeError{
public:
	CreationFailed(const std::string& cause);
	CreationFailed(const char* cause);
	CreationFailed(const std::wstring& cause);
	CreationFailed(const wchar_t* cause);
	~CreationFailed();

	//���{��ŃG���[���b�Z�[�W���̂��̂�Ԃ�
	virtual const char* what() const;
	virtual const wchar_t* what_w() const;
};

class AccessDenied : public MyExceptionBase_RuntimeError{
public:
	AccessDenied(const std::string& cause);
	AccessDenied(const char* cause);
	AccessDenied(const std::wstring& cause);
	AccessDenied(const wchar_t* cause);
	~AccessDenied();

	//���{��ŃG���[���b�Z�[�W���̂��̂�Ԃ�
	virtual const char* what() const;
	virtual const wchar_t* what_w() const;
};

class GeneralFileError : public MyExceptionBase_RuntimeError{
public:
	GeneralFileError(const std::string& filename,const std::string& message);
	GeneralFileError(const char* filename, const char* message);
	GeneralFileError(const std::wstring& filename, const std::wstring& message);
	GeneralFileError(const wchar_t* filename, const wchar_t* message);
	~GeneralFileError();

	//���{��ŃG���[���b�Z�[�W���̂��̂�Ԃ�
	virtual const char* what() const;
	virtual const wchar_t* what_w() const;
};

}

/*
����̐��w�n����₱���
*/
#pragma once
#include<Windows.h>
#include<d3d9.h>

namespace Inferno
{
//�񎟌����W
template<typename T> struct Vec2 //�e���v���[�g�̓w�b�_�[�Ɏ����������̂�����
{
	T x;
	T y;
	Vec2() : x(0), y(0) {}
	Vec2(T x_, T y_) : x(x_), y(y_) {}

	const Vec2<T> operator+(const Vec2<T>& vec) const
	{
		Vec2<T> result = *this;
		result.x += vec.x;
		result.y += vec.y;
		return result;
	}

	const Vec2<T> operator+(Vec2<T>& vec) const
	{
		return this->operator+(vec);
	}

	void operator+=(const Vec2<T>& vec)
	{
		this->x += vec.x;
		this->y += vec.y;
	}

	void operator+=(Vec2<T>& vec)
	{
		this->operator+=(vec);
	}
};

//DirectX�̕W���s��i3DX�̃w���p�[�֘A�͂Ȃ�ׂ��g��Ȃ��j
typedef D3DMATRIX Matrix;
//�ȉ��s��֘A���[�e���e�B
Matrix* MatrixIdentity(Matrix* m);
Matrix* MatrixTransform2D(Matrix* m, const float x, const float y);

//Windows&DirectX��RECT�g��
//typedef RECT Rect;

class Rect
{
public:
	Rect();
	Rect(const int height, const int width);
	Rect(const Vec2<int>& p, const int height, const int width);

	//Win32��RECT��Ԃ�
	RECT GetMSRECT() const;

	int Top() const;
	int Right() const;
	int Left() const;
	int Bottom() const;
	Vec2<int> UpperLeft() const;
	Vec2<int> UpperRight() const;
	Vec2<int> BottomLeft() const;
	Vec2<int> BottomRight() const;

	void SetSize(const int Height, const int Width);
	void AMove(const Vec2<int>& v);
	void AMove(const int x, const int y);
	void RMove(const int x, const int y);
	void SetPosofULCorner(const int x, const int y);
	int Width() const;
	int Height() const;
	Vec2<int> Center() const;


	const Rect operator=(const Rect& r);

private:
	Vec2<int> m_center;
	int m_height;
	int m_width;
};


//�ȉ�Rect�֘A�̃��[�e���e�B
//���ƍ������Rect�����i0�𒆐S�ɍ��j
Rect SetRectFromWH(const unsigned width, const unsigned height);
Vec2<int> GetCenterOfRect(const Rect& r);
long GetWidthOfRect(const Rect& r);
long GetHeightOfRect(const Rect& r);
Rect AddRect(const Rect& r1, const Rect& r2);

/*
//��`�̃T�C�Y��\���\���́i�ʒu���͎����Ȃ��j
//��Rect������΍ςނ̂ł͂Ȃ����H
template<typename T> struct RectSize
{
	T width;
	T height;
};
*/
}
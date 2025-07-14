#pragma once
#include "../Prerequisites.h"

class CVector2 {
public:
  // Componentes
  float x, y;

  // ——— Constructores ———
  CVector2();
  CVector2(float x_, float y_);

  // ——— Operadores aritméticos ———
  CVector2  operator +  (const CVector2& v) const;
  CVector2  operator -  (const CVector2& v) const;
  CVector2  operator *  (float s)           const;
  CVector2  operator /  (float s)           const;
  CVector2& operator += (const CVector2& v);
  CVector2& operator -= (const CVector2& v);
  CVector2& operator *= (float s);
  CVector2& operator /= (float s);

  // ——— Comparaciones ———
  bool operator == (const CVector2& v) const;
  bool operator != (const CVector2& v) const;

  // ——— Acceso por índice ———
  float& operator[](std::size_t i);
  const float& operator[](std::size_t i) const;

  // ——— Funciones geométricas ———
  float
    length() const;

  float
    lengthSquared() const;

  float
    dot(const CVector2& v)   const;

  float
    cross(const CVector2& v) const;

  CVector2
    normalized() const;

  void
    normalize();

  // ——— Métodos estáticos ———
  static float
    distance(const CVector2& a, const CVector2& b);

  static CVector2
    lerp(const CVector2& a, const CVector2& b, float t);

  static CVector2
    zero();

  static CVector2
    one();

  // ——— Depuración ———
  friend std::ostream& operator<<(std::ostream& os, const CVector2& v);
};
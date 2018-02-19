#ifndef __CPSC489_MATRIX4_H
#define __CPSC489_MATRIX4_H

inline void matrix4x4_copy(real32* X, const real32* A)
{
 X[0x0] = A[0x0]; X[0x1] = A[0x1]; X[0x2] = A[0x2]; X[0x3] = A[0x3];
 X[0x4] = A[0x4]; X[0x5] = A[0x5]; X[0x6] = A[0x6]; X[0x7] = A[0x7];
 X[0x8] = A[0x8]; X[0x9] = A[0x9]; X[0xA] = A[0xA]; X[0xB] = A[0xB];
 X[0xC] = A[0xC]; X[0xD] = A[0xD]; X[0xE] = A[0xE]; X[0xF] = A[0xF];
}

inline void matrix4x4_identity(real32* X)
{
 real32 one = 1.0f;
 real32 zer = 0.0f;
 X[0x0] = one; X[0x1] = zer; X[0x2] = zer; X[0x3] = zer;
 X[0x4] = zer; X[0x5] = one; X[0x6] = zer; X[0x7] = zer;
 X[0x8] = zer; X[0x9] = zer; X[0xA] = one; X[0xB] = zer;
 X[0xC] = zer; X[0xD] = zer; X[0xE] = zer; X[0xF] = one;
}

inline void matrix4x4_transpose(real32* X, const real32* A)
{
 X[0x0] = A[0x0]; X[0x1] = A[0x4]; X[0x2] = A[0x8]; X[0x3] = A[0xC];
 X[0x4] = A[0x1]; X[0x5] = A[0x5]; X[0x6] = A[0x9]; X[0x7] = A[0xD];
 X[0x8] = A[0x2]; X[0x9] = A[0x6]; X[0xA] = A[0xA]; X[0xB] = A[0xE];
 X[0xC] = A[0x3]; X[0xD] = A[0x7]; X[0xE] = A[0xB]; X[0xF] = A[0xF];
}

inline void matrix4x4_transpose(real32* A)
{
 real32 temp;
 temp = A[0x1]; A[0x1] = A[0x4]; A[0x4] = temp;
 temp = A[0x2]; A[0x2] = A[0x8]; A[0x8] = temp;
 temp = A[0x3]; A[0x3] = A[0xC]; A[0xC] = temp;
 temp = A[0x6]; A[0x6] = A[0x9]; A[0x9] = temp;
 temp = A[0x7]; A[0x7] = A[0xD]; A[0xD] = temp;
 temp = A[0xB]; A[0xB] = A[0xE]; A[0xE] = temp;
}

inline void matrix4x4_add(real32* X, const real32* A, const real32* B)
{
 X[0x0] = (A[0x0] + B[0x0]); X[0x1] = (A[0x1] + B[0x1]); X[0x2] = (A[0x2] + B[0x2]); X[0x3] = (A[0x3] + B[0x3]);
 X[0x4] = (A[0x4] + B[0x4]); X[0x5] = (A[0x5] + B[0x5]); X[0x6] = (A[0x6] + B[0x6]); X[0x7] = (A[0x7] + B[0x7]);
 X[0x8] = (A[0x8] + B[0x8]); X[0x9] = (A[0x9] + B[0x9]); X[0xA] = (A[0xA] + B[0xA]); X[0xB] = (A[0xB] + B[0xB]);
 X[0xC] = (A[0xC] + B[0xC]); X[0xD] = (A[0xD] + B[0xD]); X[0xE] = (A[0xE] + B[0xE]); X[0xF] = (A[0xF] + B[0xF]);
}

inline void matrix4x4_add(real32* A, const real32* B)
{
 A[0x0] += B[0x0]; A[0x1] += B[0x1]; A[0x2] += B[0x2]; A[0x3] += B[0x3];
 A[0x4] += B[0x4]; A[0x5] += B[0x5]; A[0x6] += B[0x6]; A[0x7] += B[0x7];
 A[0x8] += B[0x8]; A[0x9] += B[0x9]; A[0xA] += B[0xA]; A[0xB] += B[0xB];
 A[0xC] += B[0xC]; A[0xD] += B[0xD]; A[0xE] += B[0xE]; A[0xF] += B[0xF];
}

inline void matrix4x4_sub(real32* X, const real32* A, const real32* B)
{
 X[0x0] = (A[0x0] - B[0x0]); X[0x1] = (A[0x1] - B[0x1]); X[0x2] = (A[0x2] - B[0x2]); X[0x3] = (A[0x3] - B[0x3]);
 X[0x4] = (A[0x4] - B[0x4]); X[0x5] = (A[0x5] - B[0x5]); X[0x6] = (A[0x6] - B[0x6]); X[0x7] = (A[0x7] - B[0x7]);
 X[0x8] = (A[0x8] - B[0x8]); X[0x9] = (A[0x9] - B[0x9]); X[0xA] = (A[0xA] - B[0xA]); X[0xB] = (A[0xB] - B[0xB]);
 X[0xC] = (A[0xC] - B[0xC]); X[0xD] = (A[0xD] - B[0xD]); X[0xE] = (A[0xE] - B[0xE]); X[0xF] = (A[0xF] - B[0xF]);
}

inline void matrix4x4_sub(real32* A, const real32* B)
{
 A[0x0] -= B[0x0]; A[0x1] -= B[0x1]; A[0x2] -= B[0x2]; A[0x3] -= B[0x3];
 A[0x4] -= B[0x4]; A[0x5] -= B[0x5]; A[0x6] -= B[0x6]; A[0x7] -= B[0x7];
 A[0x8] -= B[0x8]; A[0x9] -= B[0x9]; A[0xA] -= B[0xA]; A[0xB] -= B[0xB];
 A[0xC] -= B[0xC]; A[0xD] -= B[0xD]; A[0xE] -= B[0xE]; A[0xF] -= B[0xF];
}

inline void matrix4x4_mul(real32* X, const real32* A, const real32* B)
{
 X[0x0] = A[0x0]*B[0x0] + A[0x1]*B[0x4] + A[0x2]*B[0x8] + A[0x3]*B[0xC];
 X[0x1] = A[0x0]*B[0x1] + A[0x1]*B[0x5] + A[0x2]*B[0x9] + A[0x3]*B[0xD];
 X[0x2] = A[0x0]*B[0x2] + A[0x1]*B[0x6] + A[0x2]*B[0xA] + A[0x3]*B[0xE];
 X[0x3] = A[0x0]*B[0x3] + A[0x1]*B[0x7] + A[0x2]*B[0xB] + A[0x3]*B[0xF];
 X[0x4] = A[0x4]*B[0x0] + A[0x5]*B[0x4] + A[0x6]*B[0x8] + A[0x7]*B[0xC];
 X[0x5] = A[0x4]*B[0x1] + A[0x5]*B[0x5] + A[0x6]*B[0x9] + A[0x7]*B[0xD];
 X[0x6] = A[0x4]*B[0x2] + A[0x5]*B[0x6] + A[0x6]*B[0xA] + A[0x7]*B[0xE];
 X[0x7] = A[0x4]*B[0x3] + A[0x5]*B[0x7] + A[0x6]*B[0xB] + A[0x7]*B[0xF];
 X[0x8] = A[0x8]*B[0x0] + A[0x9]*B[0x4] + A[0xA]*B[0x8] + A[0xB]*B[0xC];
 X[0x9] = A[0x8]*B[0x1] + A[0x9]*B[0x5] + A[0xA]*B[0x9] + A[0xB]*B[0xD];
 X[0xA] = A[0x8]*B[0x2] + A[0x9]*B[0x6] + A[0xA]*B[0xA] + A[0xB]*B[0xE];
 X[0xB] = A[0x8]*B[0x3] + A[0x9]*B[0x7] + A[0xA]*B[0xB] + A[0xB]*B[0xF];
 X[0xC] = A[0xC]*B[0x0] + A[0xD]*B[0x4] + A[0xE]*B[0x8] + A[0xF]*B[0xC];
 X[0xD] = A[0xC]*B[0x1] + A[0xD]*B[0x5] + A[0xE]*B[0x9] + A[0xF]*B[0xD];
 X[0xE] = A[0xC]*B[0x2] + A[0xD]*B[0x6] + A[0xE]*B[0xA] + A[0xF]*B[0xE];
 X[0xF] = A[0xC]*B[0x3] + A[0xD]*B[0x7] + A[0xE]*B[0xB] + A[0xF]*B[0xF];
}

inline void matrix4x4_mul(real32* A, const real32* B)
{
 real32 X[16] = {
  A[0x0]*B[0x0] + A[0x1]*B[0x4] + A[0x2]*B[0x8] + A[0x3]*B[0xC],
  A[0x0]*B[0x1] + A[0x1]*B[0x5] + A[0x2]*B[0x9] + A[0x3]*B[0xD],
  A[0x0]*B[0x2] + A[0x1]*B[0x6] + A[0x2]*B[0xA] + A[0x3]*B[0xE],
  A[0x0]*B[0x3] + A[0x1]*B[0x7] + A[0x2]*B[0xB] + A[0x3]*B[0xF],
  A[0x4]*B[0x0] + A[0x5]*B[0x4] + A[0x6]*B[0x8] + A[0x7]*B[0xC],
  A[0x4]*B[0x1] + A[0x5]*B[0x5] + A[0x6]*B[0x9] + A[0x7]*B[0xD],
  A[0x4]*B[0x2] + A[0x5]*B[0x6] + A[0x6]*B[0xA] + A[0x7]*B[0xE],
  A[0x4]*B[0x3] + A[0x5]*B[0x7] + A[0x6]*B[0xB] + A[0x7]*B[0xF],
  A[0x8]*B[0x0] + A[0x9]*B[0x4] + A[0xA]*B[0x8] + A[0xB]*B[0xC],
  A[0x8]*B[0x1] + A[0x9]*B[0x5] + A[0xA]*B[0x9] + A[0xB]*B[0xD],
  A[0x8]*B[0x2] + A[0x9]*B[0x6] + A[0xA]*B[0xA] + A[0xB]*B[0xE],
  A[0x8]*B[0x3] + A[0x9]*B[0x7] + A[0xA]*B[0xB] + A[0xB]*B[0xF],
  A[0xC]*B[0x0] + A[0xD]*B[0x4] + A[0xE]*B[0x8] + A[0xF]*B[0xC],
  A[0xC]*B[0x1] + A[0xD]*B[0x5] + A[0xE]*B[0x9] + A[0xF]*B[0xD],
  A[0xC]*B[0x2] + A[0xD]*B[0x6] + A[0xE]*B[0xA] + A[0xF]*B[0xE],
  A[0xC]*B[0x3] + A[0xD]*B[0x7] + A[0xE]*B[0xB] + A[0xF]*B[0xF]
 };
 A[0x0] = X[0x0];
 A[0x1] = X[0x1];
 A[0x2] = X[0x2];
 A[0x3] = X[0x3];
 A[0x4] = X[0x4];
 A[0x5] = X[0x5];
 A[0x6] = X[0x6];
 A[0x7] = X[0x7];
 A[0x8] = X[0x8];
 A[0x9] = X[0x9];
 A[0xA] = X[0xA];
 A[0xB] = X[0xB];
 A[0xC] = X[0xC];
 A[0xD] = X[0xD];
 A[0xE] = X[0xE];
 A[0xF] = X[0xF];
}

inline void matrix4x4_vector3_mul(real32* X, const real32* A, const real32* B)
{
 X[0x0] = A[0x0]*B[0x0] + A[0x1]*B[0x1] + A[0x2]*B[0x2];
 X[0x1] = A[0x4]*B[0x0] + A[0x5]*B[0x1] + A[0x6]*B[0x2];
 X[0x2] = A[0x8]*B[0x0] + A[0x9]*B[0x1] + A[0xA]*B[0x2];
}

inline void matrix4x4_vector4_mul(real32* X, const real32* A, const real32* B)
{
 X[0x0] = A[0x0]*B[0x0] + A[0x1]*B[0x1] + A[0x2]*B[0x2] + A[0x3]*B[0x3];
 X[0x1] = A[0x4]*B[0x0] + A[0x5]*B[0x1] + A[0x6]*B[0x2] + A[0x7]*B[0x3];
 X[0x2] = A[0x8]*B[0x0] + A[0x9]*B[0x1] + A[0xA]*B[0x2] + A[0xB]*B[0x3];
 X[0x3] = A[0xC]*B[0x0] + A[0xD]*B[0x1] + A[0xE]*B[0x2] + A[0xF]*B[0x3];
}

inline real32 inverse(real32* X, const real32* A)
{
 // cache 2x2 determinants
 real32 D[12] = {
  A[0xA]*A[0xF] - A[0xB]*A[0xE],
  A[0x9]*A[0xF] - A[0xB]*A[0xD],
  A[0x9]*A[0xE] - A[0xA]*A[0xD],
  A[0x8]*A[0xF] - A[0xB]*A[0xC],
  A[0x8]*A[0xE] - A[0xA]*A[0xC],
  A[0x8]*A[0xD] - A[0x9]*A[0xC],
  A[0x2]*A[0x7] - A[0x3]*A[0x6],
  A[0x1]*A[0x7] - A[0x3]*A[0x5],
  A[0x1]*A[0x6] - A[0x2]*A[0x5],
  A[0x0]*A[0x7] - A[0x3]*A[0x4],
  A[0x0]*A[0x6] - A[0x2]*A[0x4],
  A[0x0]*A[0x5] - A[0x1]*A[0x4]
 };

 // compute determinant
 real32 det = D[0x5]*D[0x6] - D[0x4]*D[0x7] + D[0x3]*D[0x8] + D[0x2]*D[0x9] - D[0x1]*D[0xA] + D[0x0]*D[0xB];
 if(det < 1.0e-7f) return det;

 // inv(M) = inv(det(M)) * transpose(C)
 real32 invdet = inv(det);
 X[0x0] = +(A[0x5]*D[0x0] - A[0x6]*D[0x1] + A[0x7]*D[0x2])*invdet;
 X[0x4] = -(A[0x4]*D[0x0] - A[0x6]*D[0x3] + A[0x7]*D[0x4])*invdet;
 X[0x8] = +(A[0x4]*D[0x1] - A[0x5]*D[0x3] + A[0x7]*D[0x5])*invdet;
 X[0xC] = -(A[0x4]*D[0x2] - A[0x5]*D[0x4] + A[0x6]*D[0x5])*invdet;
 X[0x1] = -(A[0x1]*D[0x0] - A[0x2]*D[0x1] + A[0x3]*D[0x2])*invdet;
 X[0x5] = +(A[0x0]*D[0x0] - A[0x2]*D[0x3] + A[0x3]*D[0x4])*invdet;
 X[0x9] = -(A[0x0]*D[0x1] - A[0x1]*D[0x3] + A[0x3]*D[0x5])*invdet;
 X[0xD] = +(A[0x0]*D[0x2] - A[0x1]*D[0x4] + A[0x2]*D[0x5])*invdet;
 X[0x2] = +(A[0xD]*D[0x6] - A[0xE]*D[0x7] + A[0xF]*D[0x8])*invdet;
 X[0x6] = -(A[0xC]*D[0x6] - A[0xE]*D[0x9] + A[0xF]*D[0xA])*invdet;
 X[0xA] = +(A[0xC]*D[0x7] - A[0xD]*D[0x9] + A[0xF]*D[0xB])*invdet;
 X[0xE] = -(A[0xC]*D[0x8] - A[0xD]*D[0xA] + A[0xE]*D[0xB])*invdet;
 X[0x3] = -(A[0x9]*D[0x6] - A[0xA]*D[0x7] + A[0xB]*D[0x8])*invdet;
 X[0x7] = +(A[0x8]*D[0x6] - A[0xA]*D[0x9] + A[0xB]*D[0xA])*invdet;
 X[0xB] = -(A[0x8]*D[0x7] - A[0x9]*D[0x9] + A[0xB]*D[0xB])*invdet;
 X[0xF] = +(A[0x8]*D[0x8] - A[0x9]*D[0xA] + A[0xA]*D[0xB])*invdet;

 // return determinant
 return det;
}

inline void matrix4x4_rotate(real32* X, const real32* axis, real32 angle)
{
 // from Real-Time Rendering (Goldman equation)
 real32 cv = std::cos(angle);
 real32 sv = std::sin(angle);
 real32 dc = 1.0f - cv;
 real32 p012[2] = { dc*(axis[0]*axis[1]), sv*axis[2] };
 real32 p021[2] = { dc*(axis[0]*axis[2]), sv*axis[1] };
 real32 p120[2] = { dc*(axis[1]*axis[2]), sv*axis[0] };

 // row 0
 X[0x0] = cv + dc*(axis[0]*axis[0]);
 X[0x1] = p012[0] - p012[1];
 X[0x2] = p021[0] + p021[1];
 X[0x3] = 0.0f;

 // row 1
 X[0x4] = p012[0] + p012[1];
 X[0x5] = cv + dc*(axis[1]*axis[1]);
 X[0x6] = p120[0] - p120[1];
 X[0x7] = 0.0f;

 // row 2
 X[0x8] = p021[0] - p021[1];
 X[0x9] = p120[0] + p120[1];
 X[0xA] = cv + dc*(axis[2]*axis[2]);
 X[0xB] = 0.0f;

 // row 3
 X[0xC] = 0.0f;
 X[0xD] = 0.0f;
 X[0xE] = 0.0f;
 X[0xF] = 1.0f;
}

#endif
